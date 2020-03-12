#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für kostengr_uebersicht_search
	/// </summary>
	public ref class kostengr_uebersicht_search : public System::Windows::Forms::Form
	{
	public:
		kostengr_uebersicht_search(int user_id):
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
		~kostengr_uebersicht_search()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^  search_programm;
		int user_id_;
	protected: 
	private: System::Windows::Forms::CheckBox^  search_stadt;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::ComboBox^  jahre;
	private: System::Windows::Forms::CheckBox^  search_jahr;
	private: System::Windows::Forms::ComboBox^  gebiete;
	private: System::Windows::Forms::ComboBox^  programme;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  search_gebiet;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  staedte;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  btn_close;

	private: System::Windows::Forms::Button^  btn_create;

	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::ComboBox^  kostengruppen;
	private: System::Windows::Forms::CheckBox^  search_kostengruppen;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(kostengr_uebersicht_search::typeid));
			this->search_programm = (gcnew System::Windows::Forms::CheckBox());
			this->search_stadt = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->jahre = (gcnew System::Windows::Forms::ComboBox());
			this->search_jahr = (gcnew System::Windows::Forms::CheckBox());
			this->gebiete = (gcnew System::Windows::Forms::ComboBox());
			this->programme = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->search_gebiet = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->staedte = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->btn_create = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->kostengruppen = (gcnew System::Windows::Forms::ComboBox());
			this->search_kostengruppen = (gcnew System::Windows::Forms::CheckBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
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
			this->search_programm->CheckedChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::search_programm_CheckedChanged);
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
			this->search_stadt->CheckedChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::search_stadt_CheckedChanged);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->jahre);
			this->groupBox4->Controls->Add(this->search_jahr);
			this->groupBox4->Location = System::Drawing::Point(12, 232);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(267, 49);
			this->groupBox4->TabIndex = 5;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Jahr";
			// 
			// jahre
			// 
			this->jahre->FormattingEnabled = true;
			this->jahre->Location = System::Drawing::Point(15, 19);
			this->jahre->Name = L"jahre";
			this->jahre->Size = System::Drawing::Size(178, 21);
			this->jahre->TabIndex = 1;
			this->jahre->TextChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::jahre_TextChanged);
			// 
			// search_jahr
			// 
			this->search_jahr->AutoSize = true;
			this->search_jahr->Location = System::Drawing::Point(199, 23);
			this->search_jahr->Name = L"search_jahr";
			this->search_jahr->Size = System::Drawing::Size(61, 17);
			this->search_jahr->TabIndex = 2;
			this->search_jahr->Text = L"suchen";
			this->search_jahr->UseVisualStyleBackColor = true;
			// 
			// gebiete
			// 
			this->gebiete->FormattingEnabled = true;
			this->gebiete->Location = System::Drawing::Point(15, 19);
			this->gebiete->Name = L"gebiete";
			this->gebiete->Size = System::Drawing::Size(178, 21);
			this->gebiete->Sorted = true;
			this->gebiete->TabIndex = 1;
			this->gebiete->TextChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::gebiete_TextChanged);
			// 
			// programme
			// 
			this->programme->FormattingEnabled = true;
			this->programme->Location = System::Drawing::Point(15, 19);
			this->programme->Name = L"programme";
			this->programme->Size = System::Drawing::Size(178, 21);
			this->programme->Sorted = true;
			this->programme->TabIndex = 1;
			this->programme->TextChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::programme_TextChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->programme);
			this->groupBox3->Controls->Add(this->search_programm);
			this->groupBox3->Location = System::Drawing::Point(12, 177);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(267, 49);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Programm";
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
			this->search_gebiet->CheckedChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::search_gebiet_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->gebiete);
			this->groupBox2->Controls->Add(this->search_gebiet);
			this->groupBox2->Location = System::Drawing::Point(12, 122);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(267, 49);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Gebiet";
			// 
			// staedte
			// 
			this->staedte->FormattingEnabled = true;
			this->staedte->Location = System::Drawing::Point(15, 19);
			this->staedte->Name = L"staedte";
			this->staedte->Size = System::Drawing::Size(178, 21);
			this->staedte->Sorted = true;
			this->staedte->TabIndex = 1;
			this->staedte->TextChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::staedte_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->staedte);
			this->groupBox1->Controls->Add(this->search_stadt);
			this->groupBox1->Location = System::Drawing::Point(12, 67);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 49);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Stadt";
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 317);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(180, 24);
			this->btn_close->TabIndex = 7;
			this->btn_close->Text = L"Zurück";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &kostengr_uebersicht_search::btn_close_Click);
			// 
			// btn_create
			// 
			this->btn_create->Location = System::Drawing::Point(12, 287);
			this->btn_create->Name = L"btn_create";
			this->btn_create->Size = System::Drawing::Size(267, 24);
			this->btn_create->TabIndex = 6;
			this->btn_create->Text = L"Auswertung erstellen";
			this->btn_create->UseVisualStyleBackColor = true;
			this->btn_create->Click += gcnew System::EventHandler(this, &kostengr_uebersicht_search::btn_create_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->kostengruppen);
			this->groupBox5->Controls->Add(this->search_kostengruppen);
			this->groupBox5->Location = System::Drawing::Point(12, 12);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(267, 49);
			this->groupBox5->TabIndex = 1;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Kostengruppen";
			// 
			// kostengruppen
			// 
			this->kostengruppen->FormattingEnabled = true;
			this->kostengruppen->Location = System::Drawing::Point(15, 19);
			this->kostengruppen->Name = L"kostengruppen";
			this->kostengruppen->Size = System::Drawing::Size(178, 21);
			this->kostengruppen->Sorted = true;
			this->kostengruppen->TabIndex = 1;
			this->kostengruppen->TextChanged += gcnew System::EventHandler(this, &kostengr_uebersicht_search::kostengruppen_TextChanged);
			// 
			// search_kostengruppen
			// 
			this->search_kostengruppen->AutoSize = true;
			this->search_kostengruppen->Location = System::Drawing::Point(199, 23);
			this->search_kostengruppen->Name = L"search_kostengruppen";
			this->search_kostengruppen->Size = System::Drawing::Size(61, 17);
			this->search_kostengruppen->TabIndex = 2;
			this->search_kostengruppen->Text = L"suchen";
			this->search_kostengruppen->UseVisualStyleBackColor = true;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(198, 323);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// kostengr_uebersicht_search
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(293, 350);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->btn_create);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"kostengr_uebersicht_search";
			this->Text = L"Übersicht Kostengruppen";
			this->Load += gcnew System::EventHandler(this, &kostengr_uebersicht_search::kostengr_uebersicht_search_Load);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 

		// Loader
		void kostengr_uebersicht_search_Load(System::Object^  sender, System::EventArgs^  e);
		void load_gebiet();
		void load_programm();

		// TextChange
		void staedte_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void programme_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void jahre_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void kostengruppen_TextChanged(System::Object^  sender, System::EventArgs^  e);

		// CheckedChange
		void search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e);

		// Buttons
		void btn_create_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
};
}
