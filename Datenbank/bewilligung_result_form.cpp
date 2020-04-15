#include "StdAfx.h"
#include "MyRecordSet.h"
#include "project_class.h"
#include "project_form.h"
#include "My_Connection.h"
#include "MyResult.h"
#include "choose_printer.h"
#include "helper.h"

#include "bewilligung_result_form.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

// Loader
void bewilligung_result_form::bewilligung_result_form_Load(System::Object^  sender, System::EventArgs^  e)
{
	Hide();
	ladebalken_->Show();
	ladebalken_->Controls->Find("texter", true)[0]->Text = "Lade Jahresübersicht";  //Load annual overview
	ladebalken_->Controls->Find("texter", true)[0]->Text = "Lade Jahresübersicht";
	//Windows::Forms::MessageBox::Show("t");
	My_Connection data;
	data.connect();

	this->Controls->Clear();
	approvals_values->Clear();

	List<String^>^ Stadt_liste = gcnew List<String^>;
	if (stadt_ == "-1")  //city
	{
		MyResult^ RC = data.get_result("SELECT * FROM Staedte");
		for (int i = 0;i < RC->get_row();++i)
			Stadt_liste->Add(RC->get_val(i, 1));
	}
	else
		Stadt_liste->Add(stadt_);

	for (int stadt_param = 0;stadt_param < Stadt_liste->Count;++stadt_param)
	{
		String^ stadt = Stadt_liste[stadt_param];

		List<String^>^ Gebiet_liste = gcnew List<String^>;
		if (gebiet_ == "-1")  //area
		{
			MyResult^ RC_Stadt = data.get_cities(stadt);
			MyResult^ RC = data.get_result("SELECT Gebiet FROM Gebiete WHERE Stadt_ID=" + RC_Stadt->get_val(0, 0));
			for (int i = 0;i < RC->get_row();++i)
				Gebiet_liste->Add(RC->get_val(i, 0));
		}
		else
			Gebiet_liste->Add(gebiet_);  //area

		for (int gebiet_param = 0;gebiet_param < Gebiet_liste->Count;++gebiet_param)
		{
			String^ gebiet = Gebiet_liste[gebiet_param];  //area

			List<String^>^ Programm_liste = gcnew List<String^>;
			if (programm_ == "-1")
			{
				MyResult^ RC_Stadt = data.get_cities(stadt);
				MyResult^ RC_Gebiet = data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID=" + RC_Stadt->get_val(0, 0) + " AND Gebiet='" + gebiet + "'");
				MyResult^ RC = data.get_result("SELECT * FROM Programme WHERE Gebiet_ID=" + RC_Gebiet->get_val(0, 0));
				for (int i = 0;i < RC->get_row();++i)
					Programm_liste->Add(RC->get_val(i, 2));
			}
			else
				Programm_liste->Add(programm_);

			for (int programm_param = 0;programm_param < Programm_liste->Count;++programm_param)
			{
				bool first_run = true;
				String^ programm = Programm_liste[programm_param];
				if (jahr_ == "-1")  //when all year 
				{
					String^ query = MyRecordSet::QueryAllAnnualBudget(stadt, gebiet, programm);
					MyResult^ RC_Annual = data.get_result(query);

					for (int i = 0;i < RC_Annual->get_row();++i) {
						String^ year = RC_Annual->get_val(i, 4);
						
						List<String^>^ bewilligung = gcnew List<String^>;

						bewilligung->Add(stadt);  //approval   city
						bewilligung->Add(gebiet);   //area
						bewilligung->Add(programm);
						bewilligung->Add(year);  //year						
							
						//------table fields---------------

						for (int j = 0;j < 13;j++) {
							bewilligung->Add("0");  //cost group
						}

						approvals_values->Add(bewilligung);  //approvals_values
					}
				}

				String^ db_projekte_query = "SELECT * FROM db_projekte WHERE stadt='" + stadt + "' AND gebiet='" + gebiet + "'";
				MyResult^ RC_Projekt = data.get_result(db_projekte_query);

				for (int projekt_param = 0;projekt_param < RC_Projekt->get_row();++projekt_param)  //projects
				{
					// Projekt
					String^ id = RC_Projekt->get_val(projekt_param, 0);  //id
					String^ kostengruppe = RC_Projekt->get_val(projekt_param, 8);		// 1  //cost group
					String^ bezeichnung = RC_Projekt->get_val(projekt_param, 5);	// 3  description
					String^ bew_ztr = RC_Projekt->get_val(projekt_param, 7);		// 9   date
					String^ vn_einger = RC_Projekt->get_val(projekt_param, 11);		// 10  //furnished date
					String^ vn_gepr = RC_Projekt->get_val(projekt_param, 12);		// 11   Checked date

					String^ db_programme_query = "SELECT * FROM db_programme WHERE projekt_ID=" + id + " AND name='" + programm + "'";
					MyResult^ RC_Programm = data.get_result(db_programme_query);

					if (RC_Programm->get_row() != 0)
					{
						String^ bewilligung_query = "SELECT * FROM db_programme_bewilligung WHERE programm_ID=" + RC_Programm->get_val(0, 0);

						if (jahr_ != "-1")  //year
							bewilligung_query += " AND nr3='" + jahr_ + "' AND san_bed_ein='0'";	   //year
						if (sbe_ != "-1")
							bewilligung_query += " AND san_bed_ein='1'";

						MyResult^ RC_Bewilligung = data.get_result(bewilligung_query);  //Authorization
						//if (RC_Bewilligung->get_row() == 0) {
						//	List<String^>^ bewilligung = gcnew List<String^>;

						//	bewilligung->Add(stadt);  //approval   city
						//	bewilligung->Add(gebiet);   //area
						//	bewilligung->Add(programm);							
						//	//bewilligung->Add(RC_Bewilligung->get_val(bewilligung_param, 4));  //year
						//	bewilligungen_werte_->Add(bewilligung);  //approvals_values
						//}
						for (int bewilligung_param = 0;bewilligung_param < RC_Bewilligung->get_row();++bewilligung_param)
						{
							String^ TB = "-";
							String^ programm_id = RC_Bewilligung->get_val(bewilligung_param, 1);
							String^ zb_nr = RC_Bewilligung->get_val(bewilligung_param, 2) + "-" + RC_Bewilligung->get_val(bewilligung_param, 3) + "/" + RC_Bewilligung->get_val(bewilligung_param, 4); // 2
							String^ bew_id = RC_Bewilligung->get_val(bewilligung_param, 0);
							int tb_nr = get_tb(programm_id, bew_id);
							if (tb_nr != 0)
								TB = Convert::ToString(tb_nr) + ". TB"; // 4
							String^ vom = RC_Bewilligung->get_val(bewilligung_param, 5); // 5
							Decimal bund_land = Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param, 8))); // 7
							Decimal bund_land_vn = Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param, 9))); // 7
							Decimal mla = Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param, 6))); // 8
							Decimal mla_vn = Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param, 7))); // 8
							Decimal mehr_minder = (mla_vn + bund_land_vn) - (mla + bund_land);		//12								// 12
							Decimal förderbetrag = mla + bund_land; // 6
							Decimal förderbetrag_vn = mla_vn + bund_land_vn; // 6

							List<String^>^ bewilligung = gcnew List<String^>;

							bewilligung->Add(stadt);  //approval   city
							bewilligung->Add(gebiet);   //area
							bewilligung->Add(programm);
							if (RC_Bewilligung->get_val(bewilligung_param, 10) == "1")
								bewilligung->Add("SBE");
							else
								bewilligung->Add(RC_Bewilligung->get_val(bewilligung_param, 4));  //year
							//------table fields---------------
							bewilligung->Add(kostengruppe);  //cost group
							bewilligung->Add(zb_nr);
							bewilligung->Add(bezeichnung);
							bewilligung->Add(TB);
							bewilligung->Add(vom);
							if (vn_einger != "")
							{
								bewilligung->Add(Decimal_to_string(förderbetrag));
								bewilligung->Add(Decimal_to_string(bund_land));
								bewilligung->Add(Decimal_to_string(mla));
							}
							else
							{
								bewilligung->Add(Decimal_to_string(förderbetrag));
								bewilligung->Add(Decimal_to_string(bund_land));
								bewilligung->Add(Decimal_to_string(mla));
							}
							bewilligung->Add(bew_ztr);
							if (vn_einger != "")
								bewilligung->Add(vn_einger);
							else
								bewilligung->Add("-");
							if (vn_gepr != "")
								bewilligung->Add(vn_gepr);
							else
								bewilligung->Add("-");
							if (vn_einger != "")
								bewilligung->Add(Decimal_to_string(mehr_minder));
							else
								bewilligung->Add("-");
							bewilligung->Add(id);

							approvals_values->Add(bewilligung);  //approvals_values
							ladebalken_->Controls->Find("progress", true)[0]->Text = "a";
							ladebalken_->Controls->Find("progress", true)[0]->Text = " ";
						}
					}
				}
			}
		}
	}
	data.disconnect();

	if (approvals_values->Count == 0)
	{
		ladebalken_->Close();
		Windows::Forms::MessageBox::Show("Es wurden keine Einträge zu ihrer Anfrage gefunden.", "Ungültige Suche");
		//No entries were found for your request    Invalid search
		Close();
	}
	else
	{
		ladebalken_->Controls->Find("texter", true)[0]->Text = "Verarbeite Daten und erzeuge Einträge";  //Process data and create entries
		ladebalken_->Controls->Find("texter", true)[0]->Text = "Verarbeite Daten und erzeuge Einträge";

		sort_bewilligung();
		if (approvals_values->Count != 0)
		{
			String^ year = "";
			String^ programm = "";
			String^ stadt = "";
			String^ gebiet = "";
			int eintrag = 0;

			Decimal summe_mla = 0;
			Decimal summe_bund_land = 0;
			Decimal summe_mehr_minder = 0;
			Decimal jahreshaushalt = -1;  //annual budget
			start_pos = 0;

			for (int i = 0;i < approvals_values->Count;++i)
			{
				if (approvals_values[i][3] != year || approvals_values[i][2] != programm || approvals_values[i][1] != gebiet || approvals_values[i][0] != stadt)
				{
					if (start_pos != 0)
					{
						generate_footer(jahreshaushalt, summe_bund_land, summe_mla, summe_mehr_minder);
						start_pos += 20;
					}
					summe_mla = 0;
					summe_bund_land = 0;
					summe_mehr_minder = 0;
					eintrag = 0;
					stadt = approvals_values[i][0]; //city
					gebiet = approvals_values[i][1];  //area
					programm = approvals_values[i][2]; //Programm name
					year = approvals_values[i][3];  //year

					generate_header(stadt, gebiet, programm, year);

					jahreshaushalt = -1;  //annual budget
					if (year != "XX")
						jahreshaushalt = generate_haushalt(stadt, gebiet, programm, year);  //annual budget
					//if (approvals_values[i][4] == "0" && approvals_values[i][5] == "0" && approvals_values[i][6] == "0")
					//	continue;
					GenerateHeadings();  //generate_headings
				}

				if (approvals_values[i][4] == "0" && approvals_values[i][5] == "0" && approvals_values[i][6] == "0")
					continue;

				String^ bund_land = approvals_values[i][10];
				String^ mla = approvals_values[i][11];
				String^ mehr_minder = approvals_values[i][15];
				bool neg = false;
				if (mehr_minder[0] == '-')
					neg = true;
				mehr_minder = mehr_minder->Replace(L"€", "")->Replace("-", "")->Replace(".", "")->Trim();
				bund_land = bund_land->Replace(L"€", "")->Replace(".", "")->Trim();
				mla = mla->Replace(L"€", "")->Replace(".", "")->Trim();
				summe_bund_land += Decimal(Convert::ToDouble(bund_land));
				summe_mla += Decimal(Convert::ToDouble(mla));
				if (mehr_minder == "")
					mehr_minder = "0";
				if (!neg)
					summe_mehr_minder += Decimal(Convert::ToDouble(mehr_minder));
				else
					summe_mehr_minder += -1 * Decimal(Convert::ToDouble(mehr_minder));
				GenerateApproval(approvals_values[i]->GetRange(4, 13), eintrag);
				++eintrag;

				ladebalken_->Controls->Find("progress", true)[0]->Text = "a";
				ladebalken_->Controls->Find("progress", true)[0]->Text = " ";

				if (i == approvals_values->Count - 1)
					generate_footer(jahreshaushalt, summe_bund_land, summe_mla, summe_mehr_minder);
			}
		}
		place_button();
		ladebalken_->Hide();
		Show();
	}
}

