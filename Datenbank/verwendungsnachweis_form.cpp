#include "StdAfx.h"
#include "fremdfoerdermittel_form.h"
#include "verwendungsnachweis_form.h"
#include "helper.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

void verwendungsnachweis_form::verwendungsnachweis_form_Load(System::Object^  sender, System::EventArgs^  e)
{	
	load_bewilligung();
	load_einnahmen();
	load_ausgaben();
	aktualisiere();
	if(!load_)
	{
		for(int i=0;i<tabPage1->Controls->Count;++i)
			tabPage1->Controls[i]->Enabled=false;

		tabPage1->Controls->Find("btn_ff",true)[0]->Enabled=true;

		for(int i=0;i<tabPage2->Controls->Count;++i)
			tabPage2->Controls[i]->Enabled=false;
	}
}

void verwendungsnachweis_form::load_bewilligung()
{
	tabPage1->Controls->Clear();

	int spalte_programm=5;
	int spalte_bew_label=25;
	int spalte_bew_betrag=160;
	int spalte_bew_bund_land=295;
	int spalte_bew_mla=430;
	int beginn=25;
	int zeilen_abstand=20;
	int eintrag=0;
	int tab_index=1;

	// Überschriften
	System::Windows::Forms::Label^  label_betr = gcnew System::Windows::Forms::Label();	
	label_betr->Location = System::Drawing::Point(spalte_bew_betrag, 5);
	label_betr->AutoSize = true;
	label_betr->Text = "Betrag";
	label_betr->Name = "label_betr";
	label_betr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	System::Windows::Forms::Label^  label_bund_land = gcnew System::Windows::Forms::Label();	
	label_bund_land->Location = System::Drawing::Point(spalte_bew_bund_land, 5);
	label_bund_land->AutoSize = true;
	label_bund_land->Text = "Bund/Land";
	label_bund_land->Name = "label_bund_land";
	label_bund_land->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	System::Windows::Forms::Label^  label_mla = gcnew System::Windows::Forms::Label();	
	label_mla->Location = System::Drawing::Point(spalte_bew_mla, 5);
	label_mla->AutoSize = true;
	label_mla->Text = "MLA";
	label_mla->Name = "label_mla";
	label_mla->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	
	tabPage3->Controls->Add(label_betr);
	tabPage3->Controls->Add(label_bund_land);
	tabPage3->Controls->Add(label_mla);

	for each(String^ programm_eintrag in projekt_->get_programme())
	{		
		// Programm Label
		System::Windows::Forms::Label^  programm_label = gcnew System::Windows::Forms::Label();	
		programm_label->Location = System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
		programm_label->AutoSize = true;
		programm_label->Text = programm_eintrag;
		programm_label->Name = programm_eintrag;
		programm_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

		tabPage3->Controls->Add(programm_label);
		eintrag++;

		List<String^>^ bewilligungen = projekt_->get_bewilligungen(programm_eintrag);
		for(int i=0;i<bewilligungen->Count;++i)
		{
			bewilligung_class^ bewilligung = projekt_->get_bewilligung(programm_eintrag,i);

			// Bewilligung Label
			System::Windows::Forms::Label^  bewilligung_label = gcnew System::Windows::Forms::Label();	
			bewilligung_label->Location = System::Drawing::Point(spalte_bew_label, eintrag*zeilen_abstand+beginn+5);
			bewilligung_label->AutoSize = true;
			bewilligung_label->Text = "TB "+Convert::ToString(i+1)+" : "+bewilligung->get_nr();
			bewilligung_label->Name = programm_eintrag+"-"+Convert::ToString(i)+"-label";

			// Bewilligung Betrag
			System::Windows::Forms::Label^  bewilligung_betrag_dez = gcnew System::Windows::Forms::Label();	
			bewilligung_betrag_dez->Location = System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
			bewilligung_betrag_dez->AutoSize = false;
			bewilligung_betrag_dez->Size = System::Drawing::Size(117, 16);
			bewilligung_betrag_dez->Text = Decimal_to_dez(bewilligung->get_mla()+bewilligung->get_bund_land());
			bewilligung_betrag_dez->Name = programm_eintrag+"-"+Convert::ToString(i)+"-betrag_dez";
			bewilligung_betrag_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
			System::Windows::Forms::Label^  bewilligung_betrag_kom = gcnew System::Windows::Forms::Label();	
			bewilligung_betrag_kom->Location = System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
			bewilligung_betrag_kom->AutoSize = false;
			bewilligung_betrag_kom->Size = System::Drawing::Size(31, 13);
			bewilligung_betrag_kom->Text = Decimal_to_kom(bewilligung->get_mla()+bewilligung->get_bund_land());
			bewilligung_betrag_kom->Name = programm_eintrag+"-"+Convert::ToString(i)+"-betrag_kom";

			// Bewilligung Bund Land
			System::Windows::Forms::Label^ bewilligung_bund_land_dez = gcnew System::Windows::Forms::Label();
			bewilligung_bund_land_dez->Location = System::Drawing::Point(275, eintrag*zeilen_abstand+beginn+5);
			bewilligung_bund_land_dez->AutoSize = false;
			bewilligung_bund_land_dez->Size = System::Drawing::Size(117, 16);
			bewilligung_bund_land_dez->Text = Decimal_to_dez(bewilligung->get_bund_land());
			bewilligung_bund_land_dez->Name = programm_eintrag+"-"+Convert::ToString(i)+"-bund_land_dez";
			bewilligung_bund_land_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
			System::Windows::Forms::Label^ bewilligung_bund_land_kom = gcnew System::Windows::Forms::Label();
			bewilligung_bund_land_kom->Location = System::Drawing::Point(390, eintrag*zeilen_abstand+beginn+5);
			bewilligung_bund_land_kom->Size = System::Drawing::Size(31, 13);
			bewilligung_bund_land_kom->Text = Decimal_to_kom(bewilligung->get_bund_land());
			bewilligung_bund_land_kom->Name = programm_eintrag+"-"+Convert::ToString(i)+"-bund_land_kom";

			// Bewilligung MLA
			System::Windows::Forms::Label^ bewilligung_mla_dez = gcnew System::Windows::Forms::Label();
			bewilligung_mla_dez->Location = System::Drawing::Point(410, eintrag*zeilen_abstand+beginn+5);
			bewilligung_mla_dez->AutoSize = false;
			bewilligung_mla_dez->Size = System::Drawing::Size(117, 16);
			bewilligung_mla_dez->Text = Decimal_to_dez(bewilligung->get_mla());
			bewilligung_mla_dez->Name = programm_eintrag+"-"+Convert::ToString(i)+"-mla_dez";
			bewilligung_mla_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
			System::Windows::Forms::Label^ bewilligung_mla_kom = gcnew System::Windows::Forms::Label();
			bewilligung_mla_kom->Location = System::Drawing::Point(525, eintrag*zeilen_abstand+beginn+5);
			bewilligung_mla_kom->Size = System::Drawing::Size(31, 13);
			bewilligung_mla_kom->Text = Decimal_to_kom(bewilligung->get_mla());
			bewilligung_mla_kom->Name = programm_eintrag+"-"+Convert::ToString(i)+"-mla_kom";

			tabPage3->Controls->Add(bewilligung_label);
			tabPage3->Controls->Add(bewilligung_betrag_dez);
			tabPage3->Controls->Add(bewilligung_betrag_kom);
			tabPage3->Controls->Add(bewilligung_bund_land_dez);
			tabPage3->Controls->Add(bewilligung_bund_land_kom);
			tabPage3->Controls->Add(bewilligung_mla_dez);
			tabPage3->Controls->Add(bewilligung_mla_kom);
			eintrag++;
		}
	}
	// FF 
	++eintrag;
	System::Windows::Forms::Label^  l_ff = gcnew System::Windows::Forms::Label();	
	l_ff->AutoSize = true;
	l_ff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_ff->Location= System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
	l_ff->Text = "Fremdförderung";
	l_ff->Name = "l_ff";
	
	System::Windows::Forms::Label^  l_ff_betrag_dez = gcnew System::Windows::Forms::Label();	
	l_ff_betrag_dez->Location= System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
	l_ff_betrag_dez->AutoSize = false;
	l_ff_betrag_dez->Size = System::Drawing::Size(117, 16);
	l_ff_betrag_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
	l_ff_betrag_dez->Text = Decimal_to_dez(projekt_->get_gesamtfremdfoerderung());
	l_ff_betrag_dez->Name = "l_ff_betrag_dez";

	System::Windows::Forms::Label^  l_ff_betrag_kom = gcnew System::Windows::Forms::Label();
	l_ff_betrag_kom->Location= System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
	l_ff_betrag_kom->AutoSize = false;
	l_ff_betrag_kom->Text = Decimal_to_kom(projekt_->get_gesamtfremdfoerderung());
	l_ff_betrag_kom->Size = System::Drawing::Size(31, 13);
	l_ff_betrag_kom->Name = "l_ff_betrag_kom";

	tabPage3->Controls->Add(l_ff);
	tabPage3->Controls->Add(l_ff_betrag_dez);
	tabPage3->Controls->Add(l_ff_betrag_kom);

	fremdfoerderung_class^ ff= projekt_->get_fremdfoerderung();
	List<String^>^ ff_list=ff->get_all(false);
	++eintrag;
	for(int i=0;i<ff_list->Count;++i)
	{
		Decimal ff_betrag=ff->get_betrag(i);

		// Bewilligung Label
		System::Windows::Forms::Label^  ff_label = gcnew System::Windows::Forms::Label();	
		ff_label->Location = System::Drawing::Point(spalte_bew_label, eintrag*zeilen_abstand+beginn+5);
		ff_label->AutoSize = true;
		ff_label->Text = ff_list[i];
		ff_label->Name = ff_list[i]+"label";

		// Bewilligung Betrag
		System::Windows::Forms::Label^  ff_dez = gcnew System::Windows::Forms::Label();	
		ff_dez->Location = System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
		ff_dez->AutoSize = false;
		ff_dez->Size = System::Drawing::Size(117, 16);
		ff_dez->Text = Decimal_to_dez(ff_betrag);
		ff_dez->Name = ff_list[i]+"ff_dez";
		ff_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;

		System::Windows::Forms::Label^  ff_kom = gcnew System::Windows::Forms::Label();	
		ff_kom->Location = System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
		ff_kom->AutoSize = false;
		ff_kom->Size = System::Drawing::Size(31, 13);
		ff_kom->Text = Decimal_to_kom(ff_betrag);
		ff_kom->Name = ff_list[i]+"ff_kom";

		tabPage3->Controls->Add(ff_label);
		tabPage3->Controls->Add(ff_dez);
		tabPage3->Controls->Add(ff_kom);

		eintrag++;
	}
	
	//BHA
	++eintrag;
	System::Windows::Forms::Label^  l_bha = gcnew System::Windows::Forms::Label();	
	l_bha->AutoSize = true;
	l_bha->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_bha->Location= System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
	l_bha->Text = "Bauherrenanteil";
	l_bha->Name = "l_bha";
	
	System::Windows::Forms::Label^  l_bha_betrag_dez = gcnew System::Windows::Forms::Label();
	l_bha_betrag_dez->Location= System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
	l_bha_betrag_dez->AutoSize = false;
	l_bha_betrag_dez->Size = System::Drawing::Size(117, 16);
	l_bha_betrag_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
	l_bha_betrag_dez->Text = Decimal_to_dez(projekt_->get_bha());
	l_bha_betrag_dez->Name = "l_bha_betrag_dez";
		
	System::Windows::Forms::Label^  l_bha_betrag_kom = gcnew System::Windows::Forms::Label();
	l_bha_betrag_kom->Location= System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
	l_bha_betrag_kom->AutoSize = false;
	l_bha_betrag_kom->Text = Decimal_to_kom(projekt_->get_bha());
	l_bha_betrag_kom->Size = System::Drawing::Size(31, 13);
	l_bha_betrag_kom->Name = "l_bha_betrag_kom";

	tabPage3->Controls->Add(l_bha);
	tabPage3->Controls->Add(l_bha_betrag_dez);
	tabPage3->Controls->Add(l_bha_betrag_kom);
	++eintrag;
	
	// GK
	++eintrag;
	System::Windows::Forms::Label^  l_summe = gcnew System::Windows::Forms::Label();	
	l_summe->Location= System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
	l_summe->AutoSize = true;
	l_summe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_summe->Text = "Summe (reale GK)";
	l_summe->Name = "l_summe";
	
	System::Windows::Forms::Label^ l_summe_dez = gcnew System::Windows::Forms::Label();
	l_summe_dez->Location= System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
	l_summe_dez->Name = "l_summe_dez";
	l_summe_dez->AutoSize = false;
	l_summe_dez->Size = System::Drawing::Size(117, 16);
	l_summe_dez->Text = Decimal_to_dez(projekt_->get_gk_real());
	l_summe_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
	System::Windows::Forms::Label^ l_summe_kom = gcnew System::Windows::Forms::Label();
	l_summe_kom->Location= System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
	l_summe_kom->Name = "l_summe_dez";
	l_summe_kom->Size = System::Drawing::Size(31, 13);
	l_summe_kom->Text = Decimal_to_kom(projekt_->get_gk_real());

	System::Windows::Forms::Label^  l_zuwendungsf = gcnew System::Windows::Forms::Label();	
	l_zuwendungsf->Location= System::Drawing::Point(spalte_bew_bund_land, eintrag*zeilen_abstand+beginn+5);
	l_zuwendungsf->AutoSize = true;
	l_zuwendungsf->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_zuwendungsf->Text = "Zuwendungsfähige GK";
	l_zuwendungsf->Name = "l_zuwendungsf";

	System::Windows::Forms::Label^ l_zuwendungsf_dez = gcnew System::Windows::Forms::Label();
	l_zuwendungsf_dez->Location= System::Drawing::Point(410, eintrag*zeilen_abstand+beginn+5);
	l_zuwendungsf_dez->Name = "l_zuwendungsf_dez";
	l_zuwendungsf_dez->AutoSize = false;
	l_zuwendungsf_dez->Size = System::Drawing::Size(117, 16);
	l_zuwendungsf_dez->Text = Decimal_to_dez(projekt_->get_gk_zuwendungsf());
	l_zuwendungsf_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
	System::Windows::Forms::Label^ l_zuwendungsf_kom = gcnew System::Windows::Forms::Label();
	l_zuwendungsf_kom->Location= System::Drawing::Point(525, eintrag*zeilen_abstand+beginn+5);
	l_zuwendungsf_kom->Name = "l_zuwendungsf_kom";
	l_zuwendungsf_kom->Size = System::Drawing::Size(31, 13);
	l_zuwendungsf_kom->Text = Decimal_to_kom(projekt_->get_gk_zuwendungsf());

	tabPage3->Controls->Add(l_summe);
	tabPage3->Controls->Add(l_summe_kom);
	tabPage3->Controls->Add(l_summe_dez);
	tabPage3->Controls->Add(l_zuwendungsf);
	tabPage3->Controls->Add(l_zuwendungsf_dez);
	tabPage3->Controls->Add(l_zuwendungsf_kom);
}

