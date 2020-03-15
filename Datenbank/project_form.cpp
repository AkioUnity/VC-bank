#include "StdAfx.h"

#include "MyRecordSet.h"
#include "project_form.h"
#include "verwendungsnachweis_form.h"
#include "bewilligung_form.h"
#include "fremdfoerdermittel_form.h"
#include "adress_plankosten.h"
#include "choose_printer.h"
#include "helper.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;


// ComboBox Einträge laden
void project_form::project_form_Load(System::Object^  sender, System::EventArgs^  e)
{
	// Fill List for User Rights
	stadt_ids_->Clear();
	MyRecordSet RC_user("SELECT User_is_admin FROM Users WHERE User_ID="+Convert::ToString(user_id_));
	if(RC_user.get_val(0,0)=="1")
	{
		MyRecordSet RC_user_access("SELECT * FROM Staedte");
		for(int i=0;i<RC_user_access.get_row();++i)
			stadt_ids_->Add(RC_user_access.get_val(i,0));
	}
	else
	{
		MyRecordSet RC_user_access("SELECT * FROM User_Access WHERE User_ID="+Convert::ToString(user_id_));
		for(int i=0;i<RC_user_access.get_row();++i)
			stadt_ids_->Add(RC_user_access.get_val(i,2));
	}

	// Check if User has Rights to Change Things if project is loaded
	String^ city=projekt_->get_stadt();
	load_std_=true;
	if(city!="")
	{
		MyRecordSet RC_safe=("SELECT ID FROM Staedte WHERE Stadt='"+city+"'");
		if(!is_existent_in(stadt_ids_,RC_safe.get_val(0,0)))
		{
			load_std_=false;
		}
	}
	if(load_std_)
	{
		if(load_stadt())
		{
			if(load_kostengruppe())
			{
				if(load_sachkonto_bha())
				{
					loaded_=true;
					show_project();
					load_gebiet();
				}
				else
				{
					Windows::Forms::MessageBox::Show("Kein BHA Sachkonto gefunden.","Bitte kontaktieren Sie den Administrator");
					Close();
				}
			}
			else
			{
				Windows::Forms::MessageBox::Show("Keine Kostengruppe gefunden.","Bitte kontaktieren Sie den Administrator");
				Close();
			}
		}
		else
		{
			Windows::Forms::MessageBox::Show("Keine Stadt gefunden.","Bitte kontaktieren Sie den Administrator");
			Close();
		}
	}
	else
	{
		for(int i=0;i<this->Controls->Count;++i)
			this->Controls[i]->Enabled=false;
		loaded_=true;
		show_project();
		for(int i=0;i<this->Controls->Count;++i)
			this->Controls[i]->Enabled=false;
		strassen->Enabled=true;
		strassen->ForeColor=Color::FromName("WindowText");
		groupBox1->Enabled=true;
		add_programm->Enabled=false;
		del_programm->Enabled=false;
		programm->Enabled=false;
		add_bewilligung->Enabled=false;
		del_bewilligung->Enabled=false;
		vn_geprueft->Enabled=false;
		vn_eingereicht->Enabled=false;
		btn_VN->Enabled=true;
		button10->Enabled=true;
		btn_print->Enabled=true;
		button5->Enabled=true;
	}
}

bool project_form::load_kostengruppe()
{
	kostengruppe->Items->Clear();
	MyRecordSet RC("SELECT * FROM Kostengruppe");
	for(int i=0;i<RC.get_row();++i)
	{
		MyRecordSet RC_KA("SELECT Wert FROM Kostenart WHERE Kostengruppe_ID="+RC.get_val(0,0));
		if(RC_KA.get_row()!=0)
			kostengruppe->Items->Add(RC.get_val(i,1));
	}
	if(kostengruppe->Items->Count>0)
	{
		kostengruppe->SelectedIndex=0;		
		if(projekt_->get_kostengruppe()=="")
			projekt_->set_kostengruppe(kostengruppe->Text);
		return load_kostenart();
	}
	else
	{
		return false;
	}
}

