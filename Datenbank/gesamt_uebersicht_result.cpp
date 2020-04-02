#include "StdAfx.h"

#include "My_Connection.h"
#include "MyResult.h"
#include "MyRecordSet.h"
#include "bewilligung_result_form.h"
#include "choose_printer.h"
#include "helper.h"

#include "gesamt_uebersicht_result.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;

// Loader       total_overview_result
void gesamt_uebersicht_result::gesamt_uebersicht_result_Load(System::Object^  sender, System::EventArgs^  e)
{
	//Windows::Forms::MessageBox::Show("t1");
	ladebalken_->Show();
	Hide();
	ladebalken_->Controls->Find("texter",true)[0]->Text="Lade Daten aus Datenbank";
	start_=0;
	load_from_DB();

	if(bewilligung_liste->Count==0)
	{
		ladebalken_->Close();
		Windows::Forms::MessageBox::Show("Es wurden keine Einträge zu ihrer Anfrage gefunden.","Ungültige Suche");
		Close();
	}
	ladebalken_->Controls->Find("texter",true)[0]->Text="Verarbeite Daten";
	sort_lists();
	ladebalken_->Controls->Find("texter",true)[0]->Text="Erzeuge Formular";
	create();

	place_print_button();
	ladebalken_->Hide();
	Show();
}

