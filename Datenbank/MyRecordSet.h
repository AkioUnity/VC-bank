#pragma once
#include <oledb.h>

using namespace System::Collections::Generic;
using namespace System;

ref class MyRecordSet
{
public:
	MyRecordSet(void);
	MyRecordSet(String^);

	static void SetPath();
	static	String^ path;
	static	String^ mdbPath;

	static String^ QueryAllAnnualBudget(String^ city, String^ area, String^ program);
	static String^ QueryOneAnnualBudget(String^, String^, String^, String^);
	static String^ GetProgramNr(String^ programName);
	static String^ GetAreaId(String^ city, String^ area);
	/*static OleDbConnection^ myConnection;*/

	String^ get_Name(int);
	String^ get_Type(int);
	String^ get_val(int,int);
	int get_clm();
	int get_row();
	int get_new_id();

private:
	String^ query_;
	String^ path_;
	int coloumns_;
	int rows_;
	List<String^> namen_;
	List<String^> typen_;
	List< List<String^>^ > table_;
};

