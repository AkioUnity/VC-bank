#include "StdAfx.h"

#include "My_Connection.h"
#include "MyResult.h"
#include "MyRecordSet.h"
#include "project_form.h"
#include "choose_printer.h"
#include "helper.h"

#include "kostengr_uebersicht_result.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

// Windows::Forms::MessageBox::Show(

void kostengr_uebersicht_result::kostengr_uebersicht_result_Load(System::Object^  sender, System::EventArgs^  e)
{	
	Hide();
	ladebalken_->Show();
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Kostengruppenübersicht";
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Kostengruppenübersicht";
	page_content_->Clear();
	pages_=0;
	start_=0;
	this->Controls->Clear();
	List< List<String^>^ >^ bewilligungen = load_bewilligungen();
	if(bewilligungen->Count==0)
	{
		ladebalken_->Close();
		//No entries were found for your request
		Windows::Forms::MessageBox::Show("Es wurden keine Einträge zu ihrer Anfrage gefunden.","Ungültige Suche");		
		Close();
	}
	//Windows::Forms::MessageBox::Show(Convert::ToString(bewilligungen->Count));
	List<String^>^ kostengruppen=gcnew List<String^>;
	List<String^>^ staedte=gcnew List<String^>;
	List<String^>^ gebiete=gcnew List<String^>;
	List<String^>^ programme=gcnew List<String^>;
	List<String^>^ jahre=gcnew List<String^>;

	for(int i=0;i<bewilligungen->Count;++i)
	{
		String^ stadt=bewilligungen[i][1];
		if(!is_existent_in(staedte,stadt))
			staedte->Add(stadt);
	}

	for(int stadt_index=0;stadt_index<staedte->Count;++stadt_index)
	{
		String^ stadt=staedte[stadt_index];

		gebiete->Clear();
		for(int i=0;i<bewilligungen->Count;++i)
		{
			String^ stadt_test=bewilligungen[i][1];
			String^ gebiet=bewilligungen[i][2];
			if(!is_existent_in(gebiete,gebiet) && stadt==stadt_test)
				gebiete->Add(gebiet);
		}

		for(int gebiet_index=0;gebiet_index<gebiete->Count;++gebiet_index)
		{
			String^ gebiet=gebiete[gebiet_index];

			kostengruppen->Clear();
			for(int i=0;i<bewilligungen->Count;++i)
			{
				String^ stadt_test=bewilligungen[i][1];
				String^ gebiet_test=bewilligungen[i][2];
				String^ kostengruppe=bewilligungen[i][0];
				if(!is_existent_in(kostengruppen,kostengruppe) && stadt==stadt_test && gebiet==gebiet_test)
					kostengruppen->Add(kostengruppe);
			}

			for(int kostengr_index=0;kostengr_index<kostengruppen->Count;++kostengr_index)
			{
				String^ kostengruppe=kostengruppen[kostengr_index];

				programme->Clear();
				for(int i=0;i<bewilligungen->Count;++i)
				{
					String^ stadt_test=bewilligungen[i][1];
					String^ gebiet_test=bewilligungen[i][2];
					String^ kostengruppe_test=bewilligungen[i][0];
					String^ programm=bewilligungen[i][3];
					if(!is_existent_in(programme,programm) && stadt==stadt_test && gebiet==gebiet_test && kostengruppe==kostengruppe_test)
						programme->Add(programm);
				}

				for(int programm_index=0;programm_index<programme->Count;++programm_index)
				{
					String^ programm=programme[programm_index];

					jahre->Clear();
					for(int i=0;i<bewilligungen->Count;++i)
					{
						String^ stadt_test=bewilligungen[i][1];
						String^ gebiet_test=bewilligungen[i][2];
						String^ kostengruppe_test=bewilligungen[i][0];
						String^ programm_test=bewilligungen[i][3];
						String^ jahr=bewilligungen[i][4];
						if(!is_existent_in(jahre,jahr) && stadt==stadt_test && gebiet==gebiet_test && kostengruppe==kostengruppe_test && programm==programm_test)
							jahre->Add(jahr);
					}
					sort_for_year(jahre);


					Decimal foerder_summe=0;
					Decimal mehr_minder_summe=0;
					Decimal mla_summe=0;
					Decimal bund_land_summe=0;

					int entry_count=0;
					//Windows::Forms::MessageBox::Show("reset");
					generate_header(kostengruppe,stadt,gebiet,programm);
					GenerateTableHeader();

					List< List<String^>^ >^ tmp=gcnew List< List<String^>^ >;

					for(int jahr_index=0;jahr_index<jahre->Count;++jahr_index)
					{
						String^ jahr=jahre[jahr_index];

						for(int bew_index=0;bew_index<bewilligungen->Count;++bew_index)
						{
							if(	bewilligungen[bew_index][0]== kostengruppe &&
								bewilligungen[bew_index][1]== stadt &&
								bewilligungen[bew_index][2]== gebiet &&
								bewilligungen[bew_index][3]== programm &&
								bewilligungen[bew_index][4]== jahr)
							{
								List<String^>^ tmp_small = gcnew List<String^>;

								String^ id=bewilligungen[bew_index][5];
								String^ bew_ztr=bewilligungen[bew_index][6];
								String^ bezeichnung=bewilligungen[bew_index][7];
								String^ vn_einger=bewilligungen[bew_index][8];
								String^ vn_gepr=bewilligungen[bew_index][9];
								String^ tb=bewilligungen[bew_index][10];
								String^ ZB_NR=bewilligungen[bew_index][11];
								String^ vom=bewilligungen[bew_index][12];
								Decimal mla=Decimal(Convert::ToDouble(bewilligungen[bew_index][13]));
								Decimal bund_land=Decimal(Convert::ToDouble(bewilligungen[bew_index][14]));
								Decimal foerderbetrag=Decimal(Convert::ToDouble(bewilligungen[bew_index][15]));
								Decimal mehr_minder=0;
								if(bewilligungen[bew_index][16]!="-")
									 mehr_minder=Decimal(Convert::ToDouble(bewilligungen[bew_index][16]));
								String^ mla_s=Decimal_to_string(mla);
								String^ bund_land_s=Decimal_to_string(bund_land);
								String^ foerderbetrag_s=Decimal_to_string(foerderbetrag);
								String^ mehr_minder_s=Decimal_to_string(mehr_minder);

								tmp_small->Add(id);
								tmp_small->Add(bew_ztr);
								tmp_small->Add(bezeichnung);
								tmp_small->Add(vn_einger);
								tmp_small->Add(vn_gepr);
								tmp_small->Add(tb);
								tmp_small->Add(ZB_NR);
								tmp_small->Add(vom);
								tmp_small->Add(mla_s);
								tmp_small->Add(bund_land_s);
								tmp_small->Add(foerderbetrag_s);
								tmp_small->Add(mehr_minder_s);
								tmp_small->Add(jahr);

								tmp->Add(tmp_small);

								//Windows::Forms::MessageBox::Show(Convert::ToString(tmp->Count));

								//bewilligungen->RemoveAt(bew_index);
								// Löscht zu viel .. wenn Zeit neu!

								foerder_summe+=foerderbetrag;
								mehr_minder_summe+=mehr_minder;
								mla_summe+=mla;
								bund_land_summe+=bund_land;
								
								ladebalken_->Controls->Find("progress",true)[0]->Text="a";
								ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
							}
						}
					}

					if(tmp->Count>1)
						sort_for_ZB_NR(tmp);

					for(int i=0;i<tmp->Count;++i)
					{
						String^ id=tmp[i][0];
						String^ bew_ztr=tmp[i][1];
						String^ bezeichnung=tmp[i][2];
						String^ vn_einger=tmp[i][3];
						String^ vn_gepr=tmp[i][4];
						String^ tb=tmp[i][5];
						String^ ZB_NR=tmp[i][6];
						String^ vom=tmp[i][7];
						String^ mla_s=tmp[i][8];
						String^ bund_land_s=tmp[i][9];
						String^ foerderbetrag_s=tmp[i][10];
						String^ mehr_minder_s=tmp[i][11];
						String^ jahr=tmp[i][12];

						generate_entry(id, jahr, bew_ztr, bezeichnung, vn_einger, vn_gepr, tb, ZB_NR, vom, mla_s, bund_land_s, foerderbetrag_s, mehr_minder_s,entry_count);
						entry_count++;
					}

					String^ foerder=Decimal_to_string(foerder_summe);
					String^ mla=Decimal_to_string(mla_summe);
					String^ bund_land=Decimal_to_string(bund_land_summe);
					String^ mehr_minder=Decimal_to_string(mehr_minder_summe);
					generate_footer(foerder,mla,bund_land,mehr_minder);
				}
			}
		}
	}

	place_print_button();	
	ladebalken_->Hide();
	Show();
}

