#include "StdAfx.h"
#include "adress_uebersicht_result.h"

#include "My_Connection.h"
#include "MyResult.h"
#include "project_form.h"
#include "choose_printer.h"
#include "MyRecordSet.h"
#include "helper.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

// Loader
void adress_uebersicht_result::adress_uebersicht_result_Load(System::Object^  sender, System::EventArgs^  e)
{
	Hide();
	ladebalken_->Show();
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Adressübersicht";
	page_content_->Clear();
	pages_=0;
	start_=0;
	this->AutoSize=true;
	this->Controls->Clear();

	//Windows::Forms::MessageBox::Show("t1");
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Städte,Gebiete und Adressen";
	load_main_entries();

	My_Connection data;
	data.connect();

	List<String^>^ staedte=get_staedte();
	staedte->Sort();
	
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Daten für gefundene Adressen";
	for each(String^ stadt in staedte)
	{
		List<String^>^ gebiete=get_gebiete(stadt);
		gebiete->Sort();

		for each(String^ gebiet in gebiete)
		{
			List<String^>^ adressen=get_adressen(stadt,gebiet);
			
			adressen->Sort();

			entries_->Clear();

			MyResult^ R_Projekte=data.get_result("SELECT ID,bezeichnung,bew_ztr,vn_einger,vn_gepr FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"'");
			for(int projekt_param=0;projekt_param<R_Projekte->get_row();++projekt_param)
			{
				String^ id=R_Projekte->get_val(projekt_param,0);
				String^ bezeichnung=R_Projekte->get_val(projekt_param,1);
				String^ bew_ztr=R_Projekte->get_val(projekt_param,2);
				String^ vn_einger=R_Projekte->get_val(projekt_param,3);
				if(vn_einger=="")
					vn_einger="nicht eingereicht";
				String^ vn_gepr=R_Projekte->get_val(projekt_param,4);
				if(vn_gepr=="")
					vn_gepr="nicht geprüft";

				int anzahl=0;
				MyResult^ R_Projekte_Programme=data.get_result("SELECT ID FROM db_programme WHERE projekt_ID="+R_Projekte->get_val(projekt_param,0));
				for(int programm_param=0;programm_param<R_Projekte_Programme->get_row();++programm_param)
				{
					MyResult^ R_Projekte_Programme_bew=data.get_result("SELECT ID FROM db_programme_bewilligung WHERE programm_ID="+R_Projekte_Programme->get_val(programm_param,0));
					anzahl+=R_Projekte_Programme_bew->get_row();
				}

				String^ bew_anzahl=Convert::ToString(anzahl);
				MyResult^ R_Projekt_Adressen=data.get_result("SELECT * FROM db_adressen WHERE Projekt_ID="+R_Projekte->get_val(projekt_param,0));
				for(int adress_param=0;adress_param<R_Projekt_Adressen->get_row();++adress_param)
				{
					String^ adresse=R_Projekt_Adressen->get_val(adress_param,2);
					if(is_existent_in(adressen,adresse))
					{
						List<String^>^ cache = gcnew List<String^>;
						String^ kosten=R_Projekt_Adressen->get_val(adress_param,3);
						String^ foerderung=R_Projekt_Adressen->get_val(adress_param,4);
						if(vn_einger!="nicht eingereicht" && vn_gepr=="nicht geprüft")
						{
							kosten=R_Projekt_Adressen->get_val(adress_param,5);
							foerderung=R_Projekt_Adressen->get_val(adress_param,6);
						}
						
						cache->Add(adresse);
						if(bezeichnung->Length>32)
							bezeichnung=bezeichnung->Substring(0,32);
						cache->Add(bezeichnung);
						cache->Add(bew_anzahl);
						cache->Add(bew_ztr);
						cache->Add(vn_einger);
						cache->Add(vn_gepr);
						cache->Add(kosten);
						cache->Add(foerderung);
						cache->Add(id);

						entries_->Add(cache);
						ladebalken_->Controls->Find("progress",true)[0]->Text="a";
						ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
					}
				}
			}
			create_main_entries(stadt,gebiet,adressen);
		}
	}
	data.disconnect();
	place_print_button();
	ladebalken_->Hide();
	Show();
}

void adress_uebersicht_result::load_main_entries()
{
	main_entries_->Clear();

	My_Connection data;
	data.connect();
	
	List<String^>^ staedte=gcnew List<String^>;
	if(stadt_=="-1")
	{
		MyResult^ R_Staedte=data.get_result("SELECT Stadt FROM Staedte");
		for(int i=0;i<R_Staedte->get_row();++i)
			staedte->Add(R_Staedte->get_val(i,0));
	}
	else
		staedte->Add(stadt_);

	for(int stadt_param=0;stadt_param<staedte->Count;++stadt_param)
	{
		String^ stadt=staedte[stadt_param];

		List<String^>^ gebiete=gcnew List<String^>;
		if(gebiet_=="-1")
		{
			MyResult^ R_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
			MyResult^ R_Gebiete=data.get_result("SELECT Gebiet FROM Gebiete Where Stadt_ID="+R_Stadt->get_val(0,0));
			for(int i=0;i<R_Gebiete->get_row();++i)
				gebiete->Add(R_Gebiete->get_val(i,0));
		}
		else
			gebiete->Add(gebiet_);

		for(int gebiet_param=0;gebiet_param<gebiete->Count;++gebiet_param)
		{
			String^ gebiet=gebiete[gebiet_param];

			List<String^>^ adressen=gcnew List<String^>;
			if(adresse_=="-1")
			{
				MyResult^ R_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
				MyResult^ R_Gebiete=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+R_Stadt->get_val(0,0)+" AND Gebiet='"+gebiet+"'");
				MyResult^ R_Adresse=data.get_result("SELECT Strasse FROM Strassen WHERE Gebiet_ID="+R_Gebiete->get_val(0,0));
				for(int i=0;i<R_Adresse->get_row();++i)
					adressen->Add(R_Adresse->get_val(i,0));
			}
			else
				adressen->Add(adresse_);

			for(int adressen_param=0;adressen_param<adressen->Count;++adressen_param)
			{
				String^ adresse=adressen[adressen_param];

				List<String^>^ cache =gcnew List<String^>;
				cache->Add(stadt);
				cache->Add(gebiet);
				cache->Add(adresse);

				main_entries_->Add(cache);

			}
			
			ladebalken_->Controls->Find("progress",true)[0]->Text="a";
			ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
		}
	}

	data.disconnect();
}

