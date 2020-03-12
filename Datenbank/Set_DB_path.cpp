#include "StdAfx.h"
#include "Set_DB_path.h"


using namespace System;
using namespace System::IO;
using namespace System::Text;

System::Void Datenbank::Set_DB_path::btn_search_path_Click(System::Object^  sender, System::EventArgs^  e)
{
	openFileDialog1->Filter="Access Datenbank|*.mdb";
	openFileDialog1->FileName="";
	openFileDialog1->ShowDialog();
	tb_path->Text=openFileDialog1->FileName;
}

void AddText( FileStream^ fs, String^ value )
{
   array<Byte>^info = (gcnew UTF8Encoding( true ))->GetBytes( value );
   fs->Write( info, 0, info->Length );
}

System::Void Datenbank::Set_DB_path::btn_back_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(File::Exists(tb_path->Text))
	{
		String^ pfad=Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
		pfad+="\\db_pfad.txt";
		FileStream^ fs = File::Create(pfad);
		AddText(fs,tb_path->Text);
		fs->Close();
		Close();
	}
	else
		Windows::Forms::MessageBox::Show("Bitte einen gültigen Pfad angeben.");
}