#include "StdAfx.h"
#include "My_Connection.h"
#include "MyRecordSet.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Data::OleDb;
using namespace System::Data;
using namespace System::Collections::Generic;


My_Connection::My_Connection(void):
	db_pfad_(""),
	Connection_(gcnew OleDbConnection())
{
	// Datenbank Pfad auslesen
	/*String^ pfad=Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
	pfad+="\\db_pfad.txt";
	FileStream^ fs = File::OpenRead(pfad);
	array<Byte>^b = gcnew array<Byte>(1024);
    UTF8Encoding^ temp = gcnew UTF8Encoding( true );
    fs->Read( b, 0, b->Length );
    db_pfad_ = temp->GetString( b );
	fs->Close();*/
}

void My_Connection::connect()
{	
	// Verbindung herstellen
	//String^ connection_string="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	//connection_string+=db_pfad_;
	String^ connection_string = MyRecordSet::path;
    Connection_ = gcnew OleDbConnection(connection_string);
	Connection_->Open();
}

MyResult^ My_Connection::get_cities(String^ city)
{
	return get_result("SELECT ID FROM Staedte WHERE Stadt='" + city + "'");
}

MyResult^ My_Connection::get_result(String^ query)
{
    OleDbCommand^ myCommand = gcnew OleDbCommand(query,Connection_);
	OleDbDataReader^ myReader = myCommand->ExecuteReader();
	
	List<String^>^ namen=gcnew List<String^>;
	List<String^>^ typen=gcnew List<String^>;
	List< List<String^>^ >^ table=gcnew List< List<String^>^ >;
	int rows=0;
	int coloumns = myReader->FieldCount;

	// Namen und Typen erkennen
	for(int i=0;i<coloumns;++i)
	{
		String^ data_name (myReader->GetName(i));
		String^ data_type (myReader->GetDataTypeName(i));
		namen->Add(data_name);
		typen->Add(data_type);
		List<String^>^ new_list = gcnew List<String^>;
		table->Add(new_list);
	}
	
	// Werte konvertieren und Tabelle füllen
	while (myReader->Read()) 
	{
		rows++;
		for(int i=0;i<coloumns;++i)
		{
			String^ data_name (myReader->GetName(i));
			String^ data_type (myReader->GetDataTypeName(i));
			if(typen[i] == "DBTYPE_I4")
				table[i]->Add( (myReader->GetInt32(i)).ToString());
			if(typen[i] == "DBTYPE_WVARCHAR")
				table[i]->Add(myReader->GetString(i));
		}
	}
	myReader->Close();

	return gcnew MyResult(coloumns,rows,namen,typen,table);
}

void My_Connection::disconnect()
{
	Connection_->Close();
}