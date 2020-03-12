#pragma once

using namespace System::Collections::Generic;

// Typconvert
System::String^ Decimal_to_string(System::Decimal);
System::String^ Decimal_to_dez(System::Decimal);
System::String^ Decimal_to_kom(System::Decimal);

System::String^ date_to_string(System::String^);

// Typtests
bool check_if_Decimal(System::String^);
bool check_if_number(System::String^);
bool check_if_date(System::String^);

// Typcompare
bool date_is_bigger(System::String^,System::String^);

// Hasher
System::String^ get_MD5_hash(System::String^);


