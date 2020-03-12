#include "StdAfx.h"
#include "MyRecordSet.h"
#include "MyInsertStatement.h"
#include "project_class.h"
#include "choose_printer.h"
#include "helper.h"

project_class::project_class(void):
	db_id_(-1),
	gk_real_(0),
	gk_zuwendungsf_(0),
	gk_real_vn_(0),
	gk_zuwendungsf_vn_(0),
	bezeichnung_(""),
	foeuvh_(""),
	bew_ztr_(""),
	kostengruppe_(""),
	kostenart_(""),
	sk_bha_(""),
	vn_eingereicht_(""),
	vn_geprueft_(""),
	aenderungsbescheid_(""),
	stadt_(""),
	gebiet_(""),
	bemerkung_(""),
	programme_(gcnew List<programm^>),
	adressen_(gcnew List<adresse^>),
	fremdfoerderungen_vn_(gcnew fremdfoerderung_class()),
	fremdfoerderungen_(gcnew fremdfoerderung_class()),
	act_entry(0),
	act_program(0)
{}

project_class::project_class(int db_id):
	db_id_(db_id),
	gk_real_(0),
	gk_zuwendungsf_(0),
	gk_real_vn_(0),
	gk_zuwendungsf_vn_(0),
	bezeichnung_(""),
	foeuvh_(""),
	bew_ztr_(""),
	kostengruppe_(""),
	kostenart_(""),
	sk_bha_(""),
	vn_eingereicht_(""),
	vn_geprueft_(""),
	aenderungsbescheid_(""),
	stadt_(""),
	gebiet_(""),
	bemerkung_(""),
	programme_(gcnew List<programm^>),
	adressen_(gcnew List<adresse^>),
	fremdfoerderungen_vn_(gcnew fremdfoerderung_class(Convert::ToString(db_id),true)),
	fremdfoerderungen_(gcnew fremdfoerderung_class(Convert::ToString(db_id),false)),
	act_entry(0),
	act_program(0)
{
	load();	
}

// Setter
void project_class::set_bezeichnung(String^ input)
{
	bezeichnung_=input;
}

void project_class::set_foeuvh(String^ input)
{
	foeuvh_=input;
}

void project_class::set_bew_ztr(String^ input)
{
	bew_ztr_=input;
}

void project_class::set_kostengruppe(String^ input)
{
	kostengruppe_=input;
}

void project_class::set_kostenart(String^ input)
{
	kostenart_=input;
}

void project_class::set_gk_real(Decimal input)
{
	gk_real_=input;
}

void project_class::set_gk_zuwendungsf(Decimal input)
{
	gk_zuwendungsf_=input;
}

void project_class::set_gk_real_vn(Decimal input)
{
	gk_real_vn_=input;
}

void project_class::set_gk_zuwendungsf_vn(Decimal input)
{
	gk_zuwendungsf_vn_=input;
}

void project_class::set_sk_bha(String^ input)
{
	sk_bha_=input;
}

void project_class::set_vn_eingereicht(String^ input)
{
	vn_eingereicht_=input;
}

void project_class::set_vn_geprueft(String^ input)
{
	vn_geprueft_=input;
}

void project_class::set_aenderungsbescheid(String^ input)
{
	aenderungsbescheid_=input;
}

void project_class::set_stadt(String^ input)
{
	stadt_=input;
}

void project_class::set_gebiet(String^ input)
{
	gebiet_=input;
}

void project_class::set_bemerkung(String^ input)
{
	bemerkung_=input;
}

void project_class::add_adresse(String^ adr)
{
	adressen_->Add(gcnew adresse(adr));
}

void project_class::rem_adresse(String^ adr)
{
	adressen_->RemoveAt(get_adress_index(adr));
}

void project_class::clear_adressen()
{
	adressen_->Clear();
}

void project_class::add_programm(String^ programmname, String^ programmnr)
{
	programme_->Add(gcnew programm(programmname,programmnr));
}

void project_class::rem_programm(String^ programmname)
{
	programme_->RemoveAt(get_programm_index(programmname));
}

void project_class::clear_programm()
{
	programme_->Clear();
}

