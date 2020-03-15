#include "StdAfx.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"
#include "helper.h"
#include "admin.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace Datenbank;
using namespace System::Collections::Generic;

//Windows::Forms::MessageBox::Show();

System::Void admin::load_stadt_entries()
{
	cB_staedte->Items->Clear();
	MyRecordSet RC("SELECT Stadt FROM Staedte");
	if(RC.get_row()>0)
	{
		cB_staedte->Enabled=true;
		for(int i=0;i<RC.get_row();++i)
		{
			cB_staedte->Items->Add(RC.get_val(i,0));
		}
		cB_staedte->SelectedIndex=0;
		load_gebiet_entries();
	}
	else
	{
		cB_staedte->Enabled=false;
		cB_staedte->Text="";
		cB_gebiete->Enabled=false;
		cB_gebiete->Text="";
		cB_programme->Enabled=false;
		cB_programme->Text="";
		cB_Strassen->Enabled=false;
		cB_Strassen->Text="";
	}
}

System::Void admin::load_gebiet_entries()
{
	cB_gebiete->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
	MyRecordSet RC("SELECT Gebiet FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
	if(RC.get_row()>0 && cB_staedte->Enabled)
	{
		cB_gebiete->Enabled=true;
		for(int i=0;i<RC.get_row();++i)
		{
			cB_gebiete->Items->Add(RC.get_val(i,0));
		}
		cB_gebiete->SelectedIndex=0;
		load_strassen_entries();
		load_program_entries();
	}
	else
	{
		cB_gebiete->Enabled=false;
		cB_gebiete->Text="";
		cB_programme->Enabled=false;
		cB_programme->Text="";
		cB_Strassen->Enabled=false;
		cB_Strassen->Text="";
	}
}

System::Void admin::load_program_entries()
{
	cB_programme->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
	if(RC_Gebiet.get_row()>0)
	{
		MyRecordSet RC("SELECT Programm FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
		if(RC.get_row()>0 && cB_gebiete->Enabled)
		{
			cB_programme->Enabled=true;
			for(int i=0;i<RC.get_row();++i)
			{
				cB_programme->Items->Add(RC.get_val(i,0));
			}
			cB_programme->SelectedIndex=0;
		}
		else
		{
			cB_programme->Enabled=false;
			cB_programme->Text="";
		}
	}
	else
	{
		cB_programme->Enabled=false;
		cB_programme->Text="";
	}
}

System::Void admin::load_strassen_entries()
{
	cB_Strassen->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
	if(RC_Gebiet.get_row()>0)
	{
		MyRecordSet RC("SELECT Strasse FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
		if(RC.get_row()>0 && cB_gebiete->Enabled)
		{
			cB_Strassen->Enabled=true;
			for(int i=0;i<RC.get_row();++i)
			{
				cB_Strassen->Items->Add(RC.get_val(i,0));
			}
			cB_Strassen->SelectedIndex=0;
		}
		else
		{
			cB_Strassen->Enabled=false;
			cB_Strassen->Text="";
		}
	}
	else
	{
		cB_programme->Enabled=false;
		cB_programme->Text="";
	}
}

System::Void admin::load_kostenart_entries()
{
	cB_kostenart->Items->Clear();
	MyRecordSet RC("SELECT Wert FROM Kostengruppe");
	if(RC.get_row()>0)
	{
		cB_kostenart->Enabled=true;
		for(int i=0;i<RC.get_row();++i)
		{
			cB_kostenart->Items->Add(RC.get_val(i,0));
		}
		cB_kostenart->SelectedIndex=0;
	}
	else
	{
		cB_kostenart->Enabled=false;
		cB_kostenart->Text="";
		cB_sachkonto_ges->Enabled=false;
		cB_sachkonto_ges->Text="";
	}
}

System::Void admin::load_sach_ges_entries()
{
	cB_sachkonto_ges->Items->Clear();
	MyRecordSet RC_kostenart("SELECT ID FROM Kostengruppe WHERE Wert='"+cB_kostenart->Text+"'");
	if(RC_kostenart.get_row()>0)
	{
		MyRecordSet RC("SELECT Wert FROM Kostenart WHERE Kostengruppe_ID="+RC_kostenart.get_val(0,0));
		if(RC.get_row()>0)
		{
			cB_sachkonto_ges->Enabled=true;
			for(int i=0;i<RC.get_row();++i)
			{
				cB_sachkonto_ges->Items->Add(RC.get_val(i,0));
			}
			cB_sachkonto_ges->SelectedIndex=0;
		}
		else
		{
			cB_sachkonto_ges->Enabled=false;
			cB_sachkonto_ges->Text="";
		}
	}
	else
	{
		cB_sachkonto_ges->Enabled=false;
		cB_sachkonto_ges->Text="";
	}
}

System::Void admin::load_ff_entries()
{
	cB_FF->Items->Clear();
	MyRecordSet RC("SELECT Foerderprogramm FROM Foerderprogramme");
	if(RC.get_row()>0)
	{
		cB_FF->Enabled=true;
		for(int i=0;i<RC.get_row();++i)
		{
			cB_FF->Items->Add(RC.get_val(i,0));
		}
		cB_FF->SelectedIndex=0;
	}
	else
	{
		cB_FF->Enabled=false;
		cB_FF->Text="";
	}
}

// #### Text Change ####################################################################################

void admin::cB_gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(cB_gebiete->FindStringExact(cB_gebiete->Text)==-1 && cB_gebiete->Enabled )
		cB_gebiete->SelectedIndex=0;
	load_program_entries();
	load_strassen_entries();
}

System::Void admin::cB_staedte_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(cB_staedte->FindStringExact(cB_staedte->Text)==-1 && cB_staedte->Enabled )
		cB_staedte->SelectedIndex=0;
	load_gebiet_entries();
}

System::Void admin::cB_programme_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(cB_programme->FindStringExact(cB_programme->Text)==-1 && cB_programme->Enabled)
		cB_programme->SelectedIndex=0;
}

