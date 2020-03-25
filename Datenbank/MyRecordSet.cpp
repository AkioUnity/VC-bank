#include "StdAfx.h"
#include "MyRecordSet.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Data::OleDb;
using namespace System::Data;
using namespace System::Collections::Generic;

MyRecordSet::MyRecordSet(void)
{
}

void MyRecordSet::SetPath()
{
	String^ connection_string = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	// Datenbank Pfad auslesen
	String^ pfad = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
	pfad += "\\db_pfad.txt";
	FileStream^ fs = File::OpenRead(pfad);
	array<Byte>^b = gcnew array<Byte>(1024);
	UTF8Encoding^ temp = gcnew UTF8Encoding(true);
	fs->Read(b, 0, b->Length);
	mdbPath= temp->GetString(b);	
	path = connection_string+mdbPath;
	fs->Close();	
	/*OleDbConnection^ myConnection;
	myConnection = gcnew OleDbConnection(path);
	myConnection->Open();*/
	//myConnection->Close();
}

MyRecordSet::MyRecordSet(String^ input)
{	
	query_=input;	
	// Verbindung herstellen  Establish connection
	String^ mySelectQuery = input;
	OleDbConnection^ myConnection;
	myConnection = gcnew OleDbConnection(path);
	myConnection->Open();
    OleDbCommand^ myCommand = gcnew OleDbCommand(mySelectQuery,myConnection);	
	OleDbDataReader^ myReader = myCommand->ExecuteReader();
	rows_=0;
	try
	{
		coloumns_ = myReader->FieldCount;

		// Namen und Typen erkennen  //Recognize names and types
		for(int i=0;i<coloumns_;++i)
		{
			String^ data_name (myReader->GetName(i));
			String^ data_type (myReader->GetDataTypeName(i));
			namen_.Add(data_name);
			typen_.Add(data_type);
			List<String^>^ new_list = gcnew List<String^>;
			table_.Add(new_list);
		}
		// Werte konvertieren und Tabelle füllen  //Convert values and fill the table
		while (myReader->Read()) 
		{
			rows_++;
			for(int i=0;i<coloumns_;++i)
			{
				String^ data_name (myReader->GetName(i));
				String^ data_type (myReader->GetDataTypeName(i));
				if(typen_[i] == "DBTYPE_I4")
					table_[i]->Add( (myReader->GetInt32(i)).ToString());
				if(typen_[i] == "DBTYPE_WVARCHAR")
					table_[i]->Add(myReader->GetString(i));
			}
		}
	}
	__finally 
	{
		myReader->Close();	
		myConnection->Close();
	}
}

String^ MyRecordSet::get_Name(int index)
{
	return namen_[index];
}

String^ MyRecordSet::get_Type(int index)
{
	return typen_[index];
}

String^ MyRecordSet::get_val(int index_row, int index_clm)
{
	List<String^> liste(table_[index_clm]);
	return liste[index_row];
}

int MyRecordSet::get_clm()
{
	return coloumns_;
}

int MyRecordSet::get_row()
{
	return rows_;
}

int MyRecordSet::get_new_id()
{
	List<String^> liste(table_[0]);
	for(int i=1;i<liste.Count+3;++i)
		if(!liste.Contains(i.ToString()))
			return i;
	return -1;
}

String^ MyRecordSet::QueryAllAnnualBudget(String^ city, String^ area, String^ program) 
{
	return "SELECT jahreshaushalt.* FROM jahreshaushalt inner join (Programme inner join (Gebiete inner join Staedte on Gebiete.Stadt_ID=Staedte.ID ) on Programme.Gebiet_ID=Gebiete.ID) on jahreshaushalt.programm_ID=Programme.ID WHERE Staedte.Stadt='" + city + "' and Gebiete.Gebiet='" + area + "' and Programme.Programm='" + program+"'";
}

String^ MyRecordSet::GetProgramNr(String^ programName)
{
	String^ query = "SELECT Programm_Nr FROM Programme WHERE Programm='" + programName + "'";
	MyRecordSet RC(query);
	return RC.get_val(0, 0);
}

String^ MyRecordSet::GetAreaId(String^ city, String^ area)
{
	String^ query = "SELECT Gebiete.ID FROM Gebiete inner join Staedte on Gebiete.Stadt_ID=Staedte.ID WHERE Staedte.Stadt='" + city + "' AND Gebiet='"+area+"'";	
	MyRecordSet RC(query);
	return RC.get_val(0, 0);
}

String^ MyRecordSet::QueryOneAnnualBudget(String^ city, String^ area, String^ program, String^ year)
{
	return QueryAllAnnualBudget(city, area, program) + " and jahreshaushalt.jahr='" + year + "'";
}