int bewilligung_result_form::get_tb(String^ prog_id, String^ bew_id)
{
	My_Connection data;
	data.connect();
	String^ query = "SELECT * FROM db_programme_bewilligung WHERE programm_ID=" + prog_id;
	MyResult^ RC = data.get_result(query);
	data.disconnect();

	if (RC->get_row() != 1)
		for (int i = 0;i < RC->get_row();++i)
			if (bew_id == RC->get_val(i, 0))
				return i + 1;

	return 0;

}

void bewilligung_result_form::sort_bewilligung()
{
	List< List<String^>^ >^ zwichenspeicher = gcnew List< List<String^>^ >;

	List<String^>^ cityList = gcnew List<String^>;
	List<String^>^ areaList = gcnew List<String^>;
	List<String^>^ programList = gcnew List<String^>;
	List<String^>^ yearList = gcnew List<String^>;

	for (int i = 0;i < approvals_values->Count;++i)
	{
		if (!is_existent_in(cityList, approvals_values[i][0]))
			cityList->Add(approvals_values[i][0]);
		if (!is_existent_in(areaList, approvals_values[i][1]))
			areaList->Add(approvals_values[i][1]);
		if (!is_existent_in(programList, approvals_values[i][2]))
			programList->Add(approvals_values[i][2]);
		if (!is_existent_in(yearList, approvals_values[i][3]))
			yearList->Add(approvals_values[i][3]);
	}

	cityList->Sort();
	areaList->Sort();
	programList->Sort();
	sort_for_year(yearList);

	for (int stadt_param = 0;stadt_param < cityList->Count;++stadt_param)
	{
		for (int gebiet_param = 0;gebiet_param < areaList->Count;++gebiet_param)
		{
			for (int prog_param = 0;prog_param < programList->Count;++prog_param)
			{
				for (int jahr_param = 0;jahr_param < yearList->Count;++jahr_param)
				{
					List< List<String^>^ >^ tmp = gcnew List< List<String^>^ >;
					int i = 0;
					do
					{
						if (approvals_values[i][0] == cityList[stadt_param] &&
							approvals_values[i][1] == areaList[gebiet_param] &&
							approvals_values[i][2] == programList[prog_param] &&
							approvals_values[i][3] == yearList[jahr_param])
						{
							tmp->Add(approvals_values[i]);
						}
						++i;
					} while (i < approvals_values->Count);
					sort_for_ZB_NR(tmp);
					for (int i = 0;i < tmp->Count;++i)
						zwichenspeicher->Add(tmp[i]);
				}
			}
		}
	}
	approvals_values = zwichenspeicher;
}

