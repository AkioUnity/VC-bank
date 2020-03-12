#include "StdAfx.h"
#include "MyRecordSet.h"
#include "bewilligung_result_form.h"
#include "bewilligung_auswertung_form.h"


using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;


// Loader
void bewilligung_auswertung_form::bewilligung_auswertung_form_Load(System::Object^  sender, System::EventArgs^  e)
{
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

	MyRecordSet RC_Jahr("SELECT * FROM Jahreseintraege");
	for(int i=0;i<RC_Jahr.get_row();++i)
		jahre->Items->Add(RC_Jahr.get_val(i,1));
	if(jahre->Items->Count==0)
	{
		Windows::Forms::MessageBox::Show("Es konnten keine Jahreseintraege gefunden werden.\nBitte kontaktieren Sie den Administrator","Fehler in der Datenbank");
		Close();
	}
	else
		jahre->SelectedIndex=0;
}

void bewilligung_auswertung_form::load_gebiet()
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

void bewilligung_auswertung_form::load_programm()
{
	programme->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+gebiete->Text+"'");
	MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
	for(int i=0;i<RC_Programm.get_row();++i)
		programme->Items->Add(RC_Programm.get_val(i,3)+" - "+RC_Programm.get_val(i,2));
	programme->SelectedIndex=0;
}

// Text Changes
void bewilligung_auswertung_form::staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(staedte->FindStringExact(staedte->Text)==-1)
		staedte->SelectedIndex=0;
	load_gebiet();
}

void bewilligung_auswertung_form::gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(gebiete->FindStringExact(gebiete->Text)==-1)
		gebiete->SelectedIndex=0;
	load_programm();
}

void bewilligung_auswertung_form::programme_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->FindStringExact(programme->Text)==-1)
		programme->SelectedIndex=0;
}

void bewilligung_auswertung_form::jahre_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(jahre->FindStringExact(jahre->Text)==-1)
		jahre->SelectedIndex=0;
}

// Btn
void bewilligung_auswertung_form::button1_Click(System::Object^  sender, System::EventArgs^  e) // Auswertung
{
	String^ stadt="-1";
	String^ gebiet="-1";
	String^ programm="-1";
	String^ jahr="-1";
	String^ sbe="-1";
	
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
	if(SBE->Checked)
		sbe="1";

	Form^ result =gcnew bewilligung_result_form(stadt,gebiet,programm,jahr,sbe,user_id_);
	Hide();
	result->ShowDialog();
	Close();
}

void bewilligung_auswertung_form::button2_Click(System::Object^  sender, System::EventArgs^  e) // Close
{
	Close();
}

// Checked Change
void bewilligung_auswertung_form::search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_stadt->Checked)
	{
		search_gebiet->Checked=false;
		search_programm->Checked=false;
	}
}

void bewilligung_auswertung_form::search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_gebiet->Checked)
		search_programm->Checked=false;
	else
		search_stadt->Checked=true;
}

void bewilligung_auswertung_form::search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(search_programm->Checked)
	{
		search_gebiet->Checked=true;
		search_stadt->Checked=true;
	}
}

void bewilligung_auswertung_form::search_jahr_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(search_jahr->Checked)
		SBE->Checked=false;
}

void bewilligung_auswertung_form::SBE_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(SBE->Checked)
	{
		search_jahr->Checked=false;
		search_programm->Checked=true;
		search_gebiet->Checked=true;
		search_stadt->Checked=true;
	}
}