List<String^>^ adress_uebersicht_result::get_staedte()
{
	List<String^>^ staedte = gcnew List<String^>;

	for(int i=0;i<main_entries_->Count;++i)
		if(!is_existent_in(staedte,main_entries_[i][0]))
			staedte->Add(main_entries_[i][0]);

	return staedte;
}

List<String^>^ adress_uebersicht_result::get_gebiete(String^ stadt)
{
	List<String^>^ gebiete = gcnew List<String^>;

	for(int i=0;i<main_entries_->Count;++i)
		if(main_entries_[i][0]==stadt)
			if(!is_existent_in(gebiete,main_entries_[i][1]))
				gebiete->Add(main_entries_[i][1]);

	return gebiete;
}

List<String^>^ adress_uebersicht_result::get_adressen(String^ stadt,String^ gebiet)
{
	List<String^>^ adressen = gcnew List<String^>;

	for(int i=0;i<main_entries_->Count;++i)
		if(main_entries_[i][0]==stadt && main_entries_[i][1]==gebiet)
			if(!is_existent_in(adressen,main_entries_[i][2]))
				adressen->Add(main_entries_[i][2]);

	return adressen;
}

bool adress_uebersicht_result::is_existent_in(List<String^>^ liste,String^ value)
{
	for each(String^ eintrag in liste)
		if(eintrag==value)
			return true;
	return false;
}

