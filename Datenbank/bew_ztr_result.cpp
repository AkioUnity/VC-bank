#include "StdAfx.h"

#include "My_Connection.h"
#include "MyResult.h"
#include "helper.h"
#include "project_form.h"
#include "project_class.h"
#include "choose_printer.h"
#include "MyRecordSet.h"

#include "bew_ztr_result.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

//Windows::Forms::MessageBox::Show("t");

void bew_ztr_result::bew_ztr_result_Load(System::Object^  sender, System::EventArgs^  e)
{
	// Reset
	this->Controls->Clear();
	approvals_valueList->Clear();

	// Load
	Hide();
	ladebalken_->Show();
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Bewilligungszeitraumübersicht";
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Bewilligungszeitraumübersicht";
	My_Connection data;
	data.connect();

	List<String^>^ Stadt_liste = gcnew List<String^>;
	if(stadt_=="-1")
	{
		MyResult^ RC=data.get_result("SELECT * FROM Staedte");
		for(int i=0;i<RC->get_row();++i)
			Stadt_liste->Add(RC->get_val(i,1));
	}
	else
		Stadt_liste->Add(stadt_);

	for(int stadt_param=0;stadt_param<Stadt_liste->Count;++stadt_param)
	{
		String^ stadt =Stadt_liste[stadt_param];
		
		List<String^>^ Gebiet_liste = gcnew List<String^>;
		if(gebiet_=="-1")
		{
			MyResult^ RC_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
			MyResult^ RC=data.get_result("SELECT Gebiet FROM Gebiete WHERE Stadt_ID="+RC_Stadt->get_val(0,0));
			for(int i=0;i<RC->get_row();++i)
				Gebiet_liste->Add(RC->get_val(i,0));
		}
		else
			Gebiet_liste->Add(gebiet_);

		for(int gebiet_param=0;gebiet_param<Gebiet_liste->Count;++gebiet_param)
		{
			String^ gebiet=Gebiet_liste[gebiet_param];

			List<String^>^ Programm_liste=gcnew List<String^>;
			if(programm_=="-1")
			{
				MyResult^ RC_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
				MyResult^ RC_Gebiet=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+RC_Stadt->get_val(0,0)+" AND Gebiet='"+gebiet+"'");
				MyResult^ RC=data.get_result("SELECT * FROM Programme WHERE Gebiet_ID="+RC_Gebiet->get_val(0,0));
				for(int i=0;i<RC->get_row();++i)
					Programm_liste->Add(RC->get_val(i,2));
			}
			else
				Programm_liste->Add(programm_);

			for(int programm_param=0;programm_param<Programm_liste->Count;++programm_param)
			{
				String^ programm=Programm_liste[programm_param];
				MyResult^ RC_Projekt=data.get_result("SELECT * FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"'");

				for(int projekt_param=0;projekt_param<RC_Projekt->get_row();++projekt_param)
				{
					// Projekt
					String^ id=RC_Projekt->get_val(projekt_param,0);
					String^ kostengruppe=RC_Projekt->get_val(projekt_param,8);		// 1
					String^ bezeichnung=RC_Projekt->get_val(projekt_param,5);	// 3
					String^ bew_ztr=RC_Projekt->get_val(projekt_param,7);		// 9
					String^ vn_einger=RC_Projekt->get_val(projekt_param,11);		// 10
					String^ vn_gepr=RC_Projekt->get_val(projekt_param,12);		// 11

					bool load1=true;
					bool load2=true;
					bool load3=true;
					if(bis_!="-1")
						load2=date_is_bigger(bis_,bew_ztr);
					if(nicht_einger_)
						load3=(vn_einger=="");
					else
						load3=(vn_einger!="" && vn_gepr=="");


					if(load1 && load2 && load3)
					{
						MyResult^ RC_Programm=data.get_result("SELECT * FROM db_programme WHERE projekt_ID="+RC_Projekt->get_val(projekt_param,0)+" AND name='"+programm+"'");

						if(RC_Programm->get_row()!=0)
						{
							String^ bewilligung_query="SELECT * FROM db_programme_bewilligung WHERE programm_ID="+RC_Programm->get_val(0,0);

							MyResult^ RC_Bewilligung=data.get_result(bewilligung_query);
							for(int bewilligung_param=0;bewilligung_param<RC_Bewilligung->get_row();++bewilligung_param)
							{
								String^ TB="-";
								String^ programm_id=RC_Bewilligung->get_val(bewilligung_param,1);
								String^ zb_nr=RC_Bewilligung->get_val(bewilligung_param,2)+"-"+RC_Bewilligung->get_val(bewilligung_param,3)+"/"+RC_Bewilligung->get_val(bewilligung_param,4); // 2
								String^ bew_id=RC_Bewilligung->get_val(bewilligung_param,0);
								int tb_nr=get_tb(programm_id,bew_id);
								if(tb_nr!=0)
									TB=Convert::ToString(tb_nr)+". TB"; // 4
								String^ vom=RC_Bewilligung->get_val(bewilligung_param,5); // 5
								Decimal bund_land=Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param,8))); // 7
								Decimal bund_land_vn=Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param,9))); // 7
								Decimal mla=Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param,6))); // 8
								Decimal mla_vn=Decimal(Convert::ToDouble(RC_Bewilligung->get_val(bewilligung_param,7))); // 8
								Decimal mehr_minder=(mla_vn+bund_land_vn)-(mla+bund_land);		//12								// 12
								Decimal förderbetrag=mla+bund_land; // 6
								Decimal förderbetrag_vn=mla_vn+bund_land_vn; // 6

								List<String^>^ bewilligung=gcnew List<String^>;

								/*
								bew_werte:
								[0] stadt
								[1] gebiet
								[2] programm
								[3] jahr
								[4] kostengruppe
								[5] zb_nr
								[6] bezeichnung
								[7] tb
								[8] vom
								[9] förderbetr
								[10] bund/land
								[11] mla
								[12] bew_ztr
								[13] vn_einger
								[14] vn_gepr
								[15] mehr/minder
								[16] bew_id
								*/

								bewilligung->Add(stadt);
								bewilligung->Add(gebiet);
								bewilligung->Add(programm);
								if(RC_Bewilligung->get_val(bewilligung_param,10)=="1")
									bewilligung->Add("SBE");
								else
									bewilligung->Add(RC_Bewilligung->get_val(bewilligung_param,4));
								bewilligung->Add(kostengruppe);
								bewilligung->Add(zb_nr);
								bewilligung->Add(bezeichnung);
								bewilligung->Add(TB);
								bewilligung->Add(vom);
								if(vn_einger!="")
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
								if(vn_einger!="")
									bewilligung->Add(vn_einger);
								else
									bewilligung->Add("-");
								if(vn_gepr!="")
									bewilligung->Add(vn_gepr);
								else
									bewilligung->Add("-");
								if(vn_einger!="")
									bewilligung->Add(Decimal_to_string(mehr_minder));
								else
									bewilligung->Add("-");
								bewilligung->Add(id);

								approvals_valueList->Add(bewilligung);
								ladebalken_->Controls->Find("progress",true)[0]->Text="a";
								ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
							}
						}
					}
				}
			}
		}
	}
	data.disconnect();

	if(approvals_valueList->Count==0)
	{
		ladebalken_->Close();
		Windows::Forms::MessageBox::Show("Es wurden keine Einträge zu ihrer Anfrage gefunden.","Ungültige Suche");
		Close();
	}
	else
	{
		ladebalken_->Controls->Find("texter",true)[0]->Text="Verarbeite Daten und erzeuge Einträge";
		ladebalken_->Controls->Find("texter",true)[0]->Text="Verarbeite Daten und erzeuge Einträge";

		sort_bewilligung();
		if(approvals_valueList->Count!=0)
		{
			//String^ jahr="";
			String^ programm="";
			String^ stadt="";
			String^ gebiet="";
			int eintrag=0;

			Decimal summe_mla=0;
			Decimal summe_bund_land=0;
			Decimal summe_mehr_minder=0;
			start_pos=0;

			for(int i=0;i<approvals_valueList->Count;++i)
			{
				if(approvals_valueList[i][2]!=programm || approvals_valueList[i][1]!=gebiet || approvals_valueList[i][0]!=stadt )
				{
					if(start_pos!=0)
					{
						generate_footer(summe_bund_land,summe_mla,summe_mehr_minder);
						start_pos+=20;
					}
					summe_mla=0;
					summe_bund_land=0;
					summe_mehr_minder=0;
					eintrag=0;
					stadt=approvals_valueList[i][0];
					gebiet=approvals_valueList[i][1];
					programm=approvals_valueList[i][2];

					generate_header(stadt,gebiet,programm);

					Generate_TableHeadings();
				}

				String^ bund_land=approvals_valueList[i][10];
				String^ mla=approvals_valueList[i][11];
				String^ mehr_minder=approvals_valueList[i][15];
				bool neg=false;
				if(mehr_minder[0]=='-')
					neg=true;
				mehr_minder=mehr_minder->Replace(L"€","")->Replace("-","")->Replace(".","")->Trim();
				bund_land=bund_land->Replace(L"€","")->Replace(".","")->Trim();
				mla=mla->Replace(L"€","")->Replace(".","")->Trim();
				summe_bund_land+=Decimal(Convert::ToDouble(bund_land));
				summe_mla+=Decimal(Convert::ToDouble(mla));
				if(mehr_minder=="")
					mehr_minder="0";
				if(!neg)
					summe_mehr_minder+=Decimal(Convert::ToDouble(mehr_minder));
				else
					summe_mehr_minder+=-1*Decimal(Convert::ToDouble(mehr_minder));
				GenerateApproval(approvals_valueList[i]->GetRange(4,13),eintrag);

				++eintrag;
			
				ladebalken_->Controls->Find("progress",true)[0]->Text="a";
				ladebalken_->Controls->Find("progress",true)[0]->Text=" ";

				if(i==approvals_valueList->Count-1)
					generate_footer(summe_bund_land,summe_mla,summe_mehr_minder);
			}
		}
		place_button();
		ladebalken_->Hide();
		Show();
	}
}

