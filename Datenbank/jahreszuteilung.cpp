#include "StdAfx.h"
#include "helper.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"

#include "jahreszuteilung.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace Datenbank;
using namespace System::Collections::Generic;

void jahreszuteilung::jahreszuteilung_Load(System::Object^  sender, System::EventArgs^  e)
{
	if(load_stadt())
	{
		jh_stadt->Enabled=true;
		jh_gebiet->Enabled=true;
		jh_programm->Enabled=true;
		haushalte->Enabled=true;
		jh_betrag->Enabled=true;
		jh_grund->Enabled=true;
		jh_jahr->Enabled=true;
		load_jahr();
	}
	else
	{
		Windows::Forms::MessageBox::Show("Es wurden keine Städte gefunden. Bitte kontaktieren Sie den Administrator.","Keine Städte gefunden");
		Close();
		/*
		jh_stadt->Enabled=false;
		jh_stadt->Text="Keine Einträge gefunden - überprüfen Sie die Abhänbgigkeiten!";
		jh_gebiet->Enabled=false;
		jh_programm->Enabled=false;
		haushalte->Enabled=false;
		jh_betrag->Enabled=false;
		jh_grund->Enabled=false;
		jh_jahr->Enabled=false;
		jh_jahr->Text="";*/
	}
}

bool jahreszuteilung::load_stadt()
{
	jh_stadt->Items->Clear();
	List<String^>^ stadt_ids=gcnew List<String^>;
	MyRecordSet RC_user("SELECT User_is_admin FROM Users WHERE User_ID="+Convert::ToString(user_id_));
	if(RC_user.get_val(0,0)=="1")
	{
		MyRecordSet RC_user_access("SELECT * FROM Staedte");
		for(int i=0;i<RC_user_access.get_row();++i)
			stadt_ids->Add(RC_user_access.get_val(i,0));
	}
	else
	{
		MyRecordSet RC_user_access("SELECT * FROM User_Access WHERE User_ID="+Convert::ToString(user_id_));
		for(int i=0;i<RC_user_access.get_row();++i)
			stadt_ids->Add(RC_user_access.get_val(i,2));
	}
	if(stadt_ids->Count!=0)
	{
		MyRecordSet RC("SELECT * FROM Staedte");
		for(int i=0;i<RC.get_row();++i)
		{
			if(is_existent_in(stadt_ids,RC.get_val(i,0)))
			{
				bool insert=false;
				MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC.get_val(i,0));
				for(int j=0;j<RC_Gebiet.get_row();++j)
				{
					MyRecordSet RC_Adr("SELECT ID FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(j,0));
					MyRecordSet RC_Prog("SELECT ID FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(j,0));
					if(RC_Adr.get_row()>0 && RC_Prog.get_row()>0)
						insert=true;
				}
				if(insert)
					jh_stadt->Items->Add(RC.get_val(i,1));
			}
		}

		if(jh_stadt->Items->Count>0)
		{
			jh_stadt->SelectedIndex=0;
			load_gebiet();
			return true;
		}
		else 
			return false;
	}
	else
	{
		Close();
	}
}

bool jahreszuteilung::load_gebiet()
{
	jh_gebiet->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+jh_stadt->Text+"'");
	MyRecordSet RC("Select * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
	for(int i=0;i<RC.get_row();++i)
	{
		MyRecordSet RC_Adresse("SELECT * FROM Strassen WHERE Gebiet_ID="+RC.get_val(i,0));
		MyRecordSet RC_Programme("SELECT * FROM Programme WHERE Gebiet_ID="+RC.get_val(i,0));
		if(RC_Adresse.get_row()!=0 && RC_Programme.get_row()!=0)			
			jh_gebiet->Items->Add(RC.get_val(i,2));
	}
	if(jh_gebiet->Items->Count>0)
	{
		jh_gebiet->SelectedIndex=0;
		load_programm();
		return true;
	}
	else
		return false;
}

void jahreszuteilung::load_programm()
{
	jh_programm->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+jh_stadt->Text+"'");
	MyRecordSet RC_Gebiet("Select ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+jh_gebiet->Text+"'");
	MyRecordSet RC("Select Programm FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));

	for(int i=0;i<RC.get_row();++i)
		jh_programm->Items->Add(RC.get_val(i,0));
	jh_programm->SelectedIndex=0;
}

void jahreszuteilung::load_jahr()
{
	jh_jahr->Items->Clear();
	MyRecordSet RC("SELECT * FROM Jahreseintraege order by ID");
	for(int i=0;i<RC.get_row();++i)
	{
		if(RC.get_val(i,1)!="XX")
			jh_jahr->Items->Add(RC.get_val(i,1));
	}
	jh_jahr->Items->Add("SBE");
	jh_jahr->SelectedIndex=0;
	load_jh();
}

void jahreszuteilung::jh_stadt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(jh_stadt->FindStringExact(jh_stadt->Text)==-1 && jh_stadt->Enabled )
		jh_stadt->SelectedIndex=0;
	load_gebiet();
}

void jahreszuteilung::jh_gebiet_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(jh_gebiet->FindStringExact(jh_gebiet->Text)==-1 && jh_gebiet->Enabled )
		jh_gebiet->SelectedIndex=0;
	load_programm();
}

void jahreszuteilung::jh_programm_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(jh_programm->FindStringExact(jh_programm->Text)==-1 && jh_programm->Enabled )
		jh_programm->SelectedIndex=0;
	load_jh();
}

