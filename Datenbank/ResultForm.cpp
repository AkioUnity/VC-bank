#include "stdafx.h"
#include "ResultForm.h"
#include "helper.h"

using namespace Datenbank;

void ResultForm::btn_exportExl_Click(System::Object^  sender, System::EventArgs^  e) {
	exl_->saveDialoge();
	btn_exportExl->Enabled = false;
}


void ResultForm::place_button()
{
	start_pos = start_pos + 30;

	btn_exportExl->Location = System::Drawing::Point(5, start_pos);
	btn_exportExl->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_exportExl);

	System::Windows::Forms::Label^  label_freespace = gcnew System::Windows::Forms::Label();
	label_freespace->Location = System::Drawing::Point(0, start_pos + 20);
	label_freespace->AutoSize = false;
	label_freespace->Size = System::Drawing::Size(5, 10);
	this->Controls->Add(label_freespace);
	
}


void ResultForm::AddHeaderCell(String^ text, int xPos, int yPos)
{
	label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(xPos, yPos);
	label->AutoSize = true;
	label->Text = text;
	label->BackColor = System::Drawing::Color::Silver;
	label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->Controls->Add(label);

	int col = 1;
	exl_->setCell(row_,col, text);
	exl_->setCellAutofit(row_, col);
	//exl_->setCellItalic(row_, col);
	row_++;
}

void ResultForm::AddTableHeaderCell(String^ text, int xPos)
{
	label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(xPos, start_pos);
	label->AutoSize = true;
	label->Text = text;
	label->BackColor = System::Drawing::Color::Silver;
	label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));	
	this->Controls->Add(label);
	
	exl_->setCell(row_, col_, text);
	exl_->setCellAutofit(row_, col_);
	exl_->setCellBold(row_, col_);
	col_++;
}

void ResultForm::AddTableFooter(String^ text, int xPos, int width, int height)
{
	label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(xPos, start_pos);
	label->AutoSize = false;
	label->Text = text;	
	label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	label->Size = System::Drawing::Size(width, height);
	label->TextAlign = System::Drawing::ContentAlignment::TopRight;
	this->Controls->Add(label);

	if (col_==1)
		exl_->setCell(row_, col_,text);
	else
		exl_->setCellSum(row_, col_, sumStart,row_-2);
	exl_->setCellAutofit(row_, col_);
	exl_->setCellBold(row_, col_);
	col_++;
}

void ResultForm::AddTableHeaderCell(String^ text, int xPos, int width, int height)
{
	AddTableHeaderCell(text, xPos);

	label->AutoSize = false;
	label->Size = System::Drawing::Size(width, height);
	label->TextAlign = System::Drawing::ContentAlignment::TopRight;
}

void ResultForm::SetLabelSize(int width, int height)
{
	label->AutoSize = false;
	label->Size = System::Drawing::Size(width, height);
	label->TextAlign = System::Drawing::ContentAlignment::TopRight;
}

void ResultForm::AddCell(String^ text, int xPos, int row)
{
	AddCell(text, xPos, row, false);
}

void ResultForm::AddCell(String^ text, int xPos, int row, bool isDecimal)
{
	label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(xPos, start_pos);
	label->AutoSize = true;
	label->Text = text;
	label->BackColor = (row % 2 != 0) ? System::Drawing::Color::Gainsboro : System::Drawing::Color::White;
	label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	
	this->Controls->Add(label);

	if (isDecimal)
		exl_->setCellCurrency(row_, col_, String_to_Decimal(text));
	else {
		if (col_==1)
			exl_->setCellYear(row_, col_, text);
		else
			exl_->setCell(row_, col_, text);
	}		
	exl_->setCellAutofit(row_, col_);
	col_++;
}


void ResultForm::AddHeaderDivider(int width, int height)
{
	System::Windows::Forms::Label^  header_back = gcnew System::Windows::Forms::Label();
	header_back->Location = System::Drawing::Point(0, start_pos);
	header_back->AutoSize = false;
	header_back->Size = System::Drawing::Size(width, height);
	header_back->BackColor = System::Drawing::Color::Silver;
	this->Controls->Add(header_back);
}



void ResultForm::AddLineBreak(System::Drawing::Color color)
{
	label = gcnew System::Windows::Forms::Label();
	label->Location = System::Drawing::Point(0, start_pos - 3);  //-3
	label->AutoSize = false;
	if (heightCalc < 20)
		heightCalc = 20;
	label->Size = System::Drawing::Size(936, heightCalc + 6);  //20
	label->BackColor = color;	
	this->Controls->Add(label);

	start_pos += heightCalc + 8;
}


void Datenbank::ResultForm::AddGkCell(String^ text, int xPos, int row, bool isGK,bool isDecimal)
{
	if (!isGK) {
		label = gcnew System::Windows::Forms::Label();
		label->Location = System::Drawing::Point(xPos, start_pos);
		label->AutoSize = true;
		label->Text = text;
		label->BackColor = (row % 2 != 0) ? System::Drawing::Color::Gainsboro : System::Drawing::Color::White;
		label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->Controls->Add(label);
	}

	if (isDecimal)
		exl_->setCellCurrency(row_, col_, String_to_Decimal(text));
	else {
		if (col_ == 1)
			exl_->setCellYear(row_, col_, text);
		else
			exl_->setCell(row_, col_, text);
	}
	exl_->setCellAutofit(row_, col_);
	col_++;
}