bool project_form::load_kostenart()
{
	String^ txt=projekt_->get_kostenart();
	kostenart->Items->Clear();
	MyRecordSet RC_KG("SELECT ID FROM Kostengruppe WHERE Wert='"+kostengruppe->Text+"'");
	MyRecordSet RC("SELECT Wert FROM Kostenart WHERE Kostengruppe_ID="+RC_KG.get_val(0,0));
	for(int i=0;i<RC.get_row();++i)
		kostenart->Items->Add(RC.get_val(i,0));

	if(RC.get_row()>0)
	{
		int index=0;
		if(kostenart->FindStringExact(txt)!=-1)
			index=kostenart->FindStringExact(txt);

		kostenart->SelectedIndex=index;
		if(projekt_->get_kostenart()=="")
			projekt_->set_kostenart(kostenart->Text);
		MyRecordSet RC_KG_2("SELECT ID FROM Kostengruppe WHERE Wert='"+kostengruppe->Text+"'");
		MyRecordSet RC_KA("SELECT Nummer FROM Kostenart WHERE Kostengruppe_ID="+RC_KG_2.get_val(0,0)+" AND Wert='"+kostenart->Text+"'");
		kostenart_nr->Text=RC_KA.get_val(0,0)+" )";
		return true;
	}
	else
		return false;

}

bool project_form::load_sachkonto_bha()
{
	bha_sk->Items->Clear();
	MyRecordSet RC("SELECT * FROM Sachkonto_BHA");
	for(int i=0;i<RC.get_row();++i)
		bha_sk->Items->Add(RC.get_val(i,1));
	if(RC.get_row()>0)
	{
		bha_sk->SelectedIndex=0;
		if(projekt_->get_sk_bha()=="")
			projekt_->set_sk_bha(bha_sk->Text);
		return true;
	}
	else 
		return false;
}

bool project_form::load_stadt()
{
	stadt->Items->Clear();
	MyRecordSet RC("SELECT * FROM Staedte");
	for(int i=0;i<RC.get_row();++i)
	{
		if(is_existent_in(stadt_ids_,RC.get_val(i,0)))
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
				stadt->Items->Add(RC.get_val(i,1));
		}
	}
	if(stadt->Items->Count>0)
	{
		stadt->SelectedIndex=0;
		if(projekt_->get_stadt()=="")
			projekt_->set_stadt(stadt->Text);
		load_gebiet();
		return true;
	}
	else 
		return false;

}

bool project_form::load_gebiet()
{
	gebiet->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+stadt->Text+"'");
	MyRecordSet RC("Select * FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0));
	for(int i=0;i<RC.get_row();++i)
	{
		MyRecordSet RC_Adresse("SELECT * FROM Strassen WHERE Gebiet_ID="+RC.get_val(i,0));
		MyRecordSet RC_Programme("SELECT * FROM Programme WHERE Gebiet_ID="+RC.get_val(i,0));
		if(RC_Adresse.get_row()!=0 && RC_Programme.get_row()!=0)			
			gebiet->Items->Add(RC.get_val(i,2));
	}
	if(gebiet->Items->Count>0)
	{
		if(gebiet->FindStringExact(projekt_->get_gebiet())!=-1)
			gebiet->SelectedIndex=gebiet->FindStringExact(projekt_->get_gebiet());
		else
			gebiet->SelectedIndex=0;
		if(projekt_->get_gebiet()=="")
			projekt_->set_gebiet(gebiet->Text);
		load_programm();
		load_strasse();
		return true;
	}
	else
		return false;
}

