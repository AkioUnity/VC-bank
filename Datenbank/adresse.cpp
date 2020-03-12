#include "StdAfx.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"
#include "adresse.h"


adresse::adresse(void):
	adr_(""),
	einzel_gesamt_kosten_(0),
	einzel_gesamt_foerderung_(0),
	einzel_gesamt_kosten_vn_(0),
	einzel_gesamt_foerderung_vn_(0)
{}

adresse::adresse(String^ adr):
	adr_(adr),
	einzel_gesamt_kosten_(0),
	einzel_gesamt_foerderung_(0),
	einzel_gesamt_kosten_vn_(0),
	einzel_gesamt_foerderung_vn_(0)
{}

// Getter
String^ adresse::get_adresse()
{
	return adr_;
}

Decimal adresse::get_einzel_gk()
{
	return einzel_gesamt_kosten_;
}

Decimal adresse::get_einzel_gf()
{	
	return einzel_gesamt_foerderung_;
}

Decimal adresse::get_einzel_gk_vn()
{
	return einzel_gesamt_kosten_vn_;
}

Decimal adresse::get_einzel_gf_vn()
{	
	return einzel_gesamt_foerderung_vn_;
}

// Setter
void adresse::set_einzel_gk(Decimal gk)
{
	einzel_gesamt_kosten_=gk;
}

void adresse::set_einzel_gf(Decimal gf)
{
	einzel_gesamt_foerderung_=gf;
}

void adresse::set_einzel_gk_vn(Decimal gk)
{
	einzel_gesamt_kosten_vn_=gk;
}

void adresse::set_einzel_gf_vn(Decimal gf)
{
	einzel_gesamt_foerderung_vn_=gf;
}

void adresse::bewilligung_zu_vn()
{
	einzel_gesamt_kosten_vn_=einzel_gesamt_kosten_;
	einzel_gesamt_foerderung_vn_=einzel_gesamt_foerderung_;
}

void adresse::vn_zu_bewilligung()
{
	einzel_gesamt_foerderung_=einzel_gesamt_foerderung_vn_;
	einzel_gesamt_kosten_=einzel_gesamt_kosten_vn_;
}


// Speichern, Laden
void adresse::save(String^ projekt_id)
{
	MyRecordSet RC("SELECT * FROM db_adressen");
	String^ new_id=Convert::ToString(RC.get_new_id());

	MyInsertStatement IS("INSERT INTO db_adressen(ID,Projekt_ID,adresse,ges_kosten,ges_foerder,ges_kosten_vn,ges_foerder_vn) VALUES("
								+ new_id +","// ID
								+ projekt_id +",'"// projekt_id
								+ adr_ +"','"// adresse
								+ Convert::ToString(einzel_gesamt_kosten_) +"','"// ges_kosten
								+ Convert::ToString(einzel_gesamt_foerderung_) +"','"// ges_foerder
								+ Convert::ToString(einzel_gesamt_kosten_vn_) +"','"// ges_kosten_vn
								+ Convert::ToString(einzel_gesamt_foerderung_vn_) +"')"// ges_foerder_vn
								);
}

void adresse::load(String^ adress_id)
{
	MyRecordSet RC("SELECT * FROM db_adressen WHERE ID="+adress_id);
	adr_=RC.get_val(0,2);
	einzel_gesamt_kosten_=Decimal(Convert::ToDouble(RC.get_val(0,3)));
	einzel_gesamt_foerderung_=Decimal(Convert::ToDouble(RC.get_val(0,4)));
	einzel_gesamt_kosten_vn_=Decimal(Convert::ToDouble(RC.get_val(0,5)));
	einzel_gesamt_foerderung_vn_=Decimal(Convert::ToDouble(RC.get_val(0,6)));
}

// ==
bool adresse::is_equal(adresse^ rhs)
{
	if(adr_!=rhs->adr_)
		return false;
	
	if(einzel_gesamt_kosten_!=rhs->einzel_gesamt_kosten_)
		return false;
	
	if(einzel_gesamt_foerderung_!=rhs->einzel_gesamt_foerderung_)
		return false;
	
	if(einzel_gesamt_kosten_vn_!=rhs->einzel_gesamt_kosten_vn_)
		return false;
	
	if(einzel_gesamt_foerderung_vn_!=rhs->einzel_gesamt_foerderung_vn_)
		return false;

	return true;
}