void project_class::add_bewilligung(String^ programmname)
{
	int index=get_programm_index(programmname);
	programme_[index]->add_bewilligung();
}

void project_class::rem_bewilligung(String^ programmname, int index)
{
	int programm_index=get_programm_index(programmname);
	programme_[programm_index]->rem_bewilligung(index);
}

void project_class::bewilligung_zu_vn()
{
	for each(programm^ eintrag in programme_)
		eintrag->bewilligung_zu_vn();
	for each(adresse^ adr in adressen_)
		adr->bewilligung_zu_vn();

	fremdfoerderungen_vn_->programm_->Clear();
	fremdfoerderungen_vn_->betrag_->Clear();
	for(int i=0;i<fremdfoerderungen_->programm_->Count;++i)
	{
		fremdfoerderungen_vn_->programm_->Add(fremdfoerderungen_->programm_[i]);
		fremdfoerderungen_vn_->betrag_->Add(fremdfoerderungen_->betrag_[i]);
	}

	gk_real_vn_=gk_real_;
	gk_zuwendungsf_vn_=gk_zuwendungsf_;
}

void project_class::vn_zu_bewilligung()
{
	for each(programm^ eintrag in programme_)
		eintrag->vn_zu_bewilligung();
	for each(adresse^ adr in adressen_)
		adr->vn_zu_bewilligung();

	fremdfoerderungen_->programm_->Clear();
	fremdfoerderungen_->betrag_->Clear();
	for(int i=0;i<fremdfoerderungen_vn_->programm_->Count;++i)
	{
		fremdfoerderungen_->programm_->Add(fremdfoerderungen_vn_->programm_[i]);
		fremdfoerderungen_->betrag_->Add(fremdfoerderungen_vn_->betrag_[i]);
	}

	gk_real_=gk_real_vn_;
	gk_zuwendungsf_=gk_zuwendungsf_vn_;
}

// Getter

String^ project_class::get_stadt()
{
	return stadt_;
}

String^ project_class::get_gebiet()
{
	return gebiet_;
}

String^ project_class::get_bemerkung()
{
	return bemerkung_;
}

String^ project_class::get_bezeichnung()
{
	return bezeichnung_;
}

String^ project_class::get_foeuvh()
{
	return foeuvh_;
}

String^ project_class::get_bew_ztr()
{
	return bew_ztr_;
}

String^ project_class::get_kostengruppe()
{
	return kostengruppe_;
}

String^ project_class::get_kostenart()
{
	return kostenart_;
}

Decimal project_class::get_gk_real()
{
	return gk_real_;
}

Decimal project_class::get_gk_zuwendungsf()
{
	return gk_zuwendungsf_;
}

Decimal project_class::get_gk_real_vn()
{
	return gk_real_vn_;
}

Decimal project_class::get_gk_zuwendungsf_vn()
{
	return gk_zuwendungsf_vn_;
}

String^ project_class::get_sk_bha()
{
	return sk_bha_;
}

String^ project_class::get_vn_eingereicht()
{
	return vn_eingereicht_;
}

String^ project_class::get_vn_geprueft()
{
	return vn_geprueft_;
}

String^ project_class::get_aenderungsbescheid()
{
	return aenderungsbescheid_;
}

int project_class::get_db_id()
{
	return db_id_;
}

int project_class::get_programm_index(String^ programmname)
{
	for(int i=0;i<programme_->Count;++i)
		if(programme_[i]->get_name()==programmname)
			return i;
	return -1;
}

int project_class::get_adress_index(String^ adressname)
{
	for(int i=0;i<adressname->Length;++i)
		if(adressname[i]=='[')
			adressname=adressname->Substring(0,i-1);

	adressname=adressname->Trim();
	
	for(int i=0;i<adressen_->Count;++i)
		if(adressen_[i]->get_adresse()->Trim()==adressname)
			return i;
	return -1;
}

adresse^ project_class::get_adresse(String^ adr)
{
	return adressen_[get_adress_index(adr)];
}