void project_form::load_programm()
{
	programm->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+stadt->Text+"'");
	MyRecordSet RC_Gebiet("Select ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+gebiet->Text+"'");
	MyRecordSet RC("Select Programm FROM Programme WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));

	for(int i=0;i<RC.get_row();++i)
		programm->Items->Add(RC.get_val(i,0));
	programm->SelectedIndex=0;
}

void project_form::load_strasse()
{
	strasse->Items->Clear();
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+stadt->Text+"'");
	MyRecordSet RC_Gebiet("Select ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+gebiet->Text+"'");
	MyRecordSet RC("Select Strasse FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0));

	for(int i=0;i<RC.get_row();++i)
		strasse->Items->Add(RC.get_val(i,0));
	strasse->SelectedIndex=0;
}


// Text Change ComboBox
void project_form::kostengruppe_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(loaded_)
	{
		if(kostengruppe->FindStringExact(kostengruppe->Text)==-1 && kostengruppe->Enabled )
			kostengruppe->SelectedIndex=0;
		projekt_->set_kostengruppe(kostengruppe->Text);
		load_kostenart();
	}
}

void project_form::kostenart_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(loaded_)
	{
		if(kostenart->FindStringExact(kostenart->Text)==-1 && kostenart->Enabled )
			kostenart->SelectedIndex=0;
		projekt_->set_kostenart(kostenart->Text);
		MyRecordSet RC_KG("SELECT ID FROM Kostengruppe WHERE Wert='"+kostengruppe->Text+"'");
		MyRecordSet RC("SELECT Nummer FROM Kostenart WHERE Kostengruppe_ID="+RC_KG.get_val(0,0)+" AND Wert='"+kostenart->Text+"'");
		kostenart_nr->Text=RC.get_val(0,0)+" )";
	}
}

void project_form::bha_sk_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(loaded_)
	{
		if(bha_sk->FindStringExact(bha_sk->Text)==-1 && bha_sk->Enabled )
			bha_sk->SelectedIndex=0;
		projekt_->set_sk_bha(bha_sk->Text);
	}
}

void project_form::stadt_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(loaded_)
	{
		if(stadt->FindStringExact(stadt->Text)==-1 && stadt->Enabled )
			stadt->SelectedIndex=0;	

		if(stadt->Text!=projekt_->get_stadt())
		{
			if(programme->Items->Count!=0 || strassen->Items->Count!=0)
			{
				String^ message = "Bei Änderung der Stadt werden alle Programme, Adressen und Bewilligungen gelöscht.\nFortfahren?";
				String^ caption = "Wollen Sie die Stadt ändern?";
				MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				System::Windows::Forms::DialogResult result;
				result = MessageBox::Show( this, message, caption, buttons );
				if ( result == ::DialogResult::Yes )
				{
					projekt_->set_stadt(stadt->Text);
					projekt_->clear_programm();
					projekt_->clear_adressen();
					projekt_->set_gebiet("");
					projekt_->set_vn_eingereicht("");
					projekt_->set_vn_geprueft("");
					projekt_->set_aenderungsbescheid("");
					load_gebiet();
					show_project();
				}
				else
				{
					show_project();
				}
			}
			else
			{
				projekt_->set_stadt(stadt->Text);
				load_gebiet();
			}
		}
	}
}

void project_form::gebiet_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(loaded_)
	{
		if(gebiet->FindStringExact(gebiet->Text)==-1 && gebiet->Enabled )
			gebiet->SelectedIndex=0;

		if(gebiet->Text!=projekt_->get_gebiet())
		{
			if(programme->Items->Count!=0 || strassen->Items->Count!=0)
			{
				String^ message = "Bei Änderung des Gebietes werden alle Programme, Adressen und Bewilligungen gelöscht.\nFortfahren?";
				String^ caption = "Wollen Sie das Gebiet ändern?";
				MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				System::Windows::Forms::DialogResult result;
				result = MessageBox::Show( this, message, caption, buttons );
				if ( result == ::DialogResult::Yes )
				{
					projekt_->set_gebiet(gebiet->Text);
					projekt_->clear_programm();
					projekt_->clear_adressen();
					load_programm();
					load_strasse();
					projekt_->set_vn_eingereicht("");
					projekt_->set_vn_geprueft("");
					projekt_->set_aenderungsbescheid("");
					show_project();
				}
				else
				{
					show_project();
				}
			}
			else
			{
				projekt_->set_gebiet(gebiet->Text);
				load_programm();
				load_strasse();
			}
		}
	}
}

void project_form::programm_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programm->FindStringExact(programm->Text)==-1 && programm->Enabled )
		programm->SelectedIndex=0;
}

void project_form::strasse_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(strasse->FindStringExact(strasse->Text)==-1 && strasse->Enabled )
		strasse->SelectedIndex=0;
}