int bew_ztr_result::get_tb(String^ prog_id, String^ bew_id)
{
	My_Connection data;
	data.connect();
	String^ query="SELECT * FROM db_programme_bewilligung WHERE programm_ID="+prog_id;
	MyResult^ RC=data.get_result(query);
	data.disconnect();
	
	if(RC->get_row()!=1)
		for(int i=0;i<RC->get_row();++i)
			if(bew_id==RC->get_val(i,0))
				return i+1;
	
	return 0;

}

void bew_ztr_result::sort_bewilligung()
{
	List< List<String^>^ >^ zwichenspeicher = gcnew List< List<String^>^ >;

	List<String^>^ staedte = gcnew List<String^>;
	List<String^>^ gebiete = gcnew List<String^>;
	List<String^>^ programme = gcnew List<String^>;

	for(int i=0;i<approvals_valueList->Count;++i)
	{
		if(!is_existent_in(staedte,approvals_valueList[i][0]))
			staedte->Add(approvals_valueList[i][0]);
		if(!is_existent_in(gebiete,approvals_valueList[i][1]))
			gebiete->Add(approvals_valueList[i][1]);
		if(!is_existent_in(programme,approvals_valueList[i][2]))
			programme->Add(approvals_valueList[i][2]);
	}

	staedte->Sort();
	gebiete->Sort();
	programme->Sort();

	for(int stadt_param=0;stadt_param<staedte->Count;++stadt_param)
	{
		for(int gebiet_param=0;gebiet_param<gebiete->Count;++gebiet_param)
		{
			for(int prog_param=0;prog_param<programme->Count;++prog_param)
			{
				List< List<String^>^ >^ tmp = gcnew List< List<String^>^ >;
				int i=0;
				do
				{
					if(	approvals_valueList[i][0]==staedte[stadt_param] &&
						approvals_valueList[i][1]==gebiete[gebiet_param] &&
						approvals_valueList[i][2]==programme[prog_param])
					{
						tmp->Add(approvals_valueList[i]);
					}
					++i;
				}
				while(i<approvals_valueList->Count);

				tmp=sort_programm(tmp);
				for(int i=0;i<tmp->Count;++i)
					zwichenspeicher->Add(tmp[i]);
			}
		}
	}
	approvals_valueList=zwichenspeicher;
}