System::Void admin::cB_Strassen_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(cB_Strassen->FindStringExact(cB_Strassen->Text)==-1 && cB_Strassen->Enabled)
		cB_Strassen->SelectedIndex=0;
}

System::Void admin::cB_kostenart_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(cB_kostenart->FindStringExact(cB_kostenart->Text)==-1 && cB_kostenart->Enabled)
		cB_kostenart->SelectedIndex=0;
	load_sach_ges_entries();
}

System::Void admin::cB_sachkonto_ges_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(cB_sachkonto_ges->FindStringExact(cB_sachkonto_ges->Text)==-1 && cB_sachkonto_ges->Enabled)
		cB_sachkonto_ges->SelectedIndex=0;
}

System::Void admin::cB_FF_TextChanged(System::Object^  sender, System::EventArgs^  e)
{	
	if(cB_FF->FindStringExact(cB_FF->Text)==-1 && cB_FF->Enabled)
		cB_FF->SelectedIndex=0;
}

// #### DEL ###########################################################################################

System::Void admin::btn_del_stadt_Click_1(System::Object^  sender, System::EventArgs^  e)
{
	if(del_warning())
		if(cB_staedte->Enabled)
		{
			MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
			MyInsertStatement RM_Stadt("DELETE * FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
			MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
			MyInsertStatement RM_Gebiet("DELETE * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
			for(int i=0;i<RC_Gebiet.get_row();++i)
			{
				MyInsertStatement RM_Strasse("DELETE * FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(i,0));
				MyInsertStatement RM_Program("DELETE * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(i,0));
			}
			load_stadt_entries();
		}
}

System::Void admin::btn_rem_gebiet_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(del_warning())
		if(cB_gebiete->Enabled)
		{
			MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
			MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
			MyInsertStatement RM_Gebiet("DELETE * FROM Gebiete WHERE ID="+RC_Gebiet.get_val(0,0));
			MyInsertStatement RM_Program("DELETE * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
			MyInsertStatement RM_Strasse("DELETE * FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));
			load_gebiet_entries();
		}
}

System::Void admin::btn_del_prog_Click(System::Object^  sender, System::EventArgs^  e)
{ 
	if(del_warning())
		if(cB_programme->Enabled)
		{
			MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
			MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
			MyInsertStatement RM("DELETE * FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0)+" AND Programm='"+cB_programme->Text+"'");
			load_program_entries();
		}
}

System::Void admin::btn_del_stasse_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(del_warning())
		if(cB_Strassen->Enabled)
		{
			MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
			MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
			MyInsertStatement RM("DELETE * FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0)+" AND Strasse='"+cB_Strassen->Text+"'");
			load_strassen_entries();
		}
}

System::Void admin::btn_del_kostenart_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(del_warning())
	{
		MyRecordSet RC_Kostenart("SELECT ID FROM Kostengruppe WHERE Wert='"+cB_kostenart->Text+"'");
		MyInsertStatement RM_kostenart("DELETE * FROM Kostengruppe WHERE Wert='"+cB_kostenart->Text+"'");
		MyInsertStatement RM_sach_ges("DELETE * FROM Kostenart WHERE Kostengruppe_ID="+RC_Kostenart.get_val(0,0));
		load_kostenart_entries();
	}
}

System::Void admin::btn_del_sach_ges_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(del_warning())
	{
		MyInsertStatement RM("DELETE * FROM Kostenart WHERE Wert='"+cB_sachkonto_ges->Text+"'");
		load_sach_ges_entries();
	}
}

System::Void admin::btn_del_ff_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(del_warning())
	{
		MyInsertStatement RM("DELETE * FROM Foerderprogramme WHERE Foerderprogramm='"+cB_FF->Text+"'");
		load_ff_entries();
	}
}

bool admin::del_warning()
{
	String^ message = "Falls der Eintrag innerhalb der Datenbank referenziert wird, wird es zu Fehlern kommen.\nSind sie sicher dass Sie den Eintrag löschen wollen?";
	String^ caption = "Warnung";
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	System::Windows::Forms::DialogResult result;
	result = MessageBox::Show( this, message, caption, buttons );
	if ( result == ::DialogResult::Yes )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// #### ADD ###########################################################################################

System::Void admin::btn_add_stadt_Click(System::Object^  sender, System::EventArgs^  e)
{

	MyRecordSet RC("SELECT * FROM Staedte");
	if(tB_stadt->Text!="")
	{
		if(cB_staedte->FindStringExact(tB_stadt->Text)==-1)
			MyInsertStatement("INSERT INTO Staedte (ID,Stadt) VALUES ("+RC.get_new_id()+",'"+tB_stadt->Text+"')");
		else
			Windows::Forms::MessageBox::Show("Die Stadt wurde schon eingetragen","Eintrag nicht möglich");
	}
	else
		Windows::Forms::MessageBox::Show("Bitte geben Sie eine Stadt an.","Eintrag unvollständig");
	tB_stadt->Text="";
	load_stadt_entries();
}

System::Void admin::btn_add_gebiet_Click(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT * FROM Gebiete");
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
	if(tB_gebiet->Text!="")	
	{
		if(cB_gebiete->FindStringExact(tB_gebiet->Text)==-1)
			MyInsertStatement("INSERT INTO Gebiete (ID,Stadt_ID,Gebiet) VALUES ("+RC.get_new_id()+","+RC_Stadt.get_val(0,0)+",'"+tB_gebiet->Text+"')");
		else
			Windows::Forms::MessageBox::Show("Das Gebiet wurde schon eingetragen","Eintrag nicht möglich");
	}
	else
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein Gebiet an.","Eintrag unvollständig");
	tB_gebiet->Text="";
	load_gebiet_entries();
}

System::Void admin::btn_add_prog_Click(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT * FROM Programme");
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
	if(tB_prog->Text!="")
		if(check_if_number(programm_nr->Text) && programm_nr->Text->Length==4)
		{
			if(cB_programme->FindStringExact(tB_prog->Text)==-1)
				MyInsertStatement("INSERT INTO Programme (ID,Gebiet_ID,Programm,Programm_Nr) VALUES ("+RC.get_new_id()+","+RC_Gebiet.get_val(0,0)+",'"+tB_prog->Text+"','"+programm_nr->Text+"')");
			else
				Windows::Forms::MessageBox::Show("Das Programm wurde schon eingetragen","Eintrag nicht möglich");
		}
		else
			Windows::Forms::MessageBox::Show("Bitte geben Sie eine gültige Programmnummer an.","Eintrag unvollständig");
	else
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein Programm an.","Eintrag unvollständig");
	tB_prog->Text="";
	programm_nr->Text="";
	load_program_entries();
}

System::Void admin::btn_add_strasse_Click(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT * FROM Strassen");
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+cB_staedte->Text+"'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+cB_gebiete->Text+"'");
	if(tB_Strasse->Text!="")
	{
		if(cB_Strassen->FindStringExact(tB_Strasse->Text)==-1)
		{
			MyInsertStatement("INSERT INTO Strassen (ID,Gebiet_ID,Strasse) VALUES ("+RC.get_new_id()+","+RC_Gebiet.get_val(0,0)+",'"+tB_Strasse->Text+"')");
			tB_Strasse->Text="";			
			load_strassen_entries();	
		}
		else
			Windows::Forms::MessageBox::Show("Die Adresse wurde schon eingetragen","Eintrag nicht möglich");
	}
	else
	{	
		Windows::Forms::MessageBox::Show("Bitte geben Sie eine Adresse an.","Eintrag unvollständig");	
	}
}

System::Void admin::btn_add_kostenart_Click(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT * FROM Kostengruppe");
	if(tB_kostenart->Text!="" && tb_kostengr_abk->Text!="" && tb_kostengr_abk->Text->Length<=4)
	{
		if(cB_kostenart->FindStringExact(tB_kostenart->Text)==-1)
		{
			MyInsertStatement("INSERT INTO Kostengruppe (ID,Wert,Abkuerzung) VALUES ("+RC.get_new_id()+",'"+tB_kostenart->Text+"','"+tb_kostengr_abk->Text+"')");
			tB_kostenart->Text="";
			tb_kostengr_abk->Text="";
			load_kostenart_entries();	
		}
		else
			Windows::Forms::MessageBox::Show("Die Kostengruppe wurde schon eingetragen","Eintrag nicht möglich");
	}
	else
	{
		if(tB_kostenart->Text=="")
			Windows::Forms::MessageBox::Show("Bitte geben Sie eine Kostengruppe an.","Eintrag unvollständig");
		else
			Windows::Forms::MessageBox::Show("Die Akürzung darf nicht länger als 4 Zeichen sein.","Eintrag unvollständig");
	}
}

System::Void admin::btn_add_sach_ges_Click(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT * FROM Kostenart");
	MyRecordSet RC_kostenart("SELECT ID FROM Kostengruppe WHERE Wert='"+cB_kostenart->Text+"'");
	if(tB_sach_gk->Text!="" && check_if_number(tB_kostenart_nr->Text) && tB_kostenart_nr->Text->Length==6)
	{
		if(cB_sachkonto_ges->FindStringExact(tB_sach_gk->Text)==-1)
		{
			MyInsertStatement("INSERT INTO Kostenart (ID,Kostengruppe_ID,Wert,Nummer) VALUES ("+RC.get_new_id()+","+RC_kostenart.get_val(0,0)+",'"+tB_sach_gk->Text+"','"+tB_kostenart_nr->Text+"')");
			tB_sach_gk->Text="";
			tB_kostenart_nr->Text="";
			load_sach_ges_entries();	
		}
		else
			Windows::Forms::MessageBox::Show("Die Kostenart wurde schon eingetragen","Eintrag nicht möglich");
	}
	else
	{
		if(tB_sach_gk->Text=="")
			Windows::Forms::MessageBox::Show("Bitte geben Sie eine Kostenart an.","Eintrag unvollständig");
		else
			Windows::Forms::MessageBox::Show("Die Nummer sollte 6 Zeichen lang sein.","Eintrag unvollständig");
	}
}

System::Void admin::btn_add_ff_Click(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT * FROM Foerderprogramme");
	if(tB_FF->Text!="")
	{
		if(cB_FF->FindStringExact(tB_FF->Text)==-1)
			MyInsertStatement("INSERT INTO Foerderprogramme (ID,Foerderprogramm) VALUES ("+RC.get_new_id()+",'"+tB_FF->Text+"')");
		else
			Windows::Forms::MessageBox::Show("Das Förderprogramm wurde schon eingetragen","Eintrag nicht möglich");
	}
	else
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein Sachkonto an.","Eintrag unvollständig");
	tB_FF->Text="";
	load_ff_entries();
}

// Anschrift

void Add_Text( FileStream^ fs, String^ value )
{
   array<Byte>^info = (gcnew UTF8Encoding( true ))->GetBytes( value );
   fs->Write( info, 0, info->Length );
}

void admin::btn_save_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ name=tB_name->Text;
	String^ strasse=tB_ansch_strasse->Text;
	String^ hausnr=tB_hausnr->Text;
	String^ plz=tB_plz->Text;
	String^ ort=tB_ort->Text;
	if(check_if_number(plz) && plz->Length==5 && name!="" && strasse!="" && ort!="" && hausnr!="")
	{
		MyInsertStatement("DELETE * FROM Anschrift");
		MyInsertStatement("INSERT INTO Anschrift (Name,Strasse,Hausnr,Plz,Ort) VALUES('"+name+"','"+strasse+"','"+hausnr+"','"+plz+"','"+ort+"')");
		Windows::Forms::MessageBox::Show("Adresse wurde eingetragen.","Speichern erfolgreich");
	}
	else
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie gültige Werte an.","Eintrag fehlerhaft");
	}
}

void admin::Adresse_Enter(System::Object^  sender, System::EventArgs^  e)
{
	String^ name="";
	String^ strasse="";
	String^ hausnr="";
	String^ plz="";
	String^ ort="";

	MyRecordSet RC("SELECT * FROM Anschrift");
	if(RC.get_row()>=1)
	{
		name=RC.get_val(0,0);
		strasse=RC.get_val(0,1);
		hausnr=RC.get_val(0,2);
		plz=RC.get_val(0,3);
		ort=RC.get_val(0,4);
	}

	tB_name->Text=name;
	tB_ansch_strasse->Text=strasse;
	tB_hausnr->Text=hausnr;
	tB_plz->Text=plz;
	tB_ort->Text=ort;
}

// TypCompare

bool admin::date_is_bigger(String^ date1 ,String^ date2)
{
	date1=date1->Replace("/",".");
	date1=date1->Replace("-",".");
	
	date2=date2->Replace("/",".");
	date2=date2->Replace("-",".");

	List<String^>^ einzel_daten_1=gcnew List<String^>;
	einzel_daten_1->Add("");
	List<String^>^ einzel_daten_2=gcnew List<String^>;
	einzel_daten_2->Add("");
	for(int i=0;i<date1->Length;++i)
	{
		if(date1[i]=='.')
		{
			einzel_daten_1->Add("");
			einzel_daten_2->Add("");
		}
		else
		{
			einzel_daten_1[einzel_daten_1->Count-1]+=date1[i];
			einzel_daten_2[einzel_daten_2->Count-1]+=date2[i];
		}
	}
	
	int jahr1=Convert::ToInt32(einzel_daten_1[2]);
	int jahr2=Convert::ToInt32(einzel_daten_2[2]);
	int monat1=Convert::ToInt32(einzel_daten_1[1]);
	int monat2=Convert::ToInt32(einzel_daten_2[1]);
	int tag1=Convert::ToInt32(einzel_daten_1[0]);
	int tag2=Convert::ToInt32(einzel_daten_2[0]);

	if(jahr1>jahr2)
		return true;
	if(jahr1<jahr2)
		return false;
	if(monat1>monat2)
		return true;
	if(monat1<monat2)
		return false;
	if(tag1>tag2)
		return true;
	if(tag1<tag2)
		return false;
}

// User
void admin::tabPage5_Enter(System::Object^  sender, System::EventArgs^  e)
{
	load_user();
}

void admin::load_user()
{
	lB_user->Items->Clear();
	MyRecordSet RC("SELECT User_Name FROM Users");
	for(int i=0;i<RC.get_row();++i)
		lB_user->Items->Add(RC.get_val(i,0));
	lB_user->SelectedIndex=0;
}

void admin::lB_user_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	gB_user->Text=lB_user->Text;
	lB_user_access->Items->Clear();
	MyRecordSet RC("SELECT User_is_admin FROM Users WHERE User_Name='"+lB_user->Text+"'");
	if(RC.get_val(0,0)=="1")
	{
		cB_user_is_admin->Checked=true;
		lB_user_access->Enabled=false;
		MyRecordSet RC_admin("SELECT User_is_admin FROM Users WHERE User_is_admin=1");
		cB_user_is_admin->Enabled=(RC_admin.get_row()!=1);
		btn_del_user->Enabled=(RC_admin.get_row()!=1);
	}
	else
	{
		lB_user_access->Enabled=true;
		cB_user_is_admin->Checked=false;
		cB_user_is_admin->Enabled=true;
		btn_del_user->Enabled=true;
		load_user_cities();
		load_user_access();
	}
}

void admin::btn_add_user_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(tB_new_user->Text!="")
	{
		MyRecordSet RC_user("SELECT * FROM Users WHERE User_Name='"+tB_new_user->Text+"'");
		if(RC_user.get_row()==0)
		{
			MyRecordSet RC=("SELECT * FROM Users");
			String^ new_id=Convert::ToString(RC.get_new_id());
			String^ user=tB_new_user->Text;
			String^ hash=get_MD5_hash(user);
			MyInsertStatement("INSERT INTO Users (User_ID,User_Name,User_Hash,User_is_admin) VALUES ("+new_id+",'"+user+"','"+hash+"','0')");
			load_user();
			tB_new_user->Text="";
			Windows::Forms::MessageBox::Show("Der Nutzer \""+user+"\" wurde mit dem Passwort \""+user+"\" eingetragen.","Nutzer eingetragen");
		}
		else
			Windows::Forms::MessageBox::Show("Der gewählte Name ist schon vergeben.","Eintrag nicht möglich");
	}
	else
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie einen Namen an.","Eintrag unvollständig");
	}
}