void bewilligung_result_form::sort_for_year(List<String^>^ input)
{
	for (int i = input->Count;i > 1;--i)
	{
		for (int j = 0; j < i - 1; ++j)
		{
			String^ jahr1 = input[j];
			String^ jahr2 = input[j + 1];

			if (jahr1 == "XX")
				jahr1 = "70";
			if (jahr2 == "XX")
				jahr2 = "70";
			if (jahr1 == "SBE")
				jahr1 = "71";
			if (jahr2 == "SBE")
				jahr2 = "71";

			if (Convert::ToInt32(jahr1) > 89)
				jahr1 = "19" + jahr1;
			else
				jahr1 = "20" + jahr1;

			if (Convert::ToInt32(jahr2) > 89)
				jahr2 = "19" + jahr2;
			else
				jahr2 = "20" + jahr2;

			if (Convert::ToInt32(jahr1) > Convert::ToInt32(jahr2))
			{
				String^ cache = input[j];
				input[j] = input[j + 1];
				input[j + 1] = cache;
			}
		}
	}
}

void bewilligung_result_form::sort_for_ZB_NR(List< List<String^>^ >^ input)
{
	for (int i = input->Count;i > 1; --i)
	{
		for (int j = 0; j < i - 1; ++j)
		{
			String^ zb_nr1 = input[j][5];
			zb_nr1 = zb_nr1->Replace("/", "")->Replace("-", "")->Replace("X", "9");
			String^ zb_nr2 = input[j + 1][5];
			zb_nr2 = zb_nr2->Replace("/", "")->Replace("-", "")->Replace("X", "9");

			//Windows::Forms::MessageBox::Show(zb_nr1+"\n"+zb_nr2);

			if (Convert::ToInt64(zb_nr1) > Convert::ToInt64(zb_nr2))
			{
				List<String^>^ tmp = input[j];
				input[j] = input[j + 1];
				input[j + 1] = tmp;
			}
		}
	}
}

bool bewilligung_result_form::is_existent_in(List<String^>^ liste, String^ value)
{
	for each(String^ eintrag in liste)
		if (eintrag == value)
			return true;
	return false;
}

// Auswertungselemente       Evaluation elements
void bewilligung_result_form::generate_header(String^ stadt, String^ gebiet, String^ programm, String^ jahr)
{
	page_content_->Add(gcnew List< List<String^>^ >);
	List<String^>^ header = gcnew List<String^>;
	header->Add("header");
	header->Add(stadt);
	header->Add(gebiet);
	header->Add(programm);
	header->Add(jahr);
	page_content_[page_content_->Count - 1]->Add(header);

	System::Windows::Forms::Label^  stadt_label = gcnew System::Windows::Forms::Label();
	stadt_label->Location = System::Drawing::Point(5, 1 + start_pos);
	stadt_label->AutoSize = true;
	stadt_label->Text = "Stadt         : " + stadt;
	stadt_label->BackColor = System::Drawing::Color::Silver;
	stadt_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(stadt_label);

	System::Windows::Forms::Label^  gebiet_label = gcnew System::Windows::Forms::Label();
	gebiet_label->Location = System::Drawing::Point(5, 1 * 13 + 1 + start_pos);
	gebiet_label->AutoSize = true;
	gebiet_label->Text = "Gebiet       : " + gebiet;
	gebiet_label->BackColor = System::Drawing::Color::Silver;
	gebiet_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(gebiet_label);

	System::Windows::Forms::Label^  programm_label = gcnew System::Windows::Forms::Label();
	programm_label->Location = System::Drawing::Point(5, 2 * 13 + 1 + start_pos);
	programm_label->AutoSize = true;
	programm_label->Text = "Programm : " + programm;
	programm_label->BackColor = System::Drawing::Color::Silver;
	programm_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(programm_label);

	System::Windows::Forms::Label^  jahr_label = gcnew System::Windows::Forms::Label();
	jahr_label->Location = System::Drawing::Point(5, 3 * 13 + 1 + start_pos);
	jahr_label->AutoSize = true;
	jahr_label->BackColor = System::Drawing::Color::Silver;
	jahr_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(jahr_label);
	if (jahr == "SBE")
		jahr_label->Text = "Sanierungsbedingte Einnahmen";
	else
	{
		if (jahr == "XX")
			jahr_label->Text = "Plankosten";
		else
			jahr_label->Text = "Jahr           : " + jahr;
	}

	exl_->setCell(row_, 1, "Stadt : " + stadt);
	exl_->setCellAutofit(row_, 1);
	exl_->setCellItalic(row_, 1);

	exl_->setCell(row_, 3, "Gebiet : " + gebiet);
	exl_->setCellItalic(row_, 3);
	exl_->setCellAutofit(row_, 3);

	++row_;

	exl_->setCell(row_, 1, "Programm : " + programm);
	exl_->setCellAutofit(row_, 1);
	exl_->setCellItalic(row_, 1);

	exl_->setCell(row_, 3, jahr_label->Text);
	exl_->setCellAutofit(row_, 3);
	exl_->setCellItalic(row_, 3);


	++row_;
	++row_;

	System::Windows::Forms::Label^  header_back = gcnew System::Windows::Forms::Label();
	header_back->Location = System::Drawing::Point(0, start_pos);
	header_back->AutoSize = false;
	header_back->Size = System::Drawing::Size(936, 4 * 13 + 1);
	header_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(header_back);

	start_pos += 3 * 13 + 25;
}

