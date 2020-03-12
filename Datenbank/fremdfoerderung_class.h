#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class fremdfoerderung_class
{
public:
	fremdfoerderung_class(void);
	fremdfoerderung_class(String^,bool);

	//Getter
	Decimal get_betrag();
	Decimal get_betrag(int);
	String^ get_programm(int);
	List<String^>^ get_all(bool);

	//Setter
	bool add_programm(String^, Decimal);
	void rem_programm(int);
	
	// Speichern, Laden
	void save(String^,bool);
	void load(String^,bool);
	
	// ==
	bool is_equal(fremdfoerderung_class^);

	List<String^>^ programm_;
	List<Decimal>^ betrag_;
};

