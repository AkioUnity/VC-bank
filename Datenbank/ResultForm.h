#pragma once

#include "test.h"
#include "ExcelExport.h"

namespace Datenbank {

	using namespace System;
	//using namespace System::ComponentModel;
	//using namespace System::Collections;
	//using namespace System::Windows::Forms;
	//using namespace System::Data;
	//using namespace System::Drawing;
	//using namespace System::Drawing::Printing;

	public ref class ResultForm : public System::Windows::Forms::Form
	{
	public:
		ResultForm() :
			exl_(gcnew ExcelExport()),
			row_(1),
			col_(1),
			start_pos(0)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~ResultForm()
		{
			delete exl_;
		}
	public:
		void InitializeComponent(void)
		{
			this->btn_exportExl = (gcnew System::Windows::Forms::Button());
			// 
			// btn_exportExl
			// 
			this->btn_exportExl->ImageAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->btn_exportExl->Location = System::Drawing::Point(35, 85);
			this->btn_exportExl->Name = L"btn_exportExl";
			this->btn_exportExl->Size = System::Drawing::Size(808, 23);
			this->btn_exportExl->TabIndex = 4;
			this->btn_exportExl->Text = L"nach Excel exportieren";
			this->btn_exportExl->UseVisualStyleBackColor = true;
			this->btn_exportExl->Click += gcnew System::EventHandler(this, &ResultForm::btn_exportExl_Click);

			this->Controls->Add(this->btn_exportExl);

		}

		ExcelExport ^ exl_;
		System::Windows::Forms::Label^  label;
		int row_;
		int col_;

		int start_pos;
		int sumStart;

		System::Windows::Forms::Button^  btn_exportExl;

		// Events	
		void btn_exportExl_Click(System::Object^  sender, System::EventArgs^  e);

		void place_button();
		void AddCell(String^ text, int xPos, int row);
		void AddCell(String^ text, int xPos, int row, bool isDecimal);
		void AddHeaderCell(String^ text, int xPos, int yPos);
		void AddTableHeaderCell(String^ text, int xPos);
		void AddTableFooter(String^ text, int xPos, int width, int height);
		void AddTableHeaderCell(String^ text, int xPos, int width, int height);
		void SetLabelSize(int width, int height);
		void AddHeaderDivider(int width, int height);
		void AddLineBreak(System::Drawing::Color color);
		int heightCalc;
	};
}