#include "StdAfx.h"
#include "auswertung_uebersicht.h"

#include "bewilligung_auswertung_form.h"
#include "kostengr_uebersicht_search.h"
#include "gesamt_uebersicht_search.h"
#include "adress_uebersicht_search.h"
#include "bew_ztr_search.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

void auswertung_uebersicht::btn_jahr_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ jahresuebersicht = gcnew bewilligung_auswertung_form(user_id_);
	Hide();
	jahresuebersicht->ShowDialog();
	Show();
}

void auswertung_uebersicht::btn_kostengr_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ kostengruppen_uebersicht = gcnew kostengr_uebersicht_search(user_id_);
	Hide();
	kostengruppen_uebersicht->ShowDialog();
	Show();
}

void auswertung_uebersicht::btn_adress_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ adress_uebersicht = gcnew adress_uebersicht_search(user_id_);
	Hide();
	adress_uebersicht->ShowDialog();
	Show();
}

void auswertung_uebersicht::btn_gesamt_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ gesamt_uebersicht = gcnew gesamt_uebersicht_search(user_id_);
	Hide();
	gesamt_uebersicht->ShowDialog();
	Show();
}

void auswertung_uebersicht::bew_ztr_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ bew_ztr_uebersicht = gcnew bew_ztr_search(user_id_);
	Hide();
	bew_ztr_uebersicht->ShowDialog();
	Show();
}

void auswertung_uebersicht::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}