void gesamt_uebersicht_result::load_from_DB()
{
	bewilligung_liste->Clear();

	My_Connection data;
	data.connect();
	
	this->Controls->Clear();

	List<String^>^ yearList = gcnew List<String^>;
	MyResult^ R_Jahr=data.get_result("SELECT * FROM Jahreseintraege order by ID");
	for(int i=0;i<R_Jahr->get_row();++i)
		yearList->Add(R_Jahr->get_val(i,1));

	List<String^>^ cityList = data.GetCityList(stadt_);	

	for(int stadt_param=0;stadt_param<cityList->Count;++stadt_param)
	{
		String^ stadt =cityList[stadt_param];

		List<String^>^ areaList = gcnew List<String^>;
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

			List<String^>^ Programm_liste=gcnew List<String^>;
			if(programm_=="-1")
			{
				MyResult^ Result_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
				MyResult^ Result_Gebiet=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+Result_Stadt->get_val(0,0)+" AND Gebiet='"+gebiet+"'");
				MyResult^ Result=data.get_result("SELECT * FROM Programme WHERE Gebiet_ID="+Result_Gebiet->get_val(0,0));
				for(int i=0;i<Result->get_row();++i)
					Programm_liste->Add(Result->get_val(i,2));
			}
			else
				Programm_liste->Add(programm_);
			
			List<String^>^ Projekt_liste=gcnew List<String^>;
			List<bool>^ db_project_list=gcnew List<bool>;

			MyResult^ Result_Projekt=data.get_result("SELECT ID,vn_einger,vn_gepr FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"'");
			for(int projekt_param=0;projekt_param<Result_Projekt->get_row();++projekt_param)
			{
				Projekt_liste->Add(Result_Projekt->get_val(projekt_param,0));
				db_project_list->Add(Result_Projekt->get_val(projekt_param,1)!="" && Result_Projekt->get_val(projekt_param,2)=="");
			}

			for(int programm_param=0;programm_param<Programm_liste->Count;++programm_param)
			{	
				for(int jahres_param=0;jahres_param<yearList->Count;++jahres_param)
				{
					for(int projekt_id_param=0;projekt_id_param<Projekt_liste->Count;++projekt_id_param)
					{
						MyResult^ Result_Programm=data.get_result("SELECT ID FROM db_programme WHERE projekt_ID="+Projekt_liste[projekt_id_param]+" AND name='"+Programm_liste[programm_param]+"'");

						for(int projekt_programm_param=0;projekt_programm_param<Result_Programm->get_row();++projekt_programm_param)
						{
							MyResult^ Result_Bewilligung=data.get_result("SELECT * FROM db_programme_bewilligung WHERE "+
														"programm_ID="+Result_Programm->get_val(projekt_programm_param,0)+" AND "+
														"nr3='"+yearList[jahres_param]+"'");

							for(int bew_param=0;bew_param<Result_Bewilligung->get_row();++bew_param)
							{
								String^ jahr="";
								if(Result_Bewilligung->get_val(bew_param,10)!="1")
									jahr=Result_Bewilligung->get_val(bew_param,4);
								else
									jahr="SBE";

								String^ mla=Result_Bewilligung->get_val(bew_param,6);
								String^ mla_vn=Result_Bewilligung->get_val(bew_param,7);
								String^ bund_land=Result_Bewilligung->get_val(bew_param,8);
								String^ bund_land_vn=Result_Bewilligung->get_val(bew_param,9);

								String^ mehr_minder="";

								if(!db_project_list[projekt_id_param]) // kein mehr/minder
									mehr_minder="0";
								else
									mehr_minder="1";
								
								List<String^>^ bewilligung = gcnew List<String^>;
								bewilligung->Add(stadt);
								bewilligung->Add(gebiet);
								bewilligung->Add(Programm_liste[programm_param]);
								bewilligung->Add(jahr);
								bewilligung->Add(mla);
								bewilligung->Add(mla_vn);
								bewilligung->Add(bund_land);
								bewilligung->Add(bund_land_vn);
								bewilligung->Add(mehr_minder);
								bewilligung_liste->Add(bewilligung);
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
	/*
	bewilligung_liste
	[0] Stadt
	[1] Gebiet
	[2] Programm
	[3] Jahr
	[4] MLA
	[5] MLA VN
	[6] Bund Land
	[7] Bund Land VN
	[8] Mehr Minder ( 0 : nicht berechnen; 1 : berechnen )
	*/
}

void gesamt_uebersicht_result::sort_lists()
{
	staedte_->Clear();
	result_liste_->Clear();

	My_Connection data;
	data.connect();

	if(stadt_=="-1")
	{
		MyResult^ Result=data.get_result("SELECT * FROM Staedte");
		for(int i=0;i<Result->get_row();++i)
			staedte_->Add(Result->get_val(i,1));
	}
	else
		staedte_->Add(stadt_);

	staedte_->Sort();

	for(int stadt_param=0;stadt_param<staedte_->Count;++stadt_param)
	{
		String^ stadt =staedte_[stadt_param];		
		gebiete_->Clear();

		if(gebiet_=="-1")
		{
			MyResult^ Result_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
			MyResult^ Result=data.get_result("SELECT Gebiet FROM Gebiete WHERE Stadt_ID="+Result_Stadt->get_val(0,0));
			for(int i=0;i<Result->get_row();++i)
				gebiete_->Add(Result->get_val(i,0));
		}
		else
			gebiete_->Add(gebiet_);

		gebiete_->Sort();

		for(int gebiet_param=0;gebiet_param<gebiete_->Count;++gebiet_param)
		{
			String^ gebiet=gebiete_[gebiet_param];
						
			programme_->Clear();
			if(programm_=="-1")
			{
				MyResult^ Result_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
				MyResult^ Result_Gebiet=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+Result_Stadt->get_val(0,0)+" AND Gebiet='"+gebiet+"'");
				MyResult^ Result=data.get_result("SELECT * FROM Programme WHERE Gebiet_ID="+Result_Gebiet->get_val(0,0));
				for(int i=0;i<Result->get_row();++i)
					programme_->Add(Result->get_val(i,2));
			}
			else
				programme_->Add(programm_);

			programme_->Sort();

			for(int prog_param=0;prog_param<programme_->Count;++prog_param)
			{
				List< List<String^>^ >^ cache = gcnew List< List<String^>^ >;

				String^ programm=programme_[prog_param];

				for(int list_param=0;list_param<bewilligung_liste->Count;++list_param)
				{
					if(bewilligung_liste[list_param][0]==stadt && bewilligung_liste[list_param][1]==gebiet && bewilligung_liste[list_param][2]==programm )
					{
						List<String^>^ bewilligung= gcnew List<String^>;
						bewilligung->Add(bewilligung_liste[list_param][3]);
						bewilligung->Add(bewilligung_liste[list_param][4]);
						bewilligung->Add(bewilligung_liste[list_param][5]);
						bewilligung->Add(bewilligung_liste[list_param][6]);
						bewilligung->Add(bewilligung_liste[list_param][7]);
						bewilligung->Add(bewilligung_liste[list_param][8]);

						cache->Add(bewilligung);
					}
				}
			
				result_liste_->Add(get_informations(cache,stadt,gebiet,programm));

				ladebalken_->Controls->Find("progress",true)[0]->Text="a";
				ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
			}
		}
	}
	data.disconnect();
}

List< List<String^>^ >^ gesamt_uebersicht_result::get_informations(	List< List<String^>^ >^ input,String^ stadt, 
																	String^ gebiet, 
																	String^ programm)
{
	/*
	input[gefundene bewilligungen] :
	[0] Jahr
	[1] MLA
	[2] MLA VN
	[3] Bund Land
	[4] Bund Land VN
	[5] Mehr Minder ( 0 : nicht berechnen; 1 : berechnen )
	*/
	My_Connection data;
	data.connect();
	List<String^>^ jahre = gcnew List<String^>;
	MyResult^ R_Jahr=data.get_result("SELECT * FROM Jahreseintraege order by ID");
	for(int i=0;i<R_Jahr->get_row();++i)
		jahre->Add(R_Jahr->get_val(i,1));
	jahre->Add("SBE");
	data.disconnect();

	sort_for_year(jahre);

	List<Decimal>^ gk_real_list=get_gk_real(stadt,gebiet,programm,jahre);
	List<Decimal>^ gk_kom_list=get_gk_kom(stadt,gebiet,programm,jahre);
	List<Decimal>^ gk_priv_list=get_gk_priv(stadt,gebiet,programm,jahre);

	List< List<String^>^ >^ informations = gcnew List< List<String^>^ >;
	for(int jahres_param=0;jahres_param<jahre->Count;++jahres_param)
	{
		Decimal mehr_minder=0;
		Decimal bund_land=0;
		Decimal bund_land_vn=0;
		Decimal mla=0;
		Decimal mla_vn=0;
		Decimal gesamt=0;

		for(int input_param=0;input_param<input->Count;++input_param)
		{
			if(input[input_param][0]==jahre[jahres_param])
			{
				mla+=Decimal(Convert::ToDouble(input[input_param][1]));
				mla_vn+=Decimal(Convert::ToDouble(input[input_param][2]));
				bund_land+=Decimal(Convert::ToDouble(input[input_param][3]));
				bund_land_vn+=Decimal(Convert::ToDouble(input[input_param][4]));
				
				if(input[input_param][5] == "1")
					mehr_minder+=(Decimal(Convert::ToDouble(input[input_param][2]))+Decimal(Convert::ToDouble(input[input_param][4])))-(Decimal(Convert::ToDouble(input[input_param][1]))+Decimal(Convert::ToDouble(input[input_param][3])));
			}
		}
		Decimal jahreshaushalt=get_haushalt(jahre[jahres_param],stadt,gebiet,programm);
		Decimal restmittel = jahreshaushalt - (mla+bund_land);
		Decimal reale_gk = gk_real_list[jahres_param];
		Decimal gk_kom = gk_kom_list[jahres_param];
		Decimal gk_priv = gk_priv_list[jahres_param];

		List<String^>^ cache = gcnew List<String^>;
		
		cache->Add(stadt);
		cache->Add(gebiet);
		cache->Add(programm);
		cache->Add(jahre[jahres_param]);
		cache->Add(Convert::ToString(jahreshaushalt));
		cache->Add(Convert::ToString(bund_land));
		cache->Add(Convert::ToString(mla));
		cache->Add(Convert::ToString(restmittel));
		cache->Add(Convert::ToString(mehr_minder));
		cache->Add(Convert::ToString(reale_gk));  //9
		cache->Add(Convert::ToString(gk_kom));  //10
		cache->Add(Convert::ToString(gk_priv));  //11

		/*
		cache :
		[0] Stadt
		[1] Gebiet
		[2] Programm
		[3] Jahr
		[4] Jahreshaushalt
		[5] Bund Land
		[6] MLA
		[7] Restmittel
		[8] Mehr Minder
		[9] Reale GK
		[10] GK Gemeinde
		[11] GK Privat
		*/ 

		informations->Add(cache);
	}

	List<String^>^ cache;
	if(informations[informations->Count-1][3]=="SBE")
	{
		cache=informations[informations->Count-1];
		informations->RemoveAt(informations->Count-1);
	}

	int first=-1;
	int last=-1;
	for(int i=0;i<informations->Count;++i)
	{
		bool empty=false;

		if(	informations[i][4]=="0" &&
			informations[i][5]=="0" &&
			informations[i][6]=="0" &&
			informations[i][7]=="0" &&
			informations[i][8]=="0" &&
			informations[i][9]=="0" &&
			informations[i][10]=="0" &&
			informations[i][11]=="0" )
			empty=true;

		if(!empty && first==-1)
			first=i;

		if(!empty )
			last=i;
	}

	// Cut last not filled rows
	for(int i=informations->Count-1;i>last;--i)
		informations->RemoveAt(i);
	
	// Cut first not filled rows
	for(int i=first-1;i>=0;--i)
		informations->RemoveAt(i);

	if(	cache[4]!="0" ||
		cache[5]!="0" ||
		cache[6]!="0" ||
		cache[7]!="0" ||
		cache[8]!="0" ||
		cache[9]!="0" ||
		cache[10]!="0" ||
		cache[11]!="0" )
		informations->Add(cache);

	return informations;
}

Decimal gesamt_uebersicht_result::get_haushalt(	String^ jahr,
												String^ stadt,
												String^ gebiet,
												String^ programm)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Stadt=data.get_result("SELECT ID FROM Staedte WHERE Stadt='"+stadt+"'");
	MyResult^ R_Gebiet=data.get_result("SELECT ID FROM Gebiete WHERE Stadt_ID="+R_Stadt->get_val(0,0)+" AND Gebiet='"+gebiet+"'");
	MyResult^ R_Programm=data.get_result("SELECT ID FROM Programme WHERE Gebiet_ID="+R_Gebiet->get_val(0,0)+" AND Programm='"+programm+"'");
	MyResult^ R_Jahre=data.get_result("SELECT betrag FROM jahreshaushalt WHERE programm_ID="+R_Programm->get_val(0,0)+" AND jahr='"+jahr+"'");
	data.disconnect();

	Decimal summe=0;
	for(int i=0;i<R_Jahre->get_row();++i)
		summe+=Decimal(Convert::ToDouble(R_Jahre->get_val(i,0)));

	return summe;
}

List<Decimal>^ gesamt_uebersicht_result::get_gk_real(String^ stadt,String^ gebiet,String^ programm,List<String^>^ jahre)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Proj=data.get_result("SELECT * FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"'");

	List<Decimal>^ summen=gcnew List<Decimal>;
	for(int i=0;i<jahre->Count;++i)
		summen->Add(0);

	for(int i=0;i<R_Proj->get_row();++i)
	{
		Decimal gk=Decimal(Convert::ToDouble(R_Proj->get_val(i,1)));
		String^ projekt_id=R_Proj->get_val(i,0);

		MyResult^ R_Prog=data.get_result("SELECT * FROM db_programme WHERE Projekt_ID="+projekt_id+" AND name='"+programm+"'");
		if(R_Prog->get_row()!=0)
		{
			String^ programm_id=R_Prog->get_val(0,0);
			MyResult^ R_Bew=data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID="+programm_id);

			if(R_Bew->get_row()!=0)
			{
				String^ jahr=R_Bew->get_val(0,4);
				if(R_Bew->get_val(0,10)=="1")
					jahr="SBE";
				int index=jahre->IndexOf(jahr);
				if(index!=-1)
					summen[index]+=gk;
			}
		}
	}
	data.disconnect();

	return summen;
}

List<Decimal>^ gesamt_uebersicht_result::get_gk_kom(String^ stadt,String^ gebiet,String^ programm,List<String^>^ jahre)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Proj=data.get_result("SELECT * FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"' AND sk_bha='Gemeinde'");    //local community

	List<Decimal>^ summen=gcnew List<Decimal>;
	for(int i=0;i<jahre->Count;++i)
		summen->Add(0);

	for(int i=0;i<R_Proj->get_row();++i)
	{
		Decimal gk=Decimal(Convert::ToDouble(R_Proj->get_val(i,1)));
		String^ projekt_id=R_Proj->get_val(i,0);

		MyResult^ R_Prog=data.get_result("SELECT * FROM db_programme WHERE Projekt_ID="+projekt_id+" AND name='"+programm+"'");
		if(R_Prog->get_row()!=0)
		{
			String^ programm_id=R_Prog->get_val(0,0);
			MyResult^ R_Bew=data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID="+programm_id);

			if(R_Bew->get_row()!=0)
			{
				String^ jahr=R_Bew->get_val(0,4);
				if(R_Bew->get_val(0,10)=="1")
					jahr="SBE";
				int index=jahre->IndexOf(jahr);
				if(index!=-1)
					summen[index]+=gk;
			}
		}
	}
	data.disconnect();

	return summen;
}

List<Decimal>^ gesamt_uebersicht_result::get_gk_priv(String^ stadt,String^ gebiet,String^ programm,List<String^>^ jahre)
{
	My_Connection data;
	data.connect();
	MyResult^ R_Proj=data.get_result("SELECT * FROM db_projekte WHERE stadt='"+stadt+"' AND gebiet='"+gebiet+"' AND sk_bha='Privat'");

	List<Decimal>^ summen=gcnew List<Decimal>;
	for(int i=0;i<jahre->Count;++i)
		summen->Add(0);

	for(int i=0;i<R_Proj->get_row();++i)
	{
		Decimal gk=Decimal(Convert::ToDouble(R_Proj->get_val(i,1)));
		String^ projekt_id=R_Proj->get_val(i,0);

		MyResult^ R_Prog=data.get_result("SELECT * FROM db_programme WHERE Projekt_ID="+projekt_id+" AND name='"+programm+"'");
		if(R_Prog->get_row()!=0)
		{
			String^ programm_id=R_Prog->get_val(0,0);
			MyResult^ R_Bew=data.get_result("SELECT * FROM db_programme_bewilligung WHERE programm_ID="+programm_id);

			if(R_Bew->get_row()!=0)
			{
				String^ jahr=R_Bew->get_val(0,4);
				if(R_Bew->get_val(0,10)=="1")
					jahr="SBE";
				int index=jahre->IndexOf(jahr);
				if(index!=-1)
					summen[index]+=gk;
			}
		}
	}
	data.disconnect();

	return summen;
}

bool gesamt_uebersicht_result::is_existent_in(	List<String^>^ liste,
												String^ value)
{
	for each(String^ eintrag in liste)
		if(eintrag==value)
			return true;
	return false;
}

void gesamt_uebersicht_result::sort_for_year(List<String^>^ input)
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

void gesamt_uebersicht_result::create()
{
	calc_coloumns();
	for(int main_param=0;main_param<result_liste_->Count;++main_param)
	{
		if(result_liste_[main_param]->Count!=0)
		{
			String^ stadt=result_liste_[main_param][0][0];
			String^ gebiet=result_liste_[main_param][0][1];
			String^ programm=result_liste_[main_param][0][2];

			generate_header(stadt,gebiet,programm);

			/*
			result_liste[i][i] :
			[0] Stadt
			[1] Gebiet
			[2] Programm
			[3] Jahr
			[4] Jahreshaushalt
			[5] Bund Land
			[6] MLA
			[7] Restmittel
			[8] Mehr Minder
			[9] Reale GK
			[10] GK Gemeinde
			[11] GK Privat
			*/
			GenerateTableHeader();

			Decimal summe_haushalt=0;
			Decimal summe_bund_land=0;
			Decimal summe_mla=0;
			Decimal summe_restmittel=0;
			Decimal summe_mehrminder=0;
			Decimal summe_reale_gk=0;
			Decimal summe_kom_gk=0;
			Decimal summe_priv_gk=0;

			int count=0;
			for(int entry_param=0;entry_param<result_liste_[main_param]->Count;++entry_param)
			{
				String^ jahr=result_liste_[main_param][entry_param][3];
				Decimal haushalt=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][4]));
				Decimal bund_land=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][5]));
				Decimal mla=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][6]));
				Decimal restmittel=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][7]));
				Decimal mehr_minder=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][8]));
				Decimal gk_real=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][9]));
				Decimal gk_kom=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][10]));
				Decimal gk_priv=Decimal(Convert::ToDouble(result_liste_[main_param][entry_param][11]));

				if(/*haushalt+bund_land+mla+restmittel+mehr_minder+gk_real+gk_kom+gk_priv!=0 &&*/ jahr!="XX")
				{
					generate_entry(	count,
									stadt,
									gebiet,
									programm,
									jahr,
									Decimal_to_string(haushalt),
									Decimal_to_string(bund_land),
									Decimal_to_string(mla),
									Decimal_to_string(restmittel),
									Decimal_to_string(mehr_minder),
									Decimal_to_string(gk_real),
									Decimal_to_string(gk_kom),
									Decimal_to_string(gk_priv));

					summe_haushalt+=haushalt;
					summe_bund_land+=bund_land;
					summe_mla+=mla;
					summe_restmittel+=restmittel;
					summe_mehrminder+=mehr_minder;
					summe_reale_gk+=gk_real;
					summe_kom_gk+=gk_kom;
					summe_priv_gk+=gk_priv;
					++count;
				}
			}

			String^ haushalt=Decimal_to_string(summe_haushalt);
			String^ bund_land=Decimal_to_string(summe_bund_land);
			String^ mla=Decimal_to_string(summe_mla);
			String^ restmittel=Decimal_to_string(summe_restmittel);
			String^ mehr_minder=Decimal_to_string(summe_mehrminder);
			String^ gk_real=Decimal_to_string(summe_reale_gk);
			String^ gk_kom=Decimal_to_string(summe_kom_gk);
			String^ gk_priv=Decimal_to_string(summe_priv_gk);

			generate_footer(	haushalt,
								bund_land,
								mla,
								restmittel,
								mehr_minder,
								gk_real,
								gk_kom,
								gk_priv);

			ladebalken_->Controls->Find("progress",true)[0]->Text="a";
			ladebalken_->Controls->Find("progress",true)[0]->Text=" ";
		}
	}
}