Decimal bewilligung_result_form::generate_haushalt(String^ stadt, String^ gebiet, String^ programm, String^ jahr)
{
	int eintrag = 0;
	MyRecordSet RC_Stadt("SELECT ID FROM Staedte WHERE stadt='" + stadt + "'");
	MyRecordSet RC_Gebiet("SELECT ID FROM Gebiete WHERE Stadt_ID=" + RC_Stadt.get_val(0, 0) + " AND Gebiet='" + gebiet + "'");
	MyRecordSet RC_Programm("SELECT ID FROM Programme WHERE Gebiet_ID=" + RC_Gebiet.get_val(0, 0) + " AND Programm='" + programm + "'");
	MyRecordSet RC_JH("SELECT * FROM jahreshaushalt WHERE programm_ID=" + RC_Programm.get_val(0, 0) + " AND jahr='" + jahr + "'");

	int s_datum = 15;
	int s_betrag = 115;
	int s_grund = 210;

	System::Windows::Forms::Label^  jahreshh_label = gcnew System::Windows::Forms::Label();
	jahreshh_label->Location = System::Drawing::Point(5, eintrag * 13 + 1 + start_pos);
	jahreshh_label->AutoSize = true;
	jahreshh_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(jahreshh_label);
	if (jahr != "-1")
	{
		jahreshh_label->Text = "Jahreszuteilung " + jahr + " : ";
	}
	else //SBE !="-1"
	{
		s_betrag += 75;
		s_grund += 75;
		jahreshh_label->Text = "Sanierungsbedingte Einnahmen";
	}

	exl_->setCell(row_, 2, jahreshh_label->Text);
	exl_->setCellBold(row_, 2);
	exl_->setCellAutofit(row_, 2);
	year_price_row = row_;
	++row_;

	List<String^>^ jz_label = gcnew List<String^>;
	jz_label->Add("jz_label");
	jz_label->Add(jahreshh_label->Text);
	page_content_[page_content_->Count - 1]->Add(jz_label);

	System::Windows::Forms::Label^  jahreshh_ges_label = gcnew System::Windows::Forms::Label();
	jahreshh_ges_label->Location = System::Drawing::Point(s_betrag, eintrag * 13 + 1 + start_pos);
	jahreshh_ges_label->AutoSize = false;
	jahreshh_ges_label->Size = System::Drawing::Size(85, 15);
	jahreshh_ges_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
	jahreshh_ges_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(jahreshh_ges_label);

	Decimal jahreshaushalt = 0;

	for (int i = 0;i < RC_JH.get_row();++i)
	{
		eintrag++;
		// Datum
		System::Windows::Forms::Label^  jahreshh_datum = gcnew System::Windows::Forms::Label();
		jahreshh_datum->Location = System::Drawing::Point(s_datum, eintrag * 13 + 1 + start_pos);
		jahreshh_datum->AutoSize = true;
		jahreshh_datum->Text = RC_JH.get_val(i, 5);
		jahreshh_datum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->Controls->Add(jahreshh_datum);
		// Betrag
		System::Windows::Forms::Label^  jahreshh_betrag = gcnew System::Windows::Forms::Label();
		jahreshh_betrag->Location = System::Drawing::Point(s_betrag, eintrag * 13 + 1 + start_pos);
		jahreshh_betrag->AutoSize = false;
		jahreshh_betrag->Size = System::Drawing::Size(85, 15);
		jahreshh_betrag->TextAlign = System::Drawing::ContentAlignment::TopRight;
		Decimal jh_aenderung = Decimal(Convert::ToDouble(RC_JH.get_val(i, 2)));
		jahreshh_betrag->Text = Decimal_to_string(jh_aenderung);
		jahreshaushalt += jh_aenderung;
		jahreshh_betrag->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->Controls->Add(jahreshh_betrag);
		// Grund
		System::Windows::Forms::Label^  jahreshh_grund = gcnew System::Windows::Forms::Label();
		jahreshh_grund->Location = System::Drawing::Point(s_grund, eintrag * 13 + 1 + start_pos);
		jahreshh_grund->AutoSize = true;
		jahreshh_grund->Text = RC_JH.get_val(i, 3);
		jahreshh_grund->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->Controls->Add(jahreshh_grund);

		List<String^>^ jz_eintrag = gcnew List<String^>;
		jz_eintrag->Add("jz_eintrag");
		jz_eintrag->Add(RC_JH.get_val(i, 5));				// Datum
		jz_eintrag->Add(Decimal_to_string(jh_aenderung));	// Betrag
		jz_eintrag->Add(RC_JH.get_val(i, 3));				// Grund
		page_content_[page_content_->Count - 1]->Add(jz_eintrag);

		exl_->setCell(row_, 2, RC_JH.get_val(i, 5));
		exl_->setCellAutofit(row_, 2);
		exl_->setCellCurrency(row_, 3, Convert::ToDecimal(RC_JH.get_val(i, 2)));
		exl_->setCellAutofit(row_, 3);
		exl_->setCell(row_, 4, RC_JH.get_val(i, 3));
		exl_->setCellAutofit(row_, 4);
		++row_;
	}
	++row_;
	int label_index = (page_content_[page_content_->Count - 1])->Count - RC_JH.get_row() - 1;
	//Windows::Forms::MessageBox::Show(Convert::ToString((page_content_[page_content_->Count-1])->Count)+"\n"+Convert::ToString(RC_JH.get_row())+"\n"+Convert::ToString(label_index));
	page_content_[page_content_->Count - 1][label_index]->Add(Decimal_to_string(jahreshaushalt));
	jahreshh_ges_label->Text = Decimal_to_string(jahreshaushalt);
	exl_->setCellSum(year_price_row, 3, year_price_row + 1, row_ - 2);
	exl_->setCellAutofit(year_price_row, 3);
	if (jahreshaushalt != 0)
		jahreshaushalt_ = jahreshaushalt;
	eintrag += 2;
	start_pos += eintrag * 13 + 1;

	List<String^>^ ueberschrift = gcnew List<String^>;
	ueberschrift->Add("ueberschrift");
	page_content_[page_content_->Count - 1]->Add(ueberschrift);

	return jahreshaushalt;
}