List<String^>^ project_class::get_adressen()
{
	List<String^>^ adressen_liste = gcnew List<String^>;
	for each(adresse^ eintrag in adressen_)
		adressen_liste->Add(eintrag->get_adresse());
	return adressen_liste;	
}

List<String^>^ project_class::get_bewilligungen(String^ programmname)
{
	int index=get_programm_index(programmname);
	return programme_[index]->get_bewilligungen();
}

List<String^>^ project_class::get_programme()
{
	List<String^>^ programme = gcnew List<String^>;
	for each(programm^ eintrag in programme_)
		programme->Add(eintrag->get_name());
	return programme;
}

bewilligung_class^  project_class::get_bewilligung(String^ programmname, int index)
{
	int programmindex=get_programm_index(programmname);
	return programme_[programmindex]->get_bewilligung(index);
}

fremdfoerderung_class^ project_class::get_fremdfoerderung()
{
	return fremdfoerderungen_;
}

fremdfoerderung_class^ project_class::get_fremdfoerderung_vn()
{
	return fremdfoerderungen_vn_;
}

// Berechnungen
Decimal project_class::get_mla()
{
	Decimal summe=0;
	for each(programm^ eintrag in programme_)
		summe+=eintrag->get_mla();
	return summe;
}

Decimal project_class::get_bund_land()
{
	Decimal summe=0;
	for each(programm^ eintrag in programme_)
		summe+=eintrag->get_bund_land();
	return summe;
}

Decimal project_class::get_mla_vn()
{
	Decimal summe=0;
	for each(programm^ eintrag in programme_)
		summe+=eintrag->get_mla_vn();
	return summe;
}

Decimal project_class::get_bund_land_vn()
{
	Decimal summe=0;
	for each(programm^ eintrag in programme_)
		summe+=eintrag->get_bund_land_vn();
	return summe;
}

Decimal project_class::get_gesamtfoerderung()
{
	return get_mla()+get_bund_land();
}

Decimal project_class::get_gesamtfremdfoerderung()
{
	return fremdfoerderungen_->get_betrag();
}

Decimal project_class::get_gesamtfremdfoerderung_vn()
{
	return fremdfoerderungen_vn_->get_betrag();
}

Decimal project_class::get_bha()
{
	return gk_real_-(get_gesamtfoerderung()+get_gesamtfremdfoerderung());
}

Decimal project_class::get_mehr_minder_kosten()
{
	return (get_mla_vn()+get_bund_land_vn())-(get_mla()+get_bund_land());
}

// Swap Bewilligung
void project_class::swap_bewilligung(String^ programmname ,int index1 ,int index2)
{
	programme_[get_programm_index(programmname)]->swap_bewilligung(index1,index2);
}

// ==
bool project_class::is_equal(project_class^ rhs)
{
	if(bemerkung_!=rhs->bemerkung_)
		return false;
	if(gk_real_!=rhs->gk_real_)
		return false;
	if(gk_zuwendungsf_!=rhs->gk_zuwendungsf_)
		return false;
	if(gk_real_vn_!=rhs->gk_real_vn_)
		return false;
	if(gk_zuwendungsf_vn_!=rhs->gk_zuwendungsf_vn_)
		return false;
	if(bezeichnung_!=rhs->bezeichnung_)
		return false;
	if(foeuvh_!=rhs->foeuvh_)
		return false;
	if(bew_ztr_!=rhs->bew_ztr_)
		return false;
	if(kostengruppe_!=rhs->kostengruppe_)
		return false;
	if(kostenart_!=rhs->kostenart_)
		return false;
	if(sk_bha_!=rhs->sk_bha_)
		return false;
	if(vn_eingereicht_!=rhs->vn_eingereicht_)
		return false;
	if(vn_geprueft_!=rhs->vn_geprueft_)
		return false;
	if(aenderungsbescheid_!=rhs->aenderungsbescheid_)
		return false;
	if(stadt_!=rhs->stadt_)
		return false;
	if(gebiet_!=rhs->gebiet_)
		return false;

	if(!fremdfoerderungen_->is_equal(rhs->fremdfoerderungen_))
		return false;
	if(!fremdfoerderungen_vn_->is_equal(rhs->fremdfoerderungen_vn_))
		return false;

	if(programme_->Count!=rhs->programme_->Count)
		return false;
	for(int i=0;i<programme_->Count;++i)
		if(!programme_[i]->is_equal(rhs->programme_[i]))
			return false;

	if(adressen_->Count!=rhs->adressen_->Count)
		return false;
	for(int i=0;i<adressen_->Count;++i)
		if(!adressen_[i]->is_equal(rhs->adressen_[i]))
			return false;

	return true;
}