// Text Change TextBox
void project_form::bezeichnung_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	projekt_->set_bezeichnung(bezeichnung->Text);
	if(bezeichnung->Text=="")
		bezeichnung->BackColor=Color::FromName("LavenderBlush");
	else
		bezeichnung->BackColor=Color::FromName("White");
}

void project_form::foeuvh_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(foeuvh->Text!="")
		if(check_if_date(foeuvh->Text))
		{
			projekt_->set_foeuvh(date_to_string(foeuvh->Text));
			foeuvh->BackColor=Color::FromName("White");
			show_project();
		}
		else
			foeuvh->BackColor=Color::FromName("LavenderBlush");
	else
	{
		projekt_->set_foeuvh("");
		foeuvh->BackColor=Color::FromName("White");
	}
}

void project_form::foeuvh_Leave(System::Object^  sender, System::EventArgs^  e)
{
	foeuvh->Text=projekt_->get_foeuvh();
}

void project_form::bew_ztr_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(check_if_date(bew_ztr->Text))
	{
		projekt_->set_bew_ztr(date_to_string(bew_ztr->Text));
		bew_ztr->BackColor=Color::FromName("White");
		show_project();
	}
	else
		bew_ztr->BackColor=Color::FromName("LavenderBlush");
}

void project_form::bew_ztr_Leave(System::Object^  sender, System::EventArgs^  e)
{
	bew_ztr->Text=projekt_->get_bew_ztr();
}

void project_form::gk_real_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=gk_real->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace("€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		projekt_->set_gk_real(Decimal(Convert::ToDouble(txt)));
		gk_real->BackColor=Color::FromName("White");
		bha_betrag->Text=Decimal_to_string(projekt_->get_bha());
	}
	else
		gk_real->BackColor=Color::FromName("LavenderBlush");
}

void project_form::gk_real_Leave(System::Object^  sender, System::EventArgs^  e)
{
	/*
	String^ out="";
	out+=Convert::ToString(Convert::ToString(projekt_->get_gk_real())->IndexOf(",")+4)+"\n";
	out+=Convert::ToString(Convert::ToString(projekt_->get_gk_real())->Length);
	Windows::Forms::MessageBox::Show(out);*/

	gk_real->Text=Decimal_to_string(projekt_->get_gk_real());
	bha_betrag->Text=Decimal_to_string(projekt_->get_bha());
}

void project_form::gk_zuwendungsf_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=gk_zuwendungsf->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace("€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		projekt_->set_gk_zuwendungsf(Decimal(Convert::ToDouble(txt)));
		gk_zuwendungsf->BackColor=Color::FromName("White");
	}
	else
		gk_zuwendungsf->BackColor=Color::FromName("LavenderBlush");
}

void project_form::gk_zuwendungsf_Leave(System::Object^  sender, System::EventArgs^  e)
{
	gk_zuwendungsf->Text=Decimal_to_string(projekt_->get_gk_zuwendungsf());
}

void project_form::aenderungsbescheid_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(aenderungsbescheid->Text!="")
		if(check_if_date(aenderungsbescheid->Text))
		{
			projekt_->set_aenderungsbescheid(date_to_string(aenderungsbescheid->Text));
			aenderungsbescheid->BackColor=Color::FromName("White");
			show_project();
		}
		else
			aenderungsbescheid->BackColor=Color::FromName("LavenderBlush");
	else
	{
		projekt_->set_aenderungsbescheid("");
		aenderungsbescheid->BackColor=Color::FromName("White");
	}
}

void project_form::aenderungsbescheid_Leave(System::Object^  sender, System::EventArgs^  e)
{
	aenderungsbescheid->Text=projekt_->get_aenderungsbescheid();
}