void adress_uebersicht_result::sort_for_bew_ztr(List< List<String^>^ >^ input)
{
	for(int i=input->Count;i>1;--i)
	{
		for (int j=0; j<i-1 ; ++j)
		{
			// XX.XX.XXXX
			String^ jahr1=input[j][3]->Substring(6,4);
			String^ monat1=input[j][3]->Substring(3,2);
			String^ tag1=input[j][3]->Substring(0,2);
			String^ jahr2=input[j+1][3]->Substring(6,4);
			String^ monat2=input[j+1][3]->Substring(3,2);
			String^ tag2=input[j+1][3]->Substring(0,2);

			String^ datum1=jahr1+monat1+tag1;
			String^ datum2=jahr2+monat2+tag2;

			if (Convert::ToInt32(datum1) > Convert::ToInt32(datum2))
			{
				List<String^>^ cache=input[j];
				input[j]=input[j+1];
				input[j+1]=cache;
			}
		}
	}
}

void adress_uebersicht_result::create_main_entries(String^ stadt, String^ gebiet, List<String^>^ adressen)
{
	for each(String^ adresse in adressen)
	{
		List< List<String^>^ >^ cache = gcnew List< List<String^>^ >;

		for(int entry_param=0;entry_param<entries_->Count;++entry_param)
			if(entries_[entry_param][0]==adresse)
				cache->Add(entries_[entry_param]);

		sort_for_bew_ztr(cache);
		//Windows::Forms::MessageBox::Show("t1");

		if(cache->Count!=0)
		{
			generate_header(stadt,gebiet,adresse);
			++row_;
			GenerateTableHeader();
			++row_;
			Decimal ges_kosten=0;
			Decimal ges_foerderung=0;
			int start = row_;
			for(int i=0;i<cache->Count;++i)
			{
				String^ bezeichnung=cache[i][1];
				String^ bew_anzahl=cache[i][2];
				String^ bew_ztr=cache[i][3];
				String^ vn_einger=cache[i][4];
				String^ vn_gepr=cache[i][5];

				String^ kosten_str=cache[i][6];
				Decimal kosten=Decimal(Convert::ToDouble(kosten_str));
				ges_kosten+=kosten;
				kosten_str=Decimal_to_string(kosten);

				String^ foerderung_str=cache[i][7];
				Decimal foerderung=Decimal(Convert::ToDouble(foerderung_str));
				ges_foerderung+=foerderung;
				foerderung_str=Decimal_to_string(foerderung);

				String^ id=cache[i][8];

				generate_entry(id,bezeichnung,bew_anzahl,bew_ztr,vn_einger,vn_gepr,kosten_str,foerderung_str,i);
				
				exl_->setCell(row_,2,bezeichnung);
				exl_->setCell(row_,3,bew_ztr);
				exl_->setCell(row_,4,bew_anzahl);
				exl_->setCell(row_,5,vn_einger);
				exl_->setCell(row_,6,vn_gepr);
				exl_->setCellCurrency(row_,7,kosten);  //costs
				exl_->setCellCurrency(row_,8,foerderung);
				++row_;
			}

			String^ ges_kosten_str=Decimal_to_string(ges_kosten);
			String^ ges_foerderung_str=Decimal_to_string(ges_foerderung);

			//exl_->setCellCurrency(row_,7,ges_kosten);
			//exl_->setCellCurrency(row_,8,ges_foerderung);
			exl_->setCellSum(row_,7,start,row_-1);
			exl_->setCellSum(row_,8,start,row_-1);
			exl_->setCellBold(row_,7);
			exl_->setCellBold(row_,8);
			++row_;

			generate_footer(ges_kosten_str,ges_foerderung_str);
			ladebalken_->Controls->Find("progress",true)[0]->Text="a";
			ladebalken_->Controls->Find("progress",true)[0]->Text=" ";

			++row_;
		}
	}
}