void verwendungsnachweis_form::load_einnahmen()
{
	tabPage1->Controls->Clear();

	int spalte_programm=5;
	int spalte_bew_label=25;
	int spalte_bew_betrag=160;
	int spalte_bew_bund_land=295;
	int spalte_bew_mla=430;
	int spalte_mehr_minder=565;
	int beginn=25;
	int zeilen_abstand=20;
	int eintrag=0;
	int tab_index=1;

	// Überschriften
	System::Windows::Forms::Label^  label_betr = gcnew System::Windows::Forms::Label();	
	label_betr->Location = System::Drawing::Point(spalte_bew_betrag, 5);
	label_betr->AutoSize = true;
	label_betr->Text = "Betrag";
	label_betr->Name = "label_betr";
	label_betr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	System::Windows::Forms::Label^  label_bund_land = gcnew System::Windows::Forms::Label();	
	label_bund_land->Location = System::Drawing::Point(spalte_bew_bund_land, 5);
	label_bund_land->AutoSize = true;
	label_bund_land->Text = "Bund/Land";
	label_bund_land->Name = "label_bund_land";
	label_bund_land->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	System::Windows::Forms::Label^  label_mla = gcnew System::Windows::Forms::Label();	
	label_mla->Location = System::Drawing::Point(spalte_bew_mla, 5);
	label_mla->AutoSize = true;
	label_mla->Text = "MLA";
	label_mla->Name = "label_mla";
	label_mla->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	System::Windows::Forms::Label^  label_mehr_minder = gcnew System::Windows::Forms::Label();	
	label_mehr_minder->Location = System::Drawing::Point(spalte_mehr_minder, 5);
	label_mehr_minder->AutoSize = true;
	label_mehr_minder->Text = "Mehr-/Minderkosten";
	label_mehr_minder->Name = "label_mehr_minder";
	label_mehr_minder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	tabPage1->Controls->Add(label_betr);
	tabPage1->Controls->Add(label_bund_land);
	tabPage1->Controls->Add(label_mla);
	tabPage1->Controls->Add(label_mehr_minder);
	
	Decimal mehr_minder_summe=0;

	for each(String^ programm_eintrag in projekt_->get_programme())
	{		
		// Programm Label
		System::Windows::Forms::Label^  programm_label = gcnew System::Windows::Forms::Label();	
		programm_label->Location = System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
		programm_label->AutoSize = true;
		programm_label->Text = programm_eintrag;
		programm_label->Name = programm_eintrag;
		programm_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

		tabPage1->Controls->Add(programm_label);
		eintrag++;
		List<String^>^ bewilligungen = projekt_->get_bewilligungen(programm_eintrag);
		for(int i=0;i<bewilligungen->Count;++i)
		{
			bewilligung_class^ bewilligung = projekt_->get_bewilligung(programm_eintrag,i);

			// Bewilligung Label
			System::Windows::Forms::Label^  bewilligung_label = gcnew System::Windows::Forms::Label();	
			bewilligung_label->Location = System::Drawing::Point(spalte_bew_label, eintrag*zeilen_abstand+beginn+5);
			bewilligung_label->AutoSize = true;
			bewilligung_label->Text = "TB "+Convert::ToString(i+1)+" : "+bewilligung->get_nr();
			bewilligung_label->Name = programm_eintrag+"-"+Convert::ToString(i)+"-label";

			// Bewilligung Betrag
			System::Windows::Forms::Label^  bewilligung_betrag_dez = gcnew System::Windows::Forms::Label();	
			bewilligung_betrag_dez->Location = System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
			bewilligung_betrag_dez->AutoSize = false;
			bewilligung_betrag_dez->Size = System::Drawing::Size(117, 16);
			bewilligung_betrag_dez->Text = Decimal_to_dez(bewilligung->get_mla_vn()+bewilligung->get_bund_land_vn());
			bewilligung_betrag_dez->Name = programm_eintrag+"-"+Convert::ToString(i)+"-betrag_dez";
			bewilligung_betrag_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
			System::Windows::Forms::Label^  bewilligung_betrag_kom = gcnew System::Windows::Forms::Label();	
			bewilligung_betrag_kom->Location = System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
			bewilligung_betrag_kom->AutoSize = false;
			bewilligung_betrag_kom->Size = System::Drawing::Size(31, 13);
			bewilligung_betrag_kom->Text = Decimal_to_kom(bewilligung->get_mla_vn()+bewilligung->get_bund_land_vn());
			bewilligung_betrag_kom->Name = programm_eintrag+"-"+Convert::ToString(i)+"-betrag_kom";

			// Bewilligung Bund Land
			System::Windows::Forms::TextBox^ bewilligung_bund_land = gcnew System::Windows::Forms::TextBox();
			bewilligung_bund_land->Location = System::Drawing::Point(spalte_bew_bund_land, eintrag*zeilen_abstand+beginn);
			bewilligung_bund_land->Size = System::Drawing::Size(127, 13);
			bewilligung_bund_land->Text = Decimal_to_string(bewilligung->get_bund_land_vn());
			bewilligung_bund_land->Name = programm_eintrag+"-"+Convert::ToString(i)+"-bundland";
			bewilligung_bund_land->TabIndex = tab_index; tab_index++;
			bewilligung_bund_land->TextChanged += gcnew System::EventHandler(this, &verwendungsnachweis_form::TextChanged);
			bewilligung_bund_land->Leave += gcnew System::EventHandler(this, &verwendungsnachweis_form::Leave);

			// Bewilligung MLA
			System::Windows::Forms::TextBox^ bewilligung_mla = gcnew System::Windows::Forms::TextBox();
			bewilligung_mla->Location = System::Drawing::Point(spalte_bew_mla, eintrag*zeilen_abstand+beginn);
			bewilligung_mla->Size = System::Drawing::Size(127, 13);
			bewilligung_mla->Text = Decimal_to_string(bewilligung->get_mla_vn());
			bewilligung_mla->Name = programm_eintrag+"-"+Convert::ToString(i)+"-mla";
			bewilligung_mla->TabIndex = tab_index; tab_index++;
			bewilligung_mla->TextChanged += gcnew System::EventHandler(this, &verwendungsnachweis_form::TextChanged);
			bewilligung_mla->Leave += gcnew System::EventHandler(this, &verwendungsnachweis_form::Leave);

			// Bewilligung Mehr-/Minder
			Decimal mehr_minder=(bewilligung->get_mla_vn()+bewilligung->get_bund_land_vn())-(bewilligung->get_mla()+bewilligung->get_bund_land());
			mehr_minder_summe+=mehr_minder;
			System::Windows::Forms::Label^  bewilligung_mehr_minder_dez = gcnew System::Windows::Forms::Label();	
			bewilligung_mehr_minder_dez->Location = System::Drawing::Point(545, eintrag*zeilen_abstand+beginn+5);
			bewilligung_mehr_minder_dez->AutoSize = false;
			bewilligung_mehr_minder_dez->Size = System::Drawing::Size(117, 16);
			bewilligung_mehr_minder_dez->Text = Decimal_to_dez(mehr_minder);
			bewilligung_mehr_minder_dez->Name = programm_eintrag+"-"+Convert::ToString(i)+"-mehrminder_dez";
			bewilligung_mehr_minder_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
			System::Windows::Forms::Label^  bewilligung_mehr_minder_kom = gcnew System::Windows::Forms::Label();	
			bewilligung_mehr_minder_kom->Location = System::Drawing::Point(660, eintrag*zeilen_abstand+beginn+5);
			bewilligung_mehr_minder_kom->AutoSize = false;
			bewilligung_mehr_minder_kom->Size = System::Drawing::Size(31, 13);
			bewilligung_mehr_minder_kom->Text = Decimal_to_kom(mehr_minder);
			bewilligung_mehr_minder_kom->Name = programm_eintrag+"-"+Convert::ToString(i)+"-mehrminder_kom";

			tabPage1->Controls->Add(bewilligung_label);
			tabPage1->Controls->Add(bewilligung_betrag_dez);
			tabPage1->Controls->Add(bewilligung_betrag_kom);
			tabPage1->Controls->Add(bewilligung_bund_land);
			tabPage1->Controls->Add(bewilligung_mla);
			tabPage1->Controls->Add(bewilligung_mehr_minder_dez);
			tabPage1->Controls->Add(bewilligung_mehr_minder_kom);
			eintrag++;
		}
	}
	// mehr minder summe
	++eintrag;

	System::Windows::Forms::Label^  mehr_minder_ges = gcnew System::Windows::Forms::Label();	
	mehr_minder_ges->Location = System::Drawing::Point(spalte_bew_bund_land+100, eintrag*zeilen_abstand+beginn+5);
	mehr_minder_ges->AutoSize = true;
	mehr_minder_ges->Text = "Mehr-/Minderkosten Summe :";
	mehr_minder_ges->Name = "-mehr.minder.ges.label.dez";
	mehr_minder_ges->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));

	System::Windows::Forms::Label^  mehr_minder_ges_dez = gcnew System::Windows::Forms::Label();	
	mehr_minder_ges_dez->Location = System::Drawing::Point(545, eintrag*zeilen_abstand+beginn+5);
	mehr_minder_ges_dez->AutoSize = false;
	mehr_minder_ges_dez->Size = System::Drawing::Size(117, 16);
	mehr_minder_ges_dez->Text = Decimal_to_dez(mehr_minder_summe);
	mehr_minder_ges_dez->Name = "l_mehrminder_summe_dez";
	mehr_minder_ges_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;

	System::Windows::Forms::Label^  mehr_minder_ges_kom = gcnew System::Windows::Forms::Label();	
	mehr_minder_ges_kom->Location = System::Drawing::Point(660, eintrag*zeilen_abstand+beginn+5);
	mehr_minder_ges_kom->AutoSize = false;
	mehr_minder_ges_kom->Size = System::Drawing::Size(31, 13);
	mehr_minder_ges_kom->Text = Decimal_to_kom(mehr_minder_summe);
	mehr_minder_ges_kom->Name = "l_mehrminder_summe_kom";
	
	tabPage1->Controls->Add(mehr_minder_ges);
	tabPage1->Controls->Add(mehr_minder_ges_dez);
	tabPage1->Controls->Add(mehr_minder_ges_kom);

	eintrag++;

	// FF 
	++eintrag;
	System::Windows::Forms::Label^  l_ff = gcnew System::Windows::Forms::Label();	
	l_ff->AutoSize = true;
	l_ff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_ff->Location= System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
	l_ff->Text = "Fremdförderung";
	l_ff->Name = "l_ff";
	
	System::Windows::Forms::Label^  l_ff_betrag_dez = gcnew System::Windows::Forms::Label();	
	l_ff_betrag_dez->Location= System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
	l_ff_betrag_dez->AutoSize = false;
	l_ff_betrag_dez->Size = System::Drawing::Size(117, 16);
	l_ff_betrag_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
	l_ff_betrag_dez->Name = "l_ff_betrag_dez";

	System::Windows::Forms::Label^  l_ff_betrag_kom = gcnew System::Windows::Forms::Label();
	l_ff_betrag_kom->Location= System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
	l_ff_betrag_kom->AutoSize = false;
	l_ff_betrag_kom->Size = System::Drawing::Size(31, 13);
	l_ff_betrag_kom->Name = "l_ff_betrag_kom";

	System::Windows::Forms::Button^ btn_ff = gcnew System::Windows::Forms::Button();
	btn_ff->Location= System::Drawing::Point(spalte_bew_bund_land,eintrag*zeilen_abstand+beginn+5);
	btn_ff->Click += gcnew System::EventHandler(this, &verwendungsnachweis_form::btn_ff_Click);
	btn_ff->Size = System::Drawing::Size(250, 21);
	btn_ff->Text = "Fremdförderungen";
	btn_ff->UseVisualStyleBackColor = true;
	btn_ff->TabIndex = tab_index; tab_index++;
	btn_ff->Name = "btn_ff";

	tabPage1->Controls->Add(l_ff);
	tabPage1->Controls->Add(l_ff_betrag_dez);
	tabPage1->Controls->Add(l_ff_betrag_kom);
	tabPage1->Controls->Add(btn_ff);

	fremdfoerderung_class^ ff= projekt_->get_fremdfoerderung_vn();
	List<String^>^ ff_list=ff->get_all(false);
	++eintrag;
	for(int i=0;i<ff_list->Count;++i)
	{
		Decimal ff_betrag=ff->get_betrag(i);

		// Bewilligung Label
		System::Windows::Forms::Label^  ff_label = gcnew System::Windows::Forms::Label();	
		ff_label->Location = System::Drawing::Point(spalte_bew_label, eintrag*zeilen_abstand+beginn+5);
		ff_label->AutoSize = true;
		ff_label->Text = ff_list[i];
		ff_label->Name = ff_list[i]+"label";

		// Bewilligung Betrag
		System::Windows::Forms::Label^  ff_dez = gcnew System::Windows::Forms::Label();	
		ff_dez->Location = System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
		ff_dez->AutoSize = false;
		ff_dez->Size = System::Drawing::Size(117, 16);
		ff_dez->Text = Decimal_to_dez(ff_betrag);
		ff_dez->Name = ff_list[i]+"ff_dez";
		ff_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;

		System::Windows::Forms::Label^  ff_kom = gcnew System::Windows::Forms::Label();	
		ff_kom->Location = System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
		ff_kom->AutoSize = false;
		ff_kom->Size = System::Drawing::Size(31, 13);
		ff_kom->Text = Decimal_to_kom(ff_betrag);
		ff_kom->Name = ff_list[i]+"ff_kom";

		tabPage1->Controls->Add(ff_label);
		tabPage1->Controls->Add(ff_dez);
		tabPage1->Controls->Add(ff_kom);

		eintrag++;
	}
	
	//BHA
	++eintrag;
	System::Windows::Forms::Label^  l_bha = gcnew System::Windows::Forms::Label();	
	l_bha->AutoSize = true;
	l_bha->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_bha->Location= System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
	l_bha->Text = "Bauherrenanteil";
	l_bha->Name = "l_bha";
	
	System::Windows::Forms::Label^  l_bha_betrag_dez = gcnew System::Windows::Forms::Label();
	l_bha_betrag_dez->Location= System::Drawing::Point(140, eintrag*zeilen_abstand+beginn+5);
	l_bha_betrag_dez->AutoSize = false;
	l_bha_betrag_dez->Size = System::Drawing::Size(117, 16);
	l_bha_betrag_dez->TextAlign = System::Drawing::ContentAlignment::TopRight;
	l_bha_betrag_dez->Name = "l_bha_betrag_dez";
		
	System::Windows::Forms::Label^  l_bha_betrag_kom = gcnew System::Windows::Forms::Label();
	l_bha_betrag_kom->Location= System::Drawing::Point(255, eintrag*zeilen_abstand+beginn+5);
	l_bha_betrag_kom->AutoSize = false;
	l_bha_betrag_kom->Size = System::Drawing::Size(31, 13);
	l_bha_betrag_kom->Name = "l_bha_betrag_kom";

	tabPage1->Controls->Add(l_bha);
	tabPage1->Controls->Add(l_bha_betrag_dez);
	tabPage1->Controls->Add(l_bha_betrag_kom);
	++eintrag;
	
	// GK
	++eintrag;
	System::Windows::Forms::Label^  l_summe = gcnew System::Windows::Forms::Label();	
	l_summe->Location= System::Drawing::Point(spalte_programm, eintrag*zeilen_abstand+beginn+5);
	l_summe->AutoSize = true;
	l_summe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_summe->Text = "Summe (reale GK)";
	l_summe->Name = "l_summe";
	
	System::Windows::Forms::TextBox^ tB_summe = gcnew System::Windows::Forms::TextBox();
	tB_summe->Location= System::Drawing::Point(spalte_bew_betrag,eintrag*zeilen_abstand+beginn);
	tB_summe->TabIndex = tab_index; tab_index++;
	tB_summe->Name = "tB_summe";
	tB_summe->Size = System::Drawing::Size(127, 20);
	tB_summe->TextChanged += gcnew System::EventHandler(this, &verwendungsnachweis_form::tB_summe_TextChanged);
	tB_summe->Leave += gcnew System::EventHandler(this, &verwendungsnachweis_form::tB_summe_Leave);

	System::Windows::Forms::Label^  l_zuwendungsf = gcnew System::Windows::Forms::Label();	
	l_zuwendungsf->Location= System::Drawing::Point(spalte_bew_bund_land, eintrag*zeilen_abstand+beginn+5);
	l_zuwendungsf->AutoSize = true;
	l_zuwendungsf->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	l_zuwendungsf->Text = "Zuwendungsfähige GK";
	l_zuwendungsf->Name = "l_zuwendungsf";

	System::Windows::Forms::TextBox^ tB_zuwendungsf = gcnew System::Windows::Forms::TextBox();
	tB_zuwendungsf->Location= System::Drawing::Point(spalte_bew_mla,eintrag*zeilen_abstand+beginn);
	tB_zuwendungsf->TabIndex = tab_index; tab_index++;
	tB_zuwendungsf->Name = "tB_zuwendungsf";
	tB_zuwendungsf->Size = System::Drawing::Size(127, 20);
	tB_zuwendungsf->TextChanged += gcnew System::EventHandler(this, &verwendungsnachweis_form::tB_zuwendungsf_TextChanged);
	tB_zuwendungsf->Leave += gcnew System::EventHandler(this, &verwendungsnachweis_form::tB_zuwendungsf_Leave);

	tabPage1->Controls->Add(l_summe);
	tabPage1->Controls->Add(tB_summe);
	tabPage1->Controls->Add(l_zuwendungsf);
	tabPage1->Controls->Add(tB_zuwendungsf);
}