void bewilligung_result_form::GenerateHeadings()  //generate_headings
{
	List<String^>^ headStrList = gcnew List<String^>;
	headStrList->Add("Kostengr.");
	headStrList->Add("ZB-Nr.");
	headStrList->Add("Vorhaben");
	headStrList->Add("TB");
	headStrList->Add("vom");
	headStrList->Add("Förderbetrag");
	headStrList->Add("Bund-/Landanteil");
	headStrList->Add("MLA Gemeinde");
	headStrList->Add("BWZ");
	headStrList->Add("VN eingereicht");
	headStrList->Add("VN geprüft");
	headStrList->Add("Mehr-Minderkosten");

	// kostenart    -cost type
	System::Windows::Forms::Label^  kostenart = gcnew System::Windows::Forms::Label();
	kostenart->Location = System::Drawing::Point(s_kostenart, start_pos);
	kostenart->AutoSize = true;
	kostenart->Text = headStrList[0];// "Kostengr.";  //Cost Gr
	kostenart->Name = "kostengr";
	kostenart->BackColor = System::Drawing::Color::Silver;
	kostenart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(kostenart);

	// zb_nr
	System::Windows::Forms::Label^  zb_nr = gcnew System::Windows::Forms::Label();
	zb_nr->Location = System::Drawing::Point(s_zb_nr, start_pos);
	zb_nr->AutoSize = true;
	zb_nr->Text = headStrList[1];//  "ZB-Nr.";
	zb_nr->Name = "zb_nr";
	zb_nr->BackColor = System::Drawing::Color::Silver;
	zb_nr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(zb_nr);

	// bezeichnung       description
	System::Windows::Forms::Label^  bezeichnung = gcnew System::Windows::Forms::Label();
	bezeichnung->Location = System::Drawing::Point(s_bezeichnung, start_pos);
	bezeichnung->AutoSize = false;
	bezeichnung->Size = System::Drawing::Size(110, 15);
	bezeichnung->TextAlign = System::Drawing::ContentAlignment::TopCenter;
	bezeichnung->Text = "Vorhaben";  //project
	bezeichnung->Name = "bezeichnung";  //description
	bezeichnung->BackColor = System::Drawing::Color::Silver;
	bezeichnung->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(bezeichnung);

	// TB
	System::Windows::Forms::Label^  tb = gcnew System::Windows::Forms::Label();
	tb->Location = System::Drawing::Point(s_tb, start_pos);
	tb->AutoSize = true;
	tb->Text = "TB";
	tb->Name = "tb";
	tb->BackColor = System::Drawing::Color::Silver;
	tb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(tb);

	// vom
	System::Windows::Forms::Label^  vom = gcnew System::Windows::Forms::Label();
	vom->Location = System::Drawing::Point(s_vom, start_pos);
	vom->AutoSize = true;
	vom->Text = "vom";
	vom->Name = "vom";
	vom->BackColor = System::Drawing::Color::Silver;
	vom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(vom);

	// foerderbetrag
	System::Windows::Forms::Label^  foerderbetrag = gcnew System::Windows::Forms::Label();
	foerderbetrag->Location = System::Drawing::Point(s_foerder, start_pos);
	foerderbetrag->AutoSize = false;
	foerderbetrag->Size = System::Drawing::Size(85, 15);
	foerderbetrag->TextAlign = System::Drawing::ContentAlignment::TopRight;
	foerderbetrag->Text = "Förderbetrag";
	foerderbetrag->Name = "foerderbetrag";
	foerderbetrag->BackColor = System::Drawing::Color::Silver;
	foerderbetrag->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(foerderbetrag);

	// bund_land
	System::Windows::Forms::Label^  bund_land = gcnew System::Windows::Forms::Label();
	bund_land->Location = System::Drawing::Point(s_bund_land, start_pos);
	bund_land->AutoSize = false;
	bund_land->Size = System::Drawing::Size(85, 15);
	bund_land->TextAlign = System::Drawing::ContentAlignment::TopRight;
	bund_land->Text = "Bund-/Landanteil";
	bund_land->Name = "bund_land";
	bund_land->BackColor = System::Drawing::Color::Silver;
	bund_land->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(bund_land);

	// mla
	System::Windows::Forms::Label^  mla = gcnew System::Windows::Forms::Label();
	mla->Location = System::Drawing::Point(s_mla, start_pos);
	mla->AutoSize = false;
	mla->Size = System::Drawing::Size(85, 15);
	mla->TextAlign = System::Drawing::ContentAlignment::TopRight;
	mla->Text = "MLA Gemeinde";
	mla->Name = "mla";
	mla->BackColor = System::Drawing::Color::Silver;
	mla->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(mla);

	// bew_ztr
	System::Windows::Forms::Label^  bew_ztr = gcnew System::Windows::Forms::Label();
	bew_ztr->Location = System::Drawing::Point(s_bew_ztr, start_pos);
	bew_ztr->AutoSize = true;
	bew_ztr->Text = "BWZ";
	bew_ztr->Name = "bew_ztr";
	bew_ztr->BackColor = System::Drawing::Color::Silver;
	bew_ztr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(bew_ztr);

	// vn_einger
	System::Windows::Forms::Label^  vn_einger = gcnew System::Windows::Forms::Label();
	vn_einger->Location = System::Drawing::Point(s_einger, start_pos);
	vn_einger->AutoSize = true;
	vn_einger->Text = "VN eingereicht";
	vn_einger->Name = "vn_einger";
	vn_einger->BackColor = System::Drawing::Color::Silver;
	vn_einger->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(vn_einger);

	// vn_gepr
	System::Windows::Forms::Label^  vn_gepr = gcnew System::Windows::Forms::Label();
	vn_gepr->Location = System::Drawing::Point(s_gepr, start_pos);
	vn_gepr->AutoSize = true;
	vn_gepr->Text = "VN geprüft";
	vn_gepr->Name = "vn_gepr";
	vn_gepr->BackColor = System::Drawing::Color::Silver;
	vn_gepr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(vn_gepr);

	// mehr_minder
	System::Windows::Forms::Label^  mehr_minder = gcnew System::Windows::Forms::Label();
	mehr_minder->Location = System::Drawing::Point(s_mehr_minder, start_pos);
	mehr_minder->AutoSize = true;
	mehr_minder->Text = "Mehr-/Minderkosten";
	mehr_minder->Name = "mehr_minder";
	mehr_minder->BackColor = System::Drawing::Color::Silver;
	mehr_minder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(mehr_minder);

	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0, start_pos);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 20);
	ueberschrift_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(ueberschrift_back);
	//excel
	for (int j = 1;j < 13;++j) {
		exl_->setCell(row_, j, headStrList[j-1]);
		exl_->setCellBold(row_, j);
		exl_->setCellAutofit(row_, j);
	}

	start_pos += 20;
	sumStart = row_ + 1;
}
//generate_approval
void bewilligung_result_form::GenerateApproval(List<String^>^ valueList, int eintrag)
{
	MyRecordSet RC("SELECT Wert,Abkuerzung FROM Kostengruppe WHERE Wert='" + valueList[0] + "'");
	String^ kostengruppe_s = RC.get_val(0, 1);
	String^ zb_nr_s = valueList[1];
	String^ bezeichnung_s = valueList[2];  //designation_s
	String^ tb_s = valueList[3];
	String^ vom_s = valueList[4];
	String^ foerderbetrag_s = valueList[5];
	String^ bund_land_s = valueList[6];
	String^ mla_s = valueList[7];
	String^ bew_ztr_s = valueList[8];
	String^ vn_einger_s = valueList[9];
	String^ vn_gepr_s = valueList[10];
	String^ mehr_minder_s = valueList[11];

	List<String^>^ entry = gcnew List<String^>;
	entry->Add("eintrag");
	entry->Add(kostengruppe_s);
	entry->Add(zb_nr_s);
	entry->Add(bezeichnung_s);
	entry->Add(tb_s);
	entry->Add(vom_s);
	entry->Add(foerderbetrag_s);
	entry->Add(bund_land_s);
	entry->Add(mla_s);
	entry->Add(bew_ztr_s);
	entry->Add(vn_einger_s);
	entry->Add(vn_gepr_s);
	entry->Add(mehr_minder_s);
	page_content_[page_content_->Count - 1]->Add(entry);

	String^ id = valueList[12];

	System::Drawing::Color color;
	if (eintrag % 2 != 0)
	{
		color = System::Drawing::Color::Gainsboro;
	}
	else
	{
		color = System::Drawing::Color::White;
	}

	int rowNum = eintrag;
	row_++;
	col_ = 1;

	AddCellC(kostengruppe_s, s_kostenart, rowNum, id);
	AddCellC(valueList[1], s_zb_nr, rowNum, id);
	AddCellC(valueList[2], s_bezeichnung, rowNum, id);

	label->MaximumSize = System::Drawing::Size(100, 0);
	heightCalc = label->Size.Height;	

	AddCellC(valueList[3], s_tb, rowNum, id);	
	AddCellC(valueList[4], s_vom, rowNum, id);
	
	AddCellC(valueList[5], s_foerder, rowNum, id,true);
	SetLabelSize(85, 15);
	AddCellC(valueList[6], s_bund_land, rowNum, id,true);
	SetLabelSize(85, 15);
	AddCellC(valueList[7], s_mla, rowNum, id,true);
	SetLabelSize(85, 15);
	AddCellC(valueList[8], s_bew_ztr, rowNum, id);
	AddCellC(valueList[9], s_einger, rowNum, id);
	AddCellC(valueList[10], s_gepr, rowNum, id);
	AddCellC(valueList[11], s_mehr_minder, rowNum, id,true);
	SetLabelSize(85, 15);

	AddLineBreak(color);
	label->Name = id;	
	label->Click += gcnew System::EventHandler(this, &bewilligung_result_form::Click);
}

