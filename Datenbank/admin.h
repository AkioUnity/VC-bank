#pragma once

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für admin
	/// </summary>
	public ref class admin : public System::Windows::Forms::Form
	{
	public:
		admin(void):
		  jh_id_(gcnew List<String^>)
		{
			InitializeComponent();

			load_stadt_entries();
			load_kostenart_entries();
			load_ff_entries();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~admin()
		{
			if (components)
			{
				delete components;
			}
		}
	private: List<String^>^ jh_id_;

	private: System::Windows::Forms::ComboBox^  cB_programme;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  cB_sachkonto_ges;
	private: System::Windows::Forms::ComboBox^  cB_kostenart;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btn_del_prog;
	private: System::Windows::Forms::Button^  btn_add_prog;
	private: System::Windows::Forms::Button^  btn_del_kostenart;
	private: System::Windows::Forms::Button^  btn_add_kostenart;
	private: System::Windows::Forms::Button^  btn_del_sach_ges;
	private: System::Windows::Forms::Button^  btn_add_sach_ges;
	private: System::Windows::Forms::Button^  btn_close;
	private: System::Windows::Forms::TextBox^  tB_prog;
	private: System::Windows::Forms::TextBox^  tB_kostenart;
	private: System::Windows::Forms::TextBox^  tB_sach_gk;
	private: System::Windows::Forms::TextBox^  tB_Strasse;
	private: System::Windows::Forms::Button^  btn_del_stasse;
	private: System::Windows::Forms::Button^  btn_add_strasse;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ComboBox^  cB_Strassen;
	private: System::Windows::Forms::TextBox^  tB_FF;
	private: System::Windows::Forms::Button^  btn_del_ff;
	private: System::Windows::Forms::Button^  btn_add_ff;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::ComboBox^  cB_FF;
	private: System::Windows::Forms::TextBox^  programm_nr;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TextBox^  tB_stadt;
	private: System::Windows::Forms::Button^  btn_del_stadt;
	private: System::Windows::Forms::Button^  btn_add_stadt;
	private: System::Windows::Forms::ComboBox^  cB_staedte;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  tB_gebiet;
	private: System::Windows::Forms::Button^  btn_rem_gebiet;
	private: System::Windows::Forms::Button^  btn_add_gebiet;
	private: System::Windows::Forms::ComboBox^  cB_gebiete;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  tB_kostenart_nr;
	private: System::Windows::Forms::TextBox^  tb_kostengr_abk;
	private: System::Windows::Forms::TextBox^  tB_Strasse_Chiffre;
	private: System::Windows::Forms::TabPage^  Adresse;
	private: System::Windows::Forms::Button^  btn_save;
	private: System::Windows::Forms::TextBox^  tB_ort;
	private: System::Windows::Forms::TextBox^  tB_plz;
	private: System::Windows::Forms::TextBox^  tB_hausnr;
	private: System::Windows::Forms::TextBox^  tB_ansch_strasse;
	private: System::Windows::Forms::TextBox^  tB_name;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::GroupBox^  gB_user;
	private: System::Windows::Forms::Button^  btn_del_user;
	private: System::Windows::Forms::CheckedListBox^  lB_user_access;
	private: System::Windows::Forms::CheckBox^  cB_user_is_admin;
	private: System::Windows::Forms::Button^  btn_add_user;
	private: System::Windows::Forms::TextBox^  tB_new_user;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::ListBox^  lB_user;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Button^  btn_reset_pwd;
	private: System::Windows::Forms::Label^  label5;
	protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(admin::typeid));
			this->cB_programme = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->cB_sachkonto_ges = (gcnew System::Windows::Forms::ComboBox());
			this->cB_kostenart = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btn_del_prog = (gcnew System::Windows::Forms::Button());
			this->btn_add_prog = (gcnew System::Windows::Forms::Button());
			this->btn_del_kostenart = (gcnew System::Windows::Forms::Button());
			this->btn_add_kostenart = (gcnew System::Windows::Forms::Button());
			this->btn_del_sach_ges = (gcnew System::Windows::Forms::Button());
			this->btn_add_sach_ges = (gcnew System::Windows::Forms::Button());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->tB_prog = (gcnew System::Windows::Forms::TextBox());
			this->tB_kostenart = (gcnew System::Windows::Forms::TextBox());
			this->tB_sach_gk = (gcnew System::Windows::Forms::TextBox());
			this->tB_Strasse = (gcnew System::Windows::Forms::TextBox());
			this->btn_del_stasse = (gcnew System::Windows::Forms::Button());
			this->btn_add_strasse = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->cB_Strassen = (gcnew System::Windows::Forms::ComboBox());
			this->tB_FF = (gcnew System::Windows::Forms::TextBox());
			this->btn_del_ff = (gcnew System::Windows::Forms::Button());
			this->btn_add_ff = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->cB_FF = (gcnew System::Windows::Forms::ComboBox());
			this->programm_nr = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->tB_Strasse_Chiffre = (gcnew System::Windows::Forms::TextBox());
			this->tB_gebiet = (gcnew System::Windows::Forms::TextBox());
			this->btn_rem_gebiet = (gcnew System::Windows::Forms::Button());
			this->btn_add_gebiet = (gcnew System::Windows::Forms::Button());
			this->cB_gebiete = (gcnew System::Windows::Forms::ComboBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->tB_stadt = (gcnew System::Windows::Forms::TextBox());
			this->btn_del_stadt = (gcnew System::Windows::Forms::Button());
			this->btn_add_stadt = (gcnew System::Windows::Forms::Button());
			this->cB_staedte = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tB_kostenart_nr = (gcnew System::Windows::Forms::TextBox());
			this->tb_kostengr_abk = (gcnew System::Windows::Forms::TextBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->gB_user = (gcnew System::Windows::Forms::GroupBox());
			this->btn_reset_pwd = (gcnew System::Windows::Forms::Button());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->btn_del_user = (gcnew System::Windows::Forms::Button());
			this->lB_user_access = (gcnew System::Windows::Forms::CheckedListBox());
			this->cB_user_is_admin = (gcnew System::Windows::Forms::CheckBox());
			this->btn_add_user = (gcnew System::Windows::Forms::Button());
			this->tB_new_user = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->lB_user = (gcnew System::Windows::Forms::ListBox());
			this->Adresse = (gcnew System::Windows::Forms::TabPage());
			this->btn_save = (gcnew System::Windows::Forms::Button());
			this->tB_ort = (gcnew System::Windows::Forms::TextBox());
			this->tB_plz = (gcnew System::Windows::Forms::TextBox());
			this->tB_hausnr = (gcnew System::Windows::Forms::TextBox());
			this->tB_ansch_strasse = (gcnew System::Windows::Forms::TextBox());
			this->tB_name = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->gB_user->SuspendLayout();
			this->Adresse->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// cB_programme
			// 
			this->cB_programme->FormattingEnabled = true;
			this->cB_programme->Location = System::Drawing::Point(89, 112);
			this->cB_programme->Name = L"cB_programme";
			this->cB_programme->Size = System::Drawing::Size(253, 21);
			this->cB_programme->Sorted = true;
			this->cB_programme->TabIndex = 11;
			this->cB_programme->TextChanged += gcnew System::EventHandler(this, &admin::cB_programme_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(11, 115);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(66, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Programme :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(29, 127);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Kostenart :";
			// 
			// cB_sachkonto_ges
			// 
			this->cB_sachkonto_ges->FormattingEnabled = true;
			this->cB_sachkonto_ges->Location = System::Drawing::Point(49, 143);
			this->cB_sachkonto_ges->Name = L"cB_sachkonto_ges";
			this->cB_sachkonto_ges->Size = System::Drawing::Size(261, 21);
			this->cB_sachkonto_ges->Sorted = true;
			this->cB_sachkonto_ges->TabIndex = 6;
			this->cB_sachkonto_ges->TextChanged += gcnew System::EventHandler(this, &admin::cB_sachkonto_ges_TextChanged);
			// 
			// cB_kostenart
			// 
			this->cB_kostenart->FormattingEnabled = true;
			this->cB_kostenart->Location = System::Drawing::Point(49, 39);
			this->cB_kostenart->Name = L"cB_kostenart";
			this->cB_kostenart->Size = System::Drawing::Size(260, 21);
			this->cB_kostenart->Sorted = true;
			this->cB_kostenart->TabIndex = 1;
			this->cB_kostenart->TextChanged += gcnew System::EventHandler(this, &admin::cB_kostenart_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(25, 23);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(79, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Kostengruppe :";
			// 
			// btn_del_prog
			// 
			this->btn_del_prog->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_prog.Image")));
			this->btn_del_prog->Location = System::Drawing::Point(347, 110);
			this->btn_del_prog->Name = L"btn_del_prog";
			this->btn_del_prog->Size = System::Drawing::Size(23, 23);
			this->btn_del_prog->TabIndex = 12;
			this->btn_del_prog->UseVisualStyleBackColor = true;
			this->btn_del_prog->Click += gcnew System::EventHandler(this, &admin::btn_del_prog_Click);
			// 
			// btn_add_prog
			// 
			this->btn_add_prog->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_prog.Image")));
			this->btn_add_prog->Location = System::Drawing::Point(347, 139);
			this->btn_add_prog->Name = L"btn_add_prog";
			this->btn_add_prog->Size = System::Drawing::Size(23, 23);
			this->btn_add_prog->TabIndex = 15;
			this->btn_add_prog->UseVisualStyleBackColor = true;
			this->btn_add_prog->Click += gcnew System::EventHandler(this, &admin::btn_add_prog_Click);
			// 
			// btn_del_kostenart
			// 
			this->btn_del_kostenart->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_kostenart.Image")));
			this->btn_del_kostenart->Location = System::Drawing::Point(315, 38);
			this->btn_del_kostenart->Name = L"btn_del_kostenart";
			this->btn_del_kostenart->Size = System::Drawing::Size(23, 23);
			this->btn_del_kostenart->TabIndex = 2;
			this->btn_del_kostenart->UseVisualStyleBackColor = true;
			this->btn_del_kostenart->Click += gcnew System::EventHandler(this, &admin::btn_del_kostenart_Click);
			// 
			// btn_add_kostenart
			// 
			this->btn_add_kostenart->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_kostenart.Image")));
			this->btn_add_kostenart->Location = System::Drawing::Point(315, 89);
			this->btn_add_kostenart->Name = L"btn_add_kostenart";
			this->btn_add_kostenart->Size = System::Drawing::Size(23, 23);
			this->btn_add_kostenart->TabIndex = 5;
			this->btn_add_kostenart->UseVisualStyleBackColor = true;
			this->btn_add_kostenart->Click += gcnew System::EventHandler(this, &admin::btn_add_kostenart_Click);
			// 
			// btn_del_sach_ges
			// 
			this->btn_del_sach_ges->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_sach_ges.Image")));
			this->btn_del_sach_ges->Location = System::Drawing::Point(316, 142);
			this->btn_del_sach_ges->Name = L"btn_del_sach_ges";
			this->btn_del_sach_ges->Size = System::Drawing::Size(23, 23);
			this->btn_del_sach_ges->TabIndex = 7;
			this->btn_del_sach_ges->UseVisualStyleBackColor = true;
			this->btn_del_sach_ges->Click += gcnew System::EventHandler(this, &admin::btn_del_sach_ges_Click);
			// 
			// btn_add_sach_ges
			// 
			this->btn_add_sach_ges->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_sach_ges.Image")));
			this->btn_add_sach_ges->Location = System::Drawing::Point(315, 197);
			this->btn_add_sach_ges->Name = L"btn_add_sach_ges";
			this->btn_add_sach_ges->Size = System::Drawing::Size(23, 23);
			this->btn_add_sach_ges->TabIndex = 10;
			this->btn_add_sach_ges->UseVisualStyleBackColor = true;
			this->btn_add_sach_ges->Click += gcnew System::EventHandler(this, &admin::btn_add_sach_ges_Click);
			// 
			// btn_close
			// 
			this->btn_close->Location = System::Drawing::Point(13, 382);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(290, 21);
			this->btn_close->TabIndex = 2;
			this->btn_close->Text = L"Schließen";
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &admin::btn_close_Click);
			// 
			// tB_prog
			// 
			this->tB_prog->Location = System::Drawing::Point(89, 139);
			this->tB_prog->Name = L"tB_prog";
			this->tB_prog->Size = System::Drawing::Size(183, 20);
			this->tB_prog->TabIndex = 13;
			// 
			// tB_kostenart
			// 
			this->tB_kostenart->Location = System::Drawing::Point(116, 67);
			this->tB_kostenart->Name = L"tB_kostenart";
			this->tB_kostenart->Size = System::Drawing::Size(222, 20);
			this->tB_kostenart->TabIndex = 3;
			// 
			// tB_sach_gk
			// 
			this->tB_sach_gk->Location = System::Drawing::Point(116, 171);
			this->tB_sach_gk->Name = L"tB_sach_gk";
			this->tB_sach_gk->Size = System::Drawing::Size(222, 20);
			this->tB_sach_gk->TabIndex = 8;
			// 
			// tB_Strasse
			// 
			this->tB_Strasse->Location = System::Drawing::Point(88, 192);
			this->tB_Strasse->Name = L"tB_Strasse";
			this->tB_Strasse->Size = System::Drawing::Size(253, 20);
			this->tB_Strasse->TabIndex = 18;
			// 
			// btn_del_stasse
			// 
			this->btn_del_stasse->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_stasse.Image")));
			this->btn_del_stasse->Location = System::Drawing::Point(347, 164);
			this->btn_del_stasse->Name = L"btn_del_stasse";
			this->btn_del_stasse->Size = System::Drawing::Size(23, 23);
			this->btn_del_stasse->TabIndex = 17;
			this->btn_del_stasse->UseVisualStyleBackColor = true;
			this->btn_del_stasse->Click += gcnew System::EventHandler(this, &admin::btn_del_stasse_Click);
			// 
			// btn_add_strasse
			// 
			this->btn_add_strasse->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_strasse.Image")));
			this->btn_add_strasse->Location = System::Drawing::Point(347, 193);
			this->btn_add_strasse->Name = L"btn_add_strasse";
			this->btn_add_strasse->Size = System::Drawing::Size(23, 23);
			this->btn_add_strasse->TabIndex = 20;
			this->btn_add_strasse->UseVisualStyleBackColor = true;
			this->btn_add_strasse->Click += gcnew System::EventHandler(this, &admin::btn_add_strasse_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(12, 170);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(57, 13);
			this->label10->TabIndex = 31;
			this->label10->Text = L"Adressen :";
			// 
			// cB_Strassen
			// 
			this->cB_Strassen->FormattingEnabled = true;
			this->cB_Strassen->Location = System::Drawing::Point(89, 166);
			this->cB_Strassen->Name = L"cB_Strassen";
			this->cB_Strassen->Size = System::Drawing::Size(253, 21);
			this->cB_Strassen->Sorted = true;
			this->cB_Strassen->TabIndex = 16;
			this->cB_Strassen->TextChanged += gcnew System::EventHandler(this, &admin::cB_Strassen_TextChanged);
			// 
			// tB_FF
			// 
			this->tB_FF->Location = System::Drawing::Point(94, 113);
			this->tB_FF->Name = L"tB_FF";
			this->tB_FF->Size = System::Drawing::Size(244, 20);
			this->tB_FF->TabIndex = 3;
			// 
			// btn_del_ff
			// 
			this->btn_del_ff->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_ff.Image")));
			this->btn_del_ff->Location = System::Drawing::Point(344, 84);
			this->btn_del_ff->Name = L"btn_del_ff";
			this->btn_del_ff->Size = System::Drawing::Size(23, 23);
			this->btn_del_ff->TabIndex = 2;
			this->btn_del_ff->UseVisualStyleBackColor = true;
			this->btn_del_ff->Click += gcnew System::EventHandler(this, &admin::btn_del_ff_Click);
			// 
			// btn_add_ff
			// 
			this->btn_add_ff->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_ff.Image")));
			this->btn_add_ff->Location = System::Drawing::Point(344, 111);
			this->btn_add_ff->Name = L"btn_add_ff";
			this->btn_add_ff->Size = System::Drawing::Size(23, 23);
			this->btn_add_ff->TabIndex = 4;
			this->btn_add_ff->UseVisualStyleBackColor = true;
			this->btn_add_ff->Click += gcnew System::EventHandler(this, &admin::btn_add_ff_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(1, 90);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(87, 13);
			this->label13->TabIndex = 36;
			this->label13->Text = L"Fremdförderung :";
			// 
			// cB_FF
			// 
			this->cB_FF->FormattingEnabled = true;
			this->cB_FF->Location = System::Drawing::Point(94, 86);
			this->cB_FF->Name = L"cB_FF";
			this->cB_FF->Size = System::Drawing::Size(244, 21);
			this->cB_FF->Sorted = true;
			this->cB_FF->TabIndex = 1;
			this->cB_FF->TextChanged += gcnew System::EventHandler(this, &admin::cB_FF_TextChanged);
			// 
			// programm_nr
			// 
			this->programm_nr->Location = System::Drawing::Point(278, 139);
			this->programm_nr->Name = L"programm_nr";
			this->programm_nr->Size = System::Drawing::Size(63, 20);
			this->programm_nr->TabIndex = 14;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->Adresse);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(384, 282);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->tB_Strasse_Chiffre);
			this->tabPage1->Controls->Add(this->tB_gebiet);
			this->tabPage1->Controls->Add(this->btn_rem_gebiet);
			this->tabPage1->Controls->Add(this->btn_add_gebiet);
			this->tabPage1->Controls->Add(this->cB_gebiete);
			this->tabPage1->Controls->Add(this->label11);
			this->tabPage1->Controls->Add(this->tB_stadt);
			this->tabPage1->Controls->Add(this->programm_nr);
			this->tabPage1->Controls->Add(this->btn_del_stadt);
			this->tabPage1->Controls->Add(this->btn_add_stadt);
			this->tabPage1->Controls->Add(this->cB_staedte);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->cB_programme);
			this->tabPage1->Controls->Add(this->tB_Strasse);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->btn_del_stasse);
			this->tabPage1->Controls->Add(this->btn_del_prog);
			this->tabPage1->Controls->Add(this->btn_add_strasse);
			this->tabPage1->Controls->Add(this->tB_prog);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->btn_add_prog);
			this->tabPage1->Controls->Add(this->cB_Strassen);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(376, 256);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Stadt";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(87, 222);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(43, 13);
			this->label5->TabIndex = 38;
			this->label5->Text = L"Chiffre :";
			// 
			// tB_Strasse_Chiffre
			// 
			this->tB_Strasse_Chiffre->Location = System::Drawing::Point(136, 219);
			this->tB_Strasse_Chiffre->Name = L"tB_Strasse_Chiffre";
			this->tB_Strasse_Chiffre->Size = System::Drawing::Size(206, 20);
			this->tB_Strasse_Chiffre->TabIndex = 19;
			// 
			// tB_gebiet
			// 
			this->tB_gebiet->Location = System::Drawing::Point(90, 86);
			this->tB_gebiet->Name = L"tB_gebiet";
			this->tB_gebiet->Size = System::Drawing::Size(252, 20);
			this->tB_gebiet->TabIndex = 9;
			// 
			// btn_rem_gebiet
			// 
			this->btn_rem_gebiet->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_rem_gebiet.Image")));
			this->btn_rem_gebiet->Location = System::Drawing::Point(348, 58);
			this->btn_rem_gebiet->Name = L"btn_rem_gebiet";
			this->btn_rem_gebiet->Size = System::Drawing::Size(23, 23);
			this->btn_rem_gebiet->TabIndex = 8;
			this->btn_rem_gebiet->UseVisualStyleBackColor = true;
			this->btn_rem_gebiet->Click += gcnew System::EventHandler(this, &admin::btn_rem_gebiet_Click);
			// 
			// btn_add_gebiet
			// 
			this->btn_add_gebiet->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_gebiet.Image")));
			this->btn_add_gebiet->Location = System::Drawing::Point(348, 84);
			this->btn_add_gebiet->Name = L"btn_add_gebiet";
			this->btn_add_gebiet->Size = System::Drawing::Size(23, 23);
			this->btn_add_gebiet->TabIndex = 10;
			this->btn_add_gebiet->UseVisualStyleBackColor = true;
			this->btn_add_gebiet->Click += gcnew System::EventHandler(this, &admin::btn_add_gebiet_Click);
			// 
			// cB_gebiete
			// 
			this->cB_gebiete->FormattingEnabled = true;
			this->cB_gebiete->Location = System::Drawing::Point(90, 59);
			this->cB_gebiete->Name = L"cB_gebiete";
			this->cB_gebiete->Size = System::Drawing::Size(252, 21);
			this->cB_gebiete->Sorted = true;
			this->cB_gebiete->TabIndex = 7;
			this->cB_gebiete->TextChanged += gcnew System::EventHandler(this, &admin::cB_gebiete_TextChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(12, 62);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(50, 13);
			this->label11->TabIndex = 36;
			this->label11->Text = L"Gebiete :";
			// 
			// tB_stadt
			// 
			this->tB_stadt->Location = System::Drawing::Point(90, 33);
			this->tB_stadt->Name = L"tB_stadt";
			this->tB_stadt->Size = System::Drawing::Size(252, 20);
			this->tB_stadt->TabIndex = 5;
			// 
			// btn_del_stadt
			// 
			this->btn_del_stadt->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_stadt.Image")));
			this->btn_del_stadt->Location = System::Drawing::Point(348, 5);
			this->btn_del_stadt->Name = L"btn_del_stadt";
			this->btn_del_stadt->Size = System::Drawing::Size(23, 23);
			this->btn_del_stadt->TabIndex = 4;
			this->btn_del_stadt->UseVisualStyleBackColor = true;
			this->btn_del_stadt->Click += gcnew System::EventHandler(this, &admin::btn_del_stadt_Click_1);
			// 
			// btn_add_stadt
			// 
			this->btn_add_stadt->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_stadt.Image")));
			this->btn_add_stadt->Location = System::Drawing::Point(348, 31);
			this->btn_add_stadt->Name = L"btn_add_stadt";
			this->btn_add_stadt->Size = System::Drawing::Size(23, 23);
			this->btn_add_stadt->TabIndex = 6;
			this->btn_add_stadt->UseVisualStyleBackColor = true;
			this->btn_add_stadt->Click += gcnew System::EventHandler(this, &admin::btn_add_stadt_Click);
			// 
			// cB_staedte
			// 
			this->cB_staedte->FormattingEnabled = true;
			this->cB_staedte->Location = System::Drawing::Point(90, 6);
			this->cB_staedte->Name = L"cB_staedte";
			this->cB_staedte->Size = System::Drawing::Size(252, 21);
			this->cB_staedte->Sorted = true;
			this->cB_staedte->TabIndex = 3;
			this->cB_staedte->TextChanged += gcnew System::EventHandler(this, &admin::cB_staedte_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 26;
			this->label1->Text = L"Städte :";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage2->Controls->Add(this->label22);
			this->tabPage2->Controls->Add(this->label21);
			this->tabPage2->Controls->Add(this->label20);
			this->tabPage2->Controls->Add(this->label18);
			this->tabPage2->Controls->Add(this->tB_kostenart_nr);
			this->tabPage2->Controls->Add(this->tb_kostengr_abk);
			this->tabPage2->Controls->Add(this->cB_kostenart);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->cB_sachkonto_ges);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->btn_del_kostenart);
			this->tabPage2->Controls->Add(this->tB_kostenart);
			this->tabPage2->Controls->Add(this->btn_add_kostenart);
			this->tabPage2->Controls->Add(this->btn_del_sach_ges);
			this->tabPage2->Controls->Add(this->tB_sach_gk);
			this->tabPage2->Controls->Add(this->btn_add_sach_ges);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(376, 256);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Kostengruppe";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(45, 202);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(52, 13);
			this->label22->TabIndex = 14;
			this->label22->Text = L"Nummer :";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(46, 174);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(41, 13);
			this->label21->TabIndex = 13;
			this->label21->Text = L"Name :";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(46, 90);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(64, 13);
			this->label20->TabIndex = 12;
			this->label20->Text = L"Abkürzung :";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(46, 70);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(41, 13);
			this->label18->TabIndex = 11;
			this->label18->Text = L"Name :";
			// 
			// tB_kostenart_nr
			// 
			this->tB_kostenart_nr->Location = System::Drawing::Point(116, 197);
			this->tB_kostenart_nr->Name = L"tB_kostenart_nr";
			this->tB_kostenart_nr->Size = System::Drawing::Size(193, 20);
			this->tB_kostenart_nr->TabIndex = 9;
			// 
			// tb_kostengr_abk
			// 
			this->tb_kostengr_abk->Location = System::Drawing::Point(116, 92);
			this->tb_kostengr_abk->Name = L"tb_kostengr_abk";
			this->tb_kostengr_abk->Size = System::Drawing::Size(193, 20);
			this->tb_kostengr_abk->TabIndex = 4;
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage4->Controls->Add(this->label13);
			this->tabPage4->Controls->Add(this->btn_add_ff);
			this->tabPage4->Controls->Add(this->btn_del_ff);
			this->tabPage4->Controls->Add(this->tB_FF);
			this->tabPage4->Controls->Add(this->cB_FF);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(376, 256);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Fremdförderung";
			// 
			// tabPage5
			// 
			this->tabPage5->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage5->Controls->Add(this->gB_user);
			this->tabPage5->Controls->Add(this->btn_add_user);
			this->tabPage5->Controls->Add(this->tB_new_user);
			this->tabPage5->Controls->Add(this->label28);
			this->tabPage5->Controls->Add(this->lB_user);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(376, 256);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Nutzer";
			this->tabPage5->Enter += gcnew System::EventHandler(this, &admin::tabPage5_Enter);
			// 
			// gB_user
			// 
			this->gB_user->Controls->Add(this->btn_reset_pwd);
			this->gB_user->Controls->Add(this->label29);
			this->gB_user->Controls->Add(this->btn_del_user);
			this->gB_user->Controls->Add(this->lB_user_access);
			this->gB_user->Controls->Add(this->cB_user_is_admin);
			this->gB_user->Location = System::Drawing::Point(13, 126);
			this->gB_user->Name = L"gB_user";
			this->gB_user->Size = System::Drawing::Size(347, 116);
			this->gB_user->TabIndex = 4;
			this->gB_user->TabStop = false;
			this->gB_user->Text = L"User";
			// 
			// btn_reset_pwd
			// 
			this->btn_reset_pwd->Location = System::Drawing::Point(11, 47);
			this->btn_reset_pwd->Name = L"btn_reset_pwd";
			this->btn_reset_pwd->Size = System::Drawing::Size(101, 34);
			this->btn_reset_pwd->TabIndex = 2;
			this->btn_reset_pwd->Text = L"Passwort zurücksetzten";
			this->btn_reset_pwd->UseVisualStyleBackColor = true;
			this->btn_reset_pwd->Click += gcnew System::EventHandler(this, &admin::btn_reset_pwd_Click);
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(119, 25);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(61, 13);
			this->label29->TabIndex = 10;
			this->label29->Text = L"Zugriff auf :";
			// 
			// btn_del_user
			// 
			this->btn_del_user->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_del_user.Image")));
			this->btn_del_user->Location = System::Drawing::Point(48, 87);
			this->btn_del_user->Name = L"btn_del_user";
			this->btn_del_user->Size = System::Drawing::Size(23, 23);
			this->btn_del_user->TabIndex = 3;
			this->btn_del_user->UseVisualStyleBackColor = true;
			this->btn_del_user->Click += gcnew System::EventHandler(this, &admin::btn_del_user_Click);
			// 
			// lB_user_access
			// 
			this->lB_user_access->CheckOnClick = true;
			this->lB_user_access->FormattingEnabled = true;
			this->lB_user_access->Location = System::Drawing::Point(119, 46);
			this->lB_user_access->Name = L"lB_user_access";
			this->lB_user_access->Size = System::Drawing::Size(222, 64);
			this->lB_user_access->Sorted = true;
			this->lB_user_access->TabIndex = 4;
			this->lB_user_access->Click += gcnew System::EventHandler(this, &admin::lB_user_access_Click);
			// 
			// cB_user_is_admin
			// 
			this->cB_user_is_admin->AutoSize = true;
			this->cB_user_is_admin->Location = System::Drawing::Point(11, 24);
			this->cB_user_is_admin->Name = L"cB_user_is_admin";
			this->cB_user_is_admin->Size = System::Drawing::Size(102, 17);
			this->cB_user_is_admin->TabIndex = 1;
			this->cB_user_is_admin->Text = L"Nutzer ist Admin";
			this->cB_user_is_admin->UseVisualStyleBackColor = true;
			this->cB_user_is_admin->CheckedChanged += gcnew System::EventHandler(this, &admin::cB_user_is_admin_CheckedChanged);
			// 
			// btn_add_user
			// 
			this->btn_add_user->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btn_add_user.Image")));
			this->btn_add_user->Location = System::Drawing::Point(338, 9);
			this->btn_add_user->Name = L"btn_add_user";
			this->btn_add_user->Size = System::Drawing::Size(23, 23);
			this->btn_add_user->TabIndex = 2;
			this->btn_add_user->UseVisualStyleBackColor = true;
			this->btn_add_user->Click += gcnew System::EventHandler(this, &admin::btn_add_user_Click);
			// 
			// tB_new_user
			// 
			this->tB_new_user->Location = System::Drawing::Point(90, 11);
			this->tB_new_user->Name = L"tB_new_user";
			this->tB_new_user->Size = System::Drawing::Size(242, 20);
			this->tB_new_user->TabIndex = 1;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(10, 14);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(74, 13);
			this->label28->TabIndex = 1;
			this->label28->Text = L"neuer Nutzer :";
			// 
			// lB_user
			// 
			this->lB_user->FormattingEnabled = true;
			this->lB_user->Location = System::Drawing::Point(13, 38);
			this->lB_user->Name = L"lB_user";
			this->lB_user->Size = System::Drawing::Size(348, 82);
			this->lB_user->Sorted = true;
			this->lB_user->TabIndex = 3;
			this->lB_user->SelectedIndexChanged += gcnew System::EventHandler(this, &admin::lB_user_SelectedIndexChanged);
			// 
			// Adresse
			// 
			this->Adresse->BackColor = System::Drawing::SystemColors::Control;
			this->Adresse->Controls->Add(this->btn_save);
			this->Adresse->Controls->Add(this->tB_ort);
			this->Adresse->Controls->Add(this->tB_plz);
			this->Adresse->Controls->Add(this->tB_hausnr);
			this->Adresse->Controls->Add(this->tB_ansch_strasse);
			this->Adresse->Controls->Add(this->tB_name);
			this->Adresse->Controls->Add(this->label27);
			this->Adresse->Controls->Add(this->label26);
			this->Adresse->Controls->Add(this->label25);
			this->Adresse->Controls->Add(this->label24);
			this->Adresse->Controls->Add(this->label23);
			this->Adresse->Location = System::Drawing::Point(4, 22);
			this->Adresse->Name = L"Adresse";
			this->Adresse->Size = System::Drawing::Size(376, 256);
			this->Adresse->TabIndex = 6;
			this->Adresse->Text = L"Anschrift";
			this->Adresse->Enter += gcnew System::EventHandler(this, &admin::Adresse_Enter);
			// 
			// btn_save
			// 
			this->btn_save->Location = System::Drawing::Point(17, 183);
			this->btn_save->Name = L"btn_save";
			this->btn_save->Size = System::Drawing::Size(342, 24);
			this->btn_save->TabIndex = 10;
			this->btn_save->Text = L"Speichern";
			this->btn_save->UseVisualStyleBackColor = true;
			this->btn_save->Click += gcnew System::EventHandler(this, &admin::btn_save_Click);
			// 
			// tB_ort
			// 
			this->tB_ort->Location = System::Drawing::Point(67, 156);
			this->tB_ort->Name = L"tB_ort";
			this->tB_ort->Size = System::Drawing::Size(293, 20);
			this->tB_ort->TabIndex = 9;
			// 
			// tB_plz
			// 
			this->tB_plz->Location = System::Drawing::Point(67, 130);
			this->tB_plz->Name = L"tB_plz";
			this->tB_plz->Size = System::Drawing::Size(293, 20);
			this->tB_plz->TabIndex = 8;
			// 
			// tB_hausnr
			// 
			this->tB_hausnr->Location = System::Drawing::Point(67, 101);
			this->tB_hausnr->Name = L"tB_hausnr";
			this->tB_hausnr->Size = System::Drawing::Size(293, 20);
			this->tB_hausnr->TabIndex = 7;
			// 
			// tB_ansch_strasse
			// 
			this->tB_ansch_strasse->Location = System::Drawing::Point(67, 71);
			this->tB_ansch_strasse->Name = L"tB_ansch_strasse";
			this->tB_ansch_strasse->Size = System::Drawing::Size(293, 20);
			this->tB_ansch_strasse->TabIndex = 6;
			// 
			// tB_name
			// 
			this->tB_name->Location = System::Drawing::Point(67, 45);
			this->tB_name->Name = L"tB_name";
			this->tB_name->Size = System::Drawing::Size(293, 20);
			this->tB_name->TabIndex = 5;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(14, 133);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(33, 13);
			this->label27->TabIndex = 4;
			this->label27->Text = L"PLZ :";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(16, 159);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(27, 13);
			this->label26->TabIndex = 3;
			this->label26->Text = L"Ort :";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(13, 104);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(47, 13);
			this->label25->TabIndex = 2;
			this->label25->Text = L"Hausnr.:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(12, 74);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(44, 13);
			this->label24->TabIndex = 1;
			this->label24->Text = L"Straße :";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(13, 48);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(41, 13);
			this->label23->TabIndex = 0;
			this->label23->Text = L"Name :";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Location = System::Drawing::Point(13, 315);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(379, 61);
			this->groupBox1->TabIndex = 44;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Hinweis";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(67, 35);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(192, 13);
			this->label8->TabIndex = 48;
			this->label8->Text = L"in der Projekterstellung nicht angezeigt.";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(27, 22);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(276, 13);
			this->label6->TabIndex = 47;
			this->label6->Text = L"Sollte ein Eintrag leere Abhängigkeiten haben, so wird er ";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(309, 386);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(83, 13);
			this->label19->TabIndex = 45;
			this->label19->Text = L"© 2012 by MKS";
			// 
			// admin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(408, 415);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->btn_close);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"admin";
			this->Text = L"Administrationbereich";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			this->tabPage5->PerformLayout();
			this->gB_user->ResumeLayout(false);
			this->gB_user->PerformLayout();
			this->Adresse->ResumeLayout(false);
			this->Adresse->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// #### Konstruktor ####
		private: 
		void load_stadt_entries();
		void load_gebiet_entries();
		void load_program_entries();
		void load_sach_ges_entries();
		void load_kostenart_entries();
		void load_ff_entries();
		void load_strassen_entries();

		void cB_staedte_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void cB_gebiete_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void cB_programme_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void cB_kostenart_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void cB_sachkonto_ges_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void cB_FF_TextChanged(System::Object^  sender, System::EventArgs^  e);
		void cB_Strassen_TextChanged(System::Object^  sender, System::EventArgs^  e);

		void btn_close_Click(System::Object^  sender, System::EventArgs^  e) {Close();}

		void btn_del_stadt_Click_1(System::Object^  sender, System::EventArgs^  e);
		void btn_rem_gebiet_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_del_prog_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_del_kostenart_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_del_sach_ges_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_del_stasse_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_del_ff_Click(System::Object^  sender, System::EventArgs^  e);
		bool del_warning();

		void btn_add_stadt_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_add_gebiet_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_add_prog_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_add_kostenart_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_add_sach_ges_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_add_strasse_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_add_ff_Click(System::Object^  sender, System::EventArgs^  e);

		// Anschrift
		void btn_save_Click(System::Object^  sender, System::EventArgs^  e);
		void Adresse_Enter(System::Object^  sender, System::EventArgs^  e);

		// Typstuff
		bool date_is_bigger(String^,String^);

		// User
		void tabPage5_Enter(System::Object^  sender, System::EventArgs^  e);
		void load_user();
		void load_user_cities();
		void load_user_access();
		void lB_user_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void btn_add_user_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_del_user_Click(System::Object^  sender, System::EventArgs^  e);
		void cB_user_is_admin_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void lB_user_access_Click(System::Object^  sender, System::EventArgs^  e);
		void btn_reset_pwd_Click(System::Object^  sender, System::EventArgs^  e);
};
}