void verwendungsnachweis_form::load_ausgaben()
{
	int spalte_label = 5;
	int spalte_gk = 175;
	int spalte_gf = 375;
	int beginn=35;
	int abstand=20;
	int eintrag=0;

	List<String^> adr_list = projekt_->get_adressen();

	adr_list.Sort();

	for each(String^ adress_eintrag in adr_list)
	{
		adresse^ adr=projekt_->get_adresse(adress_eintrag);
		// Adresse Label
		System::Windows::Forms::Label^  adresse_label = gcnew System::Windows::Forms::Label();	
		adresse_label->Location = System::Drawing::Point(spalte_label,eintrag*abstand+beginn+5);
		adresse_label->AutoSize = true;
		adresse_label->Text = adress_eintrag;
		adresse_label->Name = adress_eintrag+"-label";

		// Adresse gk
		System::Windows::Forms::TextBox^ adresse_gk = gcnew System::Windows::Forms::TextBox();
		adresse_gk->Location = System::Drawing::Point(spalte_gk,eintrag*abstand+beginn);
		adresse_gk->Size = System::Drawing::Size(127, 13);
		adresse_gk->Text = Decimal_to_string(adr->get_einzel_gk_vn());
		adresse_gk->Name = adress_eintrag+"-gk";
		adresse_gk->TextChanged += gcnew System::EventHandler(this, &verwendungsnachweis_form::AdrChanged);
		adresse_gk->Leave += gcnew System::EventHandler(this, &verwendungsnachweis_form::AdrLeave);

		// Adresse gf
		System::Windows::Forms::TextBox^ adresse_gf = gcnew System::Windows::Forms::TextBox();
		adresse_gf->Location = System::Drawing::Point(spalte_gf,eintrag*abstand+beginn);
		adresse_gf->Size = System::Drawing::Size(127, 13);
		adresse_gf->Text = Decimal_to_string(adr->get_einzel_gf_vn());
		adresse_gf->Name = adress_eintrag+"-gf";
		adresse_gf->TextChanged += gcnew System::EventHandler(this, &verwendungsnachweis_form::AdrChanged);
		adresse_gf->Leave += gcnew System::EventHandler(this, &verwendungsnachweis_form::AdrLeave);

		eintrag ++;

		tabPage2->Controls->Add(adresse_label);
		tabPage2->Controls->Add(adresse_gk);
		tabPage2->Controls->Add(adresse_gf);
	}
	eintrag++;
	l_summe_ausgaben->Location = System::Drawing::Point(spalte_label,eintrag*abstand+beginn+5);
	summe_egk->Location = System::Drawing::Point(spalte_gk,eintrag*abstand+beginn+5);
	summe_ef->Location = System::Drawing::Point(spalte_gf,eintrag*abstand+beginn+5);
}

