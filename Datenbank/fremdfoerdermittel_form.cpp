#include "StdAfx.h"
#include "MyRecordSet.h"
#include "fremdfoerdermittel_form.h"
#include "helper.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

void fremdfoerdermittel_form::fremdfoerdermittel_form_Load(System::Object^  sender, System::EventArgs^  e)
{
	programme->Items->Clear();
	MyRecordSet RC("Select * FROM Foerderprogramme");
	for(int i=0;i<RC.get_row();++i)
		programme->Items->Add(RC.get_val(i,1));
	if(programme->Items->Count!=0)
		programme->SelectedIndex=0;
	else
	{
		programme->Enabled=false;
		programme->Text="Es wurden keine Foerderprogramme gefunden.";
		betrag->Enabled=false;
		fremdfoerderungen->Enabled=false;
	}
	load_fremdfoerderungen();
	if(vn_einger_ || !load_)
	{
		programme->Enabled=false;
		betrag->Enabled=false;
		button12->Enabled=false;
		button13->Enabled=false;
	}
}

void fremdfoerdermittel_form::load_fremdfoerderungen()
{
	fremdfoerderungen->Items->Clear();
	for each(String^ eintrag in fremdfoerderung_->get_all(true))
		fremdfoerderungen->Items->Add(eintrag);
	if(fremdfoerderungen->Items->Count!=0)
	{
		fremdfoerderungen->Enabled=true;
		fremdfoerderungen->SelectedIndex=0;
	}
	else
		fremdfoerderungen->Enabled=false;
}

void fremdfoerdermittel_form::programme_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->FindStringExact(programme->Text)==-1 && programme->Enabled )
		programme->SelectedIndex=0;
}

void fremdfoerdermittel_form::button12_Click(System::Object^  sender, System::EventArgs^  e) // ADD
{
	if(programme->Enabled)
	{
		if(check_if_Decimal(betrag->Text) && betrag->Text!="")
		{
			if(fremdfoerderung_->add_programm(programme->Text,Decimal(Convert::ToDouble(betrag->Text))))
			{
				betrag->Text="";
				programme->SelectedIndex=0;
				load_fremdfoerderungen();
			}
			else
			Windows::Forms::MessageBox::Show("Das gewählte Programm wurde schon eingetragen.","Doppelter Eintrag");
		}
		else
			Windows::Forms::MessageBox::Show("Bitte überprüfen Sie den Betrag.","Fehlerhafter Eintrag");
	}
}

void fremdfoerdermittel_form::button13_Click(System::Object^  sender, System::EventArgs^  e) // REM
{
	if(fremdfoerderungen->SelectedIndex!=-1)
	{
		fremdfoerderung_->rem_programm(fremdfoerderungen->SelectedIndex);
		load_fremdfoerderungen();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie einen Eintrag.","Eintrag unbekannt");
}