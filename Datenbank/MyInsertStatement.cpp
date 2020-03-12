#include "StdAfx.h"
#include "MyInsertStatement.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Data;
using namespace System::Data::OleDb;

MyInsertStatement::MyInsertStatement(void)
{}

MyInsertStatement::MyInsertStatement(String^ input)
{
	String^ connection_string="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	String^ query=input;

	// Datenbank Pfad auslesen
	String^ pfad=Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
	pfad+="\\db_pfad.txt";
	FileStream^ fs = File::OpenRead(pfad);
	array<Byte>^b = gcnew array<Byte>(1024);
    UTF8Encoding^ temp = gcnew UTF8Encoding( true );
    fs->Read( b, 0, b->Length );
    String^ path = temp->GetString( b );
	fs->Close();
	connection_string += path;

	// Verbindung herstellen
	String^ mySelectQuery = input;
    OleDbConnection^ myConnection = gcnew OleDbConnection(connection_string);
    OleDbCommand^ myCommand = gcnew OleDbCommand(mySelectQuery,myConnection);
	myConnection->Open();

	try
	{
		myCommand->ExecuteNonQuery();
	}
	__finally 
	{
		myConnection->Close();
	}
}