void jahreszuteilung::jh_jahr_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(jh_jahr->FindStringExact(jh_jahr->Text)==-1 && jh_jahr->Enabled )
		jh_jahr->SelectedIndex=0;
	load_jh();
}

void jahreszuteilung::load_jh()  //
{
	haushalte->Items->Clear();
	jh_id_->Clear();
	List<String^>^ haushalt_list=gcnew List<String^>;
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+jh_stadt->Text+"'");
	MyRecordSet RC_Gebiet("Select ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+jh_gebiet->Text+"'");
	MyRecordSet RC_Programm("Select ID FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0)+" AND Programm='"+jh_programm->Text+"'");
	//annual budget
	MyRecordSet RC("SELECT * FROM jahreshaushalt WHERE programm_ID="+RC_Programm.get_val(0,0)+" AND jahr='"+jh_jahr->Text+"'");
	Decimal summe=0;
	for(int i=0;i<RC.get_row();++i)
	{
		Decimal betrag=Decimal(Convert::ToDouble(RC.get_val(i,2)));
		summe+=betrag;
		String^ grund=RC.get_val(i,3);
		String^ jahr=RC.get_val(i,4);
		String^ datum=RC.get_val(i,5);
		haushalt_list->Add(datum+" : "+Decimal_to_string(betrag)+" ("+grund+")");
		jh_id_->Add(RC.get_val(i,0));
	}
	jh_summe->Text=Decimal_to_string(summe);
	if(haushalt_list->Count==0)
	{
		haushalte->Enabled=false;
		haushalte->Items->Add("Kein Jahreshaushalt gefunden!");
	}
	else
	{
		haushalte->Enabled=true;
		for (int i=haushalt_list->Count; i>1;--i)
			for (int j=0; j<i-1; ++j)
			{
				//Windows::Forms::MessageBox::Show(	haushalt_list[j]->Substring(0,10)+"\n"+
				//									haushalt_list[j+1]->Substring(0,10)+"\n"+
				//									Convert::ToString(date_is_bigger(haushalt_list[j]->Substring(0,10),haushalt_list[j+1]->Substring(0,10))));
				if (date_is_bigger(haushalt_list[j]->Substring(0,10),haushalt_list[j+1]->Substring(0,10)))
				{
					String^ cache=haushalt_list[j];
					String^ id_chache=jh_id_[j];
					haushalt_list[j]=haushalt_list[j+1];
					jh_id_[j]=jh_id_[j+1];
					haushalt_list[j+1]=cache;
					jh_id_[j+1]=id_chache;
				}
			}

		for(int i=0;i<haushalt_list->Count;++i)
		{
			haushalte->Items->Add(haushalt_list[i]);
		}
	}
}
		
void jahreszuteilung::add_jh_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(jh_stadt->Enabled)
	{
		String^ datum=jh_datum->Text;
		String^ grund=jh_grund->Text;
		String^ betrag=jh_betrag->Text;
		String^ jahr=jh_jahr->Text;

		bool add=true;
		if(grund=="")
		{
			add=false;
			Windows::Forms::MessageBox::Show("Bitte überprüfen Sie den Änderungsgrund.","Eintrag unvollständig");
		}
		if(!(check_if_date(datum) && datum!=""))
		{
			add=false;
			Windows::Forms::MessageBox::Show("Bitte überprüfen Sie das Änderungsdatum.","Eintrag unvollständig");
		}
		if(!(check_if_Decimal(betrag) && betrag!=""))
		{
			add=false;
			Windows::Forms::MessageBox::Show("Bitte überprüfen Sie den Betrag.","Eintrag unvollständig");
		}

		if(add)
		{	
			MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+jh_stadt->Text+"'");
			MyRecordSet RC_Gebiet("Select ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+jh_gebiet->Text+"'");
			MyRecordSet RC_Programm("Select ID FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0)+" AND Programm='"+jh_programm->Text+"'");
			MyRecordSet RC("SELECT * FROM jahreshaushalt");
				
			MyInsertStatement("INSERT INTO jahreshaushalt (ID,programm_ID,betrag,grund,jahr,datum) VALUES ("
									+Convert::ToString(RC.get_new_id())+ ","// ID
									+RC_Programm.get_val(0,0)+ ",'"// programm_ID
									+betrag+ "','"// betrag
									+grund+ "','"// grund
									+jahr+ "','" // jahr
									+date_to_string(datum)+ "')" // datum
											);
			jh_datum->Text="";
			jh_grund->Text="";
			jh_betrag->Text="";
			load_jh();
		}
	}
}

void jahreszuteilung::del_jh_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(haushalte->Enabled)
	{
		if(haushalte->SelectedIndex!=-1)
		{
			String^ id=jh_id_[haushalte->SelectedIndex];
			MyInsertStatement RM("DELETE * FROM jahreshaushalt WHERE ID="+id);
			load_jh();
		}
		else
		{
			Windows::Forms::MessageBox::Show("Bitte wählen Sie einen Eintrag","Löschen nicht möglich");
		}
	}
	else
	{
		Windows::Forms::MessageBox::Show("Kein Jahreshaushalt eingetragen.","Löschen nicht möglich");
	}
}

void jahreszuteilung::btn_back_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}

bool jahreszuteilung::is_existent_in(List<String^>^ liste,String^ value)
{
	for each(String^ eintrag in liste)
		if(eintrag==value)
			return true;
	return false;
}