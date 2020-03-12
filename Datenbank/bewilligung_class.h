#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class bewilligung_class
{
public:
	bewilligung_class(void);
	bewilligung_class(String^);

	// Setter

	void set_nr2(String^);
	void set_nr3(String^);
	void set_vom(String^);

	void set_mla(Decimal);
	void set_mla_vn(Decimal);
	void set_bund_land(Decimal);
	void set_bund_land_vn(Decimal);
	void set_san_bed_ein(bool);

	void bewilligung_zu_vn();
	void vn_zu_bewilligung();

	// Getter

	String^ get_nr();
	String^ get_nr1();
	String^ get_nr2();
	String^ get_nr3();
	String^ get_vom();

	Decimal get_mla();
	Decimal get_mla_vn();
	Decimal get_bund_land();
	Decimal get_bund_land_vn();
	bool get_san_bed_ein();

	// Speichern, Laden
	void save(String^);
	void load(String^);

	//==
	bool is_equal(bewilligung_class^);

private:
	String^ nr1_;
	String^ nr2_;
	String^ nr3_;
	String^ vom_;

	bool san_bed_ein_;

	Decimal mla_;
	Decimal bund_land_;
	Decimal mla_vn_;
	Decimal bund_land_vn_;
};