// Speichern, Laden, Löschen
void project_class::save()
{
	if(db_id_==-1)
	{
		MyRecordSet RC("SELECT * FROM db_projekte");
		db_id_=RC.get_new_id();
	}
	else
		del();
	
	MyInsertStatement IS("INSERT INTO db_projekte(ID,gk_real,gk_zuwendungsf,gk_real_vn,gk_zuwendungsf_vn,bezeichnung,foeuvh,bew_ztr,kostengruppe,kostenart,sk_bha,vn_einger,vn_gepr,aenderungsbescheid,stadt,gebiet,bemerkung) VALUES("
						+ Convert::ToString(db_id_)	+",'"// ID
						+ gk_real_					+"','"// gk_real
						+ gk_zuwendungsf_			+"','"// gk_zuwendungsf
						+ gk_real_vn_				+"','"// gk_real_vn
						+ gk_zuwendungsf_vn_		+"','"// gk_zuwendungsf_vn
						+ bezeichnung_				+"','"// bezeichnung
						+ foeuvh_					+"','"// foevuh
						+ bew_ztr_					+"','"// bew_ztr
						+ kostengruppe_				+"','"// kostengruppe
						+ kostenart_				+"','"// kostenart
						+ sk_bha_					+"','"// sk_bha
						+ vn_eingereicht_			+"','"// vn_einger
						+ vn_geprueft_				+"','"// vn_gepr
						+ aenderungsbescheid_		+"','"// aenderungsbescheid
						+ stadt_					+"','"// stadt
						+ gebiet_					+"','" // gebiet
						+ bemerkung_				+"')" // bemerkung
						);


	for each(programm^ eintrag in programme_)
		eintrag->save(Convert::ToString(db_id_));

	for each(adresse^ eintrag in adressen_)
		eintrag->save(Convert::ToString(db_id_));

	fremdfoerderungen_->save(Convert::ToString(db_id_),false);
	fremdfoerderungen_vn_->save(Convert::ToString(db_id_),true);
}

void project_class::del()
{
	if(db_id_!=-1)
	{
		// Projekt
		MyInsertStatement RM("DELETE * FROM db_projekte WHERE ID="+Convert::ToString(db_id_));

		// Fremdfoerderung
		MyInsertStatement RM_fremdfoerder("DELETE * FROM db_Fremdfoerderungen WHERE projekt_ID="+Convert::ToString(db_id_));
		
		// Programme
		MyRecordSet RC_programme("SELECT ID FROM db_programme WHERE projekt_ID="+Convert::ToString(db_id_));
		for(int i=0;i<RC_programme.get_row();++i)
		{
			// Programm-Bewilligungen
			MyInsertStatement RM_programme_bewilligung("DELETE * FROM db_programme_bewilligung WHERE programm_ID="+RC_programme.get_val(i,0));
		}
		MyInsertStatement RM_programme("DELETE * FROM db_programme WHERE projekt_ID="+Convert::ToString(db_id_));

		// Adressen
		MyInsertStatement RM_adressen("DELETE * FROM db_adressen WHERE Projekt_ID="+Convert::ToString(db_id_));
	}
}

