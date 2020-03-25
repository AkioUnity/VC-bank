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
	/// Zusammenfassung für gesamt_uebersicht_search
	/// </summary>
	public ref class gesamt_uebersicht_search : public System::Windows::Forms::Form
	{
	public:
		gesamt_uebersicht_search(int user_id):
			user_id_(user_id), loadingForm(gcnew test())
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

		test^ loadingForm;  //loading bar_

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~gesamt_uebersicht_search()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox3;
		int user_id_;
	protected: 
	private: System::Windows::Forms::ComboBox^  programme;
	private: System::Windows::Forms::CheckBox^  search_programm;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  gebiete;
	private: System::Windows::Forms::CheckBox^  search_gebiet;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ComboBox^  staedte;
	private: System::Windows::Forms::CheckBox^  search_stadt;
	private: System::Windows::Forms::Button^  btn_close;

	private: System::Windows::Forms::Button^  btn_create_result;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::CheckBox^  show_gk_priv;
	private: System::Windows::Forms::CheckBox^  show_gk_kom;
	private: System::Windows::Forms::CheckBox^  show_gk_real;
	private: System::Windows::Forms::CheckBox^  show_mehr_minder;
	private: System::Windows::Forms::CheckBox^  show_restmittel;
	private: System::Windows::Forms::CheckBox^  show_mla;
	private: System::Windows::Forms::CheckBox^  show_bund_land;
	private: System::Windows::Forms::CheckBox^  show_jz;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(gesamt_uebersicht_search::typeid));
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->programme = (gcnew System::Windows::Forms::ComboBox());
			this->search_programm = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->gebiete = (gcnew System::Windows::Forms::ComboBox());
			this->search_gebiet = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->staedte = (gcnew System::Windows::Forms::ComboBox());
			this->search_stadt = (gcnew System::Windows::Forms::CheckBox());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->btn_create_result = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->show_gk_priv = (gcnew System::Windows::Forms::CheckBox());
			this->show_gk_kom = (gcnew System::Windows::Forms::CheckBox());
			this->show_gk_real = (gcnew System::Windows::Forms::CheckBox());
			this->show_mehr_minder = (gcnew System::Windows::Forms::CheckBox());
			this->show_restmittel = (gcnew System::Windows::Forms::CheckBox());
			this->show_mla = (gcnew System::Windows::Forms::CheckBox());
			this->show_bund_land = (gcnew System::Windows::Forms::CheckBox());
			this->show_jz = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->programme);
			this->groupBox3->Controls->Add(this->search_programm);
			this->groupBox3->Location = System::Drawing::Point(12, 122);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(267, 49);
			this->groupBox3->TabIndex = 3;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Programm";
			// 
			// programme
			// 
			this->programme->FormattingEnabled = true;
			this->programme->Location = System::Drawing::Point(15, 19);
			this->programme->Name = L"programme";
			this->programme->Size = System::Drawing::Size(178, 21);
			this->programme->Sorted = true;
			this->programme->TabIndex = 1;
			this->programme->TextChanged += gcnew System::EventHandler(this, &gesamt_uebersicht_search::programme_TextChanged);
			// 
			// search_programm
			// 
			this->search_programm->AutoSize = true;
			this->search_programm->Location = System::Drawing::Point(199, 23);
			this->search_programm->Name = L"search_programm";
			this->search_programm->Size = System::Drawing::Size(61, 17);
			this->search_programm->TabIndex = 2;
			this->search_programm->Text = L"suchen";
			this->search_programm->UseVisualStyleBackColor = true;
			this->search_programm->CheckedChanged += gcnew System::EventHandler(this, &gesamt_uebersicht_search::search_programm_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->gebiete);
			this->groupBox2->Controls->Add(this->search_gebiet);
			this->groupBox2->Location = System::Drawing::Point(12, 67);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(267, 49);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Gebiet";
			// 
			// gebiete
			// 
			this->gebiete->FormattingEnabled = true;
			this->gebiete->Location = System::Drawing::Point(15, 19);
			this->gebiete->Name = L"gebiete";
			this->gebiete->Size = System::Drawing::Size(178, 21);
			this->gebiete->Sorted = true;
			this->gebiete->TabIndex = 1;
			this->gebiete->TextChanged += gcnew System::EventHandler(this, &gesamt_uebersicht_search::gebiete_TextChanged);
			// 
			// search_gebiet
			// 
			this->search_gebiet->AutoSize = true;
			this->search_gebiet->Location = System::Drawing::Point(199, 23);
			this->search_gebiet->Name = L"search_gebiet";
			this->search_gebiet->Size = System::Drawing::Size(61, 17);
			this->search_gebiet->TabIndex = 2;
			this->search_gebiet->Text = L"suchen";
			this->search_gebiet->UseVisualStyleBackColor = true;
			this->search_gebiet->CheckedChanged += gcnew System::EventHandler(this, &gesamt_uebersicht_search::search_gebiet_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->staedte);
			this->groupBox1->Controls->Add(this->search_stadt);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 49);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Stadt";
			// 
			// staedte
			// 
			this->staedte->FormattingEnabled = true;
			this->staedte->Location = System::Drawing::Point(15, 19);
			this->staedte->Name = L"staedte";
			this->staedte->Size = System::Drawing::Size(178, 21);
			this->staedte->Sorted = true;
			this->staedte->TabIndex = 1;
			this->staedte->TextChanged += gcnew System::EventHandler(this, &gesamt_uebersicht_search::staedte_TextChanged);
			// 
			// search_stadt
			// 
			this->search_stadt->AutoSize = true;
			this->search_stadt->Location = System::Drawing::Point(199, 23);
			this->search_stadt->Name = L"search_stadt";
			this->search_stadt->Size = System::Drawing::Size(61, 17);
			this->search_stadt->TabIndex = 2;
			this->search_stadt->Text = L"suchen";
			this->search_stadt->UseVisualStyleBackColor = true;
			this->search_stadt->CheckedChanged += gcnew System::EventHandler(this, &gesamt_uebersicht_search::search_stadt_CheckedChanged);
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 440);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(178, 24);
			this->btn_close->TabIndex = 6;
			this->btn_close->Text = L"Zurück";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &gesamt_uebersicht_search::btn_close_Click);
			// 
			// btn_create_result
			// 
			this->btn_create_result->Location = System::Drawing::Point(12, 410);
			this->btn_create_result->Name = L"btn_create_result";
			this->btn_create_result->Size = System::Drawing::Size(267, 24);
			this->btn_create_result->TabIndex = 5;
			this->btn_create_result->Text = L"Auswertung erstellen";
			this->btn_create_result->UseVisualStyleBackColor = true;
			this->btn_create_result->Click += gcnew System::EventHandler(this, &gesamt_uebersicht_search::btn_create_result_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(196, 446);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->show_gk_priv);
			this->groupBox4->Controls->Add(this->show_gk_kom);
			this->groupBox4->Controls->Add(this->show_gk_real);
			this->groupBox4->Controls->Add(this->show_mehr_minder);
			this->groupBox4->Controls->Add(this->show_restmittel);
			this->groupBox4->Controls->Add(this->show_mla);
			this->groupBox4->Controls->Add(this->show_bund_land);
			this->groupBox4->Controls->Add(this->show_jz);
			this->groupBox4->Location = System::Drawing::Point(14, 188);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(264, 207);
			this->groupBox4->TabIndex = 4;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Suche";
			// 
			// show_gk_priv
			// 
			this->show_gk_priv->AutoSize = true;
			this->show_gk_priv->Location = System::Drawing::Point(16, 183);
			this->show_gk_priv->Name = L"show_gk_priv";
			this->show_gk_priv->Size = System::Drawing::Size(129, 17);
			this->show_gk_priv->TabIndex = 8;
			this->show_gk_priv->Text = L"private Gesamtkosten";
			this->show_gk_priv->UseVisualStyleBackColor = true;
			// 
			// show_gk_kom
			// 
			this->show_gk_kom->AutoSize = true;
			this->show_gk_kom->Location = System::Drawing::Point(16, 160);
			this->show_gk_kom->Name = L"show_gk_kom";
			this->show_gk_kom->Size = System::Drawing::Size(151, 17);
			this->show_gk_kom->TabIndex = 7;
			this->show_gk_kom->Text = L"kommunale Gesamtkosten";
			this->show_gk_kom->UseVisualStyleBackColor = true;
			// 
			// show_gk_real
			// 
			this->show_gk_real->AutoSize = true;
			this->show_gk_real->Location = System::Drawing::Point(16, 137);
			this->show_gk_real->Name = L"show_gk_real";
			this->show_gk_real->Size = System::Drawing::Size(120, 17);
			this->show_gk_real->TabIndex = 6;
			this->show_gk_real->Text = L"reale Gesamtkosten";
			this->show_gk_real->UseVisualStyleBackColor = true;
			// 
			// show_mehr_minder
			// 
			this->show_mehr_minder->AutoSize = true;
			this->show_mehr_minder->Checked = true;
			this->show_mehr_minder->CheckState = System::Windows::Forms::CheckState::Checked;
			this->show_mehr_minder->Location = System::Drawing::Point(16, 114);
			this->show_mehr_minder->Name = L"show_mehr_minder";
			this->show_mehr_minder->Size = System::Drawing::Size(122, 17);
			this->show_mehr_minder->TabIndex = 5;
			this->show_mehr_minder->Text = L"Mehr-/Minderkosten";
			this->show_mehr_minder->UseVisualStyleBackColor = true;
			// 
			// show_restmittel
			// 
			this->show_restmittel->AutoSize = true;
			this->show_restmittel->Checked = true;
			this->show_restmittel->CheckState = System::Windows::Forms::CheckState::Checked;
			this->show_restmittel->Location = System::Drawing::Point(16, 91);
			this->show_restmittel->Name = L"show_restmittel";
			this->show_restmittel->Size = System::Drawing::Size(72, 17);
			this->show_restmittel->TabIndex = 4;
			this->show_restmittel->Text = L"Restmittel";
			this->show_restmittel->UseVisualStyleBackColor = true;
			// 
			// show_mla
			// 
			this->show_mla->AutoSize = true;
			this->show_mla->Checked = true;
			this->show_mla->CheckState = System::Windows::Forms::CheckState::Checked;
			this->show_mla->Location = System::Drawing::Point(16, 68);
			this->show_mla->Name = L"show_mla";
			this->show_mla->Size = System::Drawing::Size(48, 17);
			this->show_mla->TabIndex = 3;
			this->show_mla->Text = L"MLA";
			this->show_mla->UseVisualStyleBackColor = true;
			// 
			// show_bund_land
			// 
			this->show_bund_land->AutoSize = true;
			this->show_bund_land->Checked = true;
			this->show_bund_land->CheckState = System::Windows::Forms::CheckState::Checked;
			this->show_bund_land->Location = System::Drawing::Point(16, 45);
			this->show_bund_land->Name = L"show_bund_land";
			this->show_bund_land->Size = System::Drawing::Size(80, 17);
			this->show_bund_land->TabIndex = 2;
			this->show_bund_land->Text = L"Bund/Land";
			this->show_bund_land->UseVisualStyleBackColor = true;
			// 
			// show_jz
			// 
			this->show_jz->AutoSize = true;
			this->show_jz->Checked = true;
			this->show_jz->CheckState = System::Windows::Forms::CheckState::Checked;
			this->show_jz->Location = System::Drawing::Point(16, 22);
			this->show_jz->Name = L"show_jz";
			this->show_jz->Size = System::Drawing::Size(99, 17);
			this->show_jz->TabIndex = 1;
			this->show_jz->Text = L"Jahreszuteilung";
			this->show_jz->UseVisualStyleBackColor = true;
			// 
			// gesamt_uebersicht_search
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(291, 473);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->btn_create_result);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"gesamt_uebersicht_search";
			this->Text = L"Gesamtübersicht";
			this->Load += gcnew System::EventHandler(this, &gesamt_uebersicht_search::gesamt_uebersicht_search_Load);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		// Loader
		void gesamt_uebersicht_search_Load(System::Object^  sender, System::EventArgs^  e);
		void load_gebiet();
		void load_programm();

		// Text Change
		void staedte_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void programme_TextChanged(System::Object^  sender, System::EventArgs^  e);

		//Checked Change
		void search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e);

		// Button
		void btn_create_result_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
};
}
