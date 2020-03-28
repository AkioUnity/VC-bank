#include "stdafx.h"
#include "ResultForm.h"

void ResultForm::btn_exportExl_Click(System::Object^  sender, System::EventArgs^  e) {
	exl_->saveDialoge();
	btn_exportExl->Enabled = false;
}


void ResultForm::place_button()
{
	start = start + 30;

	btn_exportExl->Location = System::Drawing::Point(5, start);
	btn_exportExl->Size = System::Drawing::Size(926, 20);
	this->Controls->Add(btn_exportExl);

	System::Windows::Forms::Label^  label_freespace = gcnew System::Windows::Forms::Label();
	label_freespace->Location = System::Drawing::Point(0, start + 20);
	label_freespace->AutoSize = false;
	label_freespace->Size = System::Drawing::Size(5, 10);
	this->Controls->Add(label_freespace);
	
}
