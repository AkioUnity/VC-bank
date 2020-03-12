#include "StdAfx.h"
#include "MyResult.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections::Generic;

MyResult::MyResult(void):
	coloumns_(0),
	rows_(0),
	namen_(gcnew List<String^>),
	typen_(gcnew List<String^>),
	table_(gcnew List< List<String^>^ >)
{}

MyResult::MyResult(int coloumns,int rows,List<String^>^ namen,List<String^>^ typen,List< List<String^>^ >^ table):
	coloumns_(coloumns),
	rows_(rows),
	namen_(namen),
	typen_(typen),
	table_(table)
{}

String^ MyResult::get_Name(int index)
{
	return namen_[index];
}

String^ MyResult::get_Type(int index)
{
	return typen_[index];
}

String^ MyResult::get_val(int index_row, int index_clm)
{
	List<String^> liste(table_[index_clm]);
	return liste[index_row];
}

int MyResult::get_clm()
{
	return coloumns_;
}

int MyResult::get_row()
{
	return rows_;
}

int MyResult::get_new_id()
{
	List<String^>^ liste(table_[0]);
	for(int i=1;i<liste->Count+3;++i)
		if(!liste->Contains(i.ToString()))
			return i;
	return -1;
}