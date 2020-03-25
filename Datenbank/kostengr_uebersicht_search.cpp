#include "StdAfx.h"
#include "kostengr_uebersicht_search.h"

#include "My_Connection.h"
#include "MyResult.h"
#include "MyRecordSet.h"

#include "kostengr_uebersicht_result.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

// Loader
void kostengr_uebersicht_search::kostengr_uebersicht_search_Load(System::Object^  sender, System::EventArgs^  e)
{
	My_Connection data;
	data.connect();

	// Load Staedte
	MyResult^ R_Stadt=data.get_result("SELECT * FROM Staedte");
	for(int i=0;i<R_Stadt->get_row();++i)
	{
		bool insert=false;
		MyResult^ R_Gebiet=data.get_result("SELECT * FROM Gebiete WHERE Stadt_ID="+R_Stadt->get_val(i,0));
		for(int j=0;j<R_Gebiet->get_row();++j)
		{
			MyResult^ R_Programm=data.get_result("SELECT * FROM Programme WHERE Gebiet_ID="+R_Gebiet->get_val(j,0));
			if(R_Programm->get_row()!=0)
				insert=true;
		}
		if(insert)
			staedte->Items->Add(R_Stadt->get_val(i,1));
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

	// Load Jahr
	MyResult^ R_Jahr=data.get_result("SELECT * FROM Jahreseintraege order by ID");
	for(int i=0;i<R_Jahr->get_row();++i)
		jahre->Items->Add(R_Jahr->get_val(i,1));
	if(jahre->Items->Count==0)
	{
		Windows::Forms::MessageBox::Show("Es konnten keine Jahreseintraege gefunden werden.\nBitte kontaktieren Sie den Administrator","Fehler in der Datenbank");
		Close();
	}
	else
		jahre->SelectedIndex=0;

	// Load Kostengruppen
	MyResult^ R_Kostengruppen=data.get_result("SELECT * FROM Kostengruppe");
	for(int i=0;i<R_Kostengruppen->get_row();++i)
		kostengruppen->Items->Add(R_Kostengruppen->get_val(i,1));
	if(kostengruppen->Items->Count==0)
	{
		Windows::Forms::MessageBox::Show("Es konnten keine Kostengruppen gefunden werden.\nBitte kontaktieren Sie den Administrator","Fehler in der Datenbank");
		Close();
	}
	else
		kostengruppen->SelectedIndex=0;

	data.disconnect();
}

void kostengr_uebersicht_search::load_gebiet()
{
	gebiete->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
	for(int i=0;i<RC_Gebiet.get_row();++i)
	{
		MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(i,0));
		if(RC_Programm.get_row()!=0)
			gebiete->Items->Add(RC_Gebiet.get_val(i,2));
	}
	gebiete->SelectedIndex=0;
	load_programm();
}

void kostengr_uebersicht_search::load_programm()
{
	programme->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+gebiete->Text+"'");
	MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
	for(int i=0;i<RC_Programm.get_row();++i)
		programme->Items->Add(RC_Programm.get_val(i,3)+" - "+RC_Programm.get_val(i,2));
	programme->SelectedIndex=0;
}

// TextChange
void kostengr_uebersicht_search::staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(staedte->FindStringExact(staedte->Text)==-1)
		staedte->SelectedIndex=0;
	load_gebiet();
}

void kostengr_uebersicht_search::gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(gebiete->FindStringExact(gebiete->Text)==-1)
		gebiete->SelectedIndex=0;
	load_programm();
}

void kostengr_uebersicht_search::programme_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->FindStringExact(programme->Text)==-1)
		programme->SelectedIndex=0;
}

void kostengr_uebersicht_search::jahre_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(jahre->FindStringExact(jahre->Text)==-1)
		jahre->SelectedIndex=0;
}

void kostengr_uebersicht_search::kostengruppen_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(kostengruppen->FindStringExact(kostengruppen->Text)==-1)
		kostengruppen->SelectedIndex=0;
}


// CheckedChange
void kostengr_uebersicht_search::search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_stadt->Checked)
	{
		search_gebiet->Checked=false;
		search_programm->Checked=false;
	}
}

void kostengr_uebersicht_search::search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_gebiet->Checked)
		search_programm->Checked=false;
	else
		search_stadt->Checked=true;
}

void kostengr_uebersicht_search::search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(search_programm->Checked)
	{
		search_gebiet->Checked=true;
		search_stadt->Checked=true;
	}
}


// Buttons
void kostengr_uebersicht_search::btn_create_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ kostengruppe="-1";
	String^ stadt="-1";
	String^ gebiet="-1";
	String^ programm="-1";
	String^ jahr="-1";
	
	if(search_kostengruppen->Checked)
		kostengruppe=kostengruppen->Text;	
	if(search_stadt->Checked)
		stadt=staedte->Text;
	if(search_gebiet->Checked)
		gebiet=gebiete->Text;
	if(search_programm->Checked)
	{
		programm=programme->Text;
		programm=programm->Remove(0,6)->Trim();
	}
	if(search_jahr->Checked)
		jahr=jahre->Text;
	
	Form^ result =gcnew kostengr_uebersicht_result(kostengruppe,stadt,gebiet,programm,jahr,user_id_);
	Hide();
	result->ShowDialog();
	Show();
	//Close();
}

void kostengr_uebersicht_search::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}