// Auswertungselemente 
void gesamt_uebersicht_result::calc_coloumns()
{
	// gesamt 1000
	// jahr ca. 50
	// arbeitsfläche ca. 900 ( start bei 50 )
	int gesamt=890;
	int start=50;

	spalte_jh_=-1;
	spalte_bundland_=-1;
	spalte_mla_=-1;
	spalte_restmittel_=-1;
	spalte_mehr_minder_=-1;
	spalte_gk_real_=-1;
	spalte_gk_kom_=-1;
	spalte_gk_priv_=-1;
	spaltenbreite_=-1;

	// anzahl spalten
	int spalten_anzahl=0;

	if(show_jz_)
		++spalten_anzahl;
	if(show_bundland_)
		++spalten_anzahl;
	if(show_mla_)
		++spalten_anzahl;
	if(show_restmittel_)
		++spalten_anzahl;
	if(show_mehrminder_)
		++spalten_anzahl;
	if(show_gk_real_)
		++spalten_anzahl;
	if(show_gk_kom_)
		++spalten_anzahl;
	if(show_gk_priv_)
		++spalten_anzahl;

	int abstand=Convert::ToInt32(gesamt/spalten_anzahl);

	for(int i=0;i<spalten_anzahl;++i)
	{
		if(spalte_jh_==-1 && show_jz_)
		{
			spalte_jh_=i*abstand+start;
			continue;
		}
		if(spalte_bundland_==-1 && show_bundland_)
		{
			spalte_bundland_=i*abstand+start;
			continue;
		}
		if(spalte_mla_==-1 && show_mla_)
		{
			spalte_mla_=i*abstand+start;
			continue;
		}
		if(spalte_restmittel_==-1 && show_restmittel_)
		{
			spalte_restmittel_=i*abstand+start;
			continue;
		}
		if(spalte_mehr_minder_==-1 && show_mehrminder_)
		{
			spalte_mehr_minder_=i*abstand+start;
			continue;
		}
		if(spalte_gk_real_==-1 && show_gk_real_)
		{
			spalte_gk_real_=i*abstand+start;
			continue;
		}
		if(spalte_gk_kom_==-1 && show_gk_kom_)
		{
			spalte_gk_kom_=i*abstand+start;
			continue;
		}
		if(spalte_gk_priv_==-1 && show_gk_priv_)
		{
			spalte_gk_priv_=i*abstand+start;
			continue;
		}
	}
	spaltenbreite_=abstand-10;
}

