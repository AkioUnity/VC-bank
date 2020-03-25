#include "StdAfx.h"
#include "gesamt_uebersicht_search.h"

#include "MyRecordSet.h"
#include "gesamt_uebersicht_result.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;


// Loader
void gesamt_uebersicht_search::gesamt_uebersicht_search_Load(System::Object^  sender, System::EventArgs^  e)
{
	Hide();
	loadingForm->Show();
	loadingForm->Controls->Find("texter", true)[0]->Text = "Lade";

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
		loadingForm->SetProgress();
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

void gesamt_uebersicht_search::load_gebiet()
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

void gesamt_uebersicht_search::load_programm()
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
void gesamt_uebersicht_search::staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(staedte->FindStringExact(staedte->Text)==-1)
		staedte->SelectedIndex=0;
	load_gebiet();
}

void gesamt_uebersicht_search::gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(gebiete->FindStringExact(gebiete->Text)==-1)
		gebiete->SelectedIndex=0;
	load_programm();
}

void gesamt_uebersicht_search::programme_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->FindStringExact(programme->Text)==-1)
		programme->SelectedIndex=0;
}

// Checked Change
void gesamt_uebersicht_search::search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_stadt->Checked)
	{
		search_gebiet->Checked=false;
		search_programm->Checked=false;
	}
}

void gesamt_uebersicht_search::search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_gebiet->Checked)
		search_programm->Checked=false;
	else
		search_stadt->Checked=true;
}

void gesamt_uebersicht_search::search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(search_programm->Checked)
	{
		search_gebiet->Checked=true;
		search_stadt->Checked=true;
	}
}

// Button
void gesamt_uebersicht_search::btn_create_result_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ stadt="-1";
	String^ gebiet="-1";
	String^ programm="-1";
	
	if(search_stadt->Checked)
		stadt=staedte->Text;
	if(search_gebiet->Checked)
		gebiet=gebiete->Text;
	if(search_programm->Checked)
	{
		programm=programme->Text;
		programm=programm->Remove(0,6)->Trim();
	}

	if(	show_gk_priv->Checked || 
		show_gk_kom->Checked || 
		show_gk_real->Checked || 
		show_mehr_minder->Checked || 
		show_restmittel->Checked || 
		show_mla->Checked || 
		show_bund_land->Checked || 
		show_jz->Checked)
	{
		Form^ result =gcnew gesamt_uebersicht_result(stadt,gebiet,programm,	show_jz->Checked,
																			show_bund_land->Checked,
																			show_mla->Checked,
																			show_restmittel->Checked,
																			show_mehr_minder->Checked,
																			show_gk_real->Checked,
																			show_gk_kom->Checked,
																			show_gk_priv->Checked,
																			user_id_);
		Hide();
		result->ShowDialog();
		Show();
		//Close();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie mindestens ein Auswertungselement.","Unvollständige Eingabe");
}

void gesamt_uebersicht_search::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}
