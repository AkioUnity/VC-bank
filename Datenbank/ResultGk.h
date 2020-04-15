#pragma once
#include "ResultForm.h"
namespace Datenbank {

	using namespace System::Collections;
	using namespace System::Collections::Generic;

	public ref class ResultGk : public ResultForm
	{
	public:
		ResultGk();
		ResultGk(bool show_gk_real,
			bool show_gk_kom,
			bool show_gk_priv) :
			show_gk_real_(show_gk_real),
			show_gk_kom_(show_gk_kom),
			show_gk_priv_(show_gk_priv),
			spalte_gk_real_(-1),
			spalte_gk_kom_(-1),
			spalte_gk_priv_(-1),
			total_list(gcnew List< List< List<String^>^ >^ >)
		{};

		List<Decimal>^  get_gk_real(String^ stadt, String^ gebiet, String^ programm, List<String^>^ jahr);
		List<Decimal>^  get_gk_kom(String^ stadt, String^ gebiet, String^ programm, List<String^>^ jahr);
		List<Decimal>^  get_gk_priv(String^ stadt, String^ gebiet, String^ programm, List<String^>^ jahr);

		void GenerateTableHeader();

		List< List< List<String^>^ >^ >^ total_list;

		bool show_gk_real_;
		bool show_gk_kom_;
		bool show_gk_priv_;

		int spalte_gk_real_;
		int spalte_gk_kom_;
		int spalte_gk_priv_;

		int column_width_;
	};
}

