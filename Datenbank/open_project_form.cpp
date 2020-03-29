#include "StdAfx.h"
#include "MyRecordSet.h"
#include "project_form.h"
#include "open_project_form.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

// Windows::Forms::MessageBox::Show("");

void open_project_form::open_project_form_Load(System::Object^  sender, System::EventArgs^  e)
{
	Hide();
	loadingForm->Show();
	loadingForm->Controls->Find("texter", true)[0]->Text = "Lade";  

	staedte->Items->Clear();
	MyRecordSet RC("SELECT * FROM Staedte");
	for(int i=0;i<RC.get_row();++i)
	{
		MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE stadt='"+RC.get_val(i,1)+"'");
		MyRecordSet RC_Gebiet("SELECT gebiet FROM Gebiete WHERE stadt_id="+RC_Stadt.get_val(0,0));
		if(RC_Gebiet.get_row()!=0)
			staedte->Items->Add(RC.get_val(i,1));
		loadingForm->SetProgress();
	}
	if(staedte->Items->Count>0)
	{
		staedte->SelectedIndex=0;
		load_gebiete();
		btn_search_Click(sender,e);
	}
	else 
	{
		Windows::Forms::MessageBox::Show("Keine Stadt gefunden.","Bitte kontaktieren Sie den Administrator");
		Close();
	}

	loadingForm->Hide();
	Show();
}

void open_project_form::load_gebiete()
{
	gebiete->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE stadt='"+staedte->Text+"'");
	MyRecordSet RC("SELECT * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
	for(int i=0;i<RC.get_row();++i)
	{
		gebiete->Items->Add(RC.get_val(i,2));
		loadingForm->SetProgress();
	}
	gebiete->SelectedIndex=0;
}

void open_project_form::btn_search_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ query="SELECT ID,bezeichnung,stadt,gebiet FROM db_projekte";  
	if(search_stadt->Checked && !search_gebiet->Checked)
		query+=" WHERE stadt='"+staedte->Text+"'";
	if(search_stadt->Checked && search_gebiet->Checked)
		query+=" WHERE stadt='"+staedte->Text+"' AND gebiet='"+gebiete->Text+"'";
	if(!search_stadt->Checked && search_gebiet->Checked)
		query+=" WHERE gebiet='"+gebiete->Text+"'";
	query += " order by bezeichnung";
	MyRecordSet RC(query);
	id_->Clear();
	projekte->Items->Clear();

	for(int i=0;i<RC.get_row();++i)
	{
		if(search_bezeichnung->Checked)
		{
			String^ projekt_bez=RC.get_val(i,1)->ToLower();
			String^ such_bez=bezeichnung->Text->ToLower();
			int index=projekt_bez->IndexOf(such_bez);
			if(index!=-1)
			{
				projekte->Items->Add(RC.get_val(i,1)+" in "+RC.get_val(i,2)+" ("+RC.get_val(i,3)+")");
				id_->Add(RC.get_val(i,0));
			}
		}
		else
		{
			projekte->Items->Add(RC.get_val(i,1)+" in "+RC.get_val(i,2)+" ("+RC.get_val(i,3)+")");
			id_->Add(RC.get_val(i,0));
		}
		loadingForm->SetProgress();
	}
}

void open_project_form::projekte_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	OpenProject();
}

void open_project_form::btn_open_Click(System::Object^  sender, System::EventArgs^  e)
{
	OpenProject();
}

void open_project_form::OpenProject()
{
	if (projekte->SelectedIndex != -1)
	{
		Form^ open_project = gcnew project_form(Convert::ToInt32(id_[projekte->SelectedIndex]), user_id_);
		Hide();
		open_project->ShowDialog();
		Show();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie ein Projekt.", "Kein Eintrag gewählt.");
}

void open_project_form::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}

void open_project_form::staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(staedte->FindStringExact(staedte->Text)==-1)
		staedte->SelectedIndex=0;
	load_gebiete();
}

void open_project_form::gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(gebiete->FindStringExact(gebiete->Text)==-1)
		gebiete->SelectedIndex=0;
}