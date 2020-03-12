#pragma once

#include "bewilligung_class.h"

using namespace System;
using namespace System::Collections::Generic;

ref class programm
{
public:
	programm(void);
	programm(String^, String^);

	// Setter

	void set_name(String^);

	void add_bewilligung();
	void rem_bewilligung(int);

	void bewilligung_zu_vn();
	void vn_zu_bewilligung();

	// Getter

	String^ get_name();
	bewilligung_class^ get_bewilligung(int);
	List<String^>^ get_bewilligungen();

	// Berechnungen

	Decimal get_mla();
	Decimal get_mla_vn();
	Decimal get_bund_land();
	Decimal get_bund_land_vn();

	// Bewilligung swap
	void swap_bewilligung(int,int);

	// Speichern, Laden
	void save(String^);
	void load(String^);

	//==
	bool is_equal(programm^);

private:
	String^ name_;
	String^ nr_;
	List<bewilligung_class^>^ bewilligungen_;
};

