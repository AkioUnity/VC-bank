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
	/// Zusammenfassung für bew_ztr_search
	/// </summary>
	public ref class bew_ztr_search : public System::Windows::Forms::Form
	{
	public:
		bew_ztr_search(int user_id):
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
		~bew_ztr_search()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label19;
		int user_id_;
	protected: 
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  bis;
	private: System::Windows::Forms::CheckBox^  search_programm;
	private: System::Windows::Forms::CheckBox^  search_stadt;
	private: System::Windows::Forms::ComboBox^  programme;
	private: System::Windows::Forms::ComboBox^  gebiete;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::CheckBox^  search_gebiet;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ComboBox^  staedte;
	private: System::Windows::Forms::Button^  btn_close;
	private: System::Windows::Forms::Button^  search;
	private: System::Windows::Forms::CheckBox^  search_bis;
	private: System::Windows::Forms::RadioButton^  rB_n_einger;
	private: System::Windows::Forms::RadioButton^  rB_einger;


	private: System::Windows::Forms::GroupBox^  groupBox5;






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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(bew_ztr_search::typeid));
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->search_bis = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->bis = (gcnew System::Windows::Forms::TextBox());
			this->search_programm = (gcnew System::Windows::Forms::CheckBox());
			this->search_stadt = (gcnew System::Windows::Forms::CheckBox());
			this->programme = (gcnew System::Windows::Forms::ComboBox());
			this->gebiete = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->search_gebiet = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->staedte = (gcnew System::Windows::Forms::ComboBox());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->search = (gcnew System::Windows::Forms::Button());
			this->rB_n_einger = (gcnew System::Windows::Forms::RadioButton());
			this->rB_einger = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(196, 338);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 54;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->search_bis);
			this->groupBox4->Controls->Add(this->label2);
			this->groupBox4->Controls->Add(this->bis);
			this->groupBox4->Location = System::Drawing::Point(12, 85);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(267, 46);
			this->groupBox4->TabIndex = 2;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Bewilligungszeitraum";
			// 
			// search_bis
			// 
			this->search_bis->AutoSize = true;
			this->search_bis->Location = System::Drawing::Point(199, 21);
			this->search_bis->Name = L"search_bis";
			this->search_bis->Size = System::Drawing::Size(61, 17);
			this->search_bis->TabIndex = 2;
			this->search_bis->Text = L"suchen";
			this->search_bis->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"bis :";
			// 
			// bis
			// 
			this->bis->Location = System::Drawing::Point(51, 18);
			this->bis->Name = L"bis";
			this->bis->Size = System::Drawing::Size(142, 20);
			this->bis->TabIndex = 1;
			this->bis->TextChanged += gcnew System::EventHandler(this, &bew_ztr_search::bis_TextChanged);
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
			this->search_programm->CheckedChanged += gcnew System::EventHandler(this, &bew_ztr_search::search_programm_CheckedChanged);
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
			this->search_stadt->CheckedChanged += gcnew System::EventHandler(this, &bew_ztr_search::search_stadt_CheckedChanged);
			// 
			// programme
			// 
			this->programme->FormattingEnabled = true;
			this->programme->Location = System::Drawing::Point(15, 19);
			this->programme->Name = L"programme";
			this->programme->Size = System::Drawing::Size(178, 21);
			this->programme->Sorted = true;
			this->programme->TabIndex = 1;
			this->programme->TextChanged += gcnew System::EventHandler(this, &bew_ztr_search::programme_TextChanged);
			// 
			// gebiete
			// 
			this->gebiete->FormattingEnabled = true;
			this->gebiete->Location = System::Drawing::Point(15, 19);
			this->gebiete->Name = L"gebiete";
			this->gebiete->Size = System::Drawing::Size(178, 21);
			this->gebiete->Sorted = true;
			this->gebiete->TabIndex = 1;
			this->gebiete->TextChanged += gcnew System::EventHandler(this, &bew_ztr_search::gebiete_TextChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->programme);
			this->groupBox3->Controls->Add(this->search_programm);
			this->groupBox3->Location = System::Drawing::Point(12, 247);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(267, 49);
			this->groupBox3->TabIndex = 5;
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
			this->search_gebiet->CheckedChanged += gcnew System::EventHandler(this, &bew_ztr_search::search_gebiet_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->gebiete);
			this->groupBox2->Controls->Add(this->search_gebiet);
			this->groupBox2->Location = System::Drawing::Point(12, 192);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(267, 49);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Gebiet";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->staedte);
			this->groupBox1->Controls->Add(this->search_stadt);
			this->groupBox1->Location = System::Drawing::Point(12, 137);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(267, 49);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Stadt";
			// 
			// staedte
			// 
			this->staedte->FormattingEnabled = true;
			this->staedte->ItemHeight = 13;
			this->staedte->Location = System::Drawing::Point(15, 19);
			this->staedte->Name = L"staedte";
			this->staedte->Size = System::Drawing::Size(178, 21);
			this->staedte->Sorted = true;
			this->staedte->TabIndex = 10;
			this->staedte->TextChanged += gcnew System::EventHandler(this, &bew_ztr_search::staedte_TextChanged);
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 332);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(170, 24);
			this->btn_close->TabIndex = 7;
			this->btn_close->Text = L"Zurück";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &bew_ztr_search::Close_Click);
			// 
			// search
			// 
			this->search->Location = System::Drawing::Point(12, 302);
			this->search->Name = L"search";
			this->search->Size = System::Drawing::Size(267, 24);
			this->search->TabIndex = 6;
			this->search->Text = L"Auswertung erstellen";
			this->search->UseVisualStyleBackColor = true;
			this->search->Click += gcnew System::EventHandler(this, &bew_ztr_search::search_Click);
			// 
			// rB_n_einger
			// 
			this->rB_n_einger->AutoSize = true;
			this->rB_n_einger->Checked = true;
			this->rB_n_einger->Location = System::Drawing::Point(6, 19);
			this->rB_n_einger->Name = L"rB_n_einger";
			this->rB_n_einger->Size = System::Drawing::Size(103, 17);
			this->rB_n_einger->TabIndex = 1;
			this->rB_n_einger->TabStop = true;
			this->rB_n_einger->Text = L"nicht eingereicht";
			this->rB_n_einger->UseVisualStyleBackColor = true;
			// 
			// rB_einger
			// 
			this->rB_einger->AutoSize = true;
			this->rB_einger->Location = System::Drawing::Point(6, 42);
			this->rB_einger->Name = L"rB_einger";
			this->rB_einger->Size = System::Drawing::Size(163, 17);
			this->rB_einger->TabIndex = 2;
			this->rB_einger->Text = L"eingereicht aber nicht geprüft";
			this->rB_einger->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->rB_n_einger);
			this->groupBox5->Controls->Add(this->rB_einger);
			this->groupBox5->Location = System::Drawing::Point(12, 12);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(267, 67);
			this->groupBox5->TabIndex = 1;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Verwendungsnachweis";
			// 
			// bew_ztr_search
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(290, 363);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->search);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"bew_ztr_search";
			this->Text = L"Verwendungsnachweis";
			this->Load += gcnew System::EventHandler(this, &bew_ztr_search::bew_ztr_search_Load);
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
		void bew_ztr_search_Load(System::Object^  sender, System::EventArgs^  e);
		void load_gebiet();
		void load_programm();

		// Buttons
		void search_Click(System::Object^  sender, System::EventArgs^  e);
		void Close_Click(System::Object^  sender, System::EventArgs^  e);

		// Events
		void bis_TextChanged(System::Object^  sender, System::EventArgs^  e);

		void staedte_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e); 
		void programme_TextChanged(System::Object^  sender, System::EventArgs^  e);

		void search_stadt_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_gebiet_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void search_programm_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
};
}