void gesamt_uebersicht_result::generate_header(	String^ stadt, 
												String^ gebiet, 
												String^ programm)
{
	if(start_!=0)
		start_+=10;

	start = start_;
	AddHeaderCell("Stadt         : " + stadt, 5, 1 + start);
	AddHeaderCell("Gebiet       : " + gebiet, 5, 1 * 13 + 1 + start);
	AddHeaderCell("Programm : " + programm, 5, 2 * 13 + 1 + start);
	AddHeaderDivider(936, 3 * 13 + 1);
	start_ += 3 * 13 + 10;	
	start = start_;
}

void gesamt_uebersicht_result::GenerateTableHeader()
{
	row_++;
	col_ = 1;
	AddTableHeaderCell("Jahr", spalte_jahr_);	
	// Jahreshaushalt
	if(show_jz_)
	{
		AddTableHeaderCell("Jahreszuteilung", spalte_jh_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// BundLand
	if(show_bundland_)
	{
		AddTableHeaderCell("Bund/Land", spalte_bundland_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// MLA
	if(show_mla_)
	{
		AddTableHeaderCell("MLA", spalte_mla_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// Restmittel
	if(show_restmittel_)
	{
		AddTableHeaderCell("Restmittel", spalte_restmittel_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// Mehr-/Minderkosten
	if(show_mehrminder_)
	{
		AddTableHeaderCell("Mehr-/Minderkosten", spalte_mehr_minder_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// GK Real
	if(show_gk_real_)
	{
		AddTableHeaderCell("GK Real", spalte_gk_real_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// GK Kom
	if(show_gk_kom_)
	{
		AddTableHeaderCell("GK Komunal", spalte_gk_kom_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// GK Priv
	if(show_gk_priv_)
	{
		AddTableHeaderCell("GK Privat", spalte_gk_priv_);
		SetLabelSize(spaltenbreite_, 13);
	}

	// Hintergrund
	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0,start_);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 20);
	ueberschrift_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(ueberschrift_back);

	start_+=20;
}

void gesamt_uebersicht_result::generate_entry(	int eintrag,
												String^ stadt,
												String^ gebiet,
												String^ programm,
												String^ jahr_s,
												String^ haushalt_s,
												String^ bund_land_s,
												String^ mla_s,
												String^ restmittel_s,
												String^ mehr_minder_s,
												String^ gk_real_s,
												String^ gk_kom_s,
												String^ gk_priv_s)
{
	System::Drawing::Color color;
	if(eintrag%2!=0)
		color=System::Drawing::Color::Gainsboro;
	else
		color=System::Drawing::Color::White;

	String^ name=stadt+"\n"+gebiet+"\n"+programm+"\n"+jahr_s;
	
	
	int rowNum = eintrag;
	row_++;
	col_ = 1;

	start = start_ + 2;
	AddCellC(jahr_s, spalte_jahr_, rowNum, name);

	start = start_ + 3;
	// Jahreshaushalt
	if(show_jz_)
	{	
		AddCellC(haushalt_s, spalte_jh_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// BundLand
	if(show_bundland_)
	{
		AddCellC(bund_land_s, spalte_bundland_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// MLA
	if(show_mla_)
	{
		AddCellC(mla_s, spalte_mla_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// Restmittel
	if(show_restmittel_)
	{
		AddCellC(restmittel_s, spalte_restmittel_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// Mehr-/Minderkosten
	if(show_mehrminder_)
	{
		AddCellC(mehr_minder_s, spalte_mehr_minder_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// GK Real
	if(show_gk_real_)
	{
		AddCellC(gk_real_s, spalte_gk_real_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// GK Kom
	if(show_gk_kom_)
	{
		AddCellC(gk_kom_s, spalte_gk_kom_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// GK Priv
	if(show_gk_priv_)
	{
		AddCellC(gk_priv_s, spalte_gk_priv_, rowNum, name);
		SetLabelSize(spaltenbreite_, 13);
	}

	// Hintergrund
	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0,start_+1);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 16);
	ueberschrift_back->Name = name;
	ueberschrift_back->BackColor = color;
	ueberschrift_back->Click += gcnew System::EventHandler(this, &gesamt_uebersicht_result::Click);
	this->Controls->Add(ueberschrift_back);

	start_+=15;
}

void gesamt_uebersicht_result::generate_footer(	String^ haushalt_s,
												String^ bund_land_s,
												String^ mla_s,
												String^ restmittel_s,
												String^ mehr_minder_s,
												String^ gk_real_s,
												String^ gk_kom_s,
												String^ gk_priv_s)
{
	System::Drawing::Color color=System::Drawing::Color::Silver;

	start_+=1;

	row_++;
	col_ = 1;
	start = start_+2;
	AddTableFooter("Summen", spalte_jahr_, 20, 15);

	start = start_+3;
	// Jahreshaushalt
	if(show_jz_)
	{
		AddTableFooter(haushalt_s, spalte_jh_, spaltenbreite_, 13);
	}
	// BundLand
	if(show_bundland_)
	{
		AddTableFooter(bund_land_s, spalte_bundland_, spaltenbreite_, 13);
	}

	// MLA
	if(show_mla_)
	{
		AddTableFooter(mla_s, spalte_mla_, spaltenbreite_, 13);
	}

	// Restmittel
	if(show_restmittel_)
	{
		AddTableFooter(restmittel_s, spalte_restmittel_, spaltenbreite_, 13);		
	}

	// Mehr-/Minderkosten
	if(show_mehrminder_)
	{
		AddTableFooter(mehr_minder_s, spalte_mehr_minder_, spaltenbreite_, 13);		
	}

	// GK Real
	if(show_gk_real_)
	{
		AddTableFooter(gk_real_s, spalte_gk_real_, spaltenbreite_, 13);
	}

	// GK Kom
	if(show_gk_kom_)
	{
		AddTableFooter(gk_kom_s, spalte_gk_kom_, spaltenbreite_, 13);
	}

	// GK Priv
	if(show_gk_priv_)
	{
		AddTableFooter(gk_priv_s, spalte_gk_priv_, spaltenbreite_, 13);		
	}

	// Hintergrund
	System::Windows::Forms::Label^  ueberschrift_back = gcnew System::Windows::Forms::Label();
	ueberschrift_back->Location = System::Drawing::Point(0,start_);
	ueberschrift_back->AutoSize = false;
	ueberschrift_back->Size = System::Drawing::Size(936, 17);
	//ueberschrift_back->BackColor = color;
	this->Controls->Add(ueberschrift_back);

	start_+=15;
	row_++;
}

void gesamt_uebersicht_result::place_print_button()
{
	start_=start_+10;

	btn_print->Location=System::Drawing::Point(5, start_);
	btn_print->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_print);
	start = start_;
	ResultForm::place_button();
}

// Events
void gesamt_uebersicht_result::Click(System::Object^  sender, System::EventArgs^  e)
{
	int index=-1;
	for(int i=0;i<this->Controls->Count;++i)
		if(ReferenceEquals(this->Controls[i],sender))
		{
			index=i;
			break;
		}
	if(index!=-1)
	{
		List<String^>^ seperated_values=seperate_values(this->Controls[index]->Name);
		if(seperated_values->Count==4)
		{
			String^ stadt=seperated_values[0];
			String^ gebiet=seperated_values[1];
			String^ programm=seperated_values[2];
			String^ jahr="-1";
			String^ sbe="-1";
			if(seperated_values[3]!="SBE")
				jahr=seperated_values[3];
			else
				sbe="1";

			String^ message = "Wird die Jahresübersicht geöffnet, wird die Auswertung nach Schließen der Jahresübersicht neu geladen.\nFortfahren ?";
			String^ caption = "Soll die Jahresübersicht geöffnet werden?";
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;

			result = MessageBox::Show( this, message, caption, buttons );
			if ( result == ::DialogResult::Yes )
			{
				Form^ jahres_auswertung = gcnew bewilligung_result_form(stadt,gebiet,programm,jahr,sbe,user_id_);
				jahres_auswertung->ShowDialog();
				gesamt_uebersicht_result_Load(sender,e);
			}
		}
		else
			Windows::Forms::MessageBox::Show("Kein Eintrag gefunden.\nBitte Kontaktieren Sie den Administrator.","Fehler");
	}
	else
		Windows::Forms::MessageBox::Show("Kein Eintrag gefunden.\nBitte Kontaktieren Sie den Administrator.","Fehler");
}

List<String^>^ gesamt_uebersicht_result::seperate_values(String^ values)
{
	List<String^>^ seperated_values=gcnew List<String^>;
	String^ value="";
	for(int i=0;i<values->Length;++i)
	{
		if(values[i]!='\n')
			value+=values[i];
		else
		{
			seperated_values->Add(value);
			value="";
		}
	}
	seperated_values->Add(value);
	return seperated_values;
}

// Buttons
void gesamt_uebersicht_result::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::Label^  cache = gcnew System::Windows::Forms::Label();
	cache->Text="-1";
	Form^ choose_print =gcnew choose_printer(cache);
	choose_print->ShowDialog();
	if(cache->Text!="-1")
	{
		calc_print_coloumns();

		print_page_=0;
		pages_=result_liste_->Count;

		// Drucker selbst wählen!
		printDocument1->PrinterSettings->PrinterName=cache->Text;
		printDocument1->DefaultPageSettings->Landscape=true;
		printDocument1->DefaultPageSettings->Margins->Top=25;
		printDocument1->DefaultPageSettings->Margins->Bottom=25;
		printDocument1->DefaultPageSettings->Margins->Right=25;
		printDocument1->DefaultPageSettings->Margins->Left=25;
		printDocument1->OriginAtMargins=true;
		printDocument1->DocumentName="Gesamtübersicht";
		printDocument1->Print();
	}
}

// Printer Stuff
void gesamt_uebersicht_result::calc_print_coloumns()
{
	// gesamt ca. 1150
	// jahr ca. 50
	// arbeitsfläche ca. 1100 ( start bei 50 )
	int gesamt=1100;
	int start=50;

	p_s_jahr_=5;
	p_s_jh_=-1;
	p_s_bundland_=-1;
	p_s_mla_=-1;
	p_s_restmittel_=-1;
	p_s_mehr_minder_=-1;
	p_s_gk_real_=-1;
	p_s_gk_kom_=-1;
	p_s_gk_priv_=-1;
	p_s_breite_=-1;

	// anzahl spalten
	int spalten_anzahl=0;

	if(show_jz_)
		++spalten_anzahl;
	if(show_bundland_)
		++spalten_anzahl;
	if(show_mla_)
		++spalten_anzahl;
	if(show_restmittel_)
		++spalten_anzahl;
	if(show_mehrminder_)
		++spalten_anzahl;
	if(show_gk_real_)
		++spalten_anzahl;
	if(show_gk_kom_)
		++spalten_anzahl;
	if(show_gk_priv_)
		++spalten_anzahl;

	int abstand=Convert::ToInt32(gesamt/spalten_anzahl);

	for(int i=0;i<spalten_anzahl;++i)
	{
		if(p_s_jh_==-1 && show_jz_)
		{
			p_s_jh_=i*abstand+start;
			continue;
		}
		if(p_s_bundland_==-1 && show_bundland_)
		{
			p_s_bundland_=i*abstand+start;
			continue;
		}
		if(p_s_mla_==-1 && show_mla_)
		{
			p_s_mla_=i*abstand+start;
			continue;
		}
		if(p_s_restmittel_==-1 && show_restmittel_)
		{
			p_s_restmittel_=i*abstand+start;
			continue;
		}
		if(p_s_mehr_minder_==-1 && show_mehrminder_)
		{
			p_s_mehr_minder_=i*abstand+start;
			continue;
		}
		if(p_s_gk_real_==-1 && show_gk_real_)
		{
			p_s_gk_real_=i*abstand+start;
			continue;
		}
		if(p_s_gk_kom_==-1 && show_gk_kom_)
		{
			p_s_gk_kom_=i*abstand+start;
			continue;
		}
		if(p_s_gk_priv_==-1 && show_gk_priv_)
		{
			p_s_gk_priv_=i*abstand+start;
			continue;
		}
	}
	p_s_breite_=abstand-10;
}

void gesamt_uebersicht_result::printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e)
{
	e->Graphics->PageScale =0.95;

	int begin_at=0;

	if(result_liste_[print_page_]->Count!=0)
	{
		String^ stadt=result_liste_[print_page_][0][0];
		String^ gebiet=result_liste_[print_page_][0][1];
		String^ programm=result_liste_[print_page_][0][2];
		create_page_header(e,stadt,gebiet,programm);
		begin_at+=80;

		Decimal summe_haushalt=0;
		Decimal summe_bund_land=0;
		Decimal summe_mla=0;
		Decimal summe_restmittel=0;
		Decimal summe_mehrminder=0;
		Decimal summe_reale_gk=0;
		Decimal summe_kom_gk=0;
		Decimal summe_priv_gk=0;

		int count=0;
		for(int entry_param=0;entry_param<result_liste_[print_page_]->Count;++entry_param)
		{		
			String^ jahr=result_liste_[print_page_][entry_param][3];
			Decimal haushalt=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][4]));
			Decimal bund_land=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][5]));
			Decimal mla=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][6]));
			Decimal restmittel=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][7]));
			Decimal mehr_minder=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][8]));
			Decimal gk_real=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][9]));
			Decimal gk_kom=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][10]));
			Decimal gk_priv=Decimal(Convert::ToDouble(result_liste_[print_page_][entry_param][11]));

			if(haushalt+bund_land+mla+restmittel+mehr_minder+gk_real+gk_kom+gk_priv!=0 && jahr!="XX")
			{
				create_page_entry(	e,
									jahr,
									Decimal_to_string(haushalt),
									Decimal_to_string(bund_land),
									Decimal_to_string(mla),
									Decimal_to_string(restmittel),
									Decimal_to_string(mehr_minder),
									Decimal_to_string(gk_real),
									Decimal_to_string(gk_kom),
									Decimal_to_string(gk_priv),
									begin_at,
									count);

				begin_at+=20;

				summe_haushalt+=haushalt;
				summe_bund_land+=bund_land;
				summe_mla+=mla;
				summe_restmittel+=restmittel;
				summe_mehrminder+=mehr_minder;
				summe_reale_gk+=gk_real;
				summe_kom_gk+=gk_kom;
				summe_priv_gk+=gk_priv;
				++count;
			}
		}		
		begin_at+=10;

		String^ haushalt=Decimal_to_string(summe_haushalt);
		String^ bund_land=Decimal_to_string(summe_bund_land);
		String^ mla=Decimal_to_string(summe_mla);
		String^ restmittel=Decimal_to_string(summe_restmittel);
		String^ mehr_minder=Decimal_to_string(summe_mehrminder);
		String^ gk_real=Decimal_to_string(summe_reale_gk);
		String^ gk_kom=Decimal_to_string(summe_kom_gk);
		String^ gk_priv=Decimal_to_string(summe_priv_gk);

		create_page_footer(	e,
							haushalt,
							bund_land,
							mla,
							restmittel,
							mehr_minder,
							gk_real,
							gk_kom,
							gk_priv,
							begin_at);

		create_page_sign(e);
	}

	// Prepare Settings for next page NextSite
	print_page_++;
	e->HasMorePages=print_page_<pages_;
}