void bewilligung_result_form::generate_footer(Decimal jahreshaushalt, Decimal bund_land, Decimal mla, Decimal mehr_minder)
{
	List<String^>^ footer = gcnew List<String^>;
	footer->Add("footer");
	footer->Add(Convert::ToString(jahreshaushalt));
	footer->Add(Convert::ToString(bund_land));
	footer->Add(Convert::ToString(mla));
	footer->Add(Convert::ToString(mehr_minder));
	page_content_[page_content_->Count - 1]->Add(footer);

	row_++;
	row_++;
	col_ = 6;
	
	AddTableFooter(Decimal_to_string(bund_land + mla), s_foerder, 85, 15);	
	AddTableFooter(Decimal_to_string(bund_land ), s_bund_land, 85, 15);
	AddTableFooter(Decimal_to_string( mla), s_mla, 85, 15);
	col_ += 3;
	AddTableFooter(Decimal_to_string(mehr_minder), s_mehr_minder, 85, 15);
	
	if (jahreshaushalt != -1)
	{
		row_++;
		col_ = 4;

		System::Windows::Forms::Label^  restmittel_label = gcnew System::Windows::Forms::Label();
		restmittel_label->Location = System::Drawing::Point(s_foerder - 100, start_pos + 20);
		restmittel_label->AutoSize = true;
		restmittel_label->Text = "Restmittel";
		restmittel_label->Name = "restmittel_label";
		restmittel_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->Controls->Add(restmittel_label);

		System::Windows::Forms::Label^  restmittel = gcnew System::Windows::Forms::Label();
		restmittel->Location = System::Drawing::Point(s_foerder, start_pos + 20);
		restmittel->AutoSize = false;
		restmittel->Size = System::Drawing::Size(85, 15);
		restmittel->Text = Decimal_to_string(jahreshaushalt - (bund_land + mla));
		restmittel->Name = "restmittel";
		restmittel->TextAlign = System::Drawing::ContentAlignment::TopRight;
		restmittel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->Controls->Add(restmittel);

		start_pos = start_pos + 20;
		exl_->setCell(row_, col_, "Restmittel");		
		exl_->setCellBold(row_, col_);
		//AddTableFooter("Restmittel", s_foerder - 100, 85, 15);
		col_++;
		col_++;
		exl_->setCellSumCell(row_, col_, year_price_row,3, row_-1,col_);
		//AddTableFooter(Decimal_to_string(jahreshaushalt - (bund_land + mla)), s_foerder , 85, 15);
		start_pos = start_pos - 20;
	}
	start_pos += 30;
	row_++;
	row_++;
}

void bewilligung_result_form::place_button()
{
	start_pos = start_pos + 10;

	btn_print->Location = System::Drawing::Point(5, start_pos);
	btn_print->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_print);

	start_pos = start_pos + 30;

	btn_exportExl->Location = System::Drawing::Point(5, start_pos);
	btn_exportExl->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_exportExl);

	System::Windows::Forms::Label^  label_freespace = gcnew System::Windows::Forms::Label();
	label_freespace->Location = System::Drawing::Point(0, start_pos + 20);
	label_freespace->AutoSize = false;
	label_freespace->Size = System::Drawing::Size(5, 10);
	this->Controls->Add(label_freespace);
}

// Events
void bewilligung_result_form::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::Label^  cache = gcnew System::Windows::Forms::Label();
	cache->Text = "-1";
	Form^ choose_print = gcnew choose_printer(cache);
	choose_print->ShowDialog();
	if (cache->Text != "-1")
	{
		pages_ = page_content_->Count;
		print_page_ = 0;

		printDocument1->PrinterSettings->PrinterName = cache->Text;
		printDocument1->DefaultPageSettings->Landscape = true;
		printDocument1->DocumentName = "Jahresübersicht";
		printDocument1->DefaultPageSettings->Margins->Top = 25;
		printDocument1->DefaultPageSettings->Margins->Bottom = 25;
		printDocument1->DefaultPageSettings->Margins->Right = 25;
		printDocument1->DefaultPageSettings->Margins->Left = 25;
		printDocument1->OriginAtMargins = true;
		printDocument1->Print();
	}
}

void bewilligung_result_form::Click(System::Object^  sender, System::EventArgs^  e)
{
	int index = -1;
	for (int i = 0;i < this->Controls->Count;++i)
		if (ReferenceEquals(this->Controls[i], sender))
		{
			index = i;
			break;
		}
	int id = Convert::ToInt32(this->Controls[index]->Name);

	String^ message = "Wird das Projekt geöffnet, wird die Auswertung nach Schließen des Projektes neu geladen.\nFortfahren ?";
	String^ caption = "Soll das Projekt geöffnet werden?";
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	System::Windows::Forms::DialogResult result;

	result = MessageBox::Show(this, message, caption, buttons);
	if (result == ::DialogResult::Yes)
	{
		Form^ Projekt = gcnew project_form(id, user_id_);
		Projekt->ShowDialog();
		bewilligung_result_form_Load(sender, e);
	}
}