List< List<String^>^ >^ bew_ztr_result::sort_programm(List< List<String^>^ >^ input)
{
	/*
	input[i] :
	[0] stadt
	[1] gebiet
	[2] programm
	[3] jahr
	[4] kostengruppe
	[5] zb_nr
	[6] bezeichnung
	[7] tb
	[8] vom
	[9] förderbetr
	[10] bund/land
	[11] mla
	[12] bew_ztr
	[13] vn_einger
	[14] vn_gepr
	[15] mehr/minder
	[16] bew_id
	*/

	// Get Bew_Ztr
	List<String^>^ bew_ztr_list = gcnew List<String^>;
	for(int i=0;i<input->Count;++i)
		if(!is_existent_in(bew_ztr_list,input[i][12]))
			bew_ztr_list->Add(input[i][12]);

	// Sort Bew Ztr
	for (int i=bew_ztr_list->Count;i>1; --i)
		for (int j=0; j<i-1; ++j)
			if (date_is_bigger(bew_ztr_list[j],bew_ztr_list[j+1]))
			{
				String^ tmp = bew_ztr_list[j];
				bew_ztr_list[j]=bew_ztr_list[j+1];
				bew_ztr_list[j+1]=tmp;
			}

	// Fill Lists
	List< List<String^>^ >^ result=gcnew List< List<String^>^ >;
	for(int i=0;i<bew_ztr_list->Count;++i)
	{
		String^ current_bew_ztr=bew_ztr_list[i];
		List< List<String^>^ >^ tmp=gcnew List< List<String^>^ >;
		for(int j=0;j<input->Count;++j)
			if(input[j][12]==current_bew_ztr)
				tmp->Add(input[j]);
		tmp = sort_for_year(tmp);
		for(int j=0;j<tmp->Count;++j)
			result->Add(tmp[j]);
	}
	
	return result;
}

