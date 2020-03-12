#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für test
	/// </summary>
	public ref class test : public System::Windows::Forms::Form
	{
	public:
		test(void):
			max_(100)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
		test(int max):
			max_(max)
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
		~test()
		{
			if (components)
			{
				delete components;
			}
		}
	private: int max_;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  progress;
	private: System::Windows::Forms::Label^  texter;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(test::typeid));
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->progress = (gcnew System::Windows::Forms::Label());
			this->texter = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(9, 9);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(388, 26);
			this->progressBar1->TabIndex = 0;
			// 
			// progress
			// 
			this->progress->AutoSize = true;
			this->progress->Location = System::Drawing::Point(403, 9);
			this->progress->Name = L"progress";
			this->progress->Size = System::Drawing::Size(0, 13);
			this->progress->TabIndex = 1;
			this->progress->Visible = false;
			this->progress->TextChanged += gcnew System::EventHandler(this, &test::progress_TextChanged);
			// 
			// texter
			// 
			this->texter->AutoSize = true;
			this->texter->Location = System::Drawing::Point(12, 43);
			this->texter->Name = L"texter";
			this->texter->Size = System::Drawing::Size(0, 13);
			this->texter->TabIndex = 2;
			this->texter->TextChanged += gcnew System::EventHandler(this, &test::texter_TextChanged);
			// 
			// test
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(408, 73);
			this->Controls->Add(this->texter);
			this->Controls->Add(this->progress);
			this->Controls->Add(this->progressBar1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"test";
			this->Text = L"Fortschritt";
			this->Load += gcnew System::EventHandler(this, &test::test_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		void test_Load(System::Object^  sender, System::EventArgs^  e) 			 
		{
			Show();
			progressBar1->Minimum = 0;
			progressBar1->Maximum = max_;
			progressBar1->Value=0;
			progressBar1->Step = 1;
		}

		void progress_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			if(progressBar1->Value<progressBar1->Maximum)
				progressBar1->PerformStep();
			else
				progressBar1->Maximum=2*progressBar1->Maximum;

		}
	private: System::Void texter_TextChanged(System::Object^  sender, System::EventArgs^  e) 
			 
		{
			Hide();
			progressBar1->Value=0;
			Show();
			//Windows::Forms::MessageBox::Show(texter->Text);
		}
};
}
