#pragma once

ref class ExcelExport
{
	public:
		ExcelExport(void);
		~ExcelExport(void);
		void saveDialoge();
		void show();

		void setCell(int x, int y, System::String ^ value);
		void setCell(int x, int y, int value);
		void setCellCurrency(int x, int y, System::Decimal value);
		void setCellBold(int x, int y);
		void setCellItalic(int x, int y);
		void setCellAutofit(int x, int y);
		void setCellSum(int x, int y,int start,int end);

	private:
		Microsoft::Office::Interop::Excel::Application ^ _app;
		Microsoft::Office::Interop::Excel::Workbook ^ _workBook;
		Microsoft::Office::Interop::Excel::Worksheet ^ _workSheet;
		int _misValue;

};