// Printer Stuff
void bewilligung_result_form::printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e)
{

	e->Graphics->PageScale = 0.95;
	int begin_at = 0;
	int entry = 0;
	int end = 700;

	// Spalten Setzten
	p_s_kostengr = 10;
	p_s_ZB_NR = 60;
	p_s_bezeichnung = 150;
	p_s_tb = 310;
	p_s_vom = 350;
	p_s_foerderbetrag = 420;
	p_s_bund_land = 530;
	p_s_mla = 640;
	p_s_bew_ztr = 760;
	p_s_vn_einger = 850;
	p_s_vn_gepr = 940;
	p_s_mehr_minder = 1030;


	// iterate through Content of actual Page
	for (int i = done_page_content_;i < page_content_[print_page_]->Count;++i)
	{
		if (begin_at >= end)
		{
			page_content_[print_page_]->Insert(i, page_content_[print_page_][0]);
			List<String^>^ ueberschrift = gcnew List<String^>;
			ueberschrift->Add("ueberschrift");
			page_content_[print_page_]->Insert(i + 1, ueberschrift);
			break;
		}

		done_page_content_ = i;

		if (page_content_[print_page_][i][0] == "header")
		{
			String^ stadt = page_content_[print_page_][i][1];
			String^ gebiet = page_content_[print_page_][i][2];
			String^ programm = page_content_[print_page_][i][3];
			String^ jahr = page_content_[print_page_][i][4];
			create_page_header(e, stadt, gebiet, programm, jahr);
			begin_at += 60;
		}

		if (page_content_[print_page_][i][0] == "jz_label")
		{
			String^ label = page_content_[print_page_][i][1];
			String^ betrag = page_content_[print_page_][i][2];
			create_page_jh_label(e, label, betrag, begin_at);
			begin_at += 20;
		}

		if (page_content_[print_page_][i][0] == "jz_eintrag")
		{
			String^ datum = page_content_[print_page_][i][1];
			String^ betrag = page_content_[print_page_][i][2];
			String^ grund = page_content_[print_page_][i][3];
			create_page_jh_eintrag(e, datum, betrag, grund, begin_at);
			begin_at += 20;
		}

		if (page_content_[print_page_][i][0] == "ueberschrift")
		{
			begin_at += 10;
			create_page_uberschriften(e, begin_at);  //headlines
			begin_at += 30;
		}

		if (page_content_[print_page_][i][0] == "eintrag")
		{
			String^ kostengruppe = page_content_[print_page_][i][1];
			String^ zb_nr = page_content_[print_page_][i][2];
			String^ bezeichnung = page_content_[print_page_][i][3];
			String^ tb = page_content_[print_page_][i][4];
			String^ vom = page_content_[print_page_][i][5];
			String^ foerderbetrag = page_content_[print_page_][i][6];
			String^ bund_land = page_content_[print_page_][i][7];
			String^ mla = page_content_[print_page_][i][8];
			String^ bew_ztr = page_content_[print_page_][i][9];
			String^ vn_einger = page_content_[print_page_][i][10];
			String^ vn_gepr = page_content_[print_page_][i][11];
			String^ mehr_minder = page_content_[print_page_][i][12];
			create_page_entry(e, kostengruppe, bew_ztr, bezeichnung, vn_einger, vn_gepr, tb, zb_nr, vom, mla, bund_land, foerderbetrag, mehr_minder, begin_at, entry);
			entry++;
			begin_at += 20;
		}

		if (page_content_[print_page_][i][0] == "footer")
		{
			begin_at += 10;
			String^ jahreszuteilung = page_content_[print_page_][i][1];
			String^ bund_land = page_content_[print_page_][i][2];
			String^ mla = page_content_[print_page_][i][3];
			String^ mehr_minder = page_content_[print_page_][i][4];
			create_page_footer(e, jahreszuteilung, bund_land, mla, mehr_minder, begin_at);
		}

	}

	create_page_sign(e);

	// Prepare Settings for next page NextSite
	if (begin_at < end)
	{
		print_page_++;
		done_page_content_ = 0;
	}

	e->HasMorePages = print_page_ < pages_;
}

void bewilligung_result_form::create_page_header(System::Drawing::Printing::PrintPageEventArgs^  e,
	String^ stadt,
	String^ gebiet,
	String^ programm,
	String^ jahr)
{
	// Fonds
	System::Drawing::Font^ header_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));
	System::Drawing::Font^ ueberschrift_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.2F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Center;

	// HeaderBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 0, 1170, 33);

	// Date
	String^ date = Convert::ToString(DateTime::Today.Date);
	date = date->Substring(0, 10);
	e->Graphics->DrawString(date, header_format, Brushes::Black, 1100, 10);

	// Header
	String^ header_string = "Jahresübersicht von " + programm + " in " + stadt + " (" + gebiet + ")";
	if (jahr != "XX" && jahr != "SBE")
		header_string += " - Jahr " + jahr;
	if (jahr == "SBE")
		header_string += " - Sanierungsbedingte Einnahmen";
	if (jahr == "XX")
		header_string += " - Plankosten";
	e->Graphics->DrawString(header_string, header_format, Brushes::Black, 10, 10);
}

void bewilligung_result_form::create_page_jh_label(System::Drawing::Printing::PrintPageEventArgs^ e, String^ label, String^ betrag, int begin_at)
{
	// Fonds
	System::Drawing::Font^ format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// Data
	e->Graphics->DrawString(label, format, Brushes::Black, 10, begin_at);
	e->Graphics->DrawString(betrag, format, Brushes::Black, RectangleF(120, begin_at, 120, 20), allign);
}

void bewilligung_result_form::create_page_jh_eintrag(System::Drawing::Printing::PrintPageEventArgs^ e, String^ datum, String^ betrag, String^ grund, int begin_at)
{
	// Fonds
	System::Drawing::Font^ format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// Data
	e->Graphics->DrawString(datum, format, Brushes::Black, 50, begin_at);
	e->Graphics->DrawString(betrag, format, Brushes::Black, RectangleF(120, begin_at, 120, 20), allign);
	e->Graphics->DrawString(grund, format, Brushes::Black, 240, begin_at);
}

void bewilligung_result_form::create_page_uberschriften(System::Drawing::Printing::PrintPageEventArgs^ e, int begin_at)
{
	// Fonds
	System::Drawing::Font^ ueberschrift_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.2F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Center;

	// Ueberschrift
		// Data
	e->Graphics->DrawString("KG", ueberschrift_format, Brushes::Black, p_s_kostengr, begin_at);
	e->Graphics->DrawString("BWZ", ueberschrift_format, Brushes::Black, p_s_bew_ztr, begin_at);
	e->Graphics->DrawString("Vorhaben", ueberschrift_format, Brushes::Black, p_s_bezeichnung, begin_at);
	e->Graphics->DrawString("VN eingereicht", ueberschrift_format, Brushes::Black, p_s_vn_einger, begin_at);
	e->Graphics->DrawString("VN geprüft", ueberschrift_format, Brushes::Black, p_s_vn_gepr, begin_at);
	e->Graphics->DrawString("TB", ueberschrift_format, Brushes::Black, p_s_tb, begin_at);
	e->Graphics->DrawString("ZB-Nr.", ueberschrift_format, Brushes::Black, p_s_ZB_NR, begin_at);
	e->Graphics->DrawString("vom", ueberschrift_format, Brushes::Black, p_s_vom, begin_at);

	// Beträge
	e->Graphics->DrawString("MLA Gemeinde", ueberschrift_format, Brushes::Black, RectangleF(p_s_mla, begin_at, 100, 20), allign);
	e->Graphics->DrawString("Bund-/Landanteil", ueberschrift_format, Brushes::Black, RectangleF(p_s_bund_land, begin_at, 100, 20), allign);
	e->Graphics->DrawString("Förderbetrag", ueberschrift_format, Brushes::Black, RectangleF(p_s_foerderbetrag, begin_at, 100, 20), allign);
	e->Graphics->DrawString("Mehr-/Minderkosten", ueberschrift_format, Brushes::Black, RectangleF(p_s_mehr_minder, begin_at, 120, 20), allign);
}