void verwendungsnachweis_form::aktualisiere()
{
	// Einnahmen
	Decimal summe=0;
	Decimal mehr_minder_summe=0;
	for each(String^ programm_eintrag in projekt_->get_programme())
	{		
		List<String^>^ bewilligungen = projekt_->get_bewilligungen(programm_eintrag);
		for(int i=0;i<bewilligungen->Count;++i)
		{
			bewilligung_class^ bewilligung = projekt_->get_bewilligung(programm_eintrag,i);
			Decimal mehr_minder=(bewilligung->get_mla_vn()+bewilligung->get_bund_land_vn())-(bewilligung->get_mla()+bewilligung->get_bund_land());
			mehr_minder_summe+=mehr_minder;
			Decimal betrag=bewilligung->get_mla_vn()+bewilligung->get_bund_land_vn();
			summe+=betrag;
			tabPage1->Controls->Find(programm_eintrag+"-"+Convert::ToString(i)+"-betrag_dez",true)[0]->Text=Decimal_to_dez(betrag);
			tabPage1->Controls->Find(programm_eintrag+"-"+Convert::ToString(i)+"-betrag_kom",true)[0]->Text=Decimal_to_kom(betrag);

			tabPage1->Controls->Find(programm_eintrag+"-"+Convert::ToString(i)+"-mehrminder_dez",true)[0]->Text=Decimal_to_dez(mehr_minder);
			tabPage1->Controls->Find(programm_eintrag+"-"+Convert::ToString(i)+"-mehrminder_kom",true)[0]->Text=Decimal_to_kom(mehr_minder);
		}
	}	
	tabPage1->Controls->Find("l_mehrminder_summe_dez",true)[0]->Text=Decimal_to_dez(mehr_minder_summe);
	tabPage1->Controls->Find("l_mehrminder_summe_kom",true)[0]->Text=Decimal_to_kom(mehr_minder_summe);

	Decimal gesamtfremdfoerderung=projekt_->get_gesamtfremdfoerderung_vn();
	tabPage1->Controls->Find("l_ff_betrag_dez",true)[0]->Text=Decimal_to_dez(gesamtfremdfoerderung);
	tabPage1->Controls->Find("l_ff_betrag_kom",true)[0]->Text=Decimal_to_kom(gesamtfremdfoerderung);
	Decimal gk_real=projekt_->get_gk_real_vn();
	if(!tabPage1->Controls->Find("tB_summe",true)[0]->Focused)
		tabPage1->Controls->Find("tB_summe",true)[0]->Text=Decimal_to_string(gk_real);

	Decimal bha=gk_real-(summe+gesamtfremdfoerderung);

	tabPage1->Controls->Find("l_bha_betrag_dez",true)[0]->Text=Decimal_to_dez(bha);
	tabPage1->Controls->Find("l_bha_betrag_kom",true)[0]->Text=Decimal_to_kom(bha);
	tabPage1->Controls->Find("tB_zuwendungsf",true)[0]->Text=Decimal_to_string(projekt_->get_gk_zuwendungsf_vn());

	// Ausgaben
	Decimal summe_gk=0;
	Decimal summe_gf=0;
	for each(String^ adress_eintrag in projekt_->get_adressen())
	{
		adresse^ adr=projekt_->get_adresse(adress_eintrag);
		summe_gk+=adr->get_einzel_gk_vn();
		summe_gf+=adr->get_einzel_gf_vn();
	}
	summe_egk->Text=Decimal_to_string(summe_gk);
	summe_ef->Text=Decimal_to_string(summe_gf);

	// Übersicht
	l_gk_ein->Text=Decimal_to_string(gk_real);
	l_gk_aus->Text=summe_egk->Text;
	l_gf_ein->Text=Decimal_to_string(summe);
	l_gf_aus->Text=summe_ef->Text;
}

