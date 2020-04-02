#pragma once

#include "test.h"
#include "ExcelExport.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für adress_uebersicht_result
	/// </summary>
	public ref class adress_uebersicht_result : public System::Windows::Forms::Form
	{
	public:
		adress_uebersicht_result(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

		adress_uebersicht_result(String^ stadt, String^ gebiet, String^ adresse,int user_id):
			user_id_(user_id),
			stadt_(stadt),
			gebiet_(gebiet),
			adresse_(adresse),
			main_entries_(gcnew List< List<String^>^ >),
			entries_(gcnew List< List<String^>^ >),
			start_(0),
			// Printer Stuff
			pages_(0),
			print_page_(0),
			page_content_(gcnew List< List< List<String^>^ >^ >),
			p_s_bezeichnung(0),
			p_s_bew_anzahl(0),
			p_s_bew_ztr(0),
			p_s_vn_einger(0),
			p_s_vn_gepr(0),
			p_s_kosten(0),
			p_s_foerder(0),
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
		~adress_uebersicht_result()
		{
			if (components)
			{
				delete components;
			}
			delete exl_;
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
		String^ adresse_;

		List< List<String^>^ >^ main_entries_;
		List< List<String^>^ >^ entries_;

		// Print Stuff
		int pages_;
		int print_page_;
		List< List< List<String^>^ >^ >^ page_content_;
		// Print_Spalten
		int p_s_bezeichnung;
		int p_s_bew_anzahl;
		int p_s_bew_ztr;
		int p_s_vn_einger;
		int p_s_vn_gepr;
		int p_s_kosten;
		int p_s_foerder;
		int done_page_content_;

		ExcelExport ^ exl_;
		int row_;

	private: System::Windows::Forms::Button^  btn_print;
	private: Microsoft::VisualBasic::PowerPacks::Printing::PrintForm^  printForm1;
	private: System::Drawing::Printing::PrintDocument^  printDocument1;
	private: System::Windows::Forms::PrintDialog^  printDialog1;
	private: System::Windows::Forms::Button^  btn_exportExl;

		int start_;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(adress_uebersicht_result::typeid));
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->printForm1 = (gcnew Microsoft::VisualBasic::PowerPacks::Printing::PrintForm(this->components));
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->printDialog1 = (gcnew System::Windows::Forms::PrintDialog());
			this->btn_exportExl = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_print
			// 
			this->btn_print->Location = System::Drawing::Point(3, 309);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(808, 20);
			this->btn_print->TabIndex = 2;
			this->btn_print->Text = L"Drucken";
			this->btn_print->UseVisualStyleBackColor = true;
			this->btn_print->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::btn_print_Click);
			// 
			// printForm1
			// 
			this->printForm1->DocumentName = L"document";
			this->printForm1->Form = this;
			this->printForm1->PrintAction = System::Drawing::Printing::PrintAction::PrintToPreview;
			this->printForm1->PrinterSettings = (cli::safe_cast<System::Drawing::Printing::PrinterSettings^  >(resources->GetObject(L"printForm1.PrinterSettings")));
			this->printForm1->PrintFileName = nullptr;
			// 
			// printDocument1
			// 
			this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &adress_uebersicht_result::printDocument1_PrintPage);
			// 
			// printDialog1
			// 
			this->printDialog1->UseEXDialog = true;
			// 
			// btn_exportExl
			// 
			this->btn_exportExl->ImageAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->btn_exportExl->Location = System::Drawing::Point(3, 280);
			this->btn_exportExl->Name = L"btn_exportExl";
			this->btn_exportExl->Size = System::Drawing::Size(808, 23);
			this->btn_exportExl->TabIndex = 3;
			this->btn_exportExl->Text = L"nach Exel exportieren";
			this->btn_exportExl->UseVisualStyleBackColor = true;
			this->btn_exportExl->Click += gcnew System::EventHandler(this, &adress_uebersicht_result::btn_exportExl_Click);
			// 
			// adress_uebersicht_result
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
			this->Name = L"adress_uebersicht_result";
			this->Padding = System::Windows::Forms::Padding(0, 0, 14, 0);
			this->Text = L"Übersicht Adressen";
			this->Load += gcnew System::EventHandler(this, &adress_uebersicht_result::adress_uebersicht_result_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		// Loader
		void adress_uebersicht_result_Load(System::Object^  sender, System::EventArgs^  e);
		void load_main_entries();
		List<String^>^ get_staedte();
		List<String^>^ get_gebiete(String^);
		List<String^>^ get_adressen(String^,String^);
		bool is_existent_in(List<String^>^,String^);
		void create_main_entries(String^, String^, List<String^>^);
		void sort_for_bew_ztr(List< List<String^>^ >^ liste);

		// Auswertungselemente
		void generate_header(String^,String^,String^);
		void GenerateTableHeader();
		void generate_entry(String^,String^,String^,String^,String^,String^,String^,String^,int);
		void generate_footer(String^,String^);
		void place_print_button();

		// Events
		void Click(System::Object^  sender, System::EventArgs^  e);

		// Buttons
		void btn_print_Click(System::Object^  sender, System::EventArgs^  e);
		void printDocument1_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e);
		void btn_exportExl_Click(System::Object^  sender, System::EventArgs^  e);

		// Printer Stuff
		void create_page_header(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^);
		void create_page_entry(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,String^,String^,String^,String^,String^,int,int);
		void create_page_footer(System::Drawing::Printing::PrintPageEventArgs^,String^,String^,int);
		void create_page_sign(System::Drawing::Printing::PrintPageEventArgs^);
};
}