List< List<String^>^ >^ bew_ztr_result::sort_for_year(List< List<String^>^ >^ input)
{
	//
		// Get Years
	List<String^>^ year_list = gcnew List<String^>;
	for(int i=0;i<input->Count;++i)
		if(!is_existent_in(year_list,input[i][3]))
			year_list->Add(input[i][3]);

	// Sort Year List
	for(int i=year_list->Count;i>1;--i)
	{
		for (int j=0; j<i-1 ; ++j)
		{
			String^ jahr1=year_list[j];
			String^ jahr2=year_list[j+1];

			if(jahr1=="XX")
				jahr1="70";
			if(jahr2=="XX")
				jahr2="70";
			if(jahr1=="SBE")
				jahr1="71";
			if(jahr2=="SBE")
				jahr2="71";

			if(Convert::ToInt32(jahr1)>89)
				jahr1="19"+jahr1;
			else
				jahr1="20"+jahr1;

			if(Convert::ToInt32(jahr2)>89)
				jahr2="19"+jahr2;
			else
				jahr2="20"+jahr2;

			if (Convert::ToInt32(jahr1) > Convert::ToInt32(jahr2))
			{
				String^ cache=year_list[j];
				year_list[j]=year_list[j+1];
				year_list[j+1]=cache;
			}	
		}
	}

	// Fill Lists
	List< List<String^>^ >^ result=gcnew List< List<String^>^ >;
	for(int i=0;i<year_list->Count;++i)
	{
		String^ current_year=year_list[i];
		List< List<String^>^ >^ tmp=gcnew List< List<String^>^ >;
		for(int j=0;j<input->Count;++j)
			if(input[j][3]==current_year)
				tmp->Add(input[j]);
		sort_for_ZB_NR(tmp);
		for(int j=0;j<tmp->Count;++j)
			result->Add(tmp[j]);
	}
	
	return result;
}

void bew_ztr_result::sort_for_ZB_NR(List< List<String^>^ >^ input)
{
	for (int i=input->Count;i>1; --i)
	{
		for (int j=0; j<i-1; ++j)
		{
			String^ zb_nr1=input[j][5];
			zb_nr1=zb_nr1->Replace("/","")->Replace("-","")->Replace("X","9");
			String^ zb_nr2=input[j+1][5];
			zb_nr2=zb_nr2->Replace("/","")->Replace("-","")->Replace("X","9");

			//Windows::Forms::MessageBox::Show(zb_nr1+"\n"+zb_nr2);

			if (Convert::ToInt64(zb_nr1) > Convert::ToInt64(zb_nr2))
			{
				List<String^>^ tmp = input[j];
				input[j]=input[j+1];
				input[j+1]=tmp;
			}
		}
	}
}

bool bew_ztr_result::is_existent_in(List<String^>^ liste,String^ value)
{
	for each(String^ eintrag in liste)
		if(eintrag==value)
			return true;
	return false;
}

