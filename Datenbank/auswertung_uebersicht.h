#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für auswertung_uebersicht
	/// </summary>
	public ref class auswertung_uebersicht : public System::Windows::Forms::Form
	{
	public:
		auswertung_uebersicht(int user_id):
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
		~auswertung_uebersicht()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_jahr;
		int user_id_;
	private: System::Windows::Forms::Button^  btn_kostengr;
	private: System::Windows::Forms::Button^  btn_adress;
	private: System::Windows::Forms::Button^  btn_gesamt;
	private: System::Windows::Forms::Button^  btn_close;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Button^  bew_ztr;

	protected: 






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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(auswertung_uebersicht::typeid));
			this->btn_jahr = (gcnew System::Windows::Forms::Button());
			this->btn_kostengr = (gcnew System::Windows::Forms::Button());
			this->btn_adress = (gcnew System::Windows::Forms::Button());
			this->btn_gesamt = (gcnew System::Windows::Forms::Button());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->bew_ztr = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_jahr
			// 
			this->btn_jahr->Location = System::Drawing::Point(12, 12);
			this->btn_jahr->Name = L"btn_jahr";
			this->btn_jahr->Size = System::Drawing::Size(255, 24);
			this->btn_jahr->TabIndex = 0;
			this->btn_jahr->Text = L"Jahresübersicht";
			this->btn_jahr->UseVisualStyleBackColor = true;
			this->btn_jahr->Click += gcnew System::EventHandler(this, &auswertung_uebersicht::btn_jahr_Click);
			// 
			// btn_kostengr
			// 
			this->btn_kostengr->Location = System::Drawing::Point(12, 72);
			this->btn_kostengr->Name = L"btn_kostengr";
			this->btn_kostengr->Size = System::Drawing::Size(255, 24);
			this->btn_kostengr->TabIndex = 2;
			this->btn_kostengr->Text = L"Kostengruppenübersicht";
			this->btn_kostengr->UseVisualStyleBackColor = true;
			this->btn_kostengr->Click += gcnew System::EventHandler(this, &auswertung_uebersicht::btn_kostengr_Click);
			// 
			// btn_adress
			// 
			this->btn_adress->Location = System::Drawing::Point(12, 102);
			this->btn_adress->Name = L"btn_adress";
			this->btn_adress->Size = System::Drawing::Size(255, 24);
			this->btn_adress->TabIndex = 3;
			this->btn_adress->Text = L"Adressübersicht";
			this->btn_adress->UseVisualStyleBackColor = true;
			this->btn_adress->Click += gcnew System::EventHandler(this, &auswertung_uebersicht::btn_adress_Click);
			// 
			// btn_gesamt
			// 
			this->btn_gesamt->Location = System::Drawing::Point(12, 132);
			this->btn_gesamt->Name = L"btn_gesamt";
			this->btn_gesamt->Size = System::Drawing::Size(255, 24);
			this->btn_gesamt->TabIndex = 4;
			this->btn_gesamt->Text = L"Gesamtübersicht";
			this->btn_gesamt->UseVisualStyleBackColor = true;
			this->btn_gesamt->Click += gcnew System::EventHandler(this, &auswertung_uebersicht::btn_gesamt_Click);
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(12, 171);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(163, 24);
			this->btn_close->TabIndex = 5;
			this->btn_close->Text = L"Zurück";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &auswertung_uebersicht::btn_close_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(184, 177);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// bew_ztr
			// 
			this->bew_ztr->Location = System::Drawing::Point(12, 42);
			this->bew_ztr->Name = L"bew_ztr";
			this->bew_ztr->Size = System::Drawing::Size(255, 24);
			this->bew_ztr->TabIndex = 1;
			this->bew_ztr->Text = L"Übersicht Verwendungsnachweis";
			this->bew_ztr->UseVisualStyleBackColor = true;
			this->bew_ztr->Click += gcnew System::EventHandler(this, &auswertung_uebersicht::bew_ztr_Click);
			// 
			// auswertung_uebersicht
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(279, 205);
			this->Controls->Add(this->bew_ztr);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->btn_gesamt);
			this->Controls->Add(this->btn_adress);
			this->Controls->Add(this->btn_kostengr);
			this->Controls->Add(this->btn_jahr);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"auswertung_uebersicht";
			this->Text = L"Auswahl der Übersicht";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void btn_jahr_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_kostengr_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_adress_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_gesamt_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
		void bew_ztr_Click(System::Object^  sender, System::EventArgs^  e);
};
}