void project_class::load()
{
	if(db_id_!=-1)
	{
		MyRecordSet RC("SELECT * FROM db_projekte WHERE ID="+Convert::ToString(db_id_));
		gk_real_=Decimal(Convert::ToDouble(RC.get_val(0,1)));
		gk_zuwendungsf_=Decimal(Convert::ToDouble(RC.get_val(0,2)));
		gk_real_vn_=Decimal(Convert::ToDouble(RC.get_val(0,3)));
		gk_zuwendungsf_vn_=Decimal(Convert::ToDouble(RC.get_val(0,4)));
		bezeichnung_=RC.get_val(0,5);
		foeuvh_=RC.get_val(0,6);
		bew_ztr_=RC.get_val(0,7);
		kostengruppe_=RC.get_val(0,8);
		kostenart_=RC.get_val(0,9);
		sk_bha_=RC.get_val(0,10);
		vn_eingereicht_=RC.get_val(0,11);
		vn_geprueft_=RC.get_val(0,12);
		aenderungsbescheid_=RC.get_val(0,13);
		stadt_=RC.get_val(0,14);
		gebiet_=RC.get_val(0,15);
		bemerkung_=RC.get_val(0,16);
		
		MyRecordSet RC_Adr("SELECT ID FROM db_adressen WHERE Projekt_ID="+Convert::ToString(db_id_));
		for(int i=0;i<RC_Adr.get_row();++i)
		{
			adressen_->Add(gcnew adresse);
			adressen_[i]->load(RC_Adr.get_val(i,0));
		}

		MyRecordSet RC_Prog("SELECT ID FROM db_programme WHERE projekt_ID="+Convert::ToString(db_id_));
		for(int i=0;i<RC_Prog.get_row();++i)
		{
			programme_->Add(gcnew programm);
			programme_[i]->load(RC_Prog.get_val(i,0));
		}

		// Fremdfoerderung wird durch und im Konstruktor geladen
	}
}


void project_class::print(String^ printer)
{
		page_count_=0;
		max_pages_=4;
		pages=0;

		System::Drawing::Printing::PrintDocument^  printDocument1=gcnew System::Drawing::Printing::PrintDocument;
		printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &project_class::printDocument1_PrintPage);

		printDocument1->PrinterSettings->PrinterName=printer;
		printDocument1->DefaultPageSettings->Landscape=false;
		printDocument1->DocumentName="Projektübersicht";
		printDocument1->DefaultPageSettings->Margins->Top=25;
		printDocument1->DefaultPageSettings->Margins->Bottom=25;
		printDocument1->DefaultPageSettings->Margins->Right=25;
		printDocument1->DefaultPageSettings->Margins->Left=25;
		printDocument1->OriginAtMargins=true;
		printDocument1->Print();
}

void project_class::printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e)
{
	++pages;
	e->Graphics->PageScale =0.95;
	switch(page_count_)
	{
	case  0 :
		create_page_header(e,"Übersicht");
		create_main(e);
		page_count_++;
		break;
	case  1 :
		create_page_header(e,"Fremdförderungen");
		create_ff(e);		
		break;
	case  2 :
		create_page_header(e,"Bewilligungen");
		create_bew(e);		
		break;
	case  3 :
		create_page_header(e,"Adressen");
		create_adress(e);
		break;
	}

	create_page_sign(e);
	
	e->HasMorePages=page_count_<max_pages_;
}

