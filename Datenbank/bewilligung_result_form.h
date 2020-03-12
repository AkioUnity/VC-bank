#pragma once

#include "test.h"
#include "ExcelExport.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Printing;

	/// <summary>
	/// Zusammenfassung für bewilligung_result_form
	/// </summary>
	public ref class bewilligung_result_form : public System::Windows::Forms::Form
	{
	public:
		bewilligung_result_form(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		bewilligung_result_form(String^ stadt,String^ gebiet, String^ programm, String^ jahr, String^ sbe,int user_id):
			user_id_(user_id),
			stadt_(stadt),
			gebiet_(gebiet),
			programm_(programm),
			jahr_(jahr),
			sbe_(sbe),
			jahreshaushalt_(-1),
			bewilligungen_werte_(gcnew List< List<String^>^ >),
			s_kostenart(5),
			s_zb_nr(50),
			s_bezeichnung(115),
			s_tb(230),
			s_vom(260),
			s_foerder(315),
			s_bund_land(405),
			s_mla(495),
			s_bew_ztr(605),
			s_einger(680),
			s_gepr(755),
			s_mehr_minder(830),
			start(0),
			// Printer Stuff
			pages_(0),
			print_page_(0),
			page_content_(gcnew List< List< List<String^>^ >^ >),
			p_s_kostengr(0),
			p_s_bew_ztr(0),
			p_s_bezeichnung(0),
			p_s_vn_einger(0),
			p_s_vn_gepr(0),
			p_s_tb(0),
			p_s_ZB_NR(0),
			p_s_vom(0),
			p_s_mla(0),
			p_s_bund_land(0),
			p_s_foerderbetrag(0),
			p_s_mehr_minder(0),
			done_page_content_(0),

			ladebalken_(gcnew test()),

			exl_(gcnew ExcelExport()),
			row_(1)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~bewilligung_result_form()
		{
			if (components)
			{
				delete components;
			}
		}

			Form^ ladebalken_;

			int user_id_;
			String^ stadt_;
			String^ gebiet_;
			String^ programm_;
			String^ jahr_;
			String^ sbe_;
			Decimal jahreshaushalt_;
			List< List<String^>^ >^ bewilligungen_werte_;

			int s_kostenart;
			int s_zb_nr;
			int s_bezeichnung;
			int s_tb;
			int s_vom;
			int s_foerder;
			int s_bund_land;
			int s_mla;
			int s_bew_ztr;
			int s_einger;
			int s_gepr;
			int s_mehr_minder;
			int start;


		// Print Stuff
		int pages_;
		int print_page_;
		List< List< List<String^>^ >^ >^ page_content_;
		int done_page_content_;

		// Print Spalten
		int p_s_kostengr;
		int p_s_bew_ztr;
		int p_s_bezeichnung;
		int p_s_vn_einger;
		int p_s_vn_gepr;
		int p_s_tb;
		int p_s_ZB_NR;
		int p_s_vom;
		int p_s_mla;
		int p_s_bund_land;
		int p_s_foerderbetrag;
		int p_s_mehr_minder;

		ExcelExport ^ exl_;
		int row_;

	private: System::Windows::Forms::Button^  btn_print;
	private: System::Drawing::Printing::PrintDocument^  printDocument1;
private: System::Windows::Forms::Button^  btn_exportExl;

	protected: 


	private: System::ComponentModel::IContainer^  components;

	protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(bewilligung_result_form::typeid));
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->btn_exportExl = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_print
			// 
			this->btn_print->Location = System::Drawing::Point(35, 48);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(808, 20);
			this->btn_print->TabIndex = 0;
			this->btn_print->Text = L"Drucken";
			this->btn_print->UseVisualStyleBackColor = true;
			this->btn_print->Click += gcnew System::EventHandler(this, &bewilligung_result_form::button1_Click);
			// 
			// printDocument1
			// 
			this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &bewilligung_result_form::printDocument1_PrintPage);
			// 
			// btn_exportExl
			// 
			this->btn_exportExl->ImageAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->btn_exportExl->Location = System::Drawing::Point(35, 85);
			this->btn_exportExl->Name = L"btn_exportExl";
			this->btn_exportExl->Size = System::Drawing::Size(808, 23);
			this->btn_exportExl->TabIndex = 4;
			this->btn_exportExl->Text = L"nach Exel exportieren";
			this->btn_exportExl->UseVisualStyleBackColor = true;
			this->btn_exportExl->Click += gcnew System::EventHandler(this, &bewilligung_result_form::btn_exportExl_Click);
			// 
			// bewilligung_result_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(984, 561);
			this->Controls->Add(this->btn_exportExl);
			this->Controls->Add(this->btn_print);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1000, 600);
			this->Name = L"bewilligung_result_form";
			this->Padding = System::Windows::Forms::Padding(0, 0, 14, 0);
			this->Text = L"Bewilligung Auswertung";
			this->Load += gcnew System::EventHandler(this, &bewilligung_result_form::bewilligung_result_form_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		// Loader
		void bewilligung_result_form_Load(System::Object^  sender, System::EventArgs^  e);
		void sort_bewilligung();
		bool is_existent_in(List<String^>^,String^);
		void sort_for_year(List<String^>^);
		void sort_for_ZB_NR(List< List<String^>^ >^ );
		int get_tb(String^ prog_id, String^ bew_id);

		// Auswertungselemente
		void generate_header(String^,String^,String^,String^);
		Decimal generate_haushalt(String^,String^,String^,String^);
		void generate_ueberschriften();
		void generate_bewilligung(List<String^>^,int);
		void generate_footer(Decimal,Decimal,Decimal,Decimal);		
		void place_button();

		// Events
		void button1_Click(System::Object^  sender, System::EventArgs^  e);
		void Click(System::Object^  sender, System::EventArgs^  e);
		void btn_exportExl_Click(System::Object^  sender, System::EventArgs^  e);

		// Printer Stuff
		void printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e);
		void create_page_header(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^);
		void create_page_jh_label(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,int);
		void create_page_jh_eintrag(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,int);
		void create_page_uberschriften(System::Drawing::Printing::PrintPageEventArgs^,int);
		void create_page_entry(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,int,int);
		void create_page_footer(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^,int);
		void create_page_sign(System::Drawing::Printing::PrintPageEventArgs^);

};
}
