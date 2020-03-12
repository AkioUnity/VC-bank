#include "StdAfx.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"
#include "programm.h"


programm::programm(void):
	name_(""),
	nr_(""),
	bewilligungen_(gcnew List<bewilligung_class^>)
{}

programm::programm(String^ name, String^ nr):
	name_(name),
	nr_(nr),
	bewilligungen_(gcnew List<bewilligung_class^>)
{}

// Setter

void programm::set_name(String^ input)
{
	name_=input;
}

void programm::add_bewilligung()
{
	bewilligungen_->Add(gcnew bewilligung_class(nr_));
}

void programm::rem_bewilligung(int removeat)
{
	bewilligungen_->RemoveAt(removeat);
}

void programm::bewilligung_zu_vn()
{
	for each(bewilligung_class^ eintrag in bewilligungen_)
		eintrag->bewilligung_zu_vn();
}

void programm::vn_zu_bewilligung()
{
	for each(bewilligung_class^ eintrag in bewilligungen_)
		eintrag->vn_zu_bewilligung();
}

// Getter

String^ programm::get_name()
{
	return name_;
}

bewilligung_class^ programm::get_bewilligung(int index)
{
	return bewilligungen_[index];
}

List<String^>^ programm::get_bewilligungen()
{
	List<String^>^ bewilligungen = gcnew List<String^>;
	for each(bewilligung_class^ eintrag in bewilligungen_)
		bewilligungen->Add(eintrag->get_nr());
	return bewilligungen;
}

// Berechnungen

Decimal programm::get_mla()
{
	Decimal summe=0;
	for each(bewilligung_class^ eintrag in bewilligungen_)
		summe+=eintrag->get_mla();
	return summe;
}

Decimal programm::get_mla_vn()
{
	Decimal summe=0;
	for each(bewilligung_class^ eintrag in bewilligungen_)
		summe+=eintrag->get_mla_vn();
	return summe;
}

Decimal programm::get_bund_land()
{
	Decimal summe=0;
	for each(bewilligung_class^ eintrag in bewilligungen_)
		summe+=eintrag->get_bund_land();
	return summe;
}

Decimal programm::get_bund_land_vn()
{
	Decimal summe=0;
	for each(bewilligung_class^ eintrag in bewilligungen_)
		summe+=eintrag->get_bund_land_vn();
	return summe;
}

// Swap Bewilligung
void programm::swap_bewilligung(int index1 ,int index2)
{
	bewilligung_class^ bewilligung1=bewilligungen_[index1];
	bewilligungen_[index1]=bewilligungen_[index2];
	bewilligungen_[index2]=bewilligung1;
}

// Speichern, Laden
void programm::save(String^ projekt_id)
{
	MyRecordSet RC("SELECT * FROM db_programme");
	String^ new_id=Convert::ToString(RC.get_new_id());
	MyInsertStatement IS("INSERT INTO db_programme(ID,projekt_ID,name,nr) VALUES("
								+ new_id +","// ID
								+ projekt_id +",'"// projekt_ID
								+ name_ +"','"// name
								+ nr_ +"')"// nr
								);

	for each(bewilligung_class^ eintrag in bewilligungen_)
		eintrag->save(new_id);
}

void programm::load(String^ programm_id)
{	
	MyRecordSet RC("SELECT * FROM db_programme WHERE ID="+programm_id);
	name_=RC.get_val(0,2);
	nr_=RC.get_val(0,3);
	MyRecordSet RC_bew("SELECT ID FROM db_programme_bewilligung WHERE programm_ID="+programm_id);
	for(int i=0;i<RC_bew.get_row();++i)
	{
		bewilligungen_->Add(gcnew bewilligung_class);
		bewilligungen_[i]->load(RC_bew.get_val(i,0));
	}
}

//==
bool programm::is_equal(programm^ rhs)
{
	if(name_!=rhs->name_)
		return false;

	if(nr_!=rhs->nr_)
		return false;

	if(bewilligungen_->Count!=rhs->bewilligungen_->Count)
		return false;

	for(int i=0;i<bewilligungen_->Count;++i)
		if(!bewilligungen_[i]->is_equal(rhs->bewilligungen_[i]))
			return false;

	return true;
}