void kostengr_uebersicht_result::sort_for_ZB_NR(List< List<String^>^ >^ input)
{
	for (int i=input->Count;i>1; --i)
	{
		for (int j=0; j<i-1; ++j)
		{
			String^ zb_nr1=input[j][6];
			zb_nr1=zb_nr1->Replace("/","")->Replace("-","")->Replace("X","9");
			String^ jahr1=zb_nr1->Substring(8);
			String^ nr1=zb_nr1->Substring(0, 8);
			String^ zb_nr2=input[j+1][6];
			zb_nr2=zb_nr2->Replace("/","")->Replace("-","")->Replace("X","9");
			String^ jahr2=zb_nr1->Substring(8);
			String^ nr2=zb_nr1->Substring(0, 8);

			//Windows::Forms::MessageBox::Show(jahr1+"\n"+rest1);
			//Windows::Forms::MessageBox::Show(jahr2+"\n"+rest2);

			if (year_is_bigger(jahr1,jahr2) || (jahr1==jahr2 && Convert::ToDouble(nr1)>Convert::ToDouble(nr2)) )
			{
				List<String^>^ tmp = input[j];
				input[j]=input[j+1];
				input[j+1]=tmp;
			}
		}
	}
}

bool kostengr_uebersicht_result::year_is_bigger(String^ j1, String^ j2)
{
	int jahr1 = Convert::ToInt32(j1);
	int jahr2 = Convert::ToInt32(j2);

	if(jahr1<16)
		jahr1+=50;
	if(jahr2<16)
		jahr2+=50;

	return jahr1>jahr2;
}

