#pragma once

#include "programm.h"
#include "fremdfoerderung_class.h"
#include "adresse.h"

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

ref class project_class
{
public:
	project_class(void);
	project_class(int);

	// Setter
	void set_bezeichnung(String^);
	void set_foeuvh(String^);
	void set_bew_ztr(String^);
	void set_kostengruppe(String^);
	void set_kostenart(String^);
	void set_gk_real(Decimal);
	void set_gk_zuwendungsf(Decimal);
	void set_gk_real_vn(Decimal);
	void set_gk_zuwendungsf_vn(Decimal);
	void set_sk_bha(String^);
	void set_vn_eingereicht(String^);
	void set_vn_geprueft(String^);
	void set_aenderungsbescheid(String^);
	void set_stadt(String^);
	void set_gebiet(String^);
	void set_bemerkung(String^);

	void add_adresse(String^);
	void rem_adresse(String^);
	void clear_adressen();

	void add_programm(String^, String^);
	void rem_programm(String^);
	void clear_programm();

	void add_bewilligung(String^);
	void rem_bewilligung(String^, int);

	void bewilligung_zu_vn();
	void vn_zu_bewilligung();

	// Getter
	String^ get_bezeichnung();
	String^ get_foeuvh();
	String^ get_bew_ztr();
	String^ get_kostengruppe();
	String^ get_kostenart();
	Decimal get_gk_real();
	Decimal get_gk_zuwendungsf();
	Decimal get_gk_real_vn();
	Decimal get_gk_zuwendungsf_vn();
	String^ get_sk_bha();
	String^ get_vn_eingereicht();
	String^ get_vn_geprueft();
	String^ get_aenderungsbescheid();
	String^ get_stadt();
	String^ get_gebiet();
	String^ get_bemerkung();
	int get_db_id();

	int get_programm_index(String^);
	int get_adress_index(String^);
	adresse^ get_adresse(String^);

	List<String^>^ get_adressen();
	List<String^>^ get_bewilligungen(String^);
	List<String^>^ get_programme();
	bewilligung_class^  get_bewilligung(String^, int);
	fremdfoerderung_class^ get_fremdfoerderung();
	fremdfoerderung_class^ get_fremdfoerderung_vn();

	// Berechnungen
	Decimal get_mla();
	Decimal get_bund_land();
	Decimal get_mla_vn();
	Decimal get_bund_land_vn();
	Decimal get_gesamtfoerderung();
	Decimal get_gesamtfremdfoerderung();
	Decimal get_gesamtfremdfoerderung_vn();
	Decimal get_bha();
	Decimal get_mehr_minder_kosten();

	// Bewilligung swap
	void swap_bewilligung(String^,int,int);

	// ==
	bool is_equal(project_class^);
	
	// Speichern, Laden, Löschen
	void save();
	void del();
	void load();

	// Drucken
	void print(String^);
	void printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e);
	
	void create_main(System::Drawing::Printing::PrintPageEventArgs^ e);
	void create_ff(System::Drawing::Printing::PrintPageEventArgs^ e);
	void create_bew(System::Drawing::Printing::PrintPageEventArgs^ e);
	void create_adress(System::Drawing::Printing::PrintPageEventArgs^ e);
	void create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e);
	void create_page_header(System::Drawing::Printing::PrintPageEventArgs^ e,String^);

private:
	int db_id_;

	Decimal gk_real_;
	Decimal gk_zuwendungsf_;
	Decimal gk_real_vn_;
	Decimal gk_zuwendungsf_vn_;

	String^ bezeichnung_;
	String^ foeuvh_;
	String^ bew_ztr_;
	String^ kostengruppe_;
	String^ kostenart_;
	String^ sk_bha_;
	String^ vn_eingereicht_;
	String^ vn_geprueft_;
	String^ aenderungsbescheid_;
	String^ bemerkung_;

	String^ stadt_;
	String^ gebiet_;

	List<programm^>^ programme_;
	List<adresse^>^ adressen_;
	fremdfoerderung_class^ fremdfoerderungen_;
	fremdfoerderung_class^ fremdfoerderungen_vn_;

	int page_count_;
	int max_pages_;
	int act_entry;
	int act_program;
	int pages;
};

