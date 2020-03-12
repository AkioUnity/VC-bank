#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für open_project_form
	/// </summary>
	public ref class open_project_form : public System::Windows::Forms::Form
	{
	public:
		open_project_form(void):
			id_(gcnew List<String^>)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		open_project_form(int user_id):
			id_(gcnew List<String^>),
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
		~open_project_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: List<String^>^ id_;
			 int user_id_;

	private: System::Windows::Forms::Button^  btn_open;
	protected: 
	private: System::Windows::Forms::Button^  btn_close;
	private: System::Windows::Forms::ListBox^  projekte;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  btn_search;
	private: System::Windows::Forms::ComboBox^  staedte;
	private: System::Windows::Forms::TextBox^  bezeichnung;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  search_stadt;
	private: System::Windows::Forms::CheckBox^  search_bezeichnung;

	private: System::Windows::Forms::CheckBox^  search_gebiet;
	private: System::Windows::Forms::ComboBox^  gebiete;


	private: System::Windows::Forms::Label^  label4;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(open_project_form::typeid));
			this->btn_open = (gcnew System::Windows::Forms::Button());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->projekte = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->search_gebiet = (gcnew System::Windows::Forms::CheckBox());
			this->gebiete = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->search_stadt = (gcnew System::Windows::Forms::CheckBox());
			this->search_bezeichnung = (gcnew System::Windows::Forms::CheckBox());
			this->staedte = (gcnew System::Windows::Forms::ComboBox());
			this->bezeichnung = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btn_search = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_open
			// 
			this->btn_open->Location = System::Drawing::Point(318, 226);
			this->btn_open->Name = L"btn_open";
			this->btn_open->Size = System::Drawing::Size(341, 20);
			this->btn_open->TabIndex = 8;
			this->btn_open->Text = L"Projekt öffnen";
			this->btn_open->UseVisualStyleBackColor = true;
			this->btn_open->Click += gcnew System::EventHandler(this, &open_project_form::btn_open_Click);
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 267);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(647, 20);
			this->btn_close->TabIndex = 7;
			this->btn_close->Text = L"Zurück";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &open_project_form::btn_close_Click);
			// 
			// projekte
			// 
			this->projekte->FormattingEnabled = true;
			this->projekte->Location = System::Drawing::Point(318, 21);
			this->projekte->Name = L"projekte";
			this->projekte->Size = System::Drawing::Size(341, 199);
			this->projekte->TabIndex = 6;
			this->projekte->DoubleClick += gcnew System::EventHandler(this, &open_project_form::projekte_DoubleClick);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->search_gebiet);
			this->groupBox1->Controls->Add(this->gebiete);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->search_stadt);
			this->groupBox1->Controls->Add(this->search_bezeichnung);
			this->groupBox1->Controls->Add(this->staedte);
			this->groupBox1->Controls->Add(this->bezeichnung);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->btn_search);
			this->groupBox1->Location = System::Drawing::Point(12, 13);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(300, 248);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Projekt suchen";
			// 
			// search_gebiet
			// 
			this->search_gebiet->AutoSize = true;
			this->search_gebiet->Location = System::Drawing::Point(17, 190);
			this->search_gebiet->Name = L"search_gebiet";
			this->search_gebiet->Size = System::Drawing::Size(122, 17);
			this->search_gebiet->TabIndex = 11;
			this->search_gebiet->Text = L"nach Gebiet suchen";
			this->search_gebiet->UseVisualStyleBackColor = true;
			// 
			// gebiete
			// 
			this->gebiete->FormattingEnabled = true;
			this->gebiete->Location = System::Drawing::Point(17, 163);
			this->gebiete->Name = L"gebiete";
			this->gebiete->Size = System::Drawing::Size(266, 21);
			this->gebiete->Sorted = true;
			this->gebiete->TabIndex = 10;
			this->gebiete->TextChanged += gcnew System::EventHandler(this, &open_project_form::gebiete_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(14, 147);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(44, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Gebiet :";
			// 
			// search_stadt
			// 
			this->search_stadt->AutoSize = true;
			this->search_stadt->Location = System::Drawing::Point(17, 125);
			this->search_stadt->Name = L"search_stadt";
			this->search_stadt->Size = System::Drawing::Size(116, 17);
			this->search_stadt->TabIndex = 4;
			this->search_stadt->Text = L"nach Stadt suchen";
			this->search_stadt->UseVisualStyleBackColor = true;
			// 
			// search_bezeichnung
			// 
			this->search_bezeichnung->AutoSize = true;
			this->search_bezeichnung->Location = System::Drawing::Point(17, 62);
			this->search_bezeichnung->Name = L"search_bezeichnung";
			this->search_bezeichnung->Size = System::Drawing::Size(153, 17);
			this->search_bezeichnung->TabIndex = 2;
			this->search_bezeichnung->Text = L"nach Bezeichnung suchen";
			this->search_bezeichnung->UseVisualStyleBackColor = true;
			// 
			// staedte
			// 
			this->staedte->FormattingEnabled = true;
			this->staedte->Location = System::Drawing::Point(17, 98);
			this->staedte->Name = L"staedte";
			this->staedte->Size = System::Drawing::Size(266, 21);
			this->staedte->Sorted = true;
			this->staedte->TabIndex = 3;
			this->staedte->TextChanged += gcnew System::EventHandler(this, &open_project_form::staedte_TextChanged);
			// 
			// bezeichnung
			// 
			this->bezeichnung->Location = System::Drawing::Point(17, 36);
			this->bezeichnung->Name = L"bezeichnung";
			this->bezeichnung->Size = System::Drawing::Size(268, 20);
			this->bezeichnung->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(14, 82);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Stadt :";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Bezeichnung :";
			// 
			// btn_search
			// 
			this->btn_search->Location = System::Drawing::Point(17, 213);
			this->btn_search->Name = L"btn_search";
			this->btn_search->Size = System::Drawing::Size(266, 20);
			this->btn_search->TabIndex = 5;
			this->btn_search->Text = L"Suchen";
			this->btn_search->UseVisualStyleBackColor = true;
			this->btn_search->Click += gcnew System::EventHandler(this, &open_project_form::btn_search_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(576, 251);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// open_project_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(671, 297);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->projekte);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->btn_open);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"open_project_form";
			this->Text = L"Projekt öffnen";
			this->Load += gcnew System::EventHandler(this, &open_project_form::open_project_form_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 

		void open_project_form_Load(System::Object^  sender, System::EventArgs^  e);
		void load_gebiete();

		// Button
		void btn_open_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_search_Click(System::Object^  sender, System::EventArgs^  e);
		void projekte_DoubleClick(System::Object^  sender, System::EventArgs^  e);

		void staedte_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e);
};
}
