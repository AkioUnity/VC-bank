#include "StdAfx.h"
#include "MyRecordSet.h"
#include "login.h"
#include "helper.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections;

void login::btn_login_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(name->Text!="" && password->Text!="")
	{
		MyRecordSet RC("SELECT User_ID,User_Hash FROM Users WHERE User_Name='"+name->Text+"'");
		if(RC.get_row()!=0)
		{
			String^ Hash=get_MD5_hash(password->Text);

			if(Hash==RC.get_val(0,1))
			{
				cache_->Text=RC.get_val(0,0);
				Close();
			}
			else
			MessageBox::Show("Das angegebene Passwort ist ungültig.","Ungültige Eingabe");
			//The specified password is invalid. "," Invalid entry
		}
		else
			MessageBox::Show("Der Angegebene Nutzer wurde nicht gefunden.","Ungültige Eingabe");
		//The specified user was not found. "," Invalid entry
	}
	else
		MessageBox::Show("Bitte geben Sie Login und Passwort ein.","Unvollständige Eingabe");
}

void login::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}