void gesamt_uebersicht_result::create_page_header(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ stadt,
													String^ gebiet,
													String^ programm)
{
	// Fonds
	System::Drawing::Font^ header_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ ueberschrift_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.2F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));

	// Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// HeaderBox
	e->Graphics->FillRectangle(Brushes::Silver, 0, 0, 1170, 33);

	// Date
	String^ date=Convert::ToString(DateTime::Today.Date);
	date=date->Substring(0,10);
	e->Graphics->DrawString(date,header_format,Brushes::Black, 1100, 10);

	// Header
	e->Graphics->DrawString("Gesamtübersicht von "+programm+" in "+stadt+" ("+gebiet+")",header_format,Brushes::Black, 10, 10);

	// Ueberschrift
	e->Graphics->DrawString("Jahr",ueberschrift_format,Brushes::Black, p_s_jahr_, 55);
	if(show_jz_)
		e->Graphics->DrawString("Jahreszuteilung",ueberschrift_format,Brushes::Black,RectangleF(p_s_jh_, 55,p_s_breite_,20),allign);
	if(show_bundland_)
		e->Graphics->DrawString("Bund/Land",ueberschrift_format,Brushes::Black,RectangleF(p_s_bundland_, 55,p_s_breite_,20),allign);
	if(show_mla_)		
		e->Graphics->DrawString("MLA",ueberschrift_format,Brushes::Black,RectangleF(p_s_mla_, 55,p_s_breite_,20),allign);
	if(show_restmittel_)		
		e->Graphics->DrawString("Restmittel",ueberschrift_format,Brushes::Black,RectangleF(p_s_restmittel_, 55,p_s_breite_,20),allign);
	if(show_mehrminder_)		
		e->Graphics->DrawString("Mehr-/Minderkosten",ueberschrift_format,Brushes::Black,RectangleF(p_s_mehr_minder_, 55,p_s_breite_,20),allign);
	if(show_gk_real_)		
		e->Graphics->DrawString("GK Real",ueberschrift_format,Brushes::Black,RectangleF(p_s_gk_real_, 55,p_s_breite_,20),allign);
	if(show_gk_kom_)		
		e->Graphics->DrawString("GK Kommunal",ueberschrift_format,Brushes::Black,RectangleF(p_s_gk_kom_, 55,p_s_breite_,20),allign);
	if(show_gk_priv_)		
		e->Graphics->DrawString("GK Privat",ueberschrift_format,Brushes::Black,RectangleF(p_s_gk_priv_, 55,p_s_breite_,20),allign);
}

