#include "StdAfx.h"
#include "ExcelExport.h"

using namespace Microsoft::Office::Interop::Excel;
using namespace System::Windows::Forms;
using namespace System;

ExcelExport::ExcelExport(void)
{
	_app = gcnew Microsoft::Office::Interop::Excel::ApplicationClass();

	if (false) { //((*_app) == _nullptr) { 
		MessageBox::Show("Excel is not properly installed!!");
	}
	
	_misValue = 1;
	_workBook = _app->Workbooks->Add(_misValue);
	_workSheet = (Microsoft::Office::Interop::Excel::Worksheet^) _app->ActiveSheet;

}

ExcelExport::~ExcelExport(void) 
{	
	if (!_app->Visible)
		_app->Quit();
}

void ExcelExport::saveDialoge() {
    SaveFileDialog ^ saveDialog = gcnew SaveFileDialog();
	saveDialog->Filter = "Excel Files (*.xlsx)|*.xlsx"  ;
    saveDialog->FilterIndex = 1 ;
    saveDialog->RestoreDirectory = true ;
	if(saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
		try {		  
			_workBook->Close(true, saveDialog->FileName, _misValue);
		}
		catch (Exception ^ e) {
			MessageBox::Show(e->Message,"Fehler bei Speichern");
			_workBook->Close(false, saveDialog->FileName, _misValue);
		}
    }
	//workBook.SaveAs(filePath, AccessMode: XlSaveAsAccessMode.xlShared);
}

void ExcelExport::show() {
	_app->Visible = true;
}

void ExcelExport::setCell(int x, int y, System::String ^ value) {
	_workSheet->Cells[x,y] = value;
}

void ExcelExport::setCell(int x, int y, int value){
	_workSheet->Cells[x,y] = value;
}

void ExcelExport::setCellCurrency(int x, int y, Decimal value) {
	Microsoft::Office::Interop::Excel::Range ^ cells;
	cells = (Microsoft::Office::Interop::Excel::Range ^) _workSheet->Cells[x,y];
	cells->NumberFormat = "#,##0.00 €";
	_workSheet->Cells[x,y] = value;
}

void ExcelExport::setCellBold(int x, int y) {
	Microsoft::Office::Interop::Excel::Range ^ cells;
	cells = (Microsoft::Office::Interop::Excel::Range ^) _workSheet->Cells[x,y];
	cells->Font->Bold = true;
}

void ExcelExport::setCellItalic(int x, int y) {
	Microsoft::Office::Interop::Excel::Range ^ cells;
	cells = (Microsoft::Office::Interop::Excel::Range ^) _workSheet->Cells[x,y];
	cells->Font->Italic = true;
}

void ExcelExport::setCellAutofit(int x, int y) {
	Microsoft::Office::Interop::Excel::Range ^ cells;
	cells = (Microsoft::Office::Interop::Excel::Range ^) _workSheet->Cells[x,y];
	cells->EntireColumn->AutoFit();
}

void ExcelExport::setCellSum(int x, int y,int start,int end) {
	Microsoft::Office::Interop::Excel::Range ^ cells;
	cells = (Microsoft::Office::Interop::Excel::Range ^) _workSheet->Cells[x,y];
	String ^ index;
	switch(y) {
		case 7 : index = "G";
		case 8 : index = "H";
	}
	cells->Formula="=SUM("+index+start.ToString()+":"+index+end.ToString()+")";
	cells->NumberFormat = "#,##0.00 €";
}