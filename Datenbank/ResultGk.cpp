#include "stdafx.h"
#include "ResultGk.h"
#include "My_Connection.h"
#include "MyResult.h"
#include "MyRecordSet.h"

using namespace Datenbank;

ResultGk::ResultGk()
{
}

List<Decimal>^ ResultGk::get_gk_real(String^ stadt, String^ gebiet, String^ programm, List<String^>^ jahre)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Proj = data.get_result("SELECT * FROM db_projekte WHERE stadt='" + stadt + "' AND gebiet='" + gebiet + "'");

	List<Decimal>^ summen = gcnew List<Decimal>;
	for (int i = 0;i < jahre->Count;++i)
		summen->Add(0);

	for (int i = 0;i < R_Proj->get_row();++i)
	{
		Decimal gk = Decimal(Convert::ToDouble(R_Proj->get_val(i, 1)));
		String^ projekt_id = R_Proj->get_val(i, 0);

		MyResult^ R_Prog = data.get_result("SELECT * FROM db_programme WHERE Projekt_ID=" + projekt_id + " AND name='" + programm + "'");
		if (R_Prog->get_row() != 0)
		{
			String^ programm_id = R_Prog->get_val(0, 0);
			MyResult^ R_Bew = data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID=" + programm_id);

			if (R_Bew->get_row() != 0)
			{
				String^ jahr = R_Bew->get_val(0, 4);
				if (R_Bew->get_val(0, 10) == "1")
					jahr = "SBE";
				int index = jahre->IndexOf(jahr);
				if (index != -1)
					summen[index] += gk;
			}
		}
	}
	data.disconnect();

	return summen;
}

List<Decimal>^ ResultGk::get_gk_kom(String^ stadt, String^ gebiet, String^ programm, List<String^>^ jahre)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Proj = data.get_result("SELECT * FROM db_projekte WHERE stadt='" + stadt + "' AND gebiet='" + gebiet + "' AND sk_bha='Gemeinde'");    //local community

	List<Decimal>^ summen = gcnew List<Decimal>;
	for (int i = 0;i < jahre->Count;++i)
		summen->Add(0);

	for (int i = 0;i < R_Proj->get_row();++i)
	{
		Decimal gk = Decimal(Convert::ToDouble(R_Proj->get_val(i, 1)));
		String^ projekt_id = R_Proj->get_val(i, 0);

		MyResult^ R_Prog = data.get_result("SELECT * FROM db_programme WHERE Projekt_ID=" + projekt_id + " AND name='" + programm + "'");
		if (R_Prog->get_row() != 0)
		{
			String^ programm_id = R_Prog->get_val(0, 0);
			MyResult^ R_Bew = data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID=" + programm_id);

			if (R_Bew->get_row() != 0)
			{
				String^ jahr = R_Bew->get_val(0, 4);
				if (R_Bew->get_val(0, 10) == "1")
					jahr = "SBE";
				int index = jahre->IndexOf(jahr);
				if (index != -1)
					summen[index] += gk;
			}
		}
	}
	data.disconnect();

	return summen;
}

List<Decimal>^ ResultGk::get_gk_priv(String^ stadt, String^ gebiet, String^ programm, List<String^>^ jahre)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Proj = data.get_result("SELECT * FROM db_projekte WHERE stadt='" + stadt + "' AND gebiet='" + gebiet + "' AND sk_bha='Privat'");

	List<Decimal>^ summen = gcnew List<Decimal>;
	for (int i = 0;i < jahre->Count;++i)
		summen->Add(0);

	for (int i = 0;i < R_Proj->get_row();++i)
	{
		Decimal gk = Decimal(Convert::ToDouble(R_Proj->get_val(i, 1)));
		String^ projekt_id = R_Proj->get_val(i, 0);

		MyResult^ R_Prog = data.get_result("SELECT * FROM db_programme WHERE Projekt_ID=" + projekt_id + " AND name='" + programm + "'");
		if (R_Prog->get_row() != 0)
		{
			String^ programm_id = R_Prog->get_val(0, 0);
			MyResult^ R_Bew = data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID=" + programm_id);

			if (R_Bew->get_row() != 0)
			{
				String^ jahr = R_Bew->get_val(0, 4);
				if (R_Bew->get_val(0, 10) == "1")
					jahr = "SBE";
				int index = jahre->IndexOf(jahr);
				if (index != -1)
					summen[index] += gk;
			}
		}
	}
	data.disconnect();

	return summen;
}

void ResultGk::GenerateTableHeader() {
	// GK Real
	if (show_gk_real_)
	{
		AddTableHeaderCell("GK Real", spalte_gk_real_);
		//SetLabelSize(column_width_, 13);
	}

	// GK Kom
	if (show_gk_kom_)
	{
		AddTableHeaderCell("GK Komunal", spalte_gk_kom_);
		//SetLabelSize(column_width_, 13);
	}

	// GK Priv
	if (show_gk_priv_)
	{
		AddTableHeaderCell("GK Privat", spalte_gk_priv_);
		//SetLabelSize(column_width_, 13);
	}

	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0, start_pos);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 20);
	ueberschrift_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(ueberschrift_back);
	
	start_pos += 20;
}