List< List<String^>^ >^ kostengr_uebersicht_result::load_bewilligungen()  //load approvals
{
	List< List<String^>^ >^ permits = gcnew List< List<String^>^ >;

	My_Connection data;
	data.connect();

	List<String^>^ years=gcnew List<String^>;
	if(year_=="-1")
	{
		MyResult^ R_year=data.get_result("SELECT * FROM Jahreseintraege order by ID");  //Annual entries
		for(int i=0;i<R_year->get_row();++i)
			years->Add(R_year->get_val(i,1));
		years->Add("SBE");
	}
	else
		years->Add(year_);
	
	List<String^>^ cityList = data.GetCityList(stadt_);	

	for(int stadt_param=0;stadt_param<cityList->Count;++stadt_param)
	{
		String^ stadt =cityList[stadt_param];
		
		List<String^>^ areaList=gcnew List<String^>;
		if(gebiet_=="-1")
		{
			MyResult^ Result_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
			MyResult^ Result=data.get_result("SELECT Gebiet FROM Gebiete WHERE Stadt_ID="+Result_Stadt->get_val(0,0));
			for(int i=0;i<Result->get_row();++i)
				areaList->Add(Result->get_val(i,0));
		}
		else
			areaList->Add(gebiet_);

		for(int gebiet_param=0;gebiet_param<areaList->Count;++gebiet_param)
		{
			String^ gebiet=areaList[gebiet_param];

			List<String^>^ costGroupList=gcnew List<String^>;
			if(kostengruppe_=="-1")
			{
				MyResult^ R_Kostengruppe=data.get_result("SELECT * FROM Kostengruppe");  //Cost group
				for(int i=0;i<R_Kostengruppe->get_row();++i)
					costGroupList->Add(R_Kostengruppe->get_val(i,1));
			}
			else
				costGroupList->Add(kostengruppe_);

			for(int kostengr_param=0;kostengr_param<costGroupList->Count;++kostengr_param)
			{
				String^ costGroup=costGroupList[kostengr_param];

				MyResult^ R_Projekte=data.get_result("SELECT * FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"' AND kostengruppe='"+costGroup+"'");
				for( int projekt_param=0;projekt_param<R_Projekte->get_row();++projekt_param)
				{
					// Stadt ( PROJ )
					// Gebiet ( PROJ )
					// Kostengruppe ( PROJ )
					String^ id=R_Projekte->get_val(projekt_param,0);			// ProjektID  ( PROJ )
					String^ bew_ztr=R_Projekte->get_val(projekt_param,7);		// Bew_Ztr ( PROJ )
					String^ bezeichnung=R_Projekte->get_val(projekt_param,5);	// Vorhaben ( PROJ )
					String^ vn_einger=R_Projekte->get_val(projekt_param,11);	// VN_einger ( PROJ )
					String^ vn_gepr=R_Projekte->get_val(projekt_param,12); 		// VN_Gepr ( PROJ )

					List<String^>^ programme=gcnew List<String^>;
					if(programm_=="-1")
					{
						MyResult^ Result_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
						MyResult^ Result_Gebiet=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+Result_Stadt->get_val(0,0)+" AND Gebiet='"+gebiet+"'");
						MyResult^ Result=data.get_result("SELECT * FROM Programme WHERE Gebiet_ID="+Result_Gebiet->get_val(0,0));
						for(int i=0;i<Result->get_row();++i)
							programme->Add(Result->get_val(i,2));
					}
					else
						programme->Add(programm_);

					MyResult^ R_Programme=data.get_result("SELECT * FROM db_programme WHERE projekt_ID="+id);
					for(int programm_param=0;programm_param<R_Programme->get_row();++programm_param)
					{
						// Programm ( PROG )
						String^ programm=R_Programme->get_val(programm_param,2);
						
						String^ programm_id=R_Programme->get_val(programm_param,0);
						if(is_existent_in(programme,programm))
						{
							MyResult^ R_Bewilligungen=data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID="+programm_id);
							for(int bew_param=0;bew_param<R_Bewilligungen->get_row();++bew_param)
							{
								String^ jahr=R_Bewilligungen->get_val(bew_param,4);	// Jahr ( BEW )
								String^ tb="-";
								if(R_Bewilligungen->get_row()!=1)
									tb=Convert::ToString(bew_param+1)+". TB";			// TB ( Programm )
								if(R_Bewilligungen->get_val(bew_param,10)=="1")
									jahr="SBE";
								if(is_existent_in(years,jahr))
								{
									String^ ZB_NR=	R_Bewilligungen->get_val(bew_param,2)+"-"+	// ZB_Nr ( BEW )
													R_Bewilligungen->get_val(bew_param,3)+"/"+
													R_Bewilligungen->get_val(bew_param,4);
									String^ vom=R_Bewilligungen->get_val(bew_param,5);			// vom ( BEW )
									
									String^ mla=R_Bewilligungen->get_val(bew_param,6);			// MLA ( BEW )
									String^ mla_vn=R_Bewilligungen->get_val(bew_param,7); 
									String^ bund_land=R_Bewilligungen->get_val(bew_param,8);	// Bund/Land ( BEW )
									String^ bund_land_vn=R_Bewilligungen->get_val(bew_param,9);
									String^ mehrminder="";										// MehrMinder ( BEW )

									if(vn_einger!="" && vn_gepr=="")
									{
										mehrminder=Convert::ToString(	(Convert::ToDouble(mla_vn)+Convert::ToDouble(bund_land_vn))-
																		(Convert::ToDouble(mla)+Convert::ToDouble(bund_land)));
										//mla=mla_vn;
										//bund_land=bund_land_vn;
									}
									else
									{
										mehrminder="-";
									}
									String^ foerderbetrag=	Convert::ToString					// Förderbetrag ( BEW )
															(Convert::ToDouble(bund_land)+Convert::ToDouble(mla));
									List<String^>^ cache = gcnew List<String^>;
									cache->Add(costGroup);
									cache->Add(stadt);
									cache->Add(gebiet);
									cache->Add(programm);
									cache->Add(jahr);
									cache->Add(id);
									cache->Add(bew_ztr);
									cache->Add(bezeichnung);
									cache->Add(vn_einger);
									cache->Add(vn_gepr);
									cache->Add(tb);
									cache->Add(ZB_NR);
									cache->Add(vom);
									cache->Add(mla);
									cache->Add(bund_land);
									cache->Add(foerderbetrag);
									cache->Add(mehrminder);

									permits->Add(cache);
									
									ladebalken_->Controls->Find("progress",true)[0]->Text="a";
									ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
								}
							}
						}
					}
				}
			}
		}
	}

	data.disconnect();

	return permits;
}