void verwendungsnachweis_form::tB_summe_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=tabPage1->Controls->Find("tB_summe",true)[0]->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace(L"€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		projekt_->set_gk_real_vn(Decimal(Convert::ToDouble(txt)));
		tabPage1->Controls->Find("tB_summe",true)[0]->BackColor=Color::FromName("White");
		aktualisiere();
	}
	else
		tabPage1->Controls->Find("tB_summe",true)[0]->BackColor=Color::FromName("LavenderBlush");
}

void verwendungsnachweis_form::tB_summe_Leave(System::Object^  sender, System::EventArgs^  e)
{
	aktualisiere();
}

void verwendungsnachweis_form::tB_zuwendungsf_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	String^ txt=tabPage1->Controls->Find("tB_zuwendungsf",true)[0]->Text;
	txt=txt->Replace(".","");
	txt=txt->Replace(L"€","");
	txt=txt->Trim();
	if(txt->Length>0)
		if(txt[txt->Length-1]==',')
			txt=txt->Remove(txt->Length-1);
	if(check_if_Decimal(txt))
	{
		projekt_->set_gk_zuwendungsf_vn(Decimal(Convert::ToDouble(txt)));
		tabPage1->Controls->Find("tB_zuwendungsf",true)[0]->BackColor=Color::FromName("White");
	}
	else
		tabPage1->Controls->Find("tB_zuwendungsf",true)[0]->BackColor=Color::FromName("LavenderBlush");
}