void admin::btn_del_user_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ user_name=lB_user->Text;

	String^ message = "Soll der Nutzer \""+user_name+"\" wirklich gelöscht werden?\n(Sollte der Nutzer noch angemeldet sein, wird es in seiner Sitzung zu Fehlern kommen)";
	String^ caption = "Löschen bestätigen";
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	System::Windows::Forms::DialogResult result;
	result = MessageBox::Show( this, message, caption, buttons );
	if ( result == ::DialogResult::Yes )
	{
		MyRecordSet RC("SELECT User_ID FROM Users WHERE User_Name='"+user_name+"'");
		String^ user_id=RC.get_val(0,0);
		MyInsertStatement RM_users("DELETE * FROM Users WHERE User_ID="+user_id);
		MyInsertStatement RM_user_access("DELETE * FROM User_Access WHERE User_ID="+user_id);
		Windows::Forms::MessageBox::Show("Der Nutzer \""+user_name+"\" wurde erfolgreich gelöscht.","Nutzer gelöscht");
		load_user();
	}
}

void admin::cB_user_is_admin_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ user_name=lB_user->Text;
	String^ new_state;
	if(cB_user_is_admin->Checked)
		new_state="1";
	else
		new_state="0";
	MyRecordSet RC("SELECT * FROM Users WHERE User_Name='"+user_name+"'");
	String^ user_id=RC.get_val(0,0);
	String^ hash=RC.get_val(0,2);
	MyInsertStatement("DELETE * FROM Users WHERE User_ID="+user_id);
	MyInsertStatement("INSERT INTO Users (User_ID,User_Name,User_Hash,User_is_admin) VALUES ("+user_id+",'"+user_name+"','"+hash+"',"+new_state+")");
	lB_user_SelectedIndexChanged(sender, e);	
}

