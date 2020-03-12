#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für jahreszuteilung
	/// </summary>
	public ref class jahreszuteilung : public System::Windows::Forms::Form
	{
	public:
		jahreszuteilung(int user_id):
			jh_id_(gcnew List<String^>),
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
		~jahreszuteilung()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  jh_summe;
		List<String^>^ jh_id_;
		int user_id_;
	protected: 
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  jh_datum;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::ComboBox^  jh_jahr;
	private: System::Windows::Forms::Button^  del_jh;
	private: System::Windows::Forms::Button^  add_jh;
	private: System::Windows::Forms::TextBox^  jh_grund;
	private: System::Windows::Forms::TextBox^  jh_betrag;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::ListBox^  haushalte;
	private: System::Windows::Forms::ComboBox^  jh_gebiet;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  jh_stadt;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ComboBox^  jh_programm;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  btn_back;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(jahreszuteilung::typeid));
			this->jh_summe = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->jh_datum = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->jh_jahr = (gcnew System::Windows::Forms::ComboBox());
			this->del_jh = (gcnew System::Windows::Forms::Button());
			this->add_jh = (gcnew System::Windows::Forms::Button());
			this->jh_grund = (gcnew System::Windows::Forms::TextBox());
			this->jh_betrag = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->haushalte = (gcnew System::Windows::Forms::ListBox());
			this->jh_gebiet = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->jh_stadt = (gcnew System::Windows::Forms::ComboBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->jh_programm = (gcnew System::Windows::Forms::ComboBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btn_back = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// jh_summe
			// 
			this->jh_summe->AutoSize = true;
			this->jh_summe->Location = System::Drawing::Point(62, 196);
			this->jh_summe->Name = L"jh_summe";
			this->jh_summe->Size = System::Drawing::Size(0, 13);
			this->jh_summe->TabIndex = 72;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(8, 196);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(48, 13);
			this->label17->TabIndex = 71;
			this->label17->Text = L"Summe :";
			// 
			// jh_datum
			// 
			this->jh_datum->Location = System::Drawing::Point(233, 220);
			this->jh_datum->Name = L"jh_datum";
			this->jh_datum->Size = System::Drawing::Size(137, 20);
			this->jh_datum->TabIndex = 62;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(183, 223);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(44, 13);
			this->label16->TabIndex = 70;
			this->label16->Text = L"Datum :";
			// 
			// jh_jahr
			// 
			this->jh_jahr->FormattingEnabled = true;
			this->jh_jahr->Location = System::Drawing::Point(319, 66);
			this->jh_jahr->Name = L"jh_jahr";
			this->jh_jahr->Size = System::Drawing::Size(51, 21);
			this->jh_jahr->TabIndex = 58;
			this->jh_jahr->TextChanged += gcnew System::EventHandler(this, &jahreszuteilung::jh_jahr_TextChanged);
			// 
			// del_jh
			// 
			this->del_jh->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"del_jh.Image")));
			this->del_jh->Location = System::Drawing::Point(347, 186);
			this->del_jh->Name = L"del_jh";
			this->del_jh->Size = System::Drawing::Size(23, 23);
			this->del_jh->TabIndex = 60;
			this->del_jh->UseVisualStyleBackColor = true;
			this->del_jh->Click += gcnew System::EventHandler(this, &jahreszuteilung::del_jh_Click);
			// 
			// add_jh
			// 
			this->add_jh->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"add_jh.Image")));
			this->add_jh->Location = System::Drawing::Point(319, 186);
			this->add_jh->Name = L"add_jh";
			this->add_jh->Size = System::Drawing::Size(23, 23);
			this->add_jh->TabIndex = 64;
			this->add_jh->UseVisualStyleBackColor = true;
			this->add_jh->Click += gcnew System::EventHandler(this, &jahreszuteilung::add_jh_Click);
			// 
			// jh_grund
			// 
			this->jh_grund->Location = System::Drawing::Point(56, 248);
			this->jh_grund->Name = L"jh_grund";
			this->jh_grund->Size = System::Drawing::Size(314, 20);
			this->jh_grund->TabIndex = 63;
			// 
			// jh_betrag
			// 
			this->jh_betrag->Location = System::Drawing::Point(56, 220);
			this->jh_betrag->Name = L"jh_betrag";
			this->jh_betrag->Size = System::Drawing::Size(121, 20);
			this->jh_betrag->TabIndex = 61;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(6, 251);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(42, 13);
			this->label15->TabIndex = 69;
			this->label15->Text = L"Grund :";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 223);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(44, 13);
			this->label14->TabIndex = 68;
			this->label14->Text = L"Betrag :";
			// 
			// haushalte
			// 
			this->haushalte->FormattingEnabled = true;
			this->haushalte->Location = System::Drawing::Point(10, 97);
			this->haushalte->Name = L"haushalte";
			this->haushalte->Size = System::Drawing::Size(360, 82);
			this->haushalte->TabIndex = 59;
			// 
			// jh_gebiet
			// 
			this->jh_gebiet->FormattingEnabled = true;
			this->jh_gebiet->Location = System::Drawing::Point(79, 39);
			this->jh_gebiet->Name = L"jh_gebiet";
			this->jh_gebiet->Size = System::Drawing::Size(291, 21);
			this->jh_gebiet->Sorted = true;
			this->jh_gebiet->TabIndex = 56;
			this->jh_gebiet->TextChanged += gcnew System::EventHandler(this, &jahreszuteilung::jh_gebiet_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(8, 42);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(44, 13);
			this->label5->TabIndex = 67;
			this->label5->Text = L"Gebiet :";
			// 
			// jh_stadt
			// 
			this->jh_stadt->FormattingEnabled = true;
			this->jh_stadt->Location = System::Drawing::Point(79, 12);
			this->jh_stadt->Name = L"jh_stadt";
			this->jh_stadt->Size = System::Drawing::Size(291, 21);
			this->jh_stadt->Sorted = true;
			this->jh_stadt->TabIndex = 55;
			this->jh_stadt->TextChanged += gcnew System::EventHandler(this, &jahreszuteilung::jh_stadt_TextChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(8, 15);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(38, 13);
			this->label9->TabIndex = 66;
			this->label9->Text = L"Stadt :";
			// 
			// jh_programm
			// 
			this->jh_programm->FormattingEnabled = true;
			this->jh_programm->Location = System::Drawing::Point(79, 66);
			this->jh_programm->Name = L"jh_programm";
			this->jh_programm->Size = System::Drawing::Size(237, 21);
			this->jh_programm->Sorted = true;
			this->jh_programm->TabIndex = 57;
			this->jh_programm->TextChanged += gcnew System::EventHandler(this, &jahreszuteilung::jh_programm_TextChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(8, 69);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(60, 13);
			this->label12->TabIndex = 65;
			this->label12->Text = L"Programm :";
			// 
			// btn_back
			// 
			this->btn_back->Location = System::Drawing::Point(10, 279);
			this->btn_back->Name = L"btn_back";
			this->btn_back->Size = System::Drawing::Size(359, 24);
			this->btn_back->TabIndex = 73;
			this->btn_back->Text = L"Schließen";
			this->btn_back->UseVisualStyleBackColor = true;
			this->btn_back->Click += gcnew System::EventHandler(this, &jahreszuteilung::btn_back_Click);
			// 
			// jahreszuteilung
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(379, 316);
			this->Controls->Add(this->btn_back);
			this->Controls->Add(this->jh_summe);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->jh_datum);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->jh_jahr);
			this->Controls->Add(this->del_jh);
			this->Controls->Add(this->add_jh);
			this->Controls->Add(this->jh_grund);
			this->Controls->Add(this->jh_betrag);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->haushalte);
			this->Controls->Add(this->jh_gebiet);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->jh_stadt);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->jh_programm);
			this->Controls->Add(this->label12);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"jahreszuteilung";
			this->Text = L"Jahreszuteilung";
			this->Load += gcnew System::EventHandler(this, &jahreszuteilung::jahreszuteilung_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void jahreszuteilung_Load(System::Object^  sender, System::EventArgs^  e);

		bool load_stadt();
		bool load_gebiet();
		void load_programm();
		void load_jahr();
		void load_jh();

		void jh_stadt_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void jh_gebiet_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void jh_programm_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void jh_jahr_TextChanged(System::Object^  sender, System::EventArgs^  e);

		void add_jh_Click(System::Object^  sender, System::EventArgs^  e);
		void del_jh_Click(System::Object^  sender, System::EventArgs^  e);

		void btn_back_Click(System::Object^  sender, System::EventArgs^  e);

		bool is_existent_in(List<String^>^ liste,String^ value);
};
}
