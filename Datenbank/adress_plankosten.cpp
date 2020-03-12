#include "StdAfx.h"
#include "adress_plankosten.h"
#include "helper.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

void adress_plankosten::adress_plankosten_Load(System::Object^  sender, System::EventArgs^  e)
{
	l_Adresse->Text=adr_->get_adresse();
	tB_kosten->Text=Decimal_to_string(adr_->get_einzel_gk());
	tB_foerder->Text=Decimal_to_string(adr_->get_einzel_gf());
	if(vn_einger_ || !load_)
	{
		tB_kosten->Enabled=false;
		tB_foerder->Enabled=false;
		tB_kosten->BackColor=Color::FromName("White");
		tB_foerder->BackColor=Color::FromName("White");
	}
}

// TextChange
void adress_plankosten::tB_kosten_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=tB_kosten->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace("€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		adr_->set_einzel_gk(Decimal(Convert::ToDouble(txt)));
		tB_kosten->BackColor=Color::FromName("White");
	}
	else
		tB_kosten->BackColor=Color::FromName("LavenderBlush");
}

void adress_plankosten::tB_kosten_Leave(System::Object^  sender, System::EventArgs^  e)
{
	tB_kosten->Text=Decimal_to_string(adr_->get_einzel_gk());
}

void adress_plankosten::tB_foerder_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=tB_foerder->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace("€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		adr_->set_einzel_gf(Decimal(Convert::ToDouble(txt)));
		tB_foerder->BackColor=Color::FromName("White");
	}
	else
		tB_foerder->BackColor=Color::FromName("LavenderBlush");
}

void adress_plankosten::tB_foerder_Leave(System::Object^  sender, System::EventArgs^  e)
{
	tB_foerder->Text=Decimal_to_string(adr_->get_einzel_gf());
}

// Buttons
void adress_plankosten::btn_back_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}