void project_form::vn_eingereicht_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ einger=vn_eingereicht->Text;
	if(einger!="")
		if(check_if_date(einger))
		{
			if(projekt_->get_vn_eingereicht()=="")
			{
				projekt_->set_vn_eingereicht(date_to_string(einger));
				projekt_->bewilligung_zu_vn();
				vn_einger_=true;
			}
			else
			{
				projekt_->set_vn_eingereicht(date_to_string(einger));
				vn_einger_=true;
			}
			vn_eingereicht->BackColor=Color::FromName("White");
			show_project();
		}
		else
			vn_eingereicht->BackColor=Color::FromName("LavenderBlush");
	else
	{
		if(projekt_->get_vn_eingereicht()!="")
		{
			String^ message = "Mit dem Löschen des Datums wird der Verwendungsnachweis und das Geprüft-Datum gelöscht.\nFortfahren?";
			String^ caption = "Wollen Sie das Eingereicht-Datum löschen?";
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;
			result = MessageBox::Show( this, message, caption, buttons );
			if ( result == ::DialogResult::Yes )
			{
				projekt_->set_vn_eingereicht(einger);	
				projekt_->set_vn_geprueft("");	
				vn_einger_=false;
			}
		}
		vn_eingereicht->BackColor=Color::FromName("White");
		show_project();
	}
}

void project_form::vn_eingereicht_Leave(System::Object^  sender, System::EventArgs^  e)
{
	vn_eingereicht->Text=projekt_->get_vn_eingereicht();
}

void project_form::vn_geprueft_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(vn_geprueft->Enabled)
	{
		if(vn_geprueft->Text!="")
			if(check_if_date(vn_geprueft->Text))
			{
				if(projekt_->get_vn_geprueft()=="")
				{
					String^ message = "Mit dem Eintragen des Datums werden alle Bewilligungen überschrieben.\nFortfahren?";
					String^ caption = "Wollen Sie das Geprüft-Datum ändern?";
					MessageBoxButtons buttons = MessageBoxButtons::YesNo;
					System::Windows::Forms::DialogResult result;
					result = MessageBox::Show( this, message, caption, buttons );
					if ( result == ::DialogResult::Yes )
					{
						projekt_->vn_zu_bewilligung();
						projekt_->set_vn_geprueft(date_to_string(vn_geprueft->Text));	
					}
				}
				else
				{
					projekt_->set_vn_geprueft(date_to_string(vn_geprueft->Text));
				}
				vn_geprueft->BackColor=Color::FromName("White");
				show_project();
			}
			else
				vn_geprueft->BackColor=Color::FromName("LavenderBlush");
		else
		{
			projekt_->set_vn_geprueft("");
			vn_geprueft->BackColor=Color::FromName("White");
			show_project();
		}
	}
}

void project_form::vn_geprueft_Leave(System::Object^  sender, System::EventArgs^  e)
{
	vn_geprueft->Text=projekt_->get_vn_geprueft();
}

void project_form::bemerkung_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	projekt_->set_bemerkung(bemerkung->Text);
}

// ListBox
void project_form::programme_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->Enabled)
		show_programm_eintrag();
}

void project_form::programme_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->Enabled)
		show_programm_eintrag();
}

// Buttons
void project_form::add_programm_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(programm->Enabled)
	{
		if(projekt_->get_programm_index(programm->Text)==-1)
		{
			MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+stadt->Text+"'");
			MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" AND Gebiet='"+gebiet->Text+"'");
			MyRecordSet RC_Programm("SELECT * FROM Programme WHERE Programm='"+programm->Text+"' AND Gebiet_ID="+RC_Gebiet.get_val(0,0));
			projekt_->add_programm(programm->Text,RC_Programm.get_val(0,3));
			show_project();
		}
		else
			Windows::Forms::MessageBox::Show("Das gewählte Programm wurde schon eingetragen.","Einfügen nicht möglich");	
	}
}

void project_form::del_programm_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(programme->SelectedIndex!=-1)
	{
		projekt_->rem_programm(programme->Text);
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie ein Programm.","Kein Programm gewählt");
}

void project_form::add_strasse_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(strasse->Enabled)
	{
		if(projekt_->get_adress_index(strasse->Text)==-1)
		{
			projekt_->add_adresse(strasse->Text);
			show_project();
		}
		else
			Windows::Forms::MessageBox::Show("Die gewählte Adresse wurde schon eingetragen.","Einfügen nicht möglich");	
	}
}