void verwendungsnachweis_form::tB_zuwendungsf_Leave(System::Object^  sender, System::EventArgs^  e)
{
	aktualisiere();
}

void verwendungsnachweis_form::AdrLeave(System::Object^  sender, System::EventArgs^  e)
{
	int index=-1;
	for(int i=0;i<tabPage2->Controls->Count;++i)
		if(ReferenceEquals(tabPage2->Controls[i],sender))
		{
			index=i;
			break;
		}

	if(tabPage2->Controls[index]->BackColor==Color::FromName("White"))
	{
		String^ name=tabPage2->Controls[index]->Name;
		String^ text=tabPage2->Controls[index]->Text;

		String^ aim="";
		String^ adr="";
		for(int i=name->Length-1;i>=0;--i)
		{
			if(name[i]=='-')
			{
				name=name->Remove(i,1);
				break;
			}
			aim+=name[i];
			name=name->Remove(i,1);
		}
		for(int i=name->Length-1;i>=0;--i)
		{
			adr+=name[i];
			name=name->Remove(i,1);
		}
		aim=reverse(aim);
		adr=reverse(adr);

		adresse^ adress=projekt_->get_adresse(adr);
		Decimal betrag=0;
		if(aim=="gk")
		{
			betrag=adress->get_einzel_gk_vn();
		}
		else
		{
			betrag=adress->get_einzel_gf_vn();
		}
		tabPage2->Controls[index]->Text=Decimal_to_string(betrag);
	}
}