// Auswertungselemente
void adress_uebersicht_result::generate_header(String^ stadt, String^ gebiet, String^ adresse)
{
	page_content_->Add(gcnew List< List<String^>^ >);
	List<String^>^ header=gcnew List<String^>;
	header->Add("header");
	header->Add(stadt);
	header->Add(gebiet);
	header->Add(adresse);
	page_content_[page_content_->Count-1]->Add(header);

	if(start_!=0)
		start_+=10;

	System::Windows::Forms::Label^  label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(5, 1+start_);
	label->AutoSize = true;
	label->Text = adresse+" in "+stadt+" ("+gebiet+")";
	label->BackColor = System::Drawing::Color::Silver;
	label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(label);
	exl_->setCell(row_,1,adresse+" in "+stadt+" ("+gebiet+")");
	exl_->setCellItalic(row_,1);

	System::Windows::Forms::Label^  header_back = gcnew System::Windows::Forms::Label();
	header_back->Location = System::Drawing::Point(0, start_);
	header_back->AutoSize = false;
	header_back->Size = System::Drawing::Size(936, 15);
	header_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(header_back);	

	start_+=15;
}

void adress_uebersicht_result::GenerateTableHeader()
{
	start_+=10;

	int spalte_bezeichnung=10;
	int spalte_bew_anz=270;
	int spalte_bew_ztr=200;
	int spalte_vn_einger=370;
	int spalte_vn_gepr=470;
	int spalte_kosten=550;
	int spalte_foerderung=720;

	System::Windows::Forms::Label^  bez = gcnew System::Windows::Forms::Label();
	bez->Location = System::Drawing::Point(spalte_bezeichnung, start_);
	bez->AutoSize = true;
	bez->Text = "Bezeichnung";
	bez->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(bez);

	System::Windows::Forms::Label^  vom = gcnew System::Windows::Forms::Label();
	vom->Location = System::Drawing::Point(spalte_bew_ztr, start_);
	vom->AutoSize = true;
	vom->Text = "BWZ";
	vom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(vom);

	System::Windows::Forms::Label^  bew_anz = gcnew System::Windows::Forms::Label();
	bew_anz->Location = System::Drawing::Point(spalte_bew_anz, start_);
	bew_anz->AutoSize = true;
	bew_anz->Text = "Anzahl der Bew.";
	bew_anz->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(bew_anz);

	System::Windows::Forms::Label^  einger = gcnew System::Windows::Forms::Label();
	einger->Location = System::Drawing::Point(spalte_vn_einger, start_);
	einger->AutoSize = true;
	einger->Text = "VN eingereicht am";
	einger->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(einger);

	System::Windows::Forms::Label^  gepr = gcnew System::Windows::Forms::Label();
	gepr->Location = System::Drawing::Point(spalte_vn_gepr, start_);
	gepr->AutoSize = true;
	gepr->Text = "VN geprüft am";
	gepr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(gepr);

	System::Windows::Forms::Label^  label_kosten = gcnew System::Windows::Forms::Label();
	label_kosten->Location = System::Drawing::Point(spalte_kosten,start_);
	label_kosten->AutoSize = false;
	label_kosten->Size = System::Drawing::Size(150, 13);
	label_kosten->TextAlign = System::Drawing::ContentAlignment::TopRight;
	label_kosten->Text = "Gesamtkosten";
	label_kosten->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(label_kosten);

	System::Windows::Forms::Label^  label_foerderung = gcnew System::Windows::Forms::Label();
	label_foerderung->Location = System::Drawing::Point(spalte_foerderung,start_);
	label_foerderung->AutoSize = false;
	label_foerderung->Size = System::Drawing::Size(150, 13);
	label_foerderung->TextAlign = System::Drawing::ContentAlignment::TopRight;
	label_foerderung->Text = "Gesamtförderung";
	label_foerderung->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	this->Controls->Add(label_foerderung);

	exl_->setCell(row_,2,"Bezeichnung");
	exl_->setCell(row_,3,"BWZ");
	exl_->setCell(row_,4,"Anzahl der Bew.");
	exl_->setCell(row_,5,"VN eingereicht am");
	exl_->setCell(row_,6,"VN geprüft am");
	exl_->setCell(row_,7,"Gesamtkosten");
	exl_->setCell(row_,8,"Gesamtförderung");
	for(int j=0;j<7;++j) {
		exl_->setCellBold(row_,2+j);
		exl_->setCellAutofit(row_,2+j);
	}

	start_+=20;
}

