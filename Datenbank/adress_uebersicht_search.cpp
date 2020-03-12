#include "StdAfx.h"
#include "adress_uebersicht_search.h"

#include "adress_uebersicht_result.h"
#include "My_Connection.h"
#include "MyResult.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

void adress_uebersicht_search::adress_uebersicht_search_Load(System::Object^  sender, System::EventArgs^  e)
{
	My_Connection data;
	data.connect();

	MyResult^ R_Stadt=data.get_result("SELECT * FROM Staedte");
	for(int i=0;i<R_Stadt->get_row();++i)
	{
		bool insert=false;
		MyResult^ R_Gebiet=data.get_result("SELECT * FROM Gebiete WHERE Stadt_ID="+R_Stadt->get_val(i,0));
		for(int j=0;j<R_Gebiet->get_row();++j)
		{
			MyResult^ R_Adresse=data.get_result("SELECT * FROM Strassen WHERE Gebiet_ID="+R_Gebiet->get_val(j,0));
			if(R_Adresse->get_row()!=0)
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
	data.disconnect();
}

void adress_uebersicht_search::load_gebiet()
{
	My_Connection data;
	data.connect();
	gebiete->Items->Clear();
	MyResult^ R_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyResult^ R_Gebiet=data.get_result("SELECT * FROM Gebiete WHERE Stadt_ID="+R_Stadt->get_val(0,0));
	for(int i=0;i<R_Gebiet->get_row();++i)
	{
		MyResult^ R_Adresse=data.get_result("SELECT * FROM Strassen WHERE Gebiet_ID="+R_Gebiet->get_val(i,0));
		if(R_Adresse->get_row()!=0)
			gebiete->Items->Add(R_Gebiet->get_val(i,2));
	}
	gebiete->SelectedIndex=0;
	load_adresse();
	data.disconnect();
}

void adress_uebersicht_search::load_adresse()
{
	My_Connection data;
	data.connect();
	adressen->Items->Clear();
	MyResult^ R_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+staedte->Text+"'");
	MyResult^ R_Gebiet=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+R_Stadt->get_val(0,0)+" AND Gebiet='"+gebiete->Text+"'");
	MyResult^ R_Adresse=data.get_result("SELECT * FROM Strassen WHERE Gebiet_ID="+R_Gebiet->get_val(0,0));
	for(int i=0;i<R_Adresse->get_row();++i)
		adressen->Items->Add(R_Adresse->get_val(i,2));
	adressen->SelectedIndex=0;
}

// Text Changes
void adress_uebersicht_search::staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(staedte->FindStringExact(staedte->Text)==-1)
		staedte->SelectedIndex=0;
	load_gebiet();
}

void adress_uebersicht_search::gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(gebiete->FindStringExact(gebiete->Text)==-1)
		gebiete->SelectedIndex=0;
	load_adresse();
}

void adress_uebersicht_search::adressen_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(adressen->FindStringExact(adressen->Text)==-1)
		adressen->SelectedIndex=0;
}

// Checked Change
void adress_uebersicht_search::search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_stadt->Checked)
	{
		search_gebiet->Checked=false;
		search_adresse->Checked=false;
	}
}

void adress_uebersicht_search::search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(!search_gebiet->Checked)
		search_adresse->Checked=false;
	else
		search_stadt->Checked=true;
}

void adress_uebersicht_search::search_adresse_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(search_adresse->Checked)
	{
		search_gebiet->Checked=true;
		search_stadt->Checked=true;
	}
}

// Buttons
void adress_uebersicht_search::btn_create_result_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ stadt="-1";
	String^ gebiet="-1";
	String^ adresse="-1";
	
	if(search_stadt->Checked)
		stadt=staedte->Text;
	if(search_gebiet->Checked)
		gebiet=gebiete->Text;
	if(search_adresse->Checked)
		adresse=adressen->Text;

	Form^ result =gcnew adress_uebersicht_result(stadt,gebiet,adresse,user_id_);
	Hide();
	result->ShowDialog();
	Close();
}

void adress_uebersicht_search::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}