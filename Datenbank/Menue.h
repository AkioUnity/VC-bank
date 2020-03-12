#pragma once

#include "test.h"
namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void):
		  user_id_(-1)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	int user_id_;
	private: System::Windows::Forms::Button^  btn_close;
	private: System::Windows::Forms::Button^  btn_new_proj;
	private: System::Windows::Forms::Button^  btn_open_proj;
	private: System::Windows::Forms::Button^  btn_data_result;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Button^  btn_admin;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Button^  btn_options;
	private: System::Windows::Forms::Button^  btn_jahreszuteilung;



	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->btn_new_proj = (gcnew System::Windows::Forms::Button());
			this->btn_open_proj = (gcnew System::Windows::Forms::Button());
			this->btn_data_result = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btn_admin = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->btn_options = (gcnew System::Windows::Forms::Button());
			this->btn_jahreszuteilung = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 224);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(145, 25);
			this->btn_close->TabIndex = 6;
			this->btn_close->Text = L"Beenden";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &Form1::btn_close_Click);
			// 
			// btn_new_proj
			// 
			this->btn_new_proj->Location = System::Drawing::Point(12, 12);
			this->btn_new_proj->Name = L"btn_new_proj";
			this->btn_new_proj->Size = System::Drawing::Size(260, 28);
			this->btn_new_proj->TabIndex = 1;
			this->btn_new_proj->Text = L"neues Projekt";
			this->btn_new_proj->UseVisualStyleBackColor = true;
			this->btn_new_proj->Click += gcnew System::EventHandler(this, &Form1::btn_new_proj_Click);
			// 
			// btn_open_proj
			// 
			this->btn_open_proj->Location = System::Drawing::Point(12, 46);
			this->btn_open_proj->Name = L"btn_open_proj";
			this->btn_open_proj->Size = System::Drawing::Size(260, 28);
			this->btn_open_proj->TabIndex = 2;
			this->btn_open_proj->Text = L"Projekt öffnen";
			this->btn_open_proj->UseVisualStyleBackColor = true;
			this->btn_open_proj->Click += gcnew System::EventHandler(this, &Form1::btn_open_proj_Click);
			// 
			// btn_data_result
			// 
			this->btn_data_result->Location = System::Drawing::Point(12, 97);
			this->btn_data_result->Name = L"btn_data_result";
			this->btn_data_result->Size = System::Drawing::Size(260, 28);
			this->btn_data_result->TabIndex = 3;
			this->btn_data_result->Text = L"Auswertung";
			this->btn_data_result->UseVisualStyleBackColor = true;
			this->btn_data_result->Click += gcnew System::EventHandler(this, &Form1::btn_data_result_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 73);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(259, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"__________________________________________";
			// 
			// btn_admin
			// 
			this->btn_admin->Location = System::Drawing::Point(14, 188);
			this->btn_admin->Name = L"btn_admin";
			this->btn_admin->Size = System::Drawing::Size(260, 28);
			this->btn_admin->TabIndex = 5;
			this->btn_admin->Text = L"Administration";
			this->btn_admin->UseVisualStyleBackColor = true;
			this->btn_admin->Click += gcnew System::EventHandler(this, &Form1::btn_admin_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 127);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(259, 13);
			this->label2->TabIndex = 31;
			this->label2->Text = L"__________________________________________";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(191, 230);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// btn_options
			// 
			this->btn_options->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_options.Image")));
			this->btn_options->Location = System::Drawing::Point(163, 225);
			this->btn_options->Name = L"btn_options";
			this->btn_options->Size = System::Drawing::Size(23, 23);
			this->btn_options->TabIndex = 7;
			this->btn_options->UseVisualStyleBackColor = true;
			this->btn_options->Click += gcnew System::EventHandler(this, &Form1::btn_options_Click);
			// 
			// btn_jahreszuteilung
			// 
			this->btn_jahreszuteilung->Location = System::Drawing::Point(14, 154);
			this->btn_jahreszuteilung->Name = L"btn_jahreszuteilung";
			this->btn_jahreszuteilung->Size = System::Drawing::Size(260, 28);
			this->btn_jahreszuteilung->TabIndex = 4;
			this->btn_jahreszuteilung->Text = L"Jahreszuteilung";
			this->btn_jahreszuteilung->UseVisualStyleBackColor = true;
			this->btn_jahreszuteilung->Click += gcnew System::EventHandler(this, &Form1::btn_jahreszuteilung_Click);
			// 
			// Form1
			// 
			this->ClientSize = System::Drawing::Size(284, 258);
			this->Controls->Add(this->btn_jahreszuteilung);
			this->Controls->Add(this->btn_options);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btn_admin);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btn_data_result);
			this->Controls->Add(this->btn_open_proj);
			this->Controls->Add(this->btn_new_proj);
			this->Controls->Add(this->btn_close);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"Menü";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Form - Konstruktor
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);

	// Projektbuttons
	private: System::Void btn_new_proj_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_open_proj_Click(System::Object^  sender, System::EventArgs^  e);

	// Beenden
	private: System::Void btn_close_Click(System::Object^  sender, System::EventArgs^  e);

	// Admin
	private: System::Void btn_admin_Click(System::Object^  sender, System::EventArgs^  e);

	// Prüfen ob Datenbank Pfad gesetzt ist
	private: void check_for_DB_path();

	// Auswertung
	private: void btn_data_result_Click(System::Object^  sender, System::EventArgs^  e);

	// Passwort ändern
	void btn_options_Click(System::Object^  sender, System::EventArgs^  e);

	// Jahresauswertung
	void btn_jahreszuteilung_Click(System::Object^  sender, System::EventArgs^  e);
};
}