void adress_uebersicht_result::generate_entry(String^ id,String^ bezeichnung, String^ bew_anzahl, String^ bew_ztr, String^ vn_einger, String^ vn_gepr, String^ kosten, String^ foerderung, int eintrag)
{
	System::Drawing::Color color;
	if(eintrag%2==0)
	{
		color=System::Drawing::Color::Gainsboro;
	}
	else
	{
		color=System::Drawing::Color::White;
	}

	List<String^>^ entry=gcnew List<String^>;
	entry->Add("eintrag");
	entry->Add(bezeichnung);
	entry->Add(bew_anzahl);
	entry->Add(bew_ztr);
	entry->Add(vn_einger);
	entry->Add(vn_gepr);
	entry->Add(kosten);
	entry->Add(foerderung);
	page_content_[page_content_->Count-1]->Add(entry);

	if(vn_einger=="nicht eingereicht")
	{
		vn_einger="Plankosten";
		vn_gepr="";
	}

	int spalte_bezeichnung=10;
	int spalte_bew_anz=300;
	int spalte_bew_ztr=200;
	int spalte_vn_einger=370;
	int spalte_vn_gepr=470;
	int spalte_kosten=550;
	int spalte_foerderung=720;

	System::Windows::Forms::Label^  bez = gcnew System::Windows::Forms::Label();
	bez->Location = System::Drawing::Point(spalte_bezeichnung, start_);
	bez->AutoSize = true;
	bez->Text = bezeichnung;
	bez->Name = id;
	bez->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	bez->BackColor = color;
	this->Controls->Add(bez);

	System::Windows::Forms::Label^  vom = gcnew System::Windows::Forms::Label();
	vom->Location = System::Drawing::Point(spalte_bew_ztr, start_);
	vom->AutoSize = true;
	vom->Text = bew_ztr;
	vom->Name = id;
	vom->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	vom->BackColor = color;
	this->Controls->Add(vom);

	System::Windows::Forms::Label^  bew_anz = gcnew System::Windows::Forms::Label();
	bew_anz->Location = System::Drawing::Point(spalte_bew_anz, start_);
	bew_anz->AutoSize = true;
	bew_anz->Text = bew_anzahl;
	bew_anz->Name = id;
	bew_anz->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	bew_anz->BackColor = color;
	this->Controls->Add(bew_anz);

	System::Windows::Forms::Label^  einger = gcnew System::Windows::Forms::Label();
	einger->Location = System::Drawing::Point(spalte_vn_einger, start_);
	einger->AutoSize = true;
	einger->Text = vn_einger;
	einger->Name = id;
	einger->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	einger->BackColor = color;
	this->Controls->Add(einger);

	System::Windows::Forms::Label^  gepr = gcnew System::Windows::Forms::Label();
	gepr->Location = System::Drawing::Point(spalte_vn_gepr, start_);
	gepr->AutoSize = true;
	gepr->Text = vn_gepr;
	gepr->Name = id;
	gepr->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	gepr->BackColor = color;
	this->Controls->Add(gepr);

	System::Windows::Forms::Label^  label_kosten = gcnew System::Windows::Forms::Label();
	label_kosten->Location = System::Drawing::Point(spalte_kosten,start_);
	label_kosten->AutoSize = false;
	label_kosten->Size = System::Drawing::Size(150, 13);
	label_kosten->TextAlign = System::Drawing::ContentAlignment::TopRight;
	label_kosten->Text = kosten;
	label_kosten->Name = id;
	label_kosten->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	label_kosten->BackColor = color;
	this->Controls->Add(label_kosten);

	System::Windows::Forms::Label^  label_foerderung = gcnew System::Windows::Forms::Label();
	label_foerderung->Location = System::Drawing::Point(spalte_foerderung,start_);
	label_foerderung->AutoSize = false;
	label_foerderung->Size = System::Drawing::Size(150, 13);
	label_foerderung->TextAlign = System::Drawing::ContentAlignment::TopRight;
	label_foerderung->Text = foerderung;
	label_foerderung->Name = id;
	label_foerderung->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	label_foerderung->BackColor = color;
	this->Controls->Add(label_foerderung);

	System::Windows::Forms::Label^  line_back = gcnew System::Windows::Forms::Label();
	line_back->Location = System::Drawing::Point(0,start_-3);
	line_back->Name = id;
	line_back->AutoSize = false;
	line_back->Size = System::Drawing::Size(936, 20);
	line_back->BackColor = color;
	line_back->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::Click);
	this->Controls->Add(line_back);

	start_+=20;
}

