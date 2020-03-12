#include "StdAfx.h"
#include "helper.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Security::Cryptography;

// Windows::Forms::MessageBox::Show();

// Typconvert
String^ Decimal_to_string(Decimal input)
{
	String^ pre_comma=Decimal_to_dez(input);
	String^ post_comma=Decimal_to_kom(input);
	String^ complete=pre_comma+post_comma;

	return complete;
}

String^ Decimal_to_dez(Decimal input)
{
	if(Convert::ToString(input)->IndexOf("E")==-1)
	{
		String^ complete=Convert::ToString(input);
		bool negative=(complete[0]=='-');
		complete=complete->Replace("-","")->Trim();
		int comma_index=complete->IndexOf(",");

		String^ pre_comma;

		if(comma_index!=-1)
			pre_comma=complete->Substring(0,comma_index);
		else
			pre_comma = complete;

		int count=1;
		for(int i=pre_comma->Length-1;i>=0;--i)
		{
			if(count!=0 && count%3==0 && i!=0)
				pre_comma=pre_comma->Insert(i,".");
			++count;
		}
	
		if(negative)
			pre_comma="-"+pre_comma;

		return pre_comma+",";
	}
	else
		return "0"+",";
}

String^ Decimal_to_kom(Decimal input)
{
	if(Convert::ToString(input)->IndexOf("E")==-1)
	{
		String^ complete=Convert::ToString(input);
		int comma_index=complete->IndexOf(",");

		String^ post_comma="00";

		if(comma_index!=-1)
			post_comma=complete->Substring(comma_index+1);

		if(post_comma->Length>2)
			post_comma=post_comma->Substring(0,2);

		if(post_comma->Length==1)
			post_comma+="0";

		post_comma+=" €";

		return post_comma;
	}
	else
		return "00 €";
}

String^ date_to_string(String^ input)
{
	input=input->Replace("/",".");
	input=input->Replace("-",".");

	List<String^>^ einzel_daten=gcnew List<String^>;
	einzel_daten->Add("");
	for(int i=0;i<input->Length;++i)
		if(input[i]=='.')
			einzel_daten->Add("");
		else
			einzel_daten[einzel_daten->Count-1]+=input[i];

	int tag=Convert::ToInt32(einzel_daten[0]);
	int monat=Convert::ToInt32(einzel_daten[1]);
	int jahr=Convert::ToInt32(einzel_daten[2]);

	String^ datum="";
	
	if(tag<10)
		datum+="0";
	datum+=Convert::ToString(tag);
	datum+=".";
	if(monat<10)
		datum+="0";
	datum+=Convert::ToString(monat);
	datum+=".";
	if(jahr<100)
	{
		if(jahr<=50)
			datum+="20";
		if(jahr<10)
			datum+="0";
		if(jahr>=90)
			datum+="19";
	}
	datum+=Convert::ToString(jahr);

	return datum;
}

// Typtest
bool check_if_Decimal(String^ input)
{
	try {Convert::ToDouble(input);}
	catch(FormatException^) {return false;}
	return true;
}

bool check_if_number(String^ input)
{
	try {Convert::ToInt32(input);}
	catch(FormatException^) {return false;}
	return true;
}

bool check_if_date(String^ input)
{
	input=input->Replace("/",".");
	input=input->Replace("-",".");

	List<String^>^ einzel_daten=gcnew List<String^>;
	einzel_daten->Add("");
	for(int i=0;i<input->Length;++i)
		if(input[i]=='.')
			einzel_daten->Add("");
		else
			einzel_daten[einzel_daten->Count-1]+=input[i];

	if(einzel_daten->Count!=3)
		return false;

	for(int i=0;i<einzel_daten->Count;++i)
		if(!check_if_number(einzel_daten[i]))
			return false;

	int tag=Convert::ToInt32(einzel_daten[0]);
	int monat=Convert::ToInt32(einzel_daten[1]);
	int jahr=Convert::ToInt32(einzel_daten[2]);

	if(tag<0 || tag>31)
		return false;

	if(monat<0 || monat>12)
		return false;

	if(einzel_daten[2]->Length!=2)
	{
		if(jahr<1980 || jahr>2050)
			return false;
	}
	else
	{
		if(!((jahr>=90 && jahr <=99 )||(jahr<=50 && jahr >=0)))
			return false;
	}

	return true;
}

// Typcompare
bool date_is_bigger(String^ lhs, String^ rhs)
{
	//XX.XX.XXXX
	String^ tag1=lhs->Substring(0,2);
	String^ monat1=lhs->Substring(3,2);
	String^ jahr1=lhs->Substring(6,4);

	String^ tag2=rhs->Substring(0,2);
	String^ monat2=rhs->Substring(3,2);
	String^ jahr2=rhs->Substring(6,4);

	String^ datum1=jahr1+monat1+tag1;
	String^ datum2=jahr2+monat2+tag2;
	return Convert::ToInt32(datum1)>=Convert::ToInt32(datum2);
}

// Hasher
String^ get_MD5_hash(String^ input)
{
	int length=input->Length;
	array<System::Byte>^ buffer = gcnew array<System::Byte>(length);
	for(int i=0;i<length;++i)
		buffer[i]=input[i];
	MD5CryptoServiceProvider hasher();
	//SHA512Cng hasher ;
	//hasher.ComputeHash(buffer);

	//String^ result="";

	//for(int i=0;i<hasher.Hash.Length;++i)
	//	result+=hasher.Hash[i];

	return input;
}
