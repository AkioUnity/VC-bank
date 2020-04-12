#include "StdAfx.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"
#include "fremdfoerderung_class.h"


fremdfoerderung_class::fremdfoerderung_class(void):
	betrag_(gcnew List<Decimal>),
	programm_(gcnew List<String^>)
{}

fremdfoerderung_class::fremdfoerderung_class(String^ projekt_id,bool is_vn):
	betrag_(gcnew List<Decimal>),
	programm_(gcnew List<String^>)
{
	load(projekt_id,is_vn);	
}

//Getter

Decimal fremdfoerderung_class::get_betrag()
{
	Decimal summe=0;
	for each(Decimal eintrag in betrag_)
		summe+=eintrag;
	return summe;
}

String^ fremdfoerderung_class::get_programm(int index)
{
	return programm_[index];
}

Decimal fremdfoerderung_class::get_betrag(int index)
{
	return betrag_[index];
}

List<String^>^ fremdfoerderung_class::get_all(bool show_betrag)
{
	List<String^>^ gesamt=gcnew List<String^>;
	if(show_betrag)
		for(int i=0;i<programm_->Count;++i)
			gesamt->Add(programm_[i]+" ( "+Convert::ToString(betrag_[i])+L" € )");
	else
		for(int i=0;i<programm_->Count;++i)
			gesamt->Add(programm_[i]);
	return gesamt;
}


//Setter
bool fremdfoerderung_class::add_programm(String^ programm, Decimal betrag)
{
	bool existent=false;
	for each(String^ eintrag in programm_)
		if(eintrag==programm)
			existent=true;
	if(existent)
		return false;
	else
	{
		programm_->Add(programm);
		betrag_->Add(betrag);
		return true;
	}
}

void fremdfoerderung_class::rem_programm(int removeat)
{
	programm_->RemoveAt(removeat);
	betrag_->RemoveAt(removeat);
}

// Speichern, Laden
void fremdfoerderung_class::save(String^ projekt_id,bool is_vn)
{
	String^ vn="0";
	if(is_vn)
		vn="1";
	for(int i=0;i<programm_->Count;++i)
	{
		MyRecordSet RC("Select * FROM db_Fremdfoerderungen");
		MyInsertStatement IS("INSERT INTO db_Fremdfoerderungen (ID,projekt_ID,programm,betrag,vn) VALUES ("
																+RC.get_new_id()	+","// ID
																+projekt_id			+",'"// projekt_ID
																+programm_[i]		+"','"// programm
																+betrag_[i]			+"','"// betrag
																+vn					+"')"// vn
																);
	}
}

void fremdfoerderung_class::load(String^ projekt_id,bool is_vn)
{
	String^ vn="0";
	if(is_vn)
		vn="1";

	MyRecordSet RC("Select * FROM db_Fremdfoerderungen WHERE projekt_ID="+projekt_id+" AND vn='"+vn+"'");
	for(int i=0;i<RC.get_row();++i)
	{
		programm_->Add(RC.get_val(i,2));
		betrag_->Add(Decimal(Convert::ToDouble(RC.get_val(i,3))));
	}
}


// ==
bool fremdfoerderung_class::is_equal(fremdfoerderung_class^ rhs)
{
	if(programm_->Count!=rhs->programm_->Count)
		return false;
	for(int i=0;i<programm_->Count;++i)
		if(programm_[i]!=rhs->programm_[i])
			return false;

	for(int i=0;i<betrag_->Count;++i)
		if(betrag_[i]!=rhs->betrag_[i])
			return false;

	return true;
}