void adress_uebersicht_result::generate_footer(String^ kosten, String^ foerderung)
{
	List<String^>^ footer=gcnew List<String^>;
	footer->Add("footer");
	footer->Add(kosten);
	footer->Add(foerderung);
	page_content_[page_content_->Count-1]->Add(footer);

	int spalte_kosten=550;
	int spalte_foerderung=720;

	System::Windows::Forms::Label^  label_kosten = gcnew System::Windows::Forms::Label();
	label_kosten->Location = System::Drawing::Point(spalte_kosten,start_);
	label_kosten->AutoSize = false;
	label_kosten->Size = System::Drawing::Size(150, 13);
	label_kosten->TextAlign = System::Drawing::ContentAlignment::TopRight;
	label_kosten->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	label_kosten->Text = kosten;
	this->Controls->Add(label_kosten);

	System::Windows::Forms::Label^  label_foerderung = gcnew System::Windows::Forms::Label();
	label_foerderung->Location = System::Drawing::Point(spalte_foerderung,start_);
	label_foerderung->AutoSize = false;
	label_foerderung->Size = System::Drawing::Size(150, 13);
	label_foerderung->TextAlign = System::Drawing::ContentAlignment::TopRight;
	label_foerderung->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
	label_foerderung->Text = foerderung;
	this->Controls->Add(label_foerderung);

	start_+=20;
}

void adress_uebersicht_result::place_print_button()
{
	start_=start_+10;

	if(start_==10)
	{
		ladebalken_->Close();
		Windows::Forms::MessageBox::Show("Es wurden keine Einträge zu ihrer Anfrage gefunden.","Ungültige Suche");
		Close();
	}

	btn_print->Location=System::Drawing::Point(5, start_);
	btn_print->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_print);

	start_=start_+30;

	btn_exportExl->Location=System::Drawing::Point(5, start_);
	btn_exportExl->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_exportExl);

	System::Windows::Forms::Label^  label_freespace = gcnew System::Windows::Forms::Label();
	label_freespace->Location = System::Drawing::Point(0,start_+20);
	label_freespace->AutoSize = false;
	label_freespace->Size = System::Drawing::Size(5, 10);
	this->Controls->Add(label_freespace);
}

// Events
void adress_uebersicht_result::Click(System::Object^  sender, System::EventArgs^  e)
{
	int index1=-1;
	int index2=-1;
	for(int i=0;i<this->Controls->Count;++i)
		if(ReferenceEquals(this->Controls[i],sender))
		{
			index1=i;
			break;
		}
		else
			for(int j=0;j<this->Controls[i]->Controls->Count;++j)
				if(ReferenceEquals(this->Controls[i]->Controls[j],sender))
				{
					index1=i;
					index2=j;
					break;
				}

	int id=-1;
	if(index2==-1)
		id=Convert::ToInt32(this->Controls[index1]->Name);
	else
		id=Convert::ToInt32(this->Controls[index1]->Controls[index2]->Name);

	String^ message = "Wird das Projekt geöffnet, wird die Auswertung nach Schließen des Projektes neu geladen.\nFortfahren ?";
	String^ caption = "Soll das Projekt geöffnet werden?";
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	System::Windows::Forms::DialogResult result;

		result = MessageBox::Show( this, message, caption, buttons );
	if ( result == ::DialogResult::Yes )
	{
		Form^ Projekt = gcnew project_form(id,user_id_);
		Projekt->ShowDialog();
		adress_uebersicht_result_Load(sender,e);
	}
}

