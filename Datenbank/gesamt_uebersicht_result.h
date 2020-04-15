#pragma once

#include "test.h"
#include "ResultGk.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für gesamt_uebersicht_result  amg3.5
	/// </summary>
	public ref class gesamt_uebersicht_result : public ResultGk
	{
	public:
		gesamt_uebersicht_result(void)
		{
			InitializeComponent();
		}
		
		gesamt_uebersicht_result(	String^ stadt, 
									String^ gebiet, 
									String^ programm, 
									bool show_jz,
									bool show_bundland,
									bool show_mla,
									bool show_restmittel,
									bool show_mehrminder,
									bool show_gk_real,
									bool show_gk_kom,
									bool show_gk_priv,
									int user_id):	
			ResultGk(show_gk_real, show_gk_kom, show_gk_priv),
			user_id_(user_id),
			stadt_(stadt),
			gebiet_(gebiet),
			programm_(programm),
			show_jz_(show_jz),
			show_bundland_(show_bundland),
			show_mla_(show_mla),
			show_restmittel_(show_restmittel),
			show_mehrminder_(show_mehrminder),
			
			
			spalte_jahr_(20),
			spalte_jh_(-1),
			spalte_bundland_(-1),
			spalte_mla_(-1),
			spalte_restmittel_(-1),
			spalte_mehr_minder_(-1),
			
			bewilligung_liste(gcnew List< List<String^>^ >),
			staedte_(gcnew List<String^>),
			gebiete_(gcnew List<String^>),
			programme_(gcnew List<String^>),			
			haushalte_(gcnew List<String^>),

			// Printer Stuff
			pages_(0),
			print_page_(0),
			
			p_s_jahr_(-1),
			p_s_jh_(-1),
			p_s_bundland_(-1),
			p_s_mla_(-1),
			p_s_restmittel_(-1),
			p_s_mehr_minder_(-1),
			p_s_gk_real_(-1),
			p_s_gk_kom_(-1),
			p_s_gk_priv_(-1),
			p_s_breite_(-1),

			// Ladebalken
			ladebalken_(gcnew test())
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
		~gesamt_uebersicht_result()
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
		String^ stadt_;
		String^ gebiet_;
		String^ programm_;
		bool show_jz_;
		bool show_bundland_;
		bool show_mla_;
		bool show_restmittel_;
		bool show_mehrminder_;

		int spalte_jahr_;
		int spalte_jh_;
		int spalte_bundland_;
		int spalte_mla_;
		int spalte_restmittel_;
		int spalte_mehr_minder_;
		
		List< List<String^>^ >^ bewilligung_liste;
		List<String^>^ staedte_;
		List<String^>^ gebiete_;
		List<String^>^ programme_;
		List<String^>^ haushalte_;

		// Print Stuff
		int pages_;
		int print_page_;

		// Print_Spalten
		int p_s_jahr_;
		int p_s_jh_;
		int p_s_bundland_;
		int p_s_mla_;
		int p_s_restmittel_;
		int p_s_mehr_minder_;
		int p_s_gk_real_;
		int p_s_gk_kom_;
		int p_s_gk_priv_;
		int p_s_breite_;

	private: System::Windows::Forms::Button^  btn_print;
	private: System::Drawing::Printing::PrintDocument^  printDocument1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(gesamt_uebersicht_result::typeid));
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->SuspendLayout();
			// 
			// btn_print
			// 
			this->btn_print->Location = System::Drawing::Point(19, 156);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(808, 20);
			this->btn_print->TabIndex = 2;
			this->btn_print->Text = L"Drucken";
			this->btn_print->UseVisualStyleBackColor = true;
			this->btn_print->Click += gcnew System::EventHandler(this, &gesamt_uebersicht_result::btn_print_Click);
			// 
			// printDocument1
			// 
			this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &gesamt_uebersicht_result::printDocument1_PrintPage);
			// 
			// gesamt_uebersicht_result
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(994, 572);
			this->Controls->Add(this->btn_print);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1000, 600);
			this->Name = L"gesamt_uebersicht_result";
			this->Padding = System::Windows::Forms::Padding(0, 0, 14, 0);
			this->Text = L"Gesamtübersicht";
			this->Load += gcnew System::EventHandler(this, &gesamt_uebersicht_result::gesamt_uebersicht_result_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 

		// Loader
		void gesamt_uebersicht_result_Load(System::Object^  sender, System::EventArgs^  e);
		void load_from_DB();
		void sort_lists();
		void create();
		List< List<String^>^ >^ get_informations(List< List<String^>^ >^,String^,String^,String^);
		void sort_for_year(List<String^>^);
		bool is_existent_in(List<String^>^,String^);
		Decimal get_haushalt(String^,String^,String^,String^);
		
		// Auswertungselemente
		void calc_coloumns();
		void generate_header(String^ stadt, String^ gebiet, String^ programm);
		void GenerateTableHeader();
		void generate_entry(	int entry_param,
								String^ stadt,
								String^ gebiet,
								String^ programm,
								String^ jahr,
								String^ haushalt,
								String^ bund_land,
								String^ mla,
								String^ restmittel,
								String^ mehr_minder,
								String^ gk_real,
								String^ gk_kom,
								String^ gk_priv);
		void generate_footer(	String^ haushalt,
								String^ bund_land,
								String^ mla,
								String^ restmittel,
								String^ mehr_minder,
								String^ gk_real,
								String^ gk_kom,
								String^ gk_priv);
		void place_print_button();

		// Events
		void Click(System::Object^  sender, System::EventArgs^  e);
		List<String^>^ seperate_values(String^);
		
		// Buttons
		void btn_print_Click(System::Object^  sender, System::EventArgs^  e);


		// PrintStuff
		void calc_print_coloumns();
		void printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e);
		void create_page_header(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^);
		void create_page_entry(	System::Drawing::Printing::PrintPageEventArgs^  e,
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
								int entry);
		void create_page_footer(	System::Drawing::Printing::PrintPageEventArgs^  e,
									String^ haushalt,
									String^ bund_land,
									String^ mla,
									String^ restmittel,
									String^ mehr_minder,
									String^ gk_real,
									String^ gk_kom,
									String^ gk_priv,
									int begin_at);
		void create_page_sign(System::Drawing::Printing::PrintPageEventArgs^);
	public:
		void AddCellC(String^ text, int xPos, int row, String^ name);
		void AddCellC(String^ text, int xPos, int row, String^ name, bool isDecimal);

};
}