void bewilligung_result_form::create_page_entry(System::Drawing::Printing::PrintPageEventArgs^  e,
	String^ kostengr,
	String^ bew_ztr,
	String^ bezeichnung,
	String^ vn_einger,
	String^ vn_gepr,
	String^ tb,
	String^ ZB_NR,
	String^ vom,
	String^ mla,
	String^ bund_land,
	String^ foerderbetrag,
	String^ mehr_minder,
	int begin_at,
	int entry)
{
	if (bezeichnung->Length >= 23)
		bezeichnung = bezeichnung->Substring(0, 23);

	// Fonds
	System::Drawing::Font^ format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	if (entry % 2 == 0)
		e->Graphics->FillRectangle(Brushes::Gainsboro, 0, begin_at - 4, 1170, 19);

	// Data
	e->Graphics->DrawString(kostengr, format, Brushes::Black, p_s_kostengr, begin_at);
	e->Graphics->DrawString(bew_ztr, format, Brushes::Black, p_s_bew_ztr, begin_at);
	e->Graphics->DrawString(bezeichnung, format, Brushes::Black, p_s_bezeichnung, begin_at);
	e->Graphics->DrawString(vn_einger, format, Brushes::Black, p_s_vn_einger, begin_at);
	e->Graphics->DrawString(vn_gepr, format, Brushes::Black, p_s_vn_gepr, begin_at);
	e->Graphics->DrawString(tb, format, Brushes::Black, p_s_tb, begin_at);
	e->Graphics->DrawString(ZB_NR, format, Brushes::Black, p_s_ZB_NR, begin_at);
	e->Graphics->DrawString(vom, format, Brushes::Black, p_s_vom, begin_at);

	// Beträge
	e->Graphics->DrawString(mla, format, Brushes::Black, RectangleF(p_s_mla, begin_at, 100, 20), allign);
	e->Graphics->DrawString(bund_land, format, Brushes::Black, RectangleF(p_s_bund_land, begin_at, 100, 20), allign);
	e->Graphics->DrawString(foerderbetrag, format, Brushes::Black, RectangleF(p_s_foerderbetrag, begin_at, 100, 20), allign);
	e->Graphics->DrawString(mehr_minder, format, Brushes::Black, RectangleF(p_s_mehr_minder, begin_at, 100, 20), allign);
}

void bewilligung_result_form::create_page_footer(System::Drawing::Printing::PrintPageEventArgs^  e,
	String^ jahreszuteilung_in,
	String^ bund_land_in,
	String^ mla_in,
	String^ mehr_minder_in,
	int begin_at)
{
	Decimal jahreszuteilung_d = Decimal(Convert::ToDouble(jahreszuteilung_in));
	Decimal bund_land_d = Decimal(Convert::ToDouble(bund_land_in));
	Decimal mla_d = Decimal(Convert::ToDouble(mla_in));
	Decimal mehr_minder_d = Decimal(Convert::ToDouble(mehr_minder_in));

	String^ foerderbetrag = Decimal_to_string(bund_land_d + mla_d);
	String^ bund_land = Decimal_to_string(bund_land_d);
	String^ mla = Decimal_to_string(mla_d);
	String^ mehr_minder = Decimal_to_string(mehr_minder_d);
	String^ restmittel = Decimal_to_string(jahreszuteilung_d - (bund_land_d + mla_d));

	// Fonds
	System::Drawing::Font^ summen_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));
	System::Drawing::Font^ label_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	//Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, p_s_foerderbetrag - 80, begin_at - 4, 830, 19);

	// Label
	e->Graphics->DrawString("Summen : ", label_format, Brushes::Black, p_s_foerderbetrag - 80, begin_at);

	// Summen
	// Beträge
	e->Graphics->DrawString(mla, summen_format, Brushes::Black, RectangleF(p_s_mla, begin_at, 100, 20), allign);
	e->Graphics->DrawString(bund_land, summen_format, Brushes::Black, RectangleF(p_s_bund_land, begin_at, 100, 20), allign);
	e->Graphics->DrawString(foerderbetrag, summen_format, Brushes::Black, RectangleF(p_s_foerderbetrag, begin_at, 100, 20), allign);
	e->Graphics->DrawString(mehr_minder, summen_format, Brushes::Black, RectangleF(p_s_mehr_minder, begin_at, 100, 20), allign);

	// Restmittel
	if (jahreszuteilung_d != -1)
	{
		e->Graphics->FillRectangle(Brushes::Silver, p_s_foerderbetrag - 80, begin_at + 16, 200, 19);
		e->Graphics->DrawString("Restmittel : ", label_format, Brushes::Black, p_s_foerderbetrag - 80, begin_at + 20);
		e->Graphics->DrawString(restmittel, summen_format, Brushes::Black, RectangleF(p_s_foerderbetrag, begin_at + 20, 100, 20), allign);
	}
}

void bewilligung_result_form::create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e)
{
	// Fonds
	System::Drawing::Font^ main_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));
	System::Drawing::Font^ small_format = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 750, 1170, 80);

	// Firma
	String^ name = "";
	String^ strasse = "";
	String^ hausnr = "";
	String^ plz = "";
	String^ ort = "";

	MyRecordSet RC("SELECT * FROM Anschrift");
	if (RC.get_row() >= 1)
	{
		name = RC.get_val(0, 0);
		strasse = RC.get_val(0, 1);
		hausnr = RC.get_val(0, 2);
		plz = RC.get_val(0, 3);
		ort = RC.get_val(0, 4);
	}
	e->Graphics->DrawString("erstellt durch :", small_format, Brushes::Black, 10, 762);
	e->Graphics->DrawString(name, main_format, Brushes::Black, 80, 760);
	e->Graphics->DrawString(strasse + " " + hausnr, main_format, Brushes::Black, 80, 780);
	e->Graphics->DrawString(plz + " " + ort, main_format, Brushes::Black, 80, 800);

	// Programm
	e->Graphics->DrawString("erstellt mit Hilfe von FÖRDI © MKS", small_format, Brushes::Black, 970, 810);

}

void bewilligung_result_form::AddCellC(String^ text, int xPos, int row, String^ name)
{
	AddCellC(text, xPos, row, name, false);
}

void bewilligung_result_form::AddCellC(String^ text, int xPos, int row, String^ name,bool isDecimal)
{
	AddCell(text, xPos, row,isDecimal);
	label->Name = name;
	label->Click += gcnew System::EventHandler(this, &bewilligung_result_form::Click);
}