void gesamt_uebersicht_result::create_page_entry(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ jahr,
													String^ haushalt,
													String^ bund_land,
													String^ mla,
													String^ restmittel,
													String^ mehr_minder,
													String^ gk_real,
													String^ gk_kom,
													String^ gk_priv,
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

	e->Graphics->DrawString(jahr,format,Brushes::Black, p_s_jahr_, begin_at);
	if(show_jz_)
		e->Graphics->DrawString(haushalt,format,Brushes::Black,RectangleF(p_s_jh_, begin_at,p_s_breite_,20),allign);
	if(show_bundland_)
		e->Graphics->DrawString(bund_land,format,Brushes::Black,RectangleF(p_s_bundland_, begin_at,p_s_breite_,20),allign);
	if(show_mla_)		
		e->Graphics->DrawString(mla,format,Brushes::Black,RectangleF(p_s_mla_, begin_at,p_s_breite_,20),allign);
	if(show_restmittel_)		
		e->Graphics->DrawString(restmittel,format,Brushes::Black,RectangleF(p_s_restmittel_, begin_at,p_s_breite_,20),allign);
	if(show_mehrminder_)		
		e->Graphics->DrawString(mehr_minder,format,Brushes::Black,RectangleF(p_s_mehr_minder_, begin_at,p_s_breite_,20),allign);
	if(show_gk_real_)		
		e->Graphics->DrawString(gk_real,format,Brushes::Black,RectangleF(p_s_gk_real_, begin_at,p_s_breite_,20),allign);
	if(show_gk_kom_)		
		e->Graphics->DrawString(gk_kom,format,Brushes::Black,RectangleF(p_s_gk_kom_, begin_at,p_s_breite_,20),allign);
	if(show_gk_priv_)		
		e->Graphics->DrawString(gk_priv,format,Brushes::Black,RectangleF(p_s_gk_priv_, begin_at,p_s_breite_,20),allign);
}

