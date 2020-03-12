#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Set_DB_path
	/// </summary>
	public ref class Set_DB_path : public System::Windows::Forms::Form
	{
	public:
		Set_DB_path(void)
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
		~Set_DB_path()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  tb_path;

	private: System::Windows::Forms::Button^  btn_search_path;
	private: System::Windows::Forms::Button^  btn_back;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Set_DB_path::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tb_path = (gcnew System::Windows::Forms::TextBox());
			this->btn_search_path = (gcnew System::Windows::Forms::Button());
			this->btn_back = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(233, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Bitte geben Sie den Pfad zu der Datenbank ein.";
			// 
			// tb_path
			// 
			this->tb_path->Location = System::Drawing::Point(18, 37);
			this->tb_path->Name = L"tb_path";
			this->tb_path->Size = System::Drawing::Size(379, 20);
			this->tb_path->TabIndex = 1;
			// 
			// btn_search_path
			// 
			this->btn_search_path->Location = System::Drawing::Point(403, 37);
			this->btn_search_path->Name = L"btn_search_path";
			this->btn_search_path->Size = System::Drawing::Size(25, 20);
			this->btn_search_path->TabIndex = 2;
			this->btn_search_path->Text = L"...";
			this->btn_search_path->UseVisualStyleBackColor = true;
			this->btn_search_path->Click += gcnew System::EventHandler(this, &Set_DB_path::btn_search_path_Click);
			// 
			// btn_back
			// 
			this->btn_back->Location = System::Drawing::Point(17, 72);
			this->btn_back->Name = L"btn_back";
			this->btn_back->Size = System::Drawing::Size(304, 23);
			this->btn_back->TabIndex = 3;
			this->btn_back->Text = L"Speichern";
			this->btn_back->UseVisualStyleBackColor = true;
			this->btn_back->Click += gcnew System::EventHandler(this, &Set_DB_path::btn_back_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(346, 77);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// Set_DB_path
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(441, 107);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->btn_back);
			this->Controls->Add(this->btn_search_path);
			this->Controls->Add(this->tb_path);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Set_DB_path";
			this->Text = L"Pfad zur Datenbank eintragen";
			this->Load += gcnew System::EventHandler(this, &Set_DB_path::Set_DB_path_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btn_search_path_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_back_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void Set_DB_path_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