// Auswertungselemente
void bew_ztr_result::generate_header(String^ stadt, String^ gebiet, String^ programm)
{
	page_content_->Add(gcnew List< List<String^>^ >);
	List<String^>^ header=gcnew List<String^>;
	header->Add("header");
	header->Add(stadt);
	header->Add(gebiet);
	header->Add(programm);
	page_content_[page_content_->Count-1]->Add(header);

	AddHeaderCell("Stadt         : " + stadt, 5, 1 + start_pos);		
	AddHeaderCell("Gebiet       : " + gebiet, 5, 1 * 13 + 1 + start_pos);	
	AddHeaderCell("Programm : " + programm, 5, 2 * 13 + 1 + start_pos);
	AddHeaderDivider(936, 3 * 13 + 1);	
	start_pos+=2*13+25;

	++row_;
}

void bew_ztr_result::Generate_TableHeadings()
{
	List<String^>^ ueberschrift=gcnew List<String^>;
	ueberschrift->Add("ueberschrift");
	page_content_[page_content_->Count-1]->Add(ueberschrift);

	col_ = 1;
	AddTableHeaderCell("Kostengr.", s_kostenart);
	AddTableHeaderCell("ZB-Nr.", s_zb_nr);
	
	AddTableHeaderCell("Vorhaben", s_bezeichnung, 110, 15);
	
	AddTableHeaderCell("TB", s_tb);
	AddTableHeaderCell("vom", s_vom);

	AddTableHeaderCell("Förderbetrag", s_foerder, 85, 15);
	AddTableHeaderCell("Bund-/Landanteil", s_bund_land, 85, 15);
	AddTableHeaderCell("MLA Gemeinde", s_mla, 85, 15);

	AddTableHeaderCell("BWZ", s_bew_ztr);
	AddTableHeaderCell("VN eingereicht", s_einger);
	AddTableHeaderCell("VN geprüft", s_gepr);
	AddTableHeaderCell("Mehr-/Minderkosten", s_mehr_minder);

	sumStart = row_+1;
			
	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0,start_pos);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 20);
	ueberschrift_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(ueberschrift_back);

	start_pos+=20;
}

void bew_ztr_result::GenerateApproval(List<String^>^ werte,int eintrag)
{
	MyRecordSet RC("SELECT Wert,Abkuerzung FROM Kostengruppe WHERE Wert='"+werte[0]+"'");
	String^ kostengruppe_s=RC.get_val(0,1);
	String^ zb_nr_s=werte[1];
	String^ bezeichnung_s=werte[2];
	String^ tb_s=werte[3];
	String^ vom_s=werte[4];
	String^ foerderbetrag_s=werte[5];
	String^ bund_land_s=werte[6];
	String^ mla_s=werte[7];
	String^ bew_ztr_s=werte[8];
	String^ vn_einger_s=werte[9];
	String^ vn_gepr_s=werte[10];
	String^ mehr_minder_s=werte[11];

	List<String^>^ entry=gcnew List<String^>;
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
	page_content_[page_content_->Count-1]->Add(entry);

	String^ id=werte[12];

	System::Drawing::Color color;
	if(eintrag%2!=0)
	{
		color=System::Drawing::Color::Gainsboro;
	}
	else
	{
		color=System::Drawing::Color::White;
	}

	row_++;
	
	int rowNum = eintrag;
	col_ = 1;
	AddCellC(RC.get_val(0, 1), s_kostenart, rowNum,id);
	AddCellC(werte[1], s_zb_nr, rowNum,id);
	AddCellC(werte[2], s_bezeichnung, rowNum, id);

	label->MaximumSize = System::Drawing::Size(110, 0);
	heightCalc = label->Size.Height;

	AddCellC(werte[3], s_tb, rowNum, id);
	AddCellC(werte[4], s_vom, rowNum, id);
	AddCellC(werte[5], s_foerder, rowNum, id,true);  // foerderbetrag
	SetLabelSize(85, 15);
	AddCellC(werte[6], s_bund_land, rowNum, id,true);  // bund_land
	SetLabelSize(85, 15);
	AddCellC(werte[7], s_mla, rowNum, id,true);  // bund_land
	SetLabelSize(85, 15);
	AddCellC(werte[8], s_bew_ztr, rowNum, id);
	AddCellC(werte[9], s_einger, rowNum, id);
	AddCellC(werte[10], s_gepr, rowNum, id);
	AddCellC(werte[11], s_mehr_minder, rowNum, id,true);
	SetLabelSize(85, 15);	

	AddLineBreak(color);
	label->Name = id;
	label->Click += gcnew System::EventHandler(this, &bew_ztr_result::Click);
}