void project_class::create_main(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	// Fonds
	System::Drawing::Font^ std_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ bold_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	int s_1=10;
	int s_2=50;
	int s_3=500;
	int s_abs=250;
	int s_abs_2=120;

	e->Graphics->DrawString("Stadt",bold_format,Brushes::Black, s_1, 70);
	e->Graphics->DrawString(stadt_,std_format,Brushes::Black, s_1+s_abs, 70);	

	e->Graphics->DrawString("Gebiet",bold_format,Brushes::Black, s_1, 90);
	e->Graphics->DrawString(gebiet_,std_format,Brushes::Black, s_1+s_abs, 90);

	e->Graphics->DrawString("Förderunschädlicher Vorhabensbeginn",bold_format,Brushes::Black, s_1, 115);
	if(foeuvh_!="")
		e->Graphics->DrawString(foeuvh_,std_format,Brushes::Black, s_1+s_abs, 115);
	else
		e->Graphics->DrawString("-",std_format,Brushes::Black, s_1+s_abs, 115);

	e->Graphics->DrawString("Bewilligungszeitraum",bold_format,Brushes::Black, s_1, 135);
		if(bew_ztr_!="")
		e->Graphics->DrawString(bew_ztr_,std_format,Brushes::Black, s_1+s_abs, 135);
	else
		e->Graphics->DrawString("-",std_format,Brushes::Black, s_1+s_abs, 135);

	e->Graphics->DrawString("Kostengruppe",bold_format,Brushes::Black, s_1, 160);
	e->Graphics->DrawString(kostengruppe_,std_format,Brushes::Black, s_1+s_abs, 160);
	
	e->Graphics->DrawString("Kostenart",bold_format,Brushes::Black, s_1, 180);
	e->Graphics->DrawString(kostenart_,std_format,Brushes::Black, s_1+s_abs, 180);

	e->Graphics->DrawString("Kosten",bold_format,Brushes::Black, s_1, 205);
	e->Graphics->DrawString("reale Gesamtkosten",bold_format,Brushes::Black, s_2, 225);
	e->Graphics->DrawString(Decimal_to_string(get_gk_real()),std_format,Brushes::Black, s_1+s_abs, 225);
	e->Graphics->DrawString("zuwendungsfähige Gesamtkosten",bold_format,Brushes::Black, s_2, 245);
	e->Graphics->DrawString(Decimal_to_string(get_gk_zuwendungsf()),std_format,Brushes::Black, s_1+s_abs, 245);
	e->Graphics->DrawString("Gesamtförderung",bold_format,Brushes::Black, s_2, 265);
	e->Graphics->DrawString(Decimal_to_string(get_gesamtfoerderung()),std_format,Brushes::Black, s_1+s_abs, 265);
	e->Graphics->DrawString("Gesamt Mitleistungsanteil",bold_format,Brushes::Black, s_2, 285);
	e->Graphics->DrawString(Decimal_to_string(get_mla()),std_format,Brushes::Black, s_1+s_abs, 285);
	e->Graphics->DrawString("Gesamt Fremdförderung",bold_format,Brushes::Black, s_2, 305);
	e->Graphics->DrawString(Decimal_to_string(get_gesamtfremdfoerderung()),std_format,Brushes::Black, s_1+s_abs, 305);
	e->Graphics->DrawString("Mehr-/Minderkosten",bold_format,Brushes::Black, s_2, 325);
	if(vn_eingereicht_!="")
		e->Graphics->DrawString(Decimal_to_string(get_mehr_minder_kosten()),std_format,Brushes::Black, s_1+s_abs, 325);
	else
		e->Graphics->DrawString("Kein Verwendungsnachweis",std_format,Brushes::Black, s_1+s_abs, 325);

	e->Graphics->DrawString("Bauherrenanteil",bold_format,Brushes::Black, s_1, 350);
	e->Graphics->DrawString("Betrag",bold_format,Brushes::Black, s_2, 370);
	e->Graphics->DrawString(Decimal_to_string(get_bha()),std_format,Brushes::Black, s_1+s_abs, 370);
	e->Graphics->DrawString("Sachkonto",bold_format,Brushes::Black, s_2, 390);
	e->Graphics->DrawString(sk_bha_,std_format,Brushes::Black, s_1+s_abs, 390);

	e->Graphics->DrawString("Verwendungsnachweis eingereicht",bold_format,Brushes::Black, s_1, 415);
	if(vn_eingereicht_!="")
		e->Graphics->DrawString(vn_eingereicht_,std_format,Brushes::Black, s_1+s_abs, 415);
	else
		e->Graphics->DrawString("-",std_format,Brushes::Black, s_1+s_abs, 415);
	
	e->Graphics->DrawString("Verwendungsnachweis geprüft",bold_format,Brushes::Black, s_1, 435);
	if(vn_geprueft_!="")
		e->Graphics->DrawString(vn_geprueft_,std_format,Brushes::Black, s_1+s_abs, 435);
	else
		e->Graphics->DrawString("-",std_format,Brushes::Black, s_1+s_abs, 435);

	e->Graphics->DrawString("Änderungsbescheid",bold_format,Brushes::Black, s_1, 460);
	if(aenderungsbescheid_!="")
		e->Graphics->DrawString(aenderungsbescheid_,std_format,Brushes::Black, s_1+s_abs, 460);
	else
		e->Graphics->DrawString("-",std_format,Brushes::Black, s_1+s_abs, 460);

	e->Graphics->DrawString("Bemerkung",bold_format,Brushes::Black, s_1, 485);
	if(bemerkung_!="")
	{
		// test if longer than line
		if (bemerkung_->Length>60)
		{

			String^ bemerkungReworked = bemerkung_->Substring(0,bemerkung_->Length);
			int lastSpacePos = -1;
			int curLineLength = 0;
			for(int i=0;i<bemerkungReworked->Length;++i) {
				if((*bemerkungReworked)[i]==' ')
					lastSpacePos = i;

				if (curLineLength>60) {
					bemerkungReworked = bemerkungReworked->Insert(lastSpacePos,"\n");
					bemerkungReworked = bemerkungReworked->Remove(lastSpacePos+1,1);
					i=lastSpacePos+1;
					curLineLength = 0;
				}
				++curLineLength;
			}
					MessageBox::Show(bemerkungReworked);
			e->Graphics->DrawString(bemerkungReworked,std_format,Brushes::Black, s_1+s_abs, 485);
		} else
			e->Graphics->DrawString(bemerkung_,std_format,Brushes::Black, s_1+s_abs, 485);

	}
	else
		e->Graphics->DrawString("-",std_format,Brushes::Black, s_1+s_abs, 485);
}

