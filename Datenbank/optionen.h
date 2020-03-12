#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für optionen
	/// </summary>
	public ref class optionen : public System::Windows::Forms::Form
	{
	public:
		optionen(int user_id):
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
		~optionen()
		{
			if (components)
			{
				delete components;
			}
		}


	protected: 
	private: System::Windows::Forms::Button^  btn_close;
	private: System::Windows::Forms::Button^  btn_change_password;
	private: System::Windows::Forms::TextBox^  tB_new_pw2;
	private: System::Windows::Forms::TextBox^  tB_new_pw1;
	private: System::Windows::Forms::TextBox^  tB_old_pw;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
		int user_id_;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(optionen::typeid));
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->btn_change_password = (gcnew System::Windows::Forms::Button());
			this->tB_new_pw2 = (gcnew System::Windows::Forms::TextBox());
			this->tB_new_pw1 = (gcnew System::Windows::Forms::TextBox());
			this->tB_old_pw = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(9, 118);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(320, 20);
			this->btn_close->TabIndex = 2;
			this->btn_close->Text = L"Fenster Schließen";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &optionen::btn_close_Click);
			// 
			// btn_change_password
			// 
			this->btn_change_password->Location = System::Drawing::Point(9, 90);
			this->btn_change_password->Name = L"btn_change_password";
			this->btn_change_password->Size = System::Drawing::Size(320, 22);
			this->btn_change_password->TabIndex = 13;
			this->btn_change_password->Text = L"Password ändern";
			this->btn_change_password->UseVisualStyleBackColor = true;
			this->btn_change_password->Click += gcnew System::EventHandler(this, &optionen::btn_change_password_Click);
			// 
			// tB_new_pw2
			// 
			this->tB_new_pw2->Location = System::Drawing::Point(116, 64);
			this->tB_new_pw2->Name = L"tB_new_pw2";
			this->tB_new_pw2->Size = System::Drawing::Size(213, 20);
			this->tB_new_pw2->TabIndex = 12;
			this->tB_new_pw2->UseSystemPasswordChar = true;
			// 
			// tB_new_pw1
			// 
			this->tB_new_pw1->Location = System::Drawing::Point(116, 38);
			this->tB_new_pw1->Name = L"tB_new_pw1";
			this->tB_new_pw1->Size = System::Drawing::Size(213, 20);
			this->tB_new_pw1->TabIndex = 11;
			this->tB_new_pw1->UseSystemPasswordChar = true;
			// 
			// tB_old_pw
			// 
			this->tB_old_pw->Location = System::Drawing::Point(116, 12);
			this->tB_old_pw->Name = L"tB_old_pw";
			this->tB_old_pw->Size = System::Drawing::Size(213, 20);
			this->tB_old_pw->TabIndex = 10;
			this->tB_old_pw->UseSystemPasswordChar = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 67);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(108, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Passwort bestätigen :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"neues Passwort :";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(81, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"altes Passwort :";
			// 
			// optionen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(340, 146);
			this->Controls->Add(this->btn_change_password);
			this->Controls->Add(this->tB_new_pw2);
			this->Controls->Add(this->tB_new_pw1);
			this->Controls->Add(this->tB_old_pw);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btn_close);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"optionen";
			this->Text = L"Password ändern";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_change_password_Click(System::Object^  sender, System::EventArgs^  e);
};
}
