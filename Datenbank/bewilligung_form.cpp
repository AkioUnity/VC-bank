#include "StdAfx.h"

#include "MyRecordSet.h"
#include "helper.h"
#include "bewilligung_form.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

void bewilligung_form::bewilligung_form_Load(System::Object^  sender, System::EventArgs^  e)
{
	MyRecordSet RC("SELECT Value FROM Jahreseintraege");
	nr_part3->Items->Clear();
	for(int i=0;i<RC.get_row();++i)
		nr_part3->Items->Add(RC.get_val(i,0));
	show_bewilligung();

	if(vn_einger_)
	{
		bund_land->BackColor=Color::FromName("White");
		mla->BackColor=Color::FromName("White");
		bund_land->Enabled=false;
		mla->Enabled=false;
	}
	if( !load_)
	{
		bund_land->BackColor=Color::FromName("White");
		mla->BackColor=Color::FromName("White");
		nr_part2->BackColor=Color::FromName("White");
		nr_part3->BackColor=Color::FromName("White");
		vom->BackColor=Color::FromName("White");
		nr_part2->Enabled=false;
		nr_part3->Enabled=false;
		vom->Enabled=false;
		san_bed_ein->Enabled=false;
		bund_land->Enabled=false;
		mla->Enabled=false;

	}
}

void bewilligung_form::show_bewilligung()
{
	nr_part1->Text=bewilligung_->get_nr1();
	nr_part2->Text=bewilligung_->get_nr2();
    nr_part3->Text=bewilligung_->get_nr3();
	vom->Text=bewilligung_->get_vom();
	san_bed_ein->Checked=bewilligung_->get_san_bed_ein();
	bund_land->Text=Decimal_to_string(bewilligung_->get_bund_land());
	mla->Text=Decimal_to_string(bewilligung_->get_mla());
}

void bewilligung_form::bund_land_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=bund_land->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace("€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		bewilligung_->set_bund_land(Decimal(Convert::ToDouble(txt)));
		bund_land->BackColor=Color::FromName("White");
	}
	else
		bund_land->BackColor=Color::FromName("LavenderBlush");
}

void bewilligung_form::bund_land_Leave(System::Object^  sender, System::EventArgs^  e)
{
	bund_land->Text=Decimal_to_string(bewilligung_->get_bund_land());
}

void bewilligung_form::mla_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=mla->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace("€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		bewilligung_->set_mla(Decimal(Convert::ToDouble(txt)));
		bund_land->BackColor=Color::FromName("White");
	}
	else
		bund_land->BackColor=Color::FromName("LavenderBlush");
}

void bewilligung_form::mla_Leave(System::Object^  sender, System::EventArgs^  e)
{
	mla->Text=Decimal_to_string(bewilligung_->get_mla());
}

void bewilligung_form::vom_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if(check_if_date(vom->Text))
	{
		bewilligung_->set_vom(date_to_string(vom->Text));
		vom->BackColor=Color::FromName("White");
	}
	else
		vom->BackColor=Color::FromName("LavenderBlush");
}

void bewilligung_form::vom_Leave(System::Object^  sender, System::EventArgs^  e)
{
	vom->Text=bewilligung_->get_vom();
}

void bewilligung_form::nr_part3_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	bewilligung_->set_nr3(nr_part3->Text);
}

void bewilligung_form::nr_part2_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	if((check_if_number(nr_part2->Text) && nr_part2->Text->Length == 4)||(nr_part2->Text=="XXXX"))
	{
		nr_part2->BackColor=Color::FromName("White");
		bewilligung_->set_nr2(nr_part2->Text);
	}
	else
		nr_part2->BackColor=Color::FromName("LavenderBlush");
}

void bewilligung_form::btn_back_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(nr_part2->BackColor==Color::FromName("LavenderBlush") || vom->BackColor==Color::FromName("LavenderBlush"))
	{
		MessageBoxButtons buttons = MessageBoxButtons::YesNo;
		System::Windows::Forms::DialogResult result;
		result = MessageBox::Show( "Sollen die letzten gültigen Werte gesichtert werden?","Fehlerhafte Einträge", buttons );
		if(result==::DialogResult::Yes)
			Close();
	}
	else
		Close();
}

void bewilligung_form::san_bed_ein_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	bewilligung_->set_san_bed_ein(san_bed_ein->Checked);
}