void gesamt_uebersicht_result::create_page_footer(	System::Drawing::Printing::PrintPageEventArgs^  e,
													String^ haushalt,
													String^ bund_land,
													String^ mla,
													String^ restmittel,
													String^ mehr_minder,
													String^ gk_real,
													String^ gk_kom,
													String^ gk_priv,
													int begin_at)
{
	// Fonds
	System::Drawing::Font^ summen_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	System::Drawing::Font^ label_format=gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0));
	
	//Allignments
	StringFormat^ allign = gcnew StringFormat();
	allign->Alignment = StringAlignment::Far;

	// BackgroundBox
	e->Graphics->FillRectangle(Brushes::Silver, 70, begin_at-4, 1100, 19);

	// Label
	e->Graphics->DrawString("Summen : ",label_format,Brushes::Black,p_s_jahr_,begin_at);

	// Summen
	if(show_jz_)
		e->Graphics->DrawString(haushalt,summen_format,Brushes::Black,RectangleF(p_s_jh_, begin_at,p_s_breite_,20),allign);
	if(show_bundland_)
		e->Graphics->DrawString(bund_land,summen_format,Brushes::Black,RectangleF(p_s_bundland_, begin_at,p_s_breite_,20),allign);
	if(show_mla_)		
		e->Graphics->DrawString(mla,summen_format,Brushes::Black,RectangleF(p_s_mla_, begin_at,p_s_breite_,20),allign);
	if(show_restmittel_)		
		e->Graphics->DrawString(restmittel,summen_format,Brushes::Black,RectangleF(p_s_restmittel_, begin_at,p_s_breite_,20),allign);
	if(show_mehrminder_)		
		e->Graphics->DrawString(mehr_minder,summen_format,Brushes::Black,RectangleF(p_s_mehr_minder_, begin_at,p_s_breite_,20),allign);
	if(show_gk_real_)		
		e->Graphics->DrawString(gk_real,summen_format,Brushes::Black,RectangleF(p_s_gk_real_, begin_at,p_s_breite_,20),allign);
	if(show_gk_kom_)		
		e->Graphics->DrawString(gk_kom,summen_format,Brushes::Black,RectangleF(p_s_gk_kom_, begin_at,p_s_breite_,20),allign);
	if(show_gk_priv_)		
		e->Graphics->DrawString(gk_priv,summen_format,Brushes::Black,RectangleF(p_s_gk_priv_, begin_at,p_s_breite_,20),allign);
}

void gesamt_uebersicht_result::create_page_sign(System::Drawing::Printing::PrintPageEventArgs^ e)
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

void gesamt_uebersicht_result::AddCellC(String^ text, int xPos, int row, String^ name)
{
	AddCell(text, xPos, row);
	label->Name = name;
	label->Click += gcnew System::EventHandler(this, &gesamt_uebersicht_result::Click);
}