void kostengr_uebersicht_result::sort_for_year(List<String^>^ input)
{
	for(int i=input->Count;i>1;--i)
	{
		for (int j=0; j<i-1 ; ++j)
		{
			String^ jahr1=input[j];
			String^ jahr2=input[j+1];

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
				String^ cache=input[j];
				input[j]=input[j+1];
				input[j+1]=cache;
			}	
		}
	}
}

bool kostengr_uebersicht_result::is_existent_in(List<String^>^ liste,String^ value)
{
	for each(String^ eintrag in liste)
		if(eintrag==value)
			return true;
	return false;
}

// Auswertungselemente
void kostengr_uebersicht_result::generate_header(	String^ kostengruppe,
													String^ stadt,
													String^ gebiet,
													String^ programm)
{
	page_content_->Add(gcnew List< List<String^>^ >);
	List<String^>^ header=gcnew List<String^>;
	header->Add("header");
	header->Add(kostengruppe);
	header->Add(stadt);
	header->Add(gebiet);
	header->Add(programm);
	page_content_[page_content_->Count-1]->Add(header);

	AddHeaderCell("Kostengruppe  : " + kostengruppe, 5, 1 + start_);
	AddHeaderCell("Stadt         : " + stadt, 5, 1 * 13 + start_);
	AddHeaderCell("Gebiet       : " + gebiet, 5, 2 * 13 + 1 + start_);
	AddHeaderCell("Programm : " + programm, 5, 3 * 13 + 1 + start_);
	start = start_;
	AddHeaderDivider(936, 4 * 13 + 1);
	start_ += 4 * 13 + 10;	
}