// Buttons
void adress_uebersicht_result::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::Label^  cache = gcnew System::Windows::Forms::Label();
	cache->Text="-1";
	Form^ choose_print =gcnew choose_printer(cache);
	choose_print->ShowDialog();
	if(cache->Text!="-1")
	{
		pages_=page_content_->Count;
		print_page_=0;
		// Drucker selbst wählen!
		printDocument1->PrinterSettings->PrinterName=cache->Text;
		printDocument1->DefaultPageSettings->Landscape=true;
		printDocument1->DocumentName="Adressübersicht";
		printDocument1->DefaultPageSettings->Margins->Top=25;
		printDocument1->DefaultPageSettings->Margins->Bottom=25;
		printDocument1->DefaultPageSettings->Margins->Right=25;
		printDocument1->DefaultPageSettings->Margins->Left=25;
		printDocument1->OriginAtMargins=true;
		printDocument1->Print();
	}
}

void adress_uebersicht_result::btn_exportExl_Click(System::Object^  sender, System::EventArgs^  e)
{
	exl_->saveDialoge();
	btn_exportExl->Enabled = false;
}

// Printer Stuff
void adress_uebersicht_result::printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e)
{
	e->Graphics->PageScale =0.95;
	int begin_at=0;
	int entry=0;
	int end=700;

	// Spalten Setzten
	p_s_bezeichnung=10;
	p_s_bew_anzahl=210;
	p_s_bew_ztr=360;
	p_s_vn_einger=510;
	p_s_vn_gepr=660;
	p_s_kosten=810;
	p_s_foerder=960;

	// iterate through Content of actual Page
	for(int i=done_page_content_;i<page_content_[print_page_]->Count;++i)
	{
		if(begin_at>=end)
		{
			page_content_[print_page_]->Insert(i,page_content_[print_page_][0]);
			break;
		}

		done_page_content_=i;

		if(page_content_[print_page_][i][0]=="header")
		{
			String^ stadt=page_content_[print_page_][i][1];
			String^ gebiet=page_content_[print_page_][i][2];
			String^ adresse=page_content_[print_page_][i][3];
			create_page_header(e,stadt,gebiet,adresse);
			begin_at+=80;
		}

		if(page_content_[print_page_][i][0]=="eintrag")
		{
			String^ bezeichnung=page_content_[print_page_][i][1];
			String^ bew_anzahl=page_content_[print_page_][i][2];
			String^ bew_ztr=page_content_[print_page_][i][3];
			String^ vn_einger=page_content_[print_page_][i][4];
			String^ vn_gepr=page_content_[print_page_][i][5];
			String^ kosten=page_content_[print_page_][i][6];
			String^ foerderung=page_content_[print_page_][i][7];
			create_page_entry(e,bezeichnung,bew_anzahl,bew_ztr,vn_einger,vn_gepr,kosten,foerderung,begin_at,entry);
			entry++;
			begin_at+=20;
		}

		if(page_content_[print_page_][i][0]=="footer")
		{
			begin_at+=10;
			String^ kosten=page_content_[print_page_][i][1];
			String^ foerderung=page_content_[print_page_][i][2];
			create_page_footer(e,kosten,foerderung,begin_at);
		}
	}

	create_page_sign(e);
	
	// Prepare Settings for next page NextSite
	if(begin_at<end)
	{
		print_page_++;
		done_page_content_=0;
	}
	e->HasMorePages=print_page_<pages_;
}