void project_class::create_bew(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	int bew_count=0;
	for(int i=0;i<programme_->Count;++i)
		bew_count+=programme_[i]->get_bewilligungen()->Count;

	// Fonds
	System::Drawing::Font^ std_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ bold_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	int start=70;
	bool first=true;
	for(int i=act_program;i<programme_->Count;++i)
	{		
		e->Graphics->DrawString(programme_[i]->get_name(),bold_format,Brushes::Black, 10, start);
		start+=20;
		for(int j=act_entry;j<programme_[i]->get_bewilligungen()->Count;++j)
		{
			if(!first)
				start+=110;
			else
				first=false;
			e->Graphics->DrawString("TB "+Convert::ToString(j+1)+" : "+programme_[i]->get_bewilligung(j)->get_nr(),bold_format,Brushes::Black, 50, start);
			e->Graphics->DrawString("vom "+programme_[i]->get_bewilligung(j)->get_vom(),std_format,Brushes::Black, 70, start+20);
			e->Graphics->DrawString("Plankosten",std_format,Brushes::Black, 200, start+40);
			e->Graphics->DrawString("Verwendungsnachweis",std_format,Brushes::Black, 400, start+40);
			e->Graphics->DrawString("MLA",std_format,Brushes::Black, 70, start+60);
			e->Graphics->DrawString(Decimal_to_string(programme_[i]->get_bewilligung(j)->get_mla()),std_format,Brushes::Black, 200, start+60);
			e->Graphics->DrawString(Decimal_to_string(programme_[i]->get_bewilligung(j)->get_mla_vn()),std_format,Brushes::Black, 400, start+60);
			e->Graphics->DrawString("Bund-/Land",std_format,Brushes::Black, 70, start+80);
			e->Graphics->DrawString(Decimal_to_string(programme_[i]->get_bewilligung(j)->get_bund_land()),std_format,Brushes::Black, 200, start+80);
			e->Graphics->DrawString(Decimal_to_string(programme_[i]->get_bewilligung(j)->get_bund_land_vn()),std_format,Brushes::Black, 400, start+80);	e->Graphics->DrawString(Decimal_to_string(programme_[i]->get_bewilligung(j)->get_bund_land_vn()),std_format,Brushes::Black, 400, start+80);
			if(j!=programme_[i]->get_bewilligungen()->Count-1)
				e->Graphics->DrawString("____________________________________________________________________________________",std_format,Brushes::Black, 40, start+90);		
			++act_entry;
			if(start>=950)
				break;
		}
		if(start>=950)
				break;
		first=true;
		++act_program;
		act_entry=0;
		start+=110;
	}
	if(start<950)
	{
		act_entry=0;
		page_count_++;
	}
}