void kostengr_uebersicht_result::GenerateTableHeader()
{
	// zb_nr
	row_++;
	col_ = 2;
	start = start_;
	AddTableHeaderCell("ZB-Nr.", s_zb_nr);	
	AddTableHeaderCell("Vorhaben", s_bezeichnung);
	SetLabelSize(110, 15);
	AddTableHeaderCell("TB", s_tb);
	AddTableHeaderCell("vom", s_vom);
	AddTableHeaderCell("Förderbetrag", s_foerder);
	SetLabelSize(85, 15);
	AddTableHeaderCell("Bund-/Landanteil", s_bund_land);
	SetLabelSize(85, 15);
	AddTableHeaderCell("MLA Gemeinde", s_mla);
	SetLabelSize(85, 15);
	AddTableHeaderCell("BWZ", s_bew_ztr);
	AddTableHeaderCell("VN eingereicht", s_einger);
	AddTableHeaderCell("VN geprüft", s_gepr);
	AddTableHeaderCell("Mehr-/Minderkosten", s_mehr_minder);

	sumStart = row_ + 1;
	
	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0,start_);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 15);
	ueberschrift_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(ueberschrift_back);

	start_+=20;
}

void kostengr_uebersicht_result::generate_entry(	String^ id,
													String^ jahr_t,
													String^ bew_ztr_t,
													String^ bezeichnung_t,
													String^ vn_einger_t,
													String^ vn_gepr_t,
													String^ tb_t,
													String^ ZB_NR_t,
													String^ vom_t,
													String^ mla_t,
													String^ bund_land_t,
													String^ foerderbetrag_t,
													String^ mehr_minder_t,
													int eintrag)
{
	List<String^>^ entry=gcnew List<String^>;
	entry->Add("eintrag");
	entry->Add(jahr_t);
	entry->Add(bew_ztr_t);
	entry->Add(bezeichnung_t);
	entry->Add(vn_einger_t);
	entry->Add(vn_gepr_t);
	entry->Add(tb_t);
	entry->Add(ZB_NR_t);
	entry->Add(vom_t);
	entry->Add(mla_t);
	entry->Add(bund_land_t);
	entry->Add(foerderbetrag_t);
	entry->Add(mehr_minder_t);
	page_content_[page_content_->Count-1]->Add(entry);

	System::Drawing::Color color;
	if(eintrag%2!=0)
	{
		color=System::Drawing::Color::Gainsboro;
	}
	else
	{
		color=System::Drawing::Color::White;
	}

	start = start_;
	int rowNum = eintrag;
	row_++;
	col_ = 1;

	AddCellC(jahr_t, s_jahr, rowNum, id);
	AddCellC(ZB_NR_t, s_zb_nr, rowNum, id);
	AddCellC(bezeichnung_t, s_bezeichnung, rowNum, id);

	label->MaximumSize = System::Drawing::Size(110, 0);
	heightCalc = label->Size.Height;
	
	AddCellC(tb_t, s_tb, rowNum, id);
	AddCellC(vom_t, s_vom, rowNum, id);
	AddCellC(foerderbetrag_t, s_foerder, rowNum, id,true);
	SetLabelSize(85, 15);
	AddCellC(bund_land_t, s_bund_land, rowNum, id,true);
	SetLabelSize(85, 15);
	AddCellC(mla_t, s_mla, rowNum, id,true);
	SetLabelSize(85, 15);
	AddCellC(bew_ztr_t, s_bew_ztr, rowNum, id);
	AddCellC(vn_einger_t, s_einger, rowNum, id);
	AddCellC(vn_gepr_t, s_gepr, rowNum, id);
	AddCellC(mehr_minder_t, s_mehr_minder, rowNum, id,true);
	SetLabelSize(85, 15);	

	AddLineBreak(color);
	label->Name = id;
	label->Click += gcnew System::EventHandler(this, &kostengr_uebersicht_result::Click);
}

