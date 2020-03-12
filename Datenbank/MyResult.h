#pragma once

using namespace System::Collections::Generic;
using namespace System;

ref class MyResult
{
public:
	MyResult(void);
	MyResult(int,int,List<String^>^,List<String^>^,List< List<String^>^ >^);

	String^ get_Name(int);
	String^ get_Type(int);
	String^ get_val(int,int);

	int get_clm();
	int get_row();
	int get_new_id();

private:
	int coloumns_;
	int rows_;
	List<String^>^ namen_;
	List<String^>^ typen_;
	List< List<String^>^ >^ table_;
};

