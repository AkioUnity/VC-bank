#pragma once

ref class ExcelExport
{
	public:
		ExcelExport(void);
		~ExcelExport(void);
		void saveDialoge();
		void show();
		
		System::String^ getColumnName(int y);

		void setCell(int x, int y, System::String ^ value);
		void setCell(int x, int y, int value);
		void setCellYear(int x, int y, System::String ^ value);
		void setCellCurrency(int x, int y, System::Decimal value);
		void setCellBold(int x, int y);
		void setCellItalic(int x, int y);
		void setCellAutofit(int x, int y);
		void setCellSum(int x, int y,int start,int end);
		void setCellSumCell(int x, int y, int x1, int y1, int x2, int y2);

	private:
		Microsoft::Office::Interop::Excel::Application ^ _app;
		Microsoft::Office::Interop::Excel::Workbook ^ _workBook;
		Microsoft::Office::Interop::Excel::Worksheet ^ _workSheet;
		int _misValue;

};