void kostengr_uebersicht_result::generate_footer(	String^ foerderbetrag_s, 
													String^ mla_s, 
													String^ bund_land_s, 
													String^ mehr_minder_s)
{
	List<String^>^ footer=gcnew List<String^>;
	footer->Add("footer");
	footer->Add(foerderbetrag_s);
	footer->Add(mla_s);
	footer->Add(bund_land_s);
	footer->Add(mehr_minder_s);
	page_content_[page_content_->Count-1]->Add(footer);

	row_++;
	row_++;
	col_ = 6;
	start = start_;
	AddTableFooter(foerderbetrag_s, s_foerder,85, 15);
	AddTableFooter(bund_land_s, s_bund_land, 85, 15);
	AddTableFooter(mla_s, s_mla, 85, 15);
	col_ += 3;
	AddTableFooter(mehr_minder_s, s_mehr_minder, 85, 15);

	start_+=25;
	row_++;
}

void kostengr_uebersicht_result::place_print_button()
{
	start_=start_+10;

	btn_print->Location=System::Drawing::Point(5, start_);
	btn_print->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_print);
	start = start_;
	ResultForm::place_button();
}

// Events
void kostengr_uebersicht_result::Click(System::Object^  sender, System::EventArgs^  e)
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
		kostengr_uebersicht_result_Load(sender,e);
	}
}

void kostengr_uebersicht_result::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
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
		printDocument1->DocumentName="Kostengruppenübersicht";
		printDocument1->DefaultPageSettings->Margins->Top=25;
		printDocument1->DefaultPageSettings->Margins->Bottom=25;
		printDocument1->DefaultPageSettings->Margins->Right=25;
		printDocument1->DefaultPageSettings->Margins->Left=25;
		printDocument1->OriginAtMargins=true;
		printDocument1->Print();
	}
}

