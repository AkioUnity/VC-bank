#pragma once
#include "bewilligung_class.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für bewilligung_form
	/// </summary>
	public ref class bewilligung_form : public System::Windows::Forms::Form
	{
	public:
		bewilligung_form(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		bewilligung_form(bewilligung_class^ bewilligung,bool vn_einger,bool load):
			bewilligung_(bewilligung),
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
		~bewilligung_form()
		{
			if (components)
			{
				delete components;
			}
		}

	private: bewilligung_class^ bewilligung_;
	private: bool vn_einger_;
			 bool load_;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  nr_part1;
	protected: 
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  nr_part2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  vom;
	private: System::Windows::Forms::Button^  btn_back;
	private: System::Drawing::Printing::PrintDocument^  printDocument1;
	private: System::Windows::Forms::ComboBox^  nr_part3;

	private: System::Windows::Forms::TextBox^  mla;
	private: System::Windows::Forms::TextBox^  bund_land;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::CheckBox^  san_bed_ein;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(bewilligung_form::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->nr_part1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->nr_part2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->vom = (gcnew System::Windows::Forms::TextBox());
			this->btn_back = (gcnew System::Windows::Forms::Button());
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->nr_part3 = (gcnew System::Windows::Forms::ComboBox());
			this->mla = (gcnew System::Windows::Forms::TextBox());
			this->bund_land = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->san_bed_ein = (gcnew System::Windows::Forms::CheckBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Bewilligungs Nr.:";
			// 
			// nr_part1
			// 
			this->nr_part1->AutoSize = true;
			this->nr_part1->Location = System::Drawing::Point(103, 9);
			this->nr_part1->Name = L"nr_part1";
			this->nr_part1->Size = System::Drawing::Size(35, 13);
			this->nr_part1->TabIndex = 1;
			this->nr_part1->Text = L"XXXX";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(144, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(10, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"-";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(217, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(12, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"/";
			// 
			// nr_part2
			// 
			this->nr_part2->Location = System::Drawing::Point(160, 6);
			this->nr_part2->Name = L"nr_part2";
			this->nr_part2->Size = System::Drawing::Size(51, 20);
			this->nr_part2->TabIndex = 1;
			this->nr_part2->TextChanged += gcnew System::EventHandler(this, &bewilligung_form::nr_part2_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(64, 33);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(33, 13);
			this->label6->TabIndex = 6;
			this->label6->Text = L"vom :";
			// 
			// vom
			// 
			this->vom->Location = System::Drawing::Point(106, 30);
			this->vom->Name = L"vom";
			this->vom->Size = System::Drawing::Size(170, 20);
			this->vom->TabIndex = 3;
			this->vom->TextChanged += gcnew System::EventHandler(this, &bewilligung_form::vom_TextChanged);
			this->vom->Leave += gcnew System::EventHandler(this, &bewilligung_form::vom_Leave);
			// 
			// btn_back
			// 
			this->btn_back->Location = System::Drawing::Point(15, 127);
			this->btn_back->Name = L"btn_back";
			this->btn_back->Size = System::Drawing::Size(174, 22);
			this->btn_back->TabIndex = 6;
			this->btn_back->Text = L"Schließen";
			this->btn_back->UseVisualStyleBackColor = true;
			this->btn_back->Click += gcnew System::EventHandler(this, &bewilligung_form::btn_back_Click);
			// 
			// nr_part3
			// 
			this->nr_part3->FormattingEnabled = true;
			this->nr_part3->Location = System::Drawing::Point(235, 5);
			this->nr_part3->Name = L"nr_part3";
			this->nr_part3->Size = System::Drawing::Size(40, 21);
			this->nr_part3->TabIndex = 2;
			this->nr_part3->TextChanged += gcnew System::EventHandler(this, &bewilligung_form::nr_part3_TextChanged);
			// 
			// mla
			// 
			this->mla->Location = System::Drawing::Point(106, 82);
			this->mla->Name = L"mla";
			this->mla->Size = System::Drawing::Size(169, 20);
			this->mla->TabIndex = 5;
			this->mla->TextChanged += gcnew System::EventHandler(this, &bewilligung_form::mla_TextChanged);
			this->mla->Leave += gcnew System::EventHandler(this, &bewilligung_form::mla_Leave);
			// 
			// bund_land
			// 
			this->bund_land->Location = System::Drawing::Point(106, 56);
			this->bund_land->Name = L"bund_land";
			this->bund_land->Size = System::Drawing::Size(169, 20);
			this->bund_land->TabIndex = 4;
			this->bund_land->TextChanged += gcnew System::EventHandler(this, &bewilligung_form::bund_land_TextChanged);
			this->bund_land->Leave += gcnew System::EventHandler(this, &bewilligung_form::bund_land_Leave);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(17, 85);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(83, 13);
			this->label8->TabIndex = 32;
			this->label8->Text = L"MLA Gemeinde:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(33, 59);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(67, 13);
			this->label7->TabIndex = 31;
			this->label7->Text = L"Bund/Land :";
			// 
			// san_bed_ein
			// 
			this->san_bed_ein->AutoSize = true;
			this->san_bed_ein->Location = System::Drawing::Point(108, 105);
			this->san_bed_ein->Name = L"san_bed_ein";
			this->san_bed_ein->Size = System::Drawing::Size(174, 17);
			this->san_bed_ein->TabIndex = 33;
			this->san_bed_ein->Text = L"sanierungsbedingte Einnahmen";
			this->san_bed_ein->UseVisualStyleBackColor = true;
			this->san_bed_ein->CheckedChanged += gcnew System::EventHandler(this, &bewilligung_form::san_bed_ein_CheckedChanged);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(195, 132);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// bewilligung_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(290, 163);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->san_bed_ein);
			this->Controls->Add(this->mla);
			this->Controls->Add(this->bund_land);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->nr_part3);
			this->Controls->Add(this->btn_back);
			this->Controls->Add(this->vom);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->nr_part2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->nr_part1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"bewilligung_form";
			this->Text = L"Bewilligung";
			this->Load += gcnew System::EventHandler(this, &bewilligung_form::bewilligung_form_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		void bewilligung_form_Load(System::Object^  sender, System::EventArgs^  e);
		void show_bewilligung();

		void nr_part2_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void nr_part3_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void vom_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void vom_Leave(System::Object^  sender, System::EventArgs^  e);
		void bund_land_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void mla_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void btn_back_Click(System::Object^  sender, System::EventArgs^  e);
		void san_bed_ein_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void bund_land_Leave(System::Object^  sender, System::EventArgs^  e);
		void mla_Leave(System::Object^  sender, System::EventArgs^  e);
};
}
