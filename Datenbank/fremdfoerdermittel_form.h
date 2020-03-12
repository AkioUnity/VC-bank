#pragma once

#include"fremdfoerderung_class.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für fremdfoerdermittel_form
	/// </summary>
	public ref class fremdfoerdermittel_form : public System::Windows::Forms::Form
	{
	public:
		fremdfoerdermittel_form(void):
			fremdfoerderung_(gcnew fremdfoerderung_class)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		fremdfoerdermittel_form(fremdfoerderung_class^ fremdfoerderung,bool vn_einger,bool load):
			fremdfoerderung_(fremdfoerderung),
			vn_einger_(vn_einger),
			load_(load)
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
		~fremdfoerdermittel_form()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private: fremdfoerderung_class^ fremdfoerderung_;
			 bool vn_einger_;
			 bool load_;

	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::ComboBox^  programme;
	private: System::Windows::Forms::TextBox^  betrag;


	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::ListBox^  fremdfoerderungen;


	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Button^  button2;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(fremdfoerdermittel_form::typeid));
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->programme = (gcnew System::Windows::Forms::ComboBox());
			this->betrag = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->fremdfoerderungen = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button12
			// 
			this->button12->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button12.Image")));
			this->button12->Location = System::Drawing::Point(203, 33);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(23, 23);
			this->button12->TabIndex = 3;
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &fremdfoerdermittel_form::button12_Click);
			// 
			// button13
			// 
			this->button13->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button13.Image")));
			this->button13->Location = System::Drawing::Point(232, 33);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(23, 23);
			this->button13->TabIndex = 4;
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &fremdfoerdermittel_form::button13_Click);
			// 
			// programme
			// 
			this->programme->FormattingEnabled = true;
			this->programme->Location = System::Drawing::Point(70, 6);
			this->programme->Name = L"programme";
			this->programme->Size = System::Drawing::Size(185, 21);
			this->programme->TabIndex = 1;
			this->programme->TextChanged += gcnew System::EventHandler(this, &fremdfoerdermittel_form::programme_TextChanged);
			// 
			// betrag
			// 
			this->betrag->Location = System::Drawing::Point(70, 36);
			this->betrag->Name = L"betrag";
			this->betrag->Size = System::Drawing::Size(127, 20);
			this->betrag->TabIndex = 2;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(15, 38);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(44, 13);
			this->label15->TabIndex = 53;
			this->label15->Text = L"Betrag :";
			// 
			// fremdfoerderungen
			// 
			this->fremdfoerderungen->FormattingEnabled = true;
			this->fremdfoerderungen->Location = System::Drawing::Point(15, 64);
			this->fremdfoerderungen->Name = L"fremdfoerderungen";
			this->fremdfoerderungen->Size = System::Drawing::Size(240, 69);
			this->fremdfoerderungen->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(52, 13);
			this->label1->TabIndex = 57;
			this->label1->Text = L"Program :";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(16, 139);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(147, 24);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Schließen";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &fremdfoerdermittel_form::button2_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(176, 147);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 58;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// fremdfoerdermittel_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(271, 169);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button13);
			this->Controls->Add(this->betrag);
			this->Controls->Add(this->programme);
			this->Controls->Add(this->fremdfoerderungen);
			this->Controls->Add(this->label15);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"fremdfoerdermittel_form";
			this->Text = L"Fremdfördermittel";
			this->Load += gcnew System::EventHandler(this, &fremdfoerdermittel_form::fremdfoerdermittel_form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void fremdfoerdermittel_form_Load(System::Object^  sender, System::EventArgs^  e);
		void load_fremdfoerderungen();
		void programme_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void button12_Click(System::Object^  sender, System::EventArgs^  e);
		void button13_Click(System::Object^  sender, System::EventArgs^  e);

	void button2_Click(System::Object^  sender, System::EventArgs^  e) {Close();}

};
}
