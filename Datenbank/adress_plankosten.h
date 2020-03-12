#pragma once

#include "adresse.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für adress_plankosten
	/// </summary>
	public ref class adress_plankosten : public System::Windows::Forms::Form
	{
	public:
		adress_plankosten(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		adress_plankosten(adresse^ adr,bool vn_einger,bool load):
			adr_(adr),
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
		~adress_plankosten()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  l_Adresse;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tB_kosten;
	private: System::Windows::Forms::TextBox^  tB_foerder;
	private: System::Windows::Forms::Button^  btn_back;

		adresse^ adr_;
		bool vn_einger_;
		bool load_;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(adress_plankosten::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->l_Adresse = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tB_kosten = (gcnew System::Windows::Forms::TextBox());
			this->tB_foerder = (gcnew System::Windows::Forms::TextBox());
			this->btn_back = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Adresse :";
			// 
			// l_Adresse
			// 
			this->l_Adresse->AutoSize = true;
			this->l_Adresse->Location = System::Drawing::Point(71, 16);
			this->l_Adresse->Name = L"l_Adresse";
			this->l_Adresse->Size = System::Drawing::Size(58, 13);
			this->l_Adresse->TabIndex = 1;
			this->l_Adresse->Text = L"ADRESSE";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(14, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Kosten :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(14, 68);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(61, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Förderung :";
			// 
			// tB_kosten
			// 
			this->tB_kosten->Location = System::Drawing::Point(74, 39);
			this->tB_kosten->Name = L"tB_kosten";
			this->tB_kosten->Size = System::Drawing::Size(191, 20);
			this->tB_kosten->TabIndex = 4;
			this->tB_kosten->TextChanged += gcnew System::EventHandler(this, &adress_plankosten::tB_kosten_TextChanged);
			this->tB_kosten->Leave += gcnew System::EventHandler(this, &adress_plankosten::tB_kosten_Leave);
			// 
			// tB_foerder
			// 
			this->tB_foerder->Location = System::Drawing::Point(74, 65);
			this->tB_foerder->Name = L"tB_foerder";
			this->tB_foerder->Size = System::Drawing::Size(191, 20);
			this->tB_foerder->TabIndex = 5;
			this->tB_foerder->TextChanged += gcnew System::EventHandler(this, &adress_plankosten::tB_foerder_TextChanged);
			this->tB_foerder->Leave += gcnew System::EventHandler(this, &adress_plankosten::tB_foerder_Leave);
			// 
			// btn_back
			// 
			this->btn_back->Location = System::Drawing::Point(12, 95);
			this->btn_back->Name = L"btn_back";
			this->btn_back->Size = System::Drawing::Size(160, 21);
			this->btn_back->TabIndex = 6;
			this->btn_back->Text = L"Zurück";
			this->btn_back->UseVisualStyleBackColor = true;
			this->btn_back->Click += gcnew System::EventHandler(this, &adress_plankosten::btn_back_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(195, 99);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// adress_plankosten
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(280, 124);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->btn_back);
			this->Controls->Add(this->tB_foerder);
			this->Controls->Add(this->tB_kosten);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->l_Adresse);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"adress_plankosten";
			this->Text = L"Plankosten Adresse";
			this->Load += gcnew System::EventHandler(this, &adress_plankosten::adress_plankosten_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void adress_plankosten_Load(System::Object^  sender, System::EventArgs^  e);

		// TextChange
		void tB_kosten_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void tB_kosten_Leave(System::Object^  sender, System::EventArgs^  e);

		void tB_foerder_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void tB_foerder_Leave(System::Object^  sender, System::EventArgs^  e);

		// Buttons
		void btn_back_Click(System::Object^  sender, System::EventArgs^  e);
};
}
