#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für adress_uebersicht_search
	/// </summary>
	public ref class adress_uebersicht_search : public System::Windows::Forms::Form
	{
	public:
		adress_uebersicht_search(int user_id):
			user_id_(user_id)
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
		~adress_uebersicht_search()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_close;
		int user_id_;
	protected: 
	private: System::Windows::Forms::Button^  btn_create_result;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ComboBox^  adressen;
	private: System::Windows::Forms::CheckBox^  search_adresse;


	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  gebiete;
	private: System::Windows::Forms::CheckBox^  search_gebiet;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ComboBox^  staedte;
	private: System::Windows::Forms::CheckBox^  search_stadt;
	private: System::Windows::Forms::Label^  label19;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(adress_uebersicht_search::typeid));
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->btn_create_result = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->adressen = (gcnew System::Windows::Forms::ComboBox());
			this->search_adresse = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->gebiete = (gcnew System::Windows::Forms::ComboBox());
			this->search_gebiet = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->staedte = (gcnew System::Windows::Forms::ComboBox());
			this->search_stadt = (gcnew System::Windows::Forms::CheckBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 207);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(193, 24);
			this->btn_close->TabIndex = 5;
			this->btn_close->Text = L"Zurück";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &adress_uebersicht_search::btn_close_Click);
			// 
			// btn_create_result
			// 
			this->btn_create_result->Location = System::Drawing::Point(12, 177);
			this->btn_create_result->Name = L"btn_create_result";
			this->btn_create_result->Size = System::Drawing::Size(267, 24);
			this->btn_create_result->TabIndex = 4;
			this->btn_create_result->Text = L"Auswertung erstellen";
			this->btn_create_result->UseVisualStyleBackColor = true;
			this->btn_create_result->Click += gcnew System::EventHandler(this, &adress_uebersicht_search::btn_create_result_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->adressen);
			this->groupBox3->Controls->Add(this->search_adresse);
			this->groupBox3->Location = System::Drawing::Point(12, 122);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(267, 49);
			this->groupBox3->TabIndex = 3;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Adresse";
			// 
			// adressen
			// 
			this->adressen->FormattingEnabled = true;
			this->adressen->Location = System::Drawing::Point(15, 19);
			this->adressen->Name = L"adressen";
			this->adressen->Size = System::Drawing::Size(178, 21);
			this->adressen->Sorted = true;
			this->adressen->TabIndex = 1;
			this->adressen->TextChanged += gcnew System::EventHandler(this, &adress_uebersicht_search::adressen_TextChanged);
			// 
			// search_adresse
			// 
			this->search_adresse->AutoSize = true;
			this->search_adresse->Location = System::Drawing::Point(199, 23);
			this->search_adresse->Name = L"search_adresse";
			this->search_adresse->Size = System::Drawing::Size(61, 17);
			this->search_adresse->TabIndex = 2;
			this->search_adresse->Text = L"suchen";
			this->search_adresse->UseVisualStyleBackColor = true;
			this->search_adresse->CheckedChanged += gcnew System::EventHandler(this, &adress_uebersicht_search::search_adresse_CheckedChanged);
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
			this->gebiete->TextChanged += gcnew System::EventHandler(this, &adress_uebersicht_search::gebiete_TextChanged);
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
			this->search_gebiet->CheckedChanged += gcnew System::EventHandler(this, &adress_uebersicht_search::search_gebiet_CheckedChanged);
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
			this->staedte->TextChanged += gcnew System::EventHandler(this, &adress_uebersicht_search::staedte_TextChanged);
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
			this->search_stadt->CheckedChanged += gcnew System::EventHandler(this, &adress_uebersicht_search::search_stadt_CheckedChanged);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(208, 213);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// adress_uebersicht_search
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(293, 240);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->btn_create_result);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"adress_uebersicht_search";
			this->Text = L"Übersicht Adressen";
			this->Load += gcnew System::EventHandler(this, &adress_uebersicht_search::adress_uebersicht_search_Load);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		//Loader
		void adress_uebersicht_search_Load(System::Object^  sender, System::EventArgs^  e);
		void load_gebiet();
		void load_adresse();

		// Text Changes
		void staedte_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void adressen_TextChanged(System::Object^  sender, System::EventArgs^  e);

		// Checked Change
		void search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_adresse_CheckedChanged(System::Object^  sender, System::EventArgs^  e);

		// Buttons
		void btn_create_result_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
};
}
