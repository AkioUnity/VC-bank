#include "StdAfx.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"
#include "bewilligung_class.h"


bewilligung_class::bewilligung_class(void):
	nr1_("XXXX"),
	nr2_("XXXX"),
	nr3_("XX"),
	vom_(""),
	mla_(0),
	bund_land_(0),
	 mla_vn_(0),
	bund_land_vn_(0),
	san_bed_ein_(false)
{}

bewilligung_class::bewilligung_class(String^ nr1):
	nr1_(nr1),
	nr2_("XXXX"),
	nr3_("XX"),
	vom_(""),
	mla_(0),
	bund_land_(0),
	mla_vn_(0),
	bund_land_vn_(0),
	san_bed_ein_(false)
{}

// Setter

void bewilligung_class::set_nr2(String^ nr2)
{
	nr2_=nr2;
}

void bewilligung_class::set_nr3(String^ nr3)
{
	nr3_=nr3;
}

void bewilligung_class::set_vom(String^ vom)
{
	vom_=vom;
}

void bewilligung_class::set_mla(Decimal mla)
{
	mla_=mla;
}

void bewilligung_class::set_mla_vn(Decimal mla)
{
	mla_vn_=mla;
}

void bewilligung_class::set_bund_land(Decimal bund_land)
{
	bund_land_=bund_land;
}

void bewilligung_class::set_bund_land_vn(Decimal bund_land)
{
	bund_land_vn_=bund_land;
}

void bewilligung_class::set_san_bed_ein(bool san_bed_ein)
{
	san_bed_ein_=san_bed_ein;
}


void bewilligung_class::bewilligung_zu_vn()
{
	mla_vn_=mla_;
	bund_land_vn_=bund_land_;
}

void bewilligung_class::vn_zu_bewilligung()
{
	mla_=mla_vn_;
	bund_land_=bund_land_vn_;
}

// Getter

String^ bewilligung_class::get_nr()
{
	return nr1_+" - "+nr2_+" / "+nr3_;
}

String^ bewilligung_class::get_nr1()
{
	return nr1_;
}

String^ bewilligung_class::get_nr2()
{
	return nr2_;
}

String^ bewilligung_class::get_nr3()
{
	return nr3_;
}
String^ bewilligung_class::get_vom()
{
	return vom_;
}

Decimal bewilligung_class::get_mla()
{
	return mla_;
}

Decimal bewilligung_class::get_mla_vn()
{
	return mla_vn_;
}

Decimal bewilligung_class::get_bund_land()
{
	return bund_land_;
}

Decimal bewilligung_class::get_bund_land_vn()
{
	return bund_land_vn_;
}

bool bewilligung_class::get_san_bed_ein()
{
	return san_bed_ein_;
}

// Speichern, Laden
void bewilligung_class::save(String^ programm_id)
{
	MyRecordSet RC("SELECT * FROM db_programme_bewilligung");
	String^ new_id=Convert::ToString(RC.get_new_id());
	String^ san_bed;
	if(san_bed_ein_)
		san_bed="1";
	else
		san_bed="0";
	MyInsertStatement IS("INSERT INTO db_programme_bewilligung(ID,programm_ID,nr1,nr2,nr3,vom,mla,mla_vn,bund_land,bund_land_vn,san_bed_ein) VALUES("
								+ new_id +","// ID
								+ programm_id +",'"// programm_ID
								+ nr1_ +"','"// nr1
								+ nr2_ +"','"// nr2
								+ nr3_ +"','"// nr3
								+ vom_ +"','"// vom
								+ Convert::ToString(mla_) +"','"// mla
								+ Convert::ToString(mla_vn_) +"','"// mla_vn
								+ Convert::ToString(bund_land_) +"','"// bund_land
								+ Convert::ToString(bund_land_vn_) +"','"// bund_land_vn
								+ san_bed +"')"// san_bed_ein
								);
}

void bewilligung_class::load(String^ bew_id)
{	
	MyRecordSet RC("SELECT * FROM db_programme_bewilligung WHERE ID="+bew_id);
	nr1_=RC.get_val(0,2);
	nr2_=RC.get_val(0,3);
	nr3_=RC.get_val(0,4);
	vom_=RC.get_val(0,5);
	mla_=Decimal(Convert::ToDouble(RC.get_val(0,6)));
	mla_vn_=Decimal(Convert::ToDouble(RC.get_val(0,7)));
	bund_land_=Decimal(Convert::ToDouble(RC.get_val(0,8)));
	bund_land_vn_=Decimal(Convert::ToDouble(RC.get_val(0,9)));
	if(RC.get_val(0,10)=="1")
		san_bed_ein_=true;
	else
		san_bed_ein_=false;
}

//==
bool bewilligung_class::is_equal(bewilligung_class^ rhs)
{
	if(nr1_!=rhs->nr1_)
		return false;

	if(nr2_!=rhs->nr2_)
		return false;
	
	if(nr3_!=rhs->nr3_)
		return false;

	if(vom_!=rhs->vom_)
		return false;

	if(mla_!=rhs->mla_)
		return false;

	if(mla_vn_!=rhs->mla_vn_)
		return false;

	if(bund_land_!=rhs->bund_land_)
		return false;

	if(bund_land_vn_!=rhs->bund_land_vn_)
		return false;

	if(san_bed_ein_!=rhs->san_bed_ein_)
		return false;

	return true;
}