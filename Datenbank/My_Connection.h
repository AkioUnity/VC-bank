#pragma once

#include <oledb.h>
#include "MyResult.h"

using namespace System::Collections::Generic;
using namespace System;
using namespace System::Data::OleDb;
using namespace System::Data;

ref class My_Connection
{
public:
	My_Connection(void);

	void connect();
	MyResult^ get_result(String^);
	MyResult^ get_cities(String^ city);
	void disconnect();
	List<String^>^ GetCityList(String^ city);

private:
	String^ db_pfad_;
	OleDbConnection^ Connection_;
};