void verwendungsnachweis_form::AdrChanged(System::Object^  sender, System::EventArgs^  e)
{
	int index=-1;
	for(int i=0;i<tabPage2->Controls->Count;++i)
		if(ReferenceEquals(tabPage2->Controls[i],sender))
		{
			index=i;
			break;
		}
	String^ name=tabPage2->Controls[index]->Name;
	String^ text=tabPage2->Controls[index]->Text;

	text=text->Replace(".","");
	text=text->Replace(L"€","");
	text=text->Trim();

	if(check_if_Decimal(text))
	{
		String^ aim="";
		String^ adr="";
		for(int i=name->Length-1;i>=0;--i)
		{
			if(name[i]=='-')
			{
				name=name->Remove(i,1);
				break;
			}
			aim+=name[i];
			name=name->Remove(i,1);
		}
		for(int i=name->Length-1;i>=0;--i)
		{
			adr+=name[i];
			name=name->Remove(i,1);
		}
		aim=reverse(aim);
		adr=reverse(adr);
		tabPage2->Controls[index]->BackColor=Color::FromName("White");
		adresse^ adress=projekt_->get_adresse(adr);
		if(aim=="gk")
		{
			adress->set_einzel_gk_vn(Decimal(Convert::ToDouble(text)));
		}
		else
		{
			adress->set_einzel_gf_vn(Decimal(Convert::ToDouble(text)));
		}
		aktualisiere();
	}
	else
	{
		tabPage2->Controls[index]->BackColor=Color::FromName("LavenderBlush");
	}
}