void project_form::rem_strasse_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(strassen->SelectedIndex!=-1)
	{
		projekt_->rem_adresse(strassen->Text);
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie eine Adresse.","Keine Adresse gewählt");
}

void project_form::add_bewilligung_Click(System::Object^  sender, System::EventArgs^  e)
{	
	if(programme->SelectedIndex!=-1)
	{
		projekt_->add_bewilligung(programme->Text);
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie ein Programm.","Kein Programm gewählt");
}

void project_form::del_bewilligung_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(bewilligungen->SelectedIndex!=-1)
	{
		projekt_->rem_bewilligung(programme->Text,bewilligungen->SelectedIndex);
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie eine Bewilligung.","Keine Bewilligung gewählt");
}

void project_form::bewilligungen_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	if(bewilligungen->Enabled && bewilligungen->SelectedIndex!=-1)
	{
		Form^ bewilligung = gcnew bewilligung_form(projekt_->get_bewilligung(programme->Text,bewilligungen->SelectedIndex),vn_einger_,load_std_);
		bewilligung->ShowDialog();
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie eine Bewilligung.","Keine Bewilligung gewählt");
}

void project_form::strassen_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	if(strassen->SelectedIndex!=-1)
	{
		String^ adress ="";
		for(int i=0;i<strassen->Text->Length;++i)
			if(strassen->Text[i]!='[')
				adress+=strassen->Text[i];
			else
				break;
		adress=adress->Trim();
		Form^ adresse_form = gcnew adress_plankosten(projekt_->get_adresse(adress),vn_einger_,load_std_);
		adresse_form->ShowDialog();
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie eine Adresse.","Keine Adresse gewählt");
}

void project_form::btn_VN_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(vn_eingereicht->Text!="")
	{
		Form^ verwendungsnachweis = gcnew verwendungsnachweis_form(projekt_,load_std_);
		verwendungsnachweis->ShowDialog();
		if(projekt_->get_vn_geprueft()!="")
			projekt_->vn_zu_bewilligung();
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte geben Sie an wann der Verwendungsnachweis eingereicht wurde.","Unvollständiger Eintrag");
}

void project_form::button10_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ fremdfoerdermittel = gcnew fremdfoerdermittel_form(projekt_->get_fremdfoerderung(),vn_einger_,load_std_);
	fremdfoerdermittel->ShowDialog();
	show_project();
}

