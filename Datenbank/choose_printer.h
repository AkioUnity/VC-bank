#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für choose_printer
	/// </summary>
	public ref class choose_printer : public System::Windows::Forms::Form
	{
	public:
		choose_printer(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

		choose_printer(System::Windows::Forms::Label^ cache):
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
		~choose_printer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  printer;
		System::Windows::Forms::Label^ cache_;
	protected: 
	private: System::Windows::Forms::Button^  btn_print;
	private: System::Windows::Forms::Button^  btn_back;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(choose_printer::typeid));
			this->printer = (gcnew System::Windows::Forms::ListBox());
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->btn_back = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// printer
			// 
			this->printer->FormattingEnabled = true;
			this->printer->Location = System::Drawing::Point(10, 9);
			this->printer->Name = L"printer";
			this->printer->Size = System::Drawing::Size(262, 95);
			this->printer->Sorted = true;
			this->printer->TabIndex = 0;
			// 
			// btn_print
			// 
			this->btn_print->Location = System::Drawing::Point(10, 109);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(261, 22);
			this->btn_print->TabIndex = 1;
			this->btn_print->Text = L"Drucken";
			this->btn_print->UseVisualStyleBackColor = true;
			this->btn_print->Click += gcnew System::EventHandler(this, &choose_printer::btn_print_Click);
			// 
			// btn_back
			// 
			this->btn_back->Location = System::Drawing::Point(10, 137);
			this->btn_back->Name = L"btn_back";
			this->btn_back->Size = System::Drawing::Size(173, 22);
			this->btn_back->TabIndex = 2;
			this->btn_back->Text = L"Abbrechen";
			this->btn_back->UseVisualStyleBackColor = true;
			this->btn_back->Click += gcnew System::EventHandler(this, &choose_printer::btn_back_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(189, 142);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 46;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// choose_printer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 168);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->btn_back);
			this->Controls->Add(this->btn_print);
			this->Controls->Add(this->printer);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"choose_printer";
			this->Text = L"Drucker wählen";
			this->Load += gcnew System::EventHandler(this, &choose_printer::choose_printer_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void choose_printer_Load(System::Object^  sender, System::EventArgs^  e);
		void btn_print_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_back_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
