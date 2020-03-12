#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für login
	/// </summary>
	public ref class login : public System::Windows::Forms::Form
	{
	public:
		login(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		login(System::Windows::Forms::Label^ cache):
			cache_(cache)
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
		~login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  name;
		System::Windows::Forms::Label^ cache_;

	protected: 

	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  password;
	private: System::Windows::Forms::Button^  btn_login;
	private: System::Windows::Forms::Button^  btn_close;




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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(login::typeid));
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->btn_login = (gcnew System::Windows::Forms::Button());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// name
			// 
			this->name->Location = System::Drawing::Point(104, 14);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(234, 20);
			this->name->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Name :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Passwort :";
			// 
			// password
			// 
			this->password->Location = System::Drawing::Point(104, 40);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(234, 20);
			this->password->TabIndex = 2;
			this->password->UseSystemPasswordChar = true;
			// 
			// btn_login
			// 
			this->btn_login->Location = System::Drawing::Point(20, 68);
			this->btn_login->Name = L"btn_login";
			this->btn_login->Size = System::Drawing::Size(317, 23);
			this->btn_login->TabIndex = 4;
			this->btn_login->Text = L"Login";
			this->btn_login->UseVisualStyleBackColor = true;
			this->btn_login->Click += gcnew System::EventHandler(this, &login::btn_login_Click);
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(20, 97);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(317, 23);
			this->btn_close->TabIndex = 5;
			this->btn_close->Text = L"Beenden";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &login::btn_close_Click);
			// 
			// login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(359, 126);
			this->Controls->Add(this->btn_close);
			this->Controls->Add(this->btn_login);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->password);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->name);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"login";
			this->Text = L"Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: 
	void btn_login_Click(System::Object^  sender, System::EventArgs^  e);
	void btn_close_Click(System::Object^  sender, System::EventArgs^  e);
};
}