void verwendungsnachweis_form::Leave(System::Object^  sender, System::EventArgs^  e)
{
	int index=-1;
	for(int i=0;i<tabPage1->Controls->Count;++i)
		if(ReferenceEquals(tabPage1->Controls[i],sender))
		{
			index=i;
			break;
		}
	String^ name=tabPage1->Controls[index]->Name;
	String^ text=tabPage1->Controls[index]->Text;

	String^ aim="";
	String^ nr="";
	String^ programm="";
	for(int i=name->Length-1;i>=0;--i)
	{
		if(name[i]=='-')
		{
			name=name->Remove(i,1);
			break;
		}
		aim+=name[i];
		name=name->Remove(i,1);
	}
	for(int i=name->Length-1;i>=0;--i)
	{
		if(name[i]=='-')
		{
			name=name->Remove(i,1);
			break;
		}
		nr+=name[i];
		name=name->Remove(i,1);
	}
	for(int i=name->Length-1;i>=0;--i)
	{
		programm+=name[i];
		name=name->Remove(i,1);
	}
	aim=reverse(aim);
	nr=reverse(nr);
	programm=reverse(programm);
	if(tabPage1->Controls[index]->BackColor==Color::FromName("White"))
	{
		Decimal betrag=0;
		bewilligung_class^ bewilligung=projekt_->get_bewilligung(programm,Convert::ToInt32(nr));
		if(aim=="mla")
			betrag=bewilligung->get_mla_vn();
		else
			betrag=bewilligung->get_bund_land_vn();
		tabPage1->Controls[index]->Text=Decimal_to_string(betrag);
	}
}

void verwendungsnachweis_form::TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	int index=-1;
	for(int i=0;i<tabPage1->Controls->Count;++i)
		if(ReferenceEquals(tabPage1->Controls[i],sender))
		{
			index=i;
			break;
		}
	String^ name=tabPage1->Controls[index]->Name;
	String^ text=tabPage1->Controls[index]->Text;

	text=text->Replace(".","");
	text=text->Replace(L"€","");
	text=text->Trim();

	if(check_if_Decimal(text))
	{
		String^ aim="";
		String^ nr="";
		String^ programm="";
		for(int i=name->Length-1;i>=0;--i)
		{
			if(name[i]=='-')
			{
				name=name->Remove(i,1);
				break;
			}
			aim+=name[i];
			name=name->Remove(i,1);
		}
		for(int i=name->Length-1;i>=0;--i)
		{
			if(name[i]=='-')
			{
				name=name->Remove(i,1);
				break;
			}
			nr+=name[i];
			name=name->Remove(i,1);
		}
		for(int i=name->Length-1;i>=0;--i)
		{
			programm+=name[i];
			name=name->Remove(i,1);
		}
		aim=reverse(aim);
		nr=reverse(nr);
		programm=reverse(programm);
		tabPage1->Controls[index]->BackColor=Color::FromName("White");
		bewilligung_class^ bewilligung=projekt_->get_bewilligung(programm,Convert::ToInt32(nr));
		if(aim=="mla")
		{
			bewilligung->set_mla_vn(Decimal(Convert::ToDouble(text)));
		}
		else
		{
			bewilligung->set_bund_land_vn(Decimal(Convert::ToDouble(text)));
		}
		aktualisiere();
	}
	else
	{
		tabPage1->Controls[index]->BackColor=Color::FromName("LavenderBlush");
	}
}

String^ verwendungsnachweis_form::reverse(String^ input)
{
	String^ ausgabe="";
	for(int i=input->Length-1;i>=0;--i)
		ausgabe+=input[i];
	return ausgabe;
}

void verwendungsnachweis_form::btn_ff_Click(System::Object^  sender, System::EventArgs^  e)
{
	Form^ fremdfoerdermittel = gcnew fremdfoerdermittel_form(projekt_->get_fremdfoerderung_vn(),false,load_);
	fremdfoerdermittel->ShowDialog();
	if(load_)
	{
		load_einnahmen();
		aktualisiere();
	}
}

void verwendungsnachweis_form::back_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}