void bew_ztr_result::generate_footer( Decimal bund_land, Decimal mla, Decimal mehr_minder)
{
	List<String^>^ footer=gcnew List<String^>;
	footer->Add("footer");
	footer->Add(Convert::ToString(bund_land));
	footer->Add(Convert::ToString(mla));
	footer->Add(Convert::ToString(mehr_minder));
	page_content_[page_content_->Count-1]->Add(footer);

	// foerderbetrag
	row_++;
	row_++;
	col_ = 6;	
	AddTableFooter(Decimal_to_string(bund_land + mla), s_foerder, 85, 15);
	//foerderbetrag_ges->Text = Decimal_to_string(bund_land + mla);
	AddTableFooter(Decimal_to_string(bund_land), s_bund_land, 85, 15);
	AddTableFooter(Decimal_to_string(mla), s_mla, 85, 15);
	col_ += 3;
	AddTableFooter(Decimal_to_string(mehr_minder), s_mehr_minder, 85, 15);

	start_pos+=20;
}

void bew_ztr_result::place_button()
{
	start_pos=start_pos+10;

	btn_print->Location=System::Drawing::Point(5, start_pos);
	btn_print->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_print);

	ResultForm::place_button();
}

// Events
void bew_ztr_result::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::Label^  cache = gcnew System::Windows::Forms::Label();
	cache->Text="-1";
	Form^ choose_print =gcnew choose_printer(cache);
	choose_print->ShowDialog();
	if(cache->Text!="-1")
	{
		pages_=page_content_->Count;
		print_page_=0;

		printDocument1->PrinterSettings->PrinterName=cache->Text;
		printDocument1->DefaultPageSettings->Landscape=true;
		printDocument1->DocumentName="Übersicht Verwendungsnachweis";		
		printDocument1->DefaultPageSettings->Margins->Top=25;
		printDocument1->DefaultPageSettings->Margins->Bottom=25;
		printDocument1->DefaultPageSettings->Margins->Right=25;
		printDocument1->DefaultPageSettings->Margins->Left=25;
		printDocument1->OriginAtMargins=true;
		printDocument1->Print();
	}
}

void bew_ztr_result::Click(System::Object^  sender, System::EventArgs^  e)
{
	int index=-1;
	for(int i=0;i<this->Controls->Count;++i)
		if(ReferenceEquals(this->Controls[i],sender))
		{
			index=i;
			break;
		}
	int id=Convert::ToInt32(this->Controls[index]->Name);

	String^ message = "Wird das Projekt geöffnet, wird die Auswertung nach Schließen des Projektes neu geladen.\nFortfahren ?";
	String^ caption = "Soll das Projekt geöffnet werden?";
	MessageBoxButtons buttons = MessageBoxButtons::YesNo;
	System::Windows::Forms::DialogResult result;

	result = MessageBox::Show( this, message, caption, buttons );
	if ( result == ::DialogResult::Yes )
	{
		Form^ Projekt = gcnew project_form(id,user_id_);
		Projekt->ShowDialog();
		bew_ztr_result_Load(sender,e);
	}
}

