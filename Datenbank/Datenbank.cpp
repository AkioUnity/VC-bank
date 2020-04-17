
// Datenbank.cpp: Hauptprojektdatei.
#include "stdafx.h"
#include "MyRecordSet.h"
#include "Menue.h"
#include "Set_DB_path.h"
#include "admin.h"
#include "project_form.h"
#include "open_project_form.h"
#include "login.h"
#include "auswertung_uebersicht.h"
#include "optionen.h"
#include "jahreszuteilung.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections;

//Windows::Forms::MessageBox::Show("");

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Aktivieren visueller Effekte von Windows XP, bevor Steuerelemente erstellt werden
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew Form1());

}

System::Void Form1::check_for_DB_path()
{
	bool exists;
	do
	{
		exists = true;
		try { 
			MyRecordSet::SetPath();
			MyRecordSet("SELECT * FROM staedte"); 
		}
		catch (FileNotFoundException^)
		{
			String^ message = "Es wurde noch keine Datenbank eingetragen.\nWollen Sie dies nun tun?";
			String^ caption = "Öffnen der Datenbank nicht möglich.";
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;

			result = MessageBox::Show(this, message, caption, buttons);
			if (result == ::DialogResult::No)
				Close();

			exists = false;
		}
		catch (Data::OleDb::OleDbException^)
		{
			String^ message = "Die gespeicherte Datenbank befindet sich nicht mehr an dem eingetragen Ort.\nWollen Sie dies berichtigen?";
			String^ caption = "Öffnen der Datenbank nicht möglich.";
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;

			result = MessageBox::Show(this, message, caption, buttons);
			if (result == ::DialogResult::No)
				Close();

			exists = false;
		}

		if (!exists)
		{
			Form^ Pfad_setzen = gcnew Set_DB_path;
			Hide();
			Pfad_setzen->ShowDialog();
			Show();
		}
	} while (!exists);
}

System::Void Form1::btn_new_proj_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ new_proj = gcnew project_form(user_id_);
	Hide();
	new_proj->ShowDialog();
	Show();
}

System::Void Form1::btn_open_proj_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ open_proj = gcnew open_project_form(user_id_);
	Hide();
	open_proj->ShowDialog();
	Show();
}

System::Void Form1::btn_admin_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ administration = gcnew admin;
	Hide();
	administration->ShowDialog();
	Show();
}

System::Void Form1::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}

System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e)
{
	Hide();
	check_for_DB_path();
	System::Windows::Forms::Label^  cache = gcnew System::Windows::Forms::Label();
	cache->Text = "-1";
	//cache->Text = "4";
	Form^ user = gcnew login(cache);
	user->ShowDialog();
	if (cache->Text == "-1") {
		Close();
		return;
	}
	user_id_ = Convert::ToInt32(cache->Text);
	MyRecordSet RC("SELECT User_is_admin FROM Users WHERE User_ID=" + Convert::ToString(user_id_));
	if (RC.get_val(0, 0) == "1")
	{
		btn_admin->Visible = true;
	}
	else
	{
		btn_admin->Visible = false;
	}
	Show();
}

void Form1::btn_data_result_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ auswertung = gcnew auswertung_uebersicht(user_id_);
	Hide();
	auswertung->ShowDialog();
	Show();
}

void Form1::btn_options_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ options = gcnew optionen(user_id_);
	Hide();
	options->ShowDialog();
	Show();
}

void Form1::btn_jahreszuteilung_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ jz = gcnew jahreszuteilung(user_id_);
	Hide();
	jz->ShowDialog();
	Show();
}