void project_form::btn_save_Click(System::Object^  sender, System::EventArgs^  e)
{
	bool regular_entry=true;
	
	if(bezeichnung->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie eine Bezeichnung an.","Unvollständiger Eintrag");
		regular_entry=false;
	}
	
	if(bew_ztr->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie einen gültigen Bewilligungszeitraum an. (TT.MM.JJJJ)","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(foeuvh->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie einen gültigen förderunschädlichen Vorhabensbeginn an. (TT.MM.JJJJ oder leer)","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(gk_real->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein ein gültigen Betrag für die realen Gesamtkosten an.","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(gk_zuwendungsf->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein ein gültigen Betrag für die zuwendungsfähigen Gesamtkosten an.","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(aenderungsbescheid->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein gültiges Datum für den Änderungsbescheid an. (TT.MM.JJJJ oder leer)","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(vn_eingereicht->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein gültiges Datum für den eingereichten Verwendungsnachweis an. (TT.MM.JJJJ oder leer)","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(vn_geprueft->BackColor==Color::FromName("LavenderBlush"))
	{
		Windows::Forms::MessageBox::Show("Bitte geben Sie ein gültiges Datum für den geprüften Verwendungsnachweis an. (TT.MM.JJJJ oder leer)","Unvollständiger Eintrag");
		regular_entry=false;
	}

	if(regular_entry)
	{
		projekt_->save();
		Windows::Forms::MessageBox::Show("Speichern erfolgreich.","Projekt gespeichert");
		show_project();
	}
	else
		Windows::Forms::MessageBox::Show("Speichern nicht möglich.","Projekt unvollständig");
}

void project_form::btn_del_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ message = "Mit Löschen des Projektes gehen alle gesichterten Daten endgültig verloren.\nFortfahren?";
	String^ caption = "Wollen Sie das Projekt löschen?";
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	System::Windows::Forms::DialogResult result;
	result = MessageBox::Show( this, message, caption, buttons );
	if ( result == ::DialogResult::Yes )
	{
		projekt_->del();
		Windows::Forms::MessageBox::Show("Das Projekt wurde gelöscht.","Löschen erfolgreich");
		Close();
	}
}

void project_form::button5_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(load_std_)
	{
		bool is_saved=true;
		if(projekt_->get_db_id()==-1)
		{
			project_class^ test=gcnew project_class();
			test->set_stadt(projekt_->get_stadt());
			test->set_gebiet(projekt_->get_gebiet());
			test->set_kostengruppe(projekt_->get_kostengruppe());
			test->set_kostenart(projekt_->get_kostenart());
			test->set_sk_bha(projekt_->get_sk_bha());
			if(!projekt_->is_equal(test))
				is_saved=false;
		}
		else
		{
			is_saved=regular_entry();
			project_class^ test=gcnew project_class(projekt_->get_db_id());
			if(!projekt_->is_equal(test))
				is_saved=false;
		}
		if(is_saved)
			Close();
		else
		{
			String^ message = "Es sind nicht gespeicherte Änderungen vorhanden.\nJetzt speichern?";
			String^ caption = "Änderungen speichern?";
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;
			result = MessageBox::Show( this, message, caption, buttons );
			if ( result == ::DialogResult::Yes )
			{
				btn_save_Click(sender,e);
				is_saved=regular_entry();
				if(projekt_->get_db_id()==-1)
					is_saved=false;
				else
				{
					project_class^ test=gcnew project_class(projekt_->get_db_id());
					if(!projekt_->is_equal(test))
						is_saved=false;
				}
				if(is_saved)
					Close();
			}
			else
				Close();
		}
	}
	else
		Close();
}

void project_form::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::Label^  cache = gcnew System::Windows::Forms::Label();
	cache->Text="-1";
	Form^ choose_print = gcnew choose_printer(cache);
	choose_print->ShowDialog();
	if(cache->Text!="-1")
	{
		projekt_->print(cache->Text);
	}
}

// Swap Bewilligungen
void project_form::bewilligungen_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	if(load_std_)
	{
		allow_swap_=true;
		swap_this_=bewilligungen->SelectedIndex;
	}
}

void project_form::bewilligungen_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
{
	if(load_std_)
	{
		if(allow_swap_)
		{
			if(swap_this_!=-1 && bewilligungen->SelectedIndex!=-1)
				projekt_->swap_bewilligung(programme->Text,swap_this_,bewilligungen->SelectedIndex);
			allow_swap_=false;
			swap_this_=-1;
			show_project();
		}
	}
}

// Projekt anzeigen
void project_form::show_project()
{
	if(loaded_)
	{
		if(projekt_->get_db_id()!=-1)
			btn_del->Visible=true;
		else
			btn_del->Visible=false;
		
		// TextBox
		bezeichnung->Text=projekt_->get_bezeichnung();
		foeuvh->Text=projekt_->get_foeuvh();
		bew_ztr->Text=projekt_->get_bew_ztr();
		if(!gk_real->Focused)
			gk_real->Text=Decimal_to_string(projekt_->get_gk_real());
		if(!gk_zuwendungsf->Focused)
			gk_zuwendungsf->Text=Decimal_to_string(projekt_->get_gk_zuwendungsf());
		bemerkung->Text=projekt_->get_bemerkung();

		vn_eingereicht->Text=projekt_->get_vn_eingereicht();
		if(vn_eingereicht->Text=="")
		{
			vn_geprueft->Enabled=false;
			vn_geprueft->Text="Kein Verwendungsnachweis";
		}
		else
		{
			vn_geprueft->Enabled=true;
			vn_geprueft->Text=projekt_->get_vn_geprueft();
		}
		if(!load_std_)
			vn_geprueft->Enabled=false;

		aenderungsbescheid->Text=projekt_->get_aenderungsbescheid();

		// Berechnungen
		foerderbetrag->Text=Decimal_to_string(projekt_->get_gesamtfoerderung());
		mla->Text=Decimal_to_string(projekt_->get_mla());
		fremdfoerderung->Text=Decimal_to_string(projekt_->get_gesamtfremdfoerderung());
		bha_betrag->Text=Decimal_to_string(projekt_->get_bha());
		if(vn_eingereicht->Text!="")
			mehr_minderkosten->Text=Decimal_to_string(projekt_->get_mehr_minder_kosten());
		else
			mehr_minderkosten->Text="Kein Verwendungsnachweis";

		// ComboBox-Auswahl
		kostengruppe->Text=projekt_->get_kostengruppe();
		kostenart->Text=projekt_->get_kostenart();
		bha_sk->Text=projekt_->get_sk_bha();
		stadt->Text=projekt_->get_stadt();
		gebiet->Text=projekt_->get_gebiet();
		load_strasse();

		// ListBox
		int programme_index=programme->SelectedIndex;
		programme->Items->Clear();
		List<String^>^ programm_liste=projekt_->get_programme();
		if(programm_liste->Count!=0)
		{
			programme->Enabled=true;
			for each(String^ eintrag in programm_liste)
				programme->Items->Add(eintrag);
			if(programme_index<programm_liste->Count && programme_index!=-1)
				programme->SelectedIndex=programme_index;
			else
				programme->SelectedIndex=0;
			show_programm_eintrag();
		}
		else
		{
			bewilligungen->Items->Clear();
			programme->Enabled=false;
			bewilligungen->Enabled=false;
		}
	
		int adress_index=strassen->SelectedIndex;
		strassen->Items->Clear();
		List<String^>^ strassen_liste=projekt_->get_adressen();
		MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE Stadt='"+stadt->Text+"'");
		MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt.get_val(0,0)+" And Gebiet='"+gebiet->Text+"'");
		if(strassen_liste->Count!=0)
		{
			strassen->Enabled=true;
			/*for each(String^ eintrag in strassen_liste)
			{
				MyRecordSet RC_Chiffre("SELECT Chiffre FROM Strassen WHERE Gebiet_ID="+RC_Gebiet.get_val(0,0)+" AND Strasse='"+eintrag+"'");

				strassen->Items->Add(eintrag+" ["+RC_Chiffre.get_val(0,0)+"]");
			}*/
			if(adress_index<strassen_liste->Count && adress_index!=-1)
				strassen->SelectedIndex=adress_index;
			else
				strassen->SelectedIndex=0;
		}
		else
		{
			strassen->Enabled=false;
		}
	}
}

void project_form::show_programm_eintrag()
{
	if(loaded_)
	{
		int bewilligung_index=bewilligungen->SelectedIndex;
		bewilligungen->Items->Clear();
		List<String^>^ bewilligung_liste=projekt_->get_bewilligungen(programme->Text);

		if(bewilligung_liste->Count!=0)
		{
			bewilligungen->Enabled=true;
			for(int i=0;i<bewilligung_liste->Count;++i)
			{
				bewilligung_class^ bew=projekt_->get_bewilligung(programme->Text,i);
				Decimal summe=bew->get_mla()+bew->get_bund_land();
				bewilligungen->Items->Add("TB "+Convert::ToString(i+1)+" : "+bewilligung_liste[i]
												+" ("+Decimal_to_string(summe)+")");
			}
			if(bewilligung_index<bewilligung_liste->Count)
				bewilligungen->SelectedIndex=bewilligung_index;
			else
				bewilligungen->SelectedIndex=0;
		}
		else
			bewilligungen->Enabled=false;
	}
}

// TypTest
bool project_form::regular_entry()
{
	bool regular_entry=true;
	
	if(bezeichnung->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;
	
	if(bew_ztr->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	if(foeuvh->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	if(gk_real->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	if(gk_zuwendungsf->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	if(aenderungsbescheid->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	if(vn_eingereicht->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	if(vn_geprueft->BackColor==Color::FromName("LavenderBlush"))
		regular_entry=false;

	return regular_entry;
}

bool project_form::is_existent_in(List<String^>^ liste,String^ value)
{
	for each(String^ eintrag in liste)
		if(eintrag==value)
			return true;
	return false;
}