void admin::load_user_cities()
{
	lB_user_access->Items->Clear();
	MyRecordSet RC("SELECT * FROM Staedte");
	for(int i=0;i<RC.get_row();++i)
		lB_user_access->Items->Add(RC.get_val(i,1));
}

void admin::load_user_access()
{
	lB_user_access->ClearSelected();

	MyRecordSet RC_user("SELECT User_ID FROM Users WHERE User_Name='"+lB_user->Text+"'");
	MyRecordSet RC_user_access("SELECT * FROM User_Access WHERE User_ID="+RC_user.get_val(0,0));
	for(int i=0;i<RC_user_access.get_row();++i)
	{
		MyRecordSet RC_stadt("SELECT Stadt FROM Staedte WHERE ID="+RC_user_access.get_val(i,2));
		int index=lB_user_access->Items->IndexOf(RC_stadt.get_val(0,0));
		lB_user_access->SetItemChecked(index,true);
	}
}

void admin::lB_user_access_Click(System::Object^  sender, System::EventArgs^  e)
{
	// Get User_ID
	MyRecordSet RC_user("SELECT User_ID FROM Users WHERE User_Name='"+lB_user->Text+"'");
	String^ user_id=RC_user.get_val(0,0);

	// Get Stadt_ID
	MyRecordSet RC_stadt("SELECT ID FROM Staedte WHERE Stadt='"+lB_user_access->Text+"'");
	String^ stadt_id=RC_stadt.get_val(0,0);

	// Perform DB operation
	bool checked=lB_user_access->GetItemChecked(lB_user_access->SelectedIndex);
	if(checked)
	{
		MyInsertStatement("DELETE * FROM User_Access WHERE User_ID="+user_id+" AND Stadt_ID="+stadt_id);
	}
	else
	{
		MyRecordSet RC("SELECT * FROM User_Access");
		MyInsertStatement("INSERT INTO User_Access (Access_ID,User_ID,Stadt_ID) VALUES ("+Convert::ToString(RC.get_new_id())+","+user_id+","+stadt_id+")");
	}
}

void admin::btn_reset_pwd_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ user_name=lB_user->Text;
	MyRecordSet RC_user("SELECT * FROM Users WHERE User_Name='"+user_name+"'");
	String^ user_id=RC_user.get_val(0,0);
	String^ is_admin=RC_user.get_val(0,3);
	String^ user_hash=get_MD5_hash(user_name);
	MyInsertStatement("DELETE * FROM Users WHERE User_ID="+user_id);
	MyInsertStatement("INSERT INTO Users (User_ID,User_Name,User_Hash,User_is_admin) VALUES ("+user_id+",'"+user_name+"','"+user_hash+"',"+is_admin+")");
	Windows::Forms::MessageBox::Show("Das Passwort von \""+user_name+"\" wurde auf \""+user_name+"\" zurückgesetzt.","Passwort zurückgesetzt");
}