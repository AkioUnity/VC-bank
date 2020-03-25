#pragma once

#include "test.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für kostengr_uebersicht_result
	/// </summary>
	public ref class kostengr_uebersicht_result : public System::Windows::Forms::Form
	{
	public:
		kostengr_uebersicht_result(void)
		{
			InitializeComponent();
		}

		kostengr_uebersicht_result(String^ kostengruppe ,String^ stadt ,String^ gebiet, String^ programm , String^ jahr, int user_id):
			user_id_(user_id),
			kostengruppe_(kostengruppe),
			stadt_(stadt),
			gebiet_(gebiet),
			programm_(programm),
			year_(jahr),
			start_(0),
			s_jahr(10),
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
			// Printer Stuff
			pages_(0),
			print_page_(0),
			page_content_(gcnew List< List< List<String^>^ >^ >),
			p_s_jahr(0),
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

			ladebalken_(gcnew test())
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~kostengr_uebersicht_result()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>

		Form^ ladebalken_;

		int user_id_;
		String^	kostengruppe_;
		String^	stadt_;
		String^	gebiet_;
		String^	programm_;
		String^	year_;

		int start_;
		int s_jahr;
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

		// Print Stuff
		int pages_;
		int print_page_;
		List< List< List<String^>^ >^ >^ page_content_;

		// Print Spalten
		int p_s_jahr;
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
		int done_page_content_;

	private: System::Drawing::Printing::PrintDocument^  printDocument1;
	private: System::Windows::Forms::Button^  btn_print;




#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(kostengr_uebersicht_result::typeid));
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->SuspendLayout();
			// 
			// btn_print
			// 
			this->btn_print->Location = System::Drawing::Point(3, 268);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(808, 20);
			this->btn_print->TabIndex = 1;
			this->btn_print->Text = L"Drucken";
			this->btn_print->UseVisualStyleBackColor = true;
			this->btn_print->Click += gcnew System::EventHandler(this, &kostengr_uebersicht_result::btn_print_Click);
			// 
			// printDocument1
			// 
			this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &kostengr_uebersicht_result::printDocument1_PrintPage);
			// 
			// kostengr_uebersicht_result
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(964, 572);
			this->Controls->Add(this->btn_print);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1000, 600);
			this->Name = L"kostengr_uebersicht_result";
			this->Padding = System::Windows::Forms::Padding(0, 0, 14, 0);
			this->Text = L"Übersicht Kostengruppen";
			this->Load += gcnew System::EventHandler(this, &kostengr_uebersicht_result::kostengr_uebersicht_result_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 

		// Loader
		void kostengr_uebersicht_result_Load(System::Object^  sender, System::EventArgs^  e);
		List< List<String^>^ >^ load_bewilligungen();
		bool is_existent_in(List<String^>^,String^);
		void sort_for_year(List<String^>^);
		void sort_for_ZB_NR(List< List<String^>^ >^);
		bool year_is_bigger(String^, String^);

		// Auswertungselemente
		void generate_header(String^,String^,String^,String^);
		void generate_ueberschriften();
		void generate_entry(String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,int);
		void generate_footer(String^,String^,String^,String^);
		void place_print_button();

		// Events
		void Click(System::Object^  sender, System::EventArgs^  e);
		void btn_print_Click(System::Object^  sender, System::EventArgs^  e);

		// PrintStuff
		void printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e);		
		void create_page_header(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^);
		void create_page_entry(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,String^,int,int);
		void create_page_footer(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^,int);
		void create_page_sign(System::Drawing::Printing::PrintPageEventArgs^);
};
}