// Printer Stuff
void kostengr_uebersicht_result::printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e)
{
    e->Graphics->PageScale =0.95;
	int begin_at=0;
	int entry=0;
	int end=700;

	// Spalten Setzten
	p_s_jahr=10;
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
			break;
		}
		
		done_page_content_=i;

		if(page_content_[print_page_][i][0]=="header")
		{
			String^ kostengruppe=page_content_[print_page_][i][1];
			String^ stadt=page_content_[print_page_][i][2];
			String^ gebiet=page_content_[print_page_][i][3];
			String^ programm=page_content_[print_page_][i][4];
			create_page_header(e,kostengruppe,stadt,gebiet,programm);
			begin_at+=80;
		}

		if(page_content_[print_page_][i][0]=="eintrag")
		{
			String^ jahr=page_content_[print_page_][i][1];
			String^ bew_ztr=page_content_[print_page_][i][2];
			String^ bezeichnung=page_content_[print_page_][i][3];
			String^ vn_einger=page_content_[print_page_][i][4];
			String^ vn_gepr=page_content_[print_page_][i][5];
			String^ tb=page_content_[print_page_][i][6];
			String^ ZB_NR=page_content_[print_page_][i][7];
			String^ vom=page_content_[print_page_][i][8];
			String^ mla=page_content_[print_page_][i][9];
			String^ bund_land=page_content_[print_page_][i][10];
			String^ foerderbetrag=page_content_[print_page_][i][11];
			String^ mehr_minder=page_content_[print_page_][i][12];
			create_page_entry(e,jahr,bew_ztr,bezeichnung,vn_einger,vn_gepr,tb,ZB_NR,vom,mla,bund_land,foerderbetrag,mehr_minder,begin_at,entry);
			entry++;
			begin_at+=20;
		}

		if(page_content_[print_page_][i][0]=="footer")
		{
			begin_at+=10;
			String^ foerderbetrag=page_content_[print_page_][i][1]; 
			String^ mla=page_content_[print_page_][i][2];
			String^ bund_land=page_content_[print_page_][i][3];
			String^ mehr_minder=page_content_[print_page_][i][4];
			create_page_footer(e,foerderbetrag,mla,bund_land,mehr_minder,begin_at);
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


void kostengr_uebersicht_result::create_page_header(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ kostengruppe,
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

	// Header
	e->Graphics->DrawString("Kostengruppenübersicht von "+kostengruppe+" ("+programm+") in "+stadt+" ("+gebiet+")",header_format,Brushes::Black, 10, 10);
	
	// Date
	String^ date=Convert::ToString(DateTime::Today.Date);
	date=date->Substring(0,10);
	e->Graphics->DrawString(date,header_format,Brushes::Black, 1100, 10);

	// Ueberschrift
		// Data
	e->Graphics->DrawString("Jahr",ueberschrift_format,Brushes::Black, p_s_jahr, 55);
	e->Graphics->DrawString("BWZ",ueberschrift_format,Brushes::Black, p_s_bew_ztr, 55);
	e->Graphics->DrawString("Vorhaben",ueberschrift_format,Brushes::Black, p_s_bezeichnung, 55);
	e->Graphics->DrawString("VN eingereicht",ueberschrift_format,Brushes::Black, p_s_vn_einger, 55);
	e->Graphics->DrawString("VN geprüft",ueberschrift_format,Brushes::Black, p_s_vn_gepr, 55);
	e->Graphics->DrawString("TB",ueberschrift_format,Brushes::Black, p_s_tb, 55);
	e->Graphics->DrawString("ZB-Nr.",ueberschrift_format,Brushes::Black, p_s_ZB_NR, 55);
	e->Graphics->DrawString("vom",ueberschrift_format,Brushes::Black, p_s_vom, 55);

		// Beträge
	e->Graphics->DrawString("MLA Gemeinde",ueberschrift_format,Brushes::Black,RectangleF(p_s_mla, 55,100,20),allign);
	e->Graphics->DrawString("Bund-/Landanteil",ueberschrift_format,Brushes::Black,RectangleF(p_s_bund_land, 55,100,20),allign);
	e->Graphics->DrawString("Förderbetrag",ueberschrift_format,Brushes::Black,RectangleF(p_s_foerderbetrag, 55,100,20),allign);
	e->Graphics->DrawString("Mehr-/Minderkosten",ueberschrift_format,Brushes::Black,RectangleF(p_s_mehr_minder, 55,120,20),allign);
}

void kostengr_uebersicht_result::create_page_entry(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ jahr,
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
	if(bezeichnung->Length>25)
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
	e->Graphics->DrawString(jahr,format,Brushes::Black, p_s_jahr, begin_at);
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

void kostengr_uebersicht_result::create_page_footer(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ foerderbetrag,
													String^ mla,
													String^ bund_land, 
													String^ mehr_minder,
													int begin_at)
{
	// Fonds
	System::Drawing::Font^ summen_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ label_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	
	//Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, p_s_foerderbetrag-50, begin_at-4, 800, 19);

	// Label
	e->Graphics->DrawString("Summen : ",label_format,Brushes::Black,p_s_foerderbetrag-50,begin_at);

	// Summen
	// Beträge
	e->Graphics->DrawString(mla,summen_format,Brushes::Black,RectangleF(p_s_mla, begin_at,100,20),allign);
	e->Graphics->DrawString(bund_land,summen_format,Brushes::Black,RectangleF(p_s_bund_land, begin_at,100,20),allign);
	e->Graphics->DrawString(foerderbetrag,summen_format,Brushes::Black,RectangleF(p_s_foerderbetrag, begin_at,100,20),allign);
	e->Graphics->DrawString(mehr_minder,summen_format,Brushes::Black,RectangleF(p_s_mehr_minder, begin_at,100,20),allign);
}

void kostengr_uebersicht_result::create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e)
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

void kostengr_uebersicht_result::AddCellC(String^ text, int xPos, int row, String^ name)
{
	AddCellC(text, xPos, row, name, false);
}

void kostengr_uebersicht_result::AddCellC(String^ text, int xPos, int row, String^ name, bool isDecimal)
{
	AddCell(text, xPos, row, isDecimal);
	label->Name = name;
	label->Click += gcnew System::EventHandler(this, &kostengr_uebersicht_result::Click);
}