// Printer Stuff
void bew_ztr_result::printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e)
{
	
    e->Graphics->PageScale =0.95;
	int begin_at=0;
	int entry=0;
	int end=700;

	// Spalten Setzten
	p_s_kostengr=10;
	p_s_ZB_NR=60;
	p_s_bezeichnung=150;
	p_s_tb=310;
	p_s_vom=350;
	p_s_foerderbetrag=420;
	p_s_bund_land=530;
	p_s_mla=640;
	p_s_bew_ztr=760;
	p_s_vn_einger=850;
	p_s_vn_gepr=940;
	p_s_mehr_minder=1030;


	// iterate through Content of actual Page
	for(int i=done_page_content_;i<page_content_[print_page_]->Count;++i)
	{
		if(begin_at>=end)
		{
			page_content_[print_page_]->Insert(i,page_content_[print_page_][0]);
			List<String^>^ ueberschrift=gcnew List<String^>;
			ueberschrift->Add("ueberschrift");
			page_content_[print_page_]->Insert(i+1,ueberschrift);
			break;
		}

		done_page_content_=i;

		if(page_content_[print_page_][i][0]=="header")
		{
			String^ stadt=page_content_[print_page_][i][1];
			String^ gebiet=page_content_[print_page_][i][2];
			String^ programm=page_content_[print_page_][i][3];
			create_page_header(e,stadt,gebiet,programm);
			begin_at+=60;
		}

		if(page_content_[print_page_][i][0]=="ueberschrift")
		{
			begin_at+=10;
			create_page_uberschriften(e,begin_at);
			begin_at+=30;
		}

		if(page_content_[print_page_][i][0]=="eintrag")
		{
			String^ kostengruppe=page_content_[print_page_][i][1];
			String^ zb_nr=page_content_[print_page_][i][2];
			String^ bezeichnung=page_content_[print_page_][i][3];
			String^ tb=page_content_[print_page_][i][4];
			String^ vom=page_content_[print_page_][i][5];
			String^ foerderbetrag=page_content_[print_page_][i][6];
			String^ bund_land=page_content_[print_page_][i][7];
			String^ mla=page_content_[print_page_][i][8];
			String^ bew_ztr=page_content_[print_page_][i][9];
			String^ vn_einger=page_content_[print_page_][i][10];
			String^ vn_gepr=page_content_[print_page_][i][11];
			String^ mehr_minder=page_content_[print_page_][i][12];
			create_page_entry(e,kostengruppe,bew_ztr,bezeichnung,vn_einger,vn_gepr,tb,zb_nr,vom,mla,bund_land,foerderbetrag,mehr_minder,begin_at,entry);
			entry++;
			begin_at+=20;
		}

		if(page_content_[print_page_][i][0]=="footer")
		{	
			begin_at+=10;
			String^ bund_land=page_content_[print_page_][i][1];
			String^ mla=page_content_[print_page_][i][2];
			String^ mehr_minder=page_content_[print_page_][i][3];
			create_page_footer(e,bund_land,mla,mehr_minder,begin_at);
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

void bew_ztr_result::create_page_header(	System::Drawing::Printing::PrintPageEventArgs^  e,
														String^ stadt,
														String^ gebiet,
														String^ programm)
{
	// Fonds
	System::Drawing::Font^ header_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ ueberschrift_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.2F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Center;

	// HeaderBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 0, 1170, 33);

	// Date
	String^ date=Convert::ToString(DateTime::Today.Date);
	date=date->Substring(0,10);
	e->Graphics->DrawString(date,header_format,Brushes::Black, 1100, 10);

	// Header
	String^ header_string="Übersicht Verwendungsnachweis von "+programm+" in "+stadt+" ("+gebiet+")";
	e->Graphics->DrawString(header_string ,header_format,Brushes::Black, 10, 10);
}

void bew_ztr_result::create_page_uberschriften(System::Drawing::Printing::PrintPageEventArgs^ e, int begin_at)
{	
	// Fonds
	System::Drawing::Font^ ueberschrift_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.2F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Center;

	// Ueberschrift
		// Data
	e->Graphics->DrawString("KG",ueberschrift_format,Brushes::Black, p_s_kostengr, begin_at);
	e->Graphics->DrawString("BWZ",ueberschrift_format,Brushes::Black, p_s_bew_ztr, begin_at);
	e->Graphics->DrawString("Vorhaben",ueberschrift_format,Brushes::Black, p_s_bezeichnung, begin_at);
	e->Graphics->DrawString("VN eingereicht",ueberschrift_format,Brushes::Black, p_s_vn_einger, begin_at);
	e->Graphics->DrawString("VN geprüft",ueberschrift_format,Brushes::Black, p_s_vn_gepr, begin_at);
	e->Graphics->DrawString("TB",ueberschrift_format,Brushes::Black, p_s_tb, begin_at);
	e->Graphics->DrawString("ZB-Nr.",ueberschrift_format,Brushes::Black, p_s_ZB_NR, begin_at);
	e->Graphics->DrawString("vom",ueberschrift_format,Brushes::Black, p_s_vom, begin_at);

		// Beträge
	e->Graphics->DrawString("MLA Gemeinde",ueberschrift_format,Brushes::Black,RectangleF(p_s_mla, begin_at,100,20),allign);
	e->Graphics->DrawString("Bund-/Landanteil",ueberschrift_format,Brushes::Black,RectangleF(p_s_bund_land, begin_at,100,20),allign);
	e->Graphics->DrawString("Förderbetrag",ueberschrift_format,Brushes::Black,RectangleF(p_s_foerderbetrag, begin_at,100,20),allign);
	e->Graphics->DrawString("Mehr-/Minderkosten",ueberschrift_format,Brushes::Black,RectangleF(p_s_mehr_minder, begin_at,120,20),allign);
}

void bew_ztr_result::create_page_entry(	System::Drawing::Printing::PrintPageEventArgs^  e,
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
	if(bezeichnung->Length>=25)
		bezeichnung=bezeichnung->Substring(0,25);

	// Fonds
	System::Drawing::Font^ format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	
	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	if( entry%2==0 )
		e->Graphics->FillRectangle(Brushes::Gainsboro, 0, begin_at-4, 1170, 19);

	// Data
	e->Graphics->DrawString(kostengr,format,Brushes::Black, p_s_kostengr, begin_at);
	e->Graphics->DrawString(bew_ztr,format,Brushes::Black, p_s_bew_ztr, begin_at);
	e->Graphics->DrawString(bezeichnung,format,Brushes::Black, p_s_bezeichnung, begin_at);
	e->Graphics->DrawString(vn_einger,format,Brushes::Black, p_s_vn_einger, begin_at);
	e->Graphics->DrawString(vn_gepr,format,Brushes::Black, p_s_vn_gepr, begin_at);
	e->Graphics->DrawString(tb,format,Brushes::Black, p_s_tb, begin_at);
	e->Graphics->DrawString(ZB_NR,format,Brushes::Black, p_s_ZB_NR, begin_at);
	e->Graphics->DrawString(vom,format,Brushes::Black, p_s_vom, begin_at);

	// Beträge
	e->Graphics->DrawString(mla,format,Brushes::Black,RectangleF(p_s_mla, begin_at,100,20),allign);
	e->Graphics->DrawString(bund_land,format,Brushes::Black,RectangleF(p_s_bund_land, begin_at,100,20),allign);
	e->Graphics->DrawString(foerderbetrag,format,Brushes::Black,RectangleF(p_s_foerderbetrag, begin_at,100,20),allign);
	e->Graphics->DrawString(mehr_minder,format,Brushes::Black,RectangleF(p_s_mehr_minder, begin_at,100,20),allign);
}

void bew_ztr_result::create_page_footer(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ bund_land_in, 
													String^ mla_in,
													String^ mehr_minder_in,
													int begin_at)
{
	Decimal bund_land_d=Decimal(Convert::ToDouble(bund_land_in));
	Decimal mla_d=Decimal(Convert::ToDouble(mla_in));
	Decimal mehr_minder_d=Decimal(Convert::ToDouble(mehr_minder_in));

	String^ foerderbetrag=Decimal_to_string(bund_land_d+mla_d);
	String^ bund_land=Decimal_to_string(bund_land_d);
	String^ mla=Decimal_to_string(mla_d);
	String^ mehr_minder=Decimal_to_string(mehr_minder_d);

	// Fonds
	System::Drawing::Font^ summen_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ label_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	
	//Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, p_s_foerderbetrag-80, begin_at-4, 830, 19);

	// Label
	e->Graphics->DrawString("Summen : ",label_format,Brushes::Black,p_s_foerderbetrag-80,begin_at);

	// Summen
	// Beträge
	e->Graphics->DrawString(mla,summen_format,Brushes::Black,RectangleF(p_s_mla, begin_at,100,20),allign);
	e->Graphics->DrawString(bund_land,summen_format,Brushes::Black,RectangleF(p_s_bund_land, begin_at,100,20),allign);
	e->Graphics->DrawString(foerderbetrag,summen_format,Brushes::Black,RectangleF(p_s_foerderbetrag, begin_at,100,20),allign);
	e->Graphics->DrawString(mehr_minder,summen_format,Brushes::Black,RectangleF(p_s_mehr_minder, begin_at,100,20),allign);
}

void bew_ztr_result::create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e)
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


void Datenbank::bew_ztr_result::AddCellC(String^ text, int xPos, int row,String^ name)
{
	AddCellC(text, xPos, row, name, false);
}

void Datenbank::bew_ztr_result::AddCellC(String^ text, int xPos, int row, String^ name, bool isDecimal)
{
	AddCell(text, xPos, row,isDecimal);
	label->Name = name;
	label->Click += gcnew System::EventHandler(this, &bew_ztr_result::Click);
}

