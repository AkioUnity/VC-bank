#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class adresse
{
public:
	adresse(void);
	adresse(String^);

	// Getter
	String^ get_adresse();
	Decimal get_einzel_gk();
	Decimal get_einzel_gf();
	Decimal get_einzel_gk_vn();
	Decimal get_einzel_gf_vn();

	// Setter
	void set_einzel_gk(Decimal);
	void set_einzel_gf(Decimal);
	void set_einzel_gk_vn(Decimal);
	void set_einzel_gf_vn(Decimal);

	void bewilligung_zu_vn();
	void vn_zu_bewilligung();

	// Speichern, Laden
	void save(String^);
	void load(String^);

	// ==
	bool is_equal(adresse^);

private:
	String^ adr_;
	Decimal einzel_gesamt_kosten_;
	Decimal einzel_gesamt_foerderung_;
	Decimal einzel_gesamt_kosten_vn_;
	Decimal einzel_gesamt_foerderung_vn_;
};

