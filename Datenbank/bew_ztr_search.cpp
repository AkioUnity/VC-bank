#include "StdAfx.h"

#include "MyRecordSet.h"
#include "bew_ztr_result.h"
#include "helper.h"

#include "bew_ztr_search.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

// Loader
void bew_ztr_search::bew_ztr_search_Load(System::Object^  sender, System::EventArgs^  e)
{
	Hide();
	loadingForm->Show();
	loadingForm->Controls->Find("texter", true)[0]->Text = "Lade";  //Load annual overview

	MyRecordSet RC_Stadt("SELECT * FROM Staedte");
	for(int i=0;i<RC_Stadt.get_row();++i)
	{
		bool insert=false;
		MyRecordSet RC_Gebiet("SELECT * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(i,0));
		for(int j=0;j<RC_Gebiet.get_row();++j)
		{
			MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(j,0));
			if(RC_Programm.get_row()!=0)
				insert=true;
			loadingForm->SetProgress();
		}
		if(insert)
			staedte->Items->Add(RC_Stadt.get_val(i,1));
	}
	if(staedte->Items->Count==0)
	{
		Windows::Forms::MessageBox::Show("Es konnten keine Städte gefunden werden.\nBitte kontaktieren Sie den Administrator","Fehler in der Datenbank");
		Close();
	}
	else
	{
		staedte->SelectedIndex=0;
		load_gebiet();
	}

	loadingForm->Hide();
	Show();
}

void bew_ztr_search::load_gebiet()
{
	gebiete->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
	for(int i=0;i<RC_Gebiet.get_row();++i)
	{
		MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(i,0));
		if(RC_Programm.get_row()!=0)
			gebiete->Items->Add(RC_Gebiet.get_val(i,2));
		loadingForm->SetProgress();
	}
	gebiete->SelectedIndex=0;
	load_programm();
}

void bew_ztr_search::load_programm()
{
	programme->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+gebiete->Text+"'");
	MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
	for(int i=0;i<RC_Programm.get_row();++i)
		programme->Items->Add(RC_Programm.get_val(i,3)+" - "+RC_Programm.get_val(i,2));
	programme->SelectedIndex=0;
}

// Buttons
void bew_ztr_search::search_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ stadt="-1";
	String^ gebiet="-1";
	String^ programm="-1";
	String^ bis_s="-1";
	
	if(search_stadt->Checked)
		stadt=staedte->Text;
	if(search_gebiet->Checked)
		gebiet=gebiete->Text;
	if(search_programm->Checked)
	{
		programm=programme->Text;
		programm=programm->Remove(0,6)->Trim();
	}

	bool load1=false;

	if(search_bis->Checked)
	{
		if( bis->BackColor==Color::FromName("White") && bis->Text!="")
		{
			bis_s=date_to_string(bis->Text);
			load1=true;
		}
		else
			load1=false;
	}
	else
		load1=true;

	if(load1)
	{
		Form^ result =gcnew bew_ztr_result(stadt,gebiet,programm,bis_s,rB_n_einger->Checked,user_id_);
		Hide();
		result->ShowDialog();
		Close();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte geben Sie gültige Daten ein.","Unvollständige Eingabe");
}

void bew_ztr_search::Close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}

// Events
	// TextChanged
void bew_ztr_search::bis_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(check_if_date(bis->Text))
		bis->BackColor=Color::FromName("White");
	else
		bis->BackColor=Color::FromName("LavenderBlush");
}

	// CheckboxChanged
void bew_ztr_search::search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_stadt->Checked)
	{
		search_gebiet->Checked=false;
		search_programm->Checked=false;
	}
}

void bew_ztr_search::search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_gebiet->Checked)
		search_programm->Checked=false;
	else
		search_stadt->Checked=true;
}

void bew_ztr_search::search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(search_programm->Checked)
	{
		search_gebiet->Checked=true;
		search_stadt->Checked=true;
	}
}

	// ComboBoxChanged
void bew_ztr_search::staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(staedte->FindStringExact(staedte->Text)==-1)
		staedte->SelectedIndex=0;
	load_gebiet();
}

void bew_ztr_search::gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(gebiete->FindStringExact(gebiete->Text)==-1)
		gebiete->SelectedIndex=0;
	load_programm();
}

void bew_ztr_search::programme_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->FindStringExact(programme->Text)==-1)
		programme->SelectedIndex=0;
}