void project_class::create_ff(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	// Fonds
	System::Drawing::Font^ std_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ bold_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	int start=70;
	fremdfoerderung_class^ ff=fremdfoerderungen_;
	if(vn_geprueft_!="")
		ff=fremdfoerderungen_vn_;

	int ff_count=ff->get_all(false)->Count;
	Decimal summe=0;
	for(int i=act_entry;i<ff_count;++i)
	{
		++act_entry;
		String^ programm=ff->get_programm(i);
		Decimal betrag=ff->get_betrag(i);
		summe+=betrag;
		String^ betrag_s=Decimal_to_string(betrag);

		e->Graphics->DrawString(programm,std_format,Brushes::Black, 50, start);
		e->Graphics->DrawString(betrag_s,std_format,Brushes::Black, 300, start);
		start+=20;
	}
	start+=10;
	e->Graphics->DrawString("Summe",bold_format,Brushes::Black, 50, start);
	e->Graphics->DrawString(Decimal_to_string(summe),bold_format,Brushes::Black, 300, start);


	if(start<950)
	{
		act_entry=0;
		page_count_++;
	}
}

void project_class::create_adress(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	// Fonds
	System::Drawing::Font^ std_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ bold_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	int start=70;
	for(int i=act_entry;i<adressen_->Count;++i)
	{		
		e->Graphics->DrawString(adressen_[i]->get_adresse(),bold_format,Brushes::Black, 10, start);
			
		e->Graphics->DrawString("Plankosten",std_format,Brushes::Black, 200, start+20);
		e->Graphics->DrawString("Verwendungsnachweis",std_format,Brushes::Black, 400, start+20);
		e->Graphics->DrawString("Kosten",std_format,Brushes::Black, 70, start+40);
		e->Graphics->DrawString(Decimal_to_string(adressen_[i]->get_einzel_gk()),std_format,Brushes::Black, 200, start+40);
		e->Graphics->DrawString(Decimal_to_string(adressen_[i]->get_einzel_gk_vn()),std_format,Brushes::Black, 400, start+40);
		e->Graphics->DrawString("Förderung",std_format,Brushes::Black, 70, start+60);
		e->Graphics->DrawString(Decimal_to_string(adressen_[i]->get_einzel_gf()),std_format,Brushes::Black, 200, start+60);
		e->Graphics->DrawString(Decimal_to_string(adressen_[i]->get_einzel_gf_vn()),std_format,Brushes::Black, 400, start+60);
		if(i!=adressen_->Count-1)
			e->Graphics->DrawString("____________________________________________________________________________________",std_format,Brushes::Black, 10, start+70);	
		start+=90;
		++act_entry;
		if(start>=1000)
			break;
	}
	if(act_entry==adressen_->Count)
		++page_count_;

}

void project_class::create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	// Fonds
	System::Drawing::Font^ main_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ small_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 1100, 1500, 80);

	// Firma
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
	e->Graphics->DrawString("erstellt durch :",small_format,Brushes::Black,10,1112);
	e->Graphics->DrawString(name,main_format,Brushes::Black,80,1110);
	e->Graphics->DrawString(strasse+" "+hausnr,main_format,Brushes::Black,80,1130);
	e->Graphics->DrawString(plz+" "+ort,main_format,Brushes::Black,80,1150);

	// Programm
	e->Graphics->DrawString("erstellt mit Hilfe von FÖRDI © MKS",small_format,Brushes::Black,635,1155);

}

void project_class::create_page_header(System::Drawing::Printing::PrintPageEventArgs^ e, String^ title)
{
	// Fonds
	System::Drawing::Font^ main_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ small_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 0, 850, 60);

	// Bezeichnung
	e->Graphics->DrawString("Projekt :",small_format,Brushes::Black,10,10);
	e->Graphics->DrawString(bezeichnung_,small_format,Brushes::Black,100,10);
	// Seitentitel
	e->Graphics->DrawString(title,main_format,Brushes::Black,10,35);
	// Datum
	String^ date=Convert::ToString(DateTime::Today.Date);
	date=date->Substring(0,10);
	e->Graphics->DrawString(date,small_format,Brushes::Black, 750,15);
}