void adress_uebersicht_result::create_page_header(System::Drawing::Printing::PrintPageEventArgs^  e,String^ stadt,String^ gebiet,String^ adresse)
{

	// Fonds
	System::Drawing::Font^ header_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ ueberschrift_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.2F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// HeaderBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 0, 1170, 33);

	// Header
	e->Graphics->DrawString("Adressübersicht von "+adresse+" in "+stadt+" ("+gebiet+")",header_format,Brushes::Black, 10, 10);

	// Date
	String^ date=Convert::ToString(DateTime::Today.Date);
	date=date->Substring(0,10);
	e->Graphics->DrawString(date,header_format,Brushes::Black, 1100, 10);

	// Ueberschrift
	e->Graphics->DrawString("Bezeichnung",ueberschrift_format,Brushes::Black, p_s_bezeichnung, 55);
	e->Graphics->DrawString("Bewilligungsanzahl",ueberschrift_format,Brushes::Black, p_s_bew_anzahl, 55);
	e->Graphics->DrawString("Bewilligungszeitraum",ueberschrift_format,Brushes::Black, p_s_bew_ztr, 55);
	e->Graphics->DrawString("VN Eingereicht am",ueberschrift_format,Brushes::Black, p_s_vn_einger, 55);
	e->Graphics->DrawString("VN Geprüft am",ueberschrift_format,Brushes::Black, p_s_vn_gepr, 55);
	e->Graphics->DrawString("Gesamtkosten",ueberschrift_format,Brushes::Black, p_s_kosten, 55);
	e->Graphics->DrawString("Gesamtförderung",ueberschrift_format,Brushes::Black, p_s_foerder, 55);
}

void adress_uebersicht_result::create_page_entry(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ bezeichnung,
													String^ bew_anzahl,
													String^ bew_ztr,
													String^ vn_einger,
													String^ vn_gepr,
													String^ kosten,
													String^ foerderung,
													int begin_at,
													int entry)
{
	// Fonds
	System::Drawing::Font^ format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	
	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	if( entry%2==0 )
		e->Graphics->FillRectangle(Brushes::Gainsboro, 0, begin_at-4, 1170, 19);

	// ProjetData
	e->Graphics->DrawString(bezeichnung,format,Brushes::Black, p_s_bezeichnung, begin_at);
	e->Graphics->DrawString(bew_anzahl,format,Brushes::Black, p_s_bew_anzahl, begin_at);
	e->Graphics->DrawString(bew_ztr,format,Brushes::Black, p_s_bew_ztr, begin_at);
	if(vn_einger=="nicht eingereicht")
	{
		vn_einger="Plankosten";
		vn_gepr="";
	}
	e->Graphics->DrawString(vn_einger,format,Brushes::Black, p_s_vn_einger, begin_at);
	e->Graphics->DrawString(vn_gepr,format,Brushes::Black, p_s_vn_gepr, begin_at);

	// Beträge
	e->Graphics->DrawString(kosten,format,Brushes::Black,RectangleF(p_s_kosten, begin_at,130,20),allign);
	e->Graphics->DrawString(foerderung,format,Brushes::Black,RectangleF(p_s_foerder, begin_at,130,20),allign);
}

void adress_uebersicht_result::create_page_footer(System::Drawing::Printing::PrintPageEventArgs^  e,String^ kosten,String^ foerderung, int begin_at)
{
	// Fonds
	System::Drawing::Font^ summen_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ label_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	
	//Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, p_s_kosten-50, begin_at-4, 410, 19);

	// Label
	e->Graphics->DrawString("Summen : ",label_format,Brushes::Black,p_s_kosten-50,begin_at);

	// Summen
	e->Graphics->DrawString(kosten,summen_format,Brushes::Black,RectangleF(p_s_kosten, begin_at,130,20),allign);
	e->Graphics->DrawString(foerderung,summen_format,Brushes::Black,RectangleF(p_s_foerder, begin_at,130,20),allign);
}

void adress_uebersicht_result::create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	// Fonds
	System::Drawing::Font^ main_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ small_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 750, 1170, 80);

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
	e->Graphics->DrawString("erstellt durch :",small_format,Brushes::Black,10,762);
	e->Graphics->DrawString(name,main_format,Brushes::Black,80,760);
	e->Graphics->DrawString(strasse+" "+hausnr,main_format,Brushes::Black,80,780);
	e->Graphics->DrawString(plz+" "+ort,main_format,Brushes::Black,80,800);


	// Programm
	e->Graphics->DrawString("erstellt mit Hilfe von FÖRDI © MKS",small_format,Brushes::Black,970,810);

}
