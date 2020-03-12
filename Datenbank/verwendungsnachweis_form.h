#pragma once

#include "project_class.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für verwendungsnachweis_form
	/// </summary>
	public ref class verwendungsnachweis_form : public System::Windows::Forms::Form
	{
	public:
		verwendungsnachweis_form(void):
			projekt_(gcnew project_class())
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		verwendungsnachweis_form(project_class^ projekt,bool load):
			projekt_(projekt),
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
		~verwendungsnachweis_form()
		{
			if (components)
			{
				delete components;
			}
		}

	private: project_class^ projekt_;
		bool load_;

	protected: 
	private: System::Windows::Forms::Button^  back;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Label^  summe_ef;
	private: System::Windows::Forms::Label^  summe_egk;
	private: System::Windows::Forms::Label^  l_summe_ausgaben;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  l_gk_aus;
	private: System::Windows::Forms::Label^  l_gk_ein;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  l_gf_aus;
	private: System::Windows::Forms::Label^  l_gf_ein;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label19;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(verwendungsnachweis_form::typeid));
			this->back = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->summe_ef = (gcnew System::Windows::Forms::Label());
			this->summe_egk = (gcnew System::Windows::Forms::Label());
			this->l_summe_ausgaben = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->l_gk_aus = (gcnew System::Windows::Forms::Label());
			this->l_gk_ein = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->l_gf_aus = (gcnew System::Windows::Forms::Label());
			this->l_gf_ein = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// back
			// 
			this->back->Location = System::Drawing::Point(258, 369);
			this->back->Name = L"back";
			this->back->Size = System::Drawing::Size(237, 22);
			this->back->TabIndex = 2;
			this->back->Text = L"Zurück";
			this->back->UseVisualStyleBackColor = true;
			this->back->Click += gcnew System::EventHandler(this, &verwendungsnachweis_form::back_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(729, 340);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage3
			// 
			this->tabPage3->AutoScroll = true;
			this->tabPage3->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(721, 314);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Bewilligungen";
			// 
			// tabPage1
			// 
			this->tabPage1->AutoScroll = true;
			this->tabPage1->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(721, 314);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Einnahmen";
			// 
			// tabPage2
			// 
			this->tabPage2->AutoScroll = true;
			this->tabPage2->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage2->Controls->Add(this->summe_ef);
			this->tabPage2->Controls->Add(this->summe_egk);
			this->tabPage2->Controls->Add(this->l_summe_ausgaben);
			this->tabPage2->Controls->Add(this->label18);
			this->tabPage2->Controls->Add(this->label17);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(721, 314);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Ausgaben";
			// 
			// summe_ef
			// 
			this->summe_ef->AutoSize = true;
			this->summe_ef->Location = System::Drawing::Point(375, 220);
			this->summe_ef->Name = L"summe_ef";
			this->summe_ef->Size = System::Drawing::Size(70, 13);
			this->summe_ef->TabIndex = 7;
			this->summe_ef->Text = L"Summen _EF";
			// 
			// summe_egk
			// 
			this->summe_egk->AutoSize = true;
			this->summe_egk->Location = System::Drawing::Point(175, 220);
			this->summe_egk->Name = L"summe_egk";
			this->summe_egk->Size = System::Drawing::Size(79, 13);
			this->summe_egk->TabIndex = 6;
			this->summe_egk->Text = L"Summen _EGK";
			// 
			// l_summe_ausgaben
			// 
			this->l_summe_ausgaben->AutoSize = true;
			this->l_summe_ausgaben->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->l_summe_ausgaben->Location = System::Drawing::Point(5, 220);
			this->l_summe_ausgaben->Name = L"l_summe_ausgaben";
			this->l_summe_ausgaben->Size = System::Drawing::Size(54, 13);
			this->l_summe_ausgaben->TabIndex = 5;
			this->l_summe_ausgaben->Text = L"Summen";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(375, 5);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(95, 13);
			this->label18->TabIndex = 4;
			this->label18->Text = L"Einzelförderung";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(175, 5);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(119, 13);
			this->label17->TabIndex = 3;
			this->label17->Text = L"Einzelgesamtkosten";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->l_gk_aus);
			this->groupBox1->Controls->Add(this->l_gk_ein);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 358);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(240, 59);
			this->groupBox1->TabIndex = 32;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Gesamtkosten";
			// 
			// l_gk_aus
			// 
			this->l_gk_aus->AutoSize = true;
			this->l_gk_aus->Location = System::Drawing::Point(78, 33);
			this->l_gk_aus->Name = L"l_gk_aus";
			this->l_gk_aus->Size = System::Drawing::Size(13, 13);
			this->l_gk_aus->TabIndex = 37;
			this->l_gk_aus->Text = L"0";
			// 
			// l_gk_ein
			// 
			this->l_gk_ein->AutoSize = true;
			this->l_gk_ein->Location = System::Drawing::Point(78, 16);
			this->l_gk_ein->Name = L"l_gk_ein";
			this->l_gk_ein->Size = System::Drawing::Size(13, 13);
			this->l_gk_ein->TabIndex = 36;
			this->l_gk_ein->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 13);
			this->label2->TabIndex = 35;
			this->label2->Text = L"Ausgaben :";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(66, 13);
			this->label1->TabIndex = 34;
			this->label1->Text = L"Einnahmen :";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->l_gf_aus);
			this->groupBox2->Controls->Add(this->l_gf_ein);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Location = System::Drawing::Point(501, 358);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(240, 59);
			this->groupBox2->TabIndex = 33;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Gesamtförderung";
			// 
			// l_gf_aus
			// 
			this->l_gf_aus->AutoSize = true;
			this->l_gf_aus->Location = System::Drawing::Point(78, 33);
			this->l_gf_aus->Name = L"l_gf_aus";
			this->l_gf_aus->Size = System::Drawing::Size(13, 13);
			this->l_gf_aus->TabIndex = 41;
			this->l_gf_aus->Text = L"0";
			// 
			// l_gf_ein
			// 
			this->l_gf_ein->AutoSize = true;
			this->l_gf_ein->Location = System::Drawing::Point(78, 16);
			this->l_gf_ein->Name = L"l_gf_ein";
			this->l_gf_ein->Size = System::Drawing::Size(13, 13);
			this->l_gf_ein->TabIndex = 40;
			this->l_gf_ein->Text = L"0";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 33);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(61, 13);
			this->label7->TabIndex = 39;
			this->label7->Text = L"Ausgaben :";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 16);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(66, 13);
			this->label8->TabIndex = 38;
			this->label8->Text = L"Einnahmen :";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(258, 394);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// verwendungsnachweis_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(753, 426);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->back);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"verwendungsnachweis_form";
			this->Text = L"Verwendungsnachweis";
			this->Load += gcnew System::EventHandler(this, &verwendungsnachweis_form::verwendungsnachweis_form_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void verwendungsnachweis_form_Load(System::Object^  sender, System::EventArgs^  e);
		void load_einnahmen();
		void load_ausgaben();
		void load_bewilligung();

		void aktualisiere();
		
		void tB_summe_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void tB_summe_Leave(System::Object^  sender, System::EventArgs^  e);
		void tB_zuwendungsf_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void tB_zuwendungsf_Leave(System::Object^  sender, System::EventArgs^  e);

		void TextChanged(System::Object^  sender, System::EventArgs^  e);
		void Leave(System::Object^  sender, System::EventArgs^  e);
		void AdrChanged(System::Object^  sender, System::EventArgs^  e);
		void AdrLeave(System::Object^  sender, System::EventArgs^  e);

		String^ reverse(String^);

		void back_Click(System::Object^  sender, System::EventArgs^  e);		
		void btn_ff_Click(System::Object^  sender, System::EventArgs^  e);
};
}
