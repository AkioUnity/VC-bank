#include "StdAfx.h"
#include "optionen.h"
#include "helper.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

void optionen::btn_close_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}

void optionen::btn_change_password_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ old_pw=tB_old_pw->Text;
	String^ new_pw=tB_new_pw1->Text;
	String^ ref_pw=tB_new_pw2->Text;

	if(old_pw!="" && new_pw!="" && ref_pw!="")
	{
		String^ user_id=Convert::ToString(user_id_);
		MyRecordSet RC_user("SELECT * FROM Users WHERE User_ID="+user_id);
		String^ user_hash=RC_user.get_val(0,2);
		if(user_hash==get_MD5_hash(old_pw))
		{
			if(new_pw==ref_pw)
			{
				if(new_pw->Length>=7)
				{
					String^ user_id=Convert::ToString(user_id_);
					MyRecordSet RC_user("SELECT * FROM Users WHERE User_ID="+user_id);
					String^ is_admin=RC_user.get_val(0,3);
					String^ user_name=RC_user.get_val(0,1);
					user_hash=get_MD5_hash(new_pw);
					MyInsertStatement("DELETE * FROM Users WHERE User_ID="+user_id);
					MyInsertStatement("INSERT INTO Users (User_ID,User_Name,User_Hash,User_is_admin) VALUES ("+user_id+",'"+user_name+"','"+user_hash+"',"+is_admin+")");
					Windows::Forms::MessageBox::Show("Das Passwort wurde erfolgreich geändert.","Passwort geändert");
					Close();
				}
				else
				{
					Windows::Forms::MessageBox::Show("Das neue Passwort sollte mindestens 7 Zeichen enthalten.","Ändern nicht möglich");
				}
			}
			else
			{
				Windows::Forms::MessageBox::Show("Die Passwörter stimmen nicht überein.","Ändern nicht möglich");
			}
		}
		else
		{
			Windows::Forms::MessageBox::Show("Das alte Password ist falsch.","Ändern nicht möglich");
		}
	}
	else
	{
			Windows::Forms::MessageBox::Show("Bitte geben Sie die Passwörter an.","Ändern nicht möglich");
	}
}
