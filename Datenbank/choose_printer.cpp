#include "StdAfx.h"
#include "choose_printer.h"

using namespace Datenbank;
using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;
using namespace System::Drawing::Printing;

void choose_printer::choose_printer_Load(System::Object^  sender, System::EventArgs^  e)
{
	for(int i=0;i<PrinterSettings::InstalledPrinters->Count;++i)
		printer->Items->Add(PrinterSettings::InstalledPrinters[i]);
}

void choose_printer::btn_print_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(printer->SelectedIndex!=-1)
	{
		cache_->Text=printer->Text;
		Close();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte wählen Sie einen Drucker.","Kein Drucker gewählt");
}

void choose_printer::btn_back_Click(System::Object^  sender, System::EventArgs^  e)
{
	Close();
}