#pragma once

#include "project_class.h"
#include "bewilligung_form.h"

namespace Datenbank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für project_form
	/// </summary>
	public ref class project_form : public System::Windows::Forms::Form
	{
	public:
		project_form(int user_id):
			projekt_(gcnew project_class),
			swap_this_(-1),
			allow_swap_(false),
			loaded_(false),
			user_id_(user_id),
			stadt_ids_(gcnew List<String^>),
			load_std_(true)
		{
			InitializeComponent();
		}

		project_form(int id,int user_id):
			projekt_(gcnew project_class(id)),
			swap_this_(-1),
			allow_swap_(false),
			loaded_(false),
			user_id_(user_id),
			stadt_ids_(gcnew List<String^>),
			load_std_(true)
		{
			InitializeComponent();

		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~project_form()
		{
			if (components)
			{
				delete components;
			}
		}

	private: project_class^ projekt_;
			 int swap_this_;
			 bool allow_swap_;
			 bool loaded_;
			 bool vn_einger_;
			 int user_id_;
			 List<String^>^ stadt_ids_;
			 bool load_std_;

	private: System::Windows::Forms::ComboBox^  kostenart;

	protected: 

	private: System::Windows::Forms::TextBox^  bezeichnung;

	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::GroupBox^  gB_gk;
	private: System::Windows::Forms::TextBox^  gk_zuwendungsf;
	private: System::Windows::Forms::TextBox^  gk_real;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  bew_ztr;
	private: System::Windows::Forms::Button^  btn_save;
	private: System::Windows::Forms::Button^  btn_del;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ListBox^  programme;
	private: System::Windows::Forms::Button^  add_programm;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ComboBox^  programm;
	private: System::Windows::Forms::Button^  del_programm;
	private: System::Windows::Forms::Button^  del_bewilligung;
	private: System::Windows::Forms::Button^  add_bewilligung;
	private: System::Windows::Forms::ListBox^  bewilligungen;
	private: System::Windows::Forms::Button^  btn_VN;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ComboBox^  kostengruppe;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  vn_eingereicht;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  vn_geprueft;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::ComboBox^  bha_sk;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  aenderungsbescheid;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  foeuvh;
	private: System::Windows::Forms::TextBox^  bha_betrag;
	private: System::Windows::Forms::TextBox^  foerderbetrag;
	private: System::Windows::Forms::TextBox^  mla;
	private: System::Windows::Forms::TextBox^  fremdfoerderung;
	private: System::Windows::Forms::TextBox^  mehr_minderkosten;
	private: System::Windows::Forms::ComboBox^  stadt;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  add_strasse;
	private: System::Windows::Forms::Button^  rem_strasse;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  strasse;
	private: System::Windows::Forms::ListBox^  strassen;
	private: System::Windows::Forms::ComboBox^  gebiet;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  bemerkung;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  kostenart_nr;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Button^  btn_print;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(project_form::typeid));
			this->kostenart = (gcnew System::Windows::Forms::ComboBox());
			this->bezeichnung = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->gB_gk = (gcnew System::Windows::Forms::GroupBox());
			this->gk_zuwendungsf = (gcnew System::Windows::Forms::TextBox());
			this->gk_real = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->bew_ztr = (gcnew System::Windows::Forms::TextBox());
			this->btn_save = (gcnew System::Windows::Forms::Button());
			this->btn_del = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->add_programm = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->programm = (gcnew System::Windows::Forms::ComboBox());
			this->del_bewilligung = (gcnew System::Windows::Forms::Button());
			this->del_programm = (gcnew System::Windows::Forms::Button());
			this->add_bewilligung = (gcnew System::Windows::Forms::Button());
			this->programme = (gcnew System::Windows::Forms::ListBox());
			this->bewilligungen = (gcnew System::Windows::Forms::ListBox());
			this->btn_VN = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->kostengruppe = (gcnew System::Windows::Forms::ComboBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->vn_eingereicht = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->vn_geprueft = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->bha_betrag = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->bha_sk = (gcnew System::Windows::Forms::ComboBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->aenderungsbescheid = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->foerderbetrag = (gcnew System::Windows::Forms::TextBox());
			this->mla = (gcnew System::Windows::Forms::TextBox());
			this->fremdfoerderung = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->foeuvh = (gcnew System::Windows::Forms::TextBox());
			this->mehr_minderkosten = (gcnew System::Windows::Forms::TextBox());
			this->stadt = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->add_strasse = (gcnew System::Windows::Forms::Button());
			this->rem_strasse = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->strasse = (gcnew System::Windows::Forms::ComboBox());
			this->strassen = (gcnew System::Windows::Forms::ListBox());
			this->gebiet = (gcnew System::Windows::Forms::ComboBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->bemerkung = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->kostenart_nr = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->gB_gk->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// kostenart
			// 
			this->kostenart->FormattingEnabled = true;
			this->kostenart->Location = System::Drawing::Point(20, 160);
			this->kostenart->Name = L"kostenart";
			this->kostenart->Size = System::Drawing::Size(290, 21);
			this->kostenart->Sorted = true;
			this->kostenart->TabIndex = 5;
			this->kostenart->Tag = L"kostenart";
			this->kostenart->TextChanged += gcnew System::EventHandler(this, &project_form::kostenart_TextChanged);
			// 
			// bezeichnung
			// 
			this->bezeichnung->BackColor = System::Drawing::Color::LavenderBlush;
			this->bezeichnung->Location = System::Drawing::Point(94, 12);
			this->bezeichnung->Name = L"bezeichnung";
			this->bezeichnung->Size = System::Drawing::Size(532, 20);
			this->bezeichnung->TabIndex = 1;
			this->bezeichnung->TextChanged += gcnew System::EventHandler(this, &project_form::bezeichnung_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 144);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Kostenart :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 15);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Bezeichnung :";
			// 
			// gB_gk
			// 
			this->gB_gk->Controls->Add(this->gk_zuwendungsf);
			this->gB_gk->Controls->Add(this->gk_real);
			this->gB_gk->Controls->Add(this->label4);
			this->gB_gk->Controls->Add(this->label3);
			this->gB_gk->Location = System::Drawing::Point(16, 187);
			this->gB_gk->Name = L"gB_gk";
			this->gB_gk->Size = System::Drawing::Size(294, 119);
			this->gB_gk->TabIndex = 6;
			this->gB_gk->TabStop = false;
			this->gB_gk->Text = L"Gesamtkosten";
			// 
			// gk_zuwendungsf
			// 
			this->gk_zuwendungsf->Location = System::Drawing::Point(14, 82);
			this->gk_zuwendungsf->Name = L"gk_zuwendungsf";
			this->gk_zuwendungsf->Size = System::Drawing::Size(259, 20);
			this->gk_zuwendungsf->TabIndex = 2;
			this->gk_zuwendungsf->TextChanged += gcnew System::EventHandler(this, &project_form::gk_zuwendungsf_TextChanged);
			this->gk_zuwendungsf->Leave += gcnew System::EventHandler(this, &project_form::gk_zuwendungsf_Leave);
			// 
			// gk_real
			// 
			this->gk_real->Location = System::Drawing::Point(14, 38);
			this->gk_real->Name = L"gk_real";
			this->gk_real->Size = System::Drawing::Size(259, 20);
			this->gk_real->TabIndex = 1;
			this->gk_real->TextChanged += gcnew System::EventHandler(this, &project_form::gk_real_TextChanged);
			this->gk_real->Leave += gcnew System::EventHandler(this, &project_form::gk_real_Leave);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(11, 66);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(173, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"zuwendungsfähige Gesamtkosten :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 22);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(107, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"reale Gesamtkosten :";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(10, 91);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(110, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"Bewilligungszeitraum :";
			// 
			// bew_ztr
			// 
			this->bew_ztr->BackColor = System::Drawing::Color::LavenderBlush;
			this->bew_ztr->Location = System::Drawing::Point(120, 88);
			this->bew_ztr->Name = L"bew_ztr";
			this->bew_ztr->Size = System::Drawing::Size(190, 20);
			this->bew_ztr->TabIndex = 3;
			this->bew_ztr->TextChanged += gcnew System::EventHandler(this, &project_form::bew_ztr_TextChanged);
			this->bew_ztr->Leave += gcnew System::EventHandler(this, &project_form::bew_ztr_Leave);
			// 
			// btn_save
			// 
			this->btn_save->Location = System::Drawing::Point(14, 598);
			this->btn_save->Name = L"btn_save";
			this->btn_save->Size = System::Drawing::Size(296, 25);
			this->btn_save->TabIndex = 21;
			this->btn_save->Text = L"Speichern";
			this->btn_save->UseVisualStyleBackColor = true;
			this->btn_save->Click += gcnew System::EventHandler(this, &project_form::btn_save_Click);
			// 
			// btn_del
			// 
			this->btn_del->Location = System::Drawing::Point(14, 567);
			this->btn_del->Name = L"btn_del";
			this->btn_del->Size = System::Drawing::Size(296, 25);
			this->btn_del->TabIndex = 20;
			this->btn_del->Text = L"Projekt Löschen";
			this->btn_del->UseVisualStyleBackColor = true;
			this->btn_del->Click += gcnew System::EventHandler(this, &project_form::btn_del_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(14, 629);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(296, 25);
			this->button5->TabIndex = 22;
			this->button5->Text = L"Schließen";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &project_form::button5_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->add_programm);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->programm);
			this->groupBox1->Controls->Add(this->del_bewilligung);
			this->groupBox1->Controls->Add(this->del_programm);
			this->groupBox1->Controls->Add(this->add_bewilligung);
			this->groupBox1->Controls->Add(this->programme);
			this->groupBox1->Controls->Add(this->bewilligungen);
			this->groupBox1->Location = System::Drawing::Point(326, 210);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(306, 193);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Programme und Bewilligungen";
			// 
			// add_programm
			// 
			this->add_programm->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"add_programm.Image")));
			this->add_programm->Location = System::Drawing::Point(248, 14);
			this->add_programm->Name = L"add_programm";
			this->add_programm->Size = System::Drawing::Size(23, 23);
			this->add_programm->TabIndex = 2;
			this->add_programm->UseVisualStyleBackColor = true;
			this->add_programm->Click += gcnew System::EventHandler(this, &project_form::add_programm_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(4, 20);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(92, 13);
			this->label8->TabIndex = 35;
			this->label8->Text = L"neues Programm :";
			// 
			// programm
			// 
			this->programm->FormattingEnabled = true;
			this->programm->Location = System::Drawing::Point(102, 17);
			this->programm->Name = L"programm";
			this->programm->Size = System::Drawing::Size(140, 21);
			this->programm->Sorted = true;
			this->programm->TabIndex = 1;
			this->programm->TextChanged += gcnew System::EventHandler(this, &project_form::programm_TextChanged);
			// 
			// del_bewilligung
			// 
			this->del_bewilligung->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"del_bewilligung.Image")));
			this->del_bewilligung->Location = System::Drawing::Point(277, 154);
			this->del_bewilligung->Name = L"del_bewilligung";
			this->del_bewilligung->Size = System::Drawing::Size(23, 23);
			this->del_bewilligung->TabIndex = 7;
			this->del_bewilligung->UseVisualStyleBackColor = true;
			this->del_bewilligung->Click += gcnew System::EventHandler(this, &project_form::del_bewilligung_Click);
			// 
			// del_programm
			// 
			this->del_programm->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"del_programm.Image")));
			this->del_programm->Location = System::Drawing::Point(277, 14);
			this->del_programm->Name = L"del_programm";
			this->del_programm->Size = System::Drawing::Size(23, 23);
			this->del_programm->TabIndex = 3;
			this->del_programm->UseVisualStyleBackColor = true;
			this->del_programm->Click += gcnew System::EventHandler(this, &project_form::del_programm_Click);
			// 
			// add_bewilligung
			// 
			this->add_bewilligung->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"add_bewilligung.Image")));
			this->add_bewilligung->Location = System::Drawing::Point(277, 125);
			this->add_bewilligung->Name = L"add_bewilligung";
			this->add_bewilligung->Size = System::Drawing::Size(23, 23);
			this->add_bewilligung->TabIndex = 6;
			this->add_bewilligung->UseVisualStyleBackColor = true;
			this->add_bewilligung->Click += gcnew System::EventHandler(this, &project_form::add_bewilligung_Click);
			// 
			// programme
			// 
			this->programme->FormattingEnabled = true;
			this->programme->Location = System::Drawing::Point(7, 45);
			this->programme->Name = L"programme";
			this->programme->Size = System::Drawing::Size(293, 69);
			this->programme->Sorted = true;
			this->programme->TabIndex = 4;
			this->programme->Click += gcnew System::EventHandler(this, &project_form::programme_Click);
			this->programme->SelectedIndexChanged += gcnew System::EventHandler(this, &project_form::programme_SelectedIndexChanged);
			// 
			// bewilligungen
			// 
			this->bewilligungen->FormattingEnabled = true;
			this->bewilligungen->Location = System::Drawing::Point(7, 125);
			this->bewilligungen->Name = L"bewilligungen";
			this->bewilligungen->Size = System::Drawing::Size(264, 56);
			this->bewilligungen->TabIndex = 5;
			this->bewilligungen->DoubleClick += gcnew System::EventHandler(this, &project_form::bewilligungen_DoubleClick);
			this->bewilligungen->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &project_form::bewilligungen_MouseDown);
			this->bewilligungen->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &project_form::bewilligungen_MouseUp);
			// 
			// btn_VN
			// 
			this->btn_VN->Location = System::Drawing::Point(326, 438);
			this->btn_VN->Name = L"btn_VN";
			this->btn_VN->Size = System::Drawing::Size(300, 25);
			this->btn_VN->TabIndex = 16;
			this->btn_VN->Text = L"Verwendungsnachweis";
			this->btn_VN->UseVisualStyleBackColor = true;
			this->btn_VN->Click += gcnew System::EventHandler(this, &project_form::btn_VN_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(16, 117);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(79, 13);
			this->label10->TabIndex = 33;
			this->label10->Text = L"Kostengruppe :";
			// 
			// kostengruppe
			// 
			this->kostengruppe->FormattingEnabled = true;
			this->kostengruppe->Location = System::Drawing::Point(97, 114);
			this->kostengruppe->Name = L"kostengruppe";
			this->kostengruppe->Size = System::Drawing::Size(213, 21);
			this->kostengruppe->Sorted = true;
			this->kostengruppe->TabIndex = 4;
			this->kostengruppe->TextChanged += gcnew System::EventHandler(this, &project_form::kostengruppe_TextChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(322, 527);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(112, 13);
			this->label9->TabIndex = 35;
			this->label9->Text = L"Mehr-/ Minderkosten :";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(323, 472);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(83, 13);
			this->label11->TabIndex = 37;
			this->label11->Text = L"VN eingereicht :";
			// 
			// vn_eingereicht
			// 
			this->vn_eingereicht->Location = System::Drawing::Point(433, 469);
			this->vn_eingereicht->Name = L"vn_eingereicht";
			this->vn_eingereicht->Size = System::Drawing::Size(190, 20);
			this->vn_eingereicht->TabIndex = 17;
			this->vn_eingereicht->TextChanged += gcnew System::EventHandler(this, &project_form::vn_eingereicht_TextChanged);
			this->vn_eingereicht->Leave += gcnew System::EventHandler(this, &project_form::vn_eingereicht_Leave);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(323, 498);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(64, 13);
			this->label12->TabIndex = 39;
			this->label12->Text = L"VN geprüft :";
			// 
			// vn_geprueft
			// 
			this->vn_geprueft->Location = System::Drawing::Point(433, 495);
			this->vn_geprueft->Name = L"vn_geprueft";
			this->vn_geprueft->Size = System::Drawing::Size(190, 20);
			this->vn_geprueft->TabIndex = 18;
			this->vn_geprueft->TextChanged += gcnew System::EventHandler(this, &project_form::vn_geprueft_TextChanged);
			this->vn_geprueft->Leave += gcnew System::EventHandler(this, &project_form::vn_geprueft_Leave);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->bha_betrag);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->bha_sk);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Location = System::Drawing::Point(17, 415);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(294, 78);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Bauherrenanteil ";
			// 
			// bha_betrag
			// 
			this->bha_betrag->BackColor = System::Drawing::SystemColors::Menu;
			this->bha_betrag->Enabled = false;
			this->bha_betrag->Location = System::Drawing::Point(88, 19);
			this->bha_betrag->Name = L"bha_betrag";
			this->bha_betrag->Size = System::Drawing::Size(199, 20);
			this->bha_betrag->TabIndex = 13;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(7, 48);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(65, 13);
			this->label17->TabIndex = 8;
			this->label17->Text = L"Sachkonto :";
			// 
			// bha_sk
			// 
			this->bha_sk->FormattingEnabled = true;
			this->bha_sk->Location = System::Drawing::Point(88, 45);
			this->bha_sk->Name = L"bha_sk";
			this->bha_sk->Size = System::Drawing::Size(200, 21);
			this->bha_sk->Sorted = true;
			this->bha_sk->TabIndex = 1;
			this->bha_sk->TextChanged += gcnew System::EventHandler(this, &project_form::bha_sk_TextChanged);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(11, 22);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(44, 13);
			this->label18->TabIndex = 4;
			this->label18->Text = L"Betrag :";
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(14, 503);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(294, 25);
			this->button10->TabIndex = 19;
			this->button10->Text = L"Fremdförderung";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &project_form::button10_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(320, 416);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(107, 13);
			this->label16->TabIndex = 39;
			this->label16->Text = L"Änderungsbescheid :";
			// 
			// aenderungsbescheid
			// 
			this->aenderungsbescheid->Location = System::Drawing::Point(433, 409);
			this->aenderungsbescheid->Name = L"aenderungsbescheid";
			this->aenderungsbescheid->Size = System::Drawing::Size(190, 20);
			this->aenderungsbescheid->TabIndex = 15;
			this->aenderungsbescheid->TextChanged += gcnew System::EventHandler(this, &project_form::aenderungsbescheid_TextChanged);
			this->aenderungsbescheid->Leave += gcnew System::EventHandler(this, &project_form::aenderungsbescheid_Leave);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->foerderbetrag);
			this->groupBox5->Controls->Add(this->mla);
			this->groupBox5->Controls->Add(this->fremdfoerderung);
			this->groupBox5->Controls->Add(this->label13);
			this->groupBox5->Controls->Add(this->label19);
			this->groupBox5->Controls->Add(this->label20);
			this->groupBox5->Location = System::Drawing::Point(16, 312);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(294, 97);
			this->groupBox5->TabIndex = 53;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Gesamtförderung";
			// 
			// foerderbetrag
			// 
			this->foerderbetrag->BackColor = System::Drawing::SystemColors::Menu;
			this->foerderbetrag->Enabled = false;
			this->foerderbetrag->Location = System::Drawing::Point(136, 19);
			this->foerderbetrag->Name = L"foerderbetrag";
			this->foerderbetrag->Size = System::Drawing::Size(152, 20);
			this->foerderbetrag->TabIndex = 12;
			// 
			// mla
			// 
			this->mla->BackColor = System::Drawing::SystemColors::Menu;
			this->mla->Enabled = false;
			this->mla->Location = System::Drawing::Point(136, 45);
			this->mla->Name = L"mla";
			this->mla->Size = System::Drawing::Size(152, 20);
			this->mla->TabIndex = 11;
			// 
			// fremdfoerderung
			// 
			this->fremdfoerderung->BackColor = System::Drawing::SystemColors::Menu;
			this->fremdfoerderung->Enabled = false;
			this->fremdfoerderung->Location = System::Drawing::Point(136, 71);
			this->fremdfoerderung->Name = L"fremdfoerderung";
			this->fremdfoerderung->Size = System::Drawing::Size(152, 20);
			this->fremdfoerderung->TabIndex = 10;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(7, 74);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(120, 13);
			this->label13->TabIndex = 9;
			this->label13->Text = L"Gesamtfremdförderung :";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(7, 48);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(74, 13);
			this->label19->TabIndex = 8;
			this->label19->Text = L"Gesamt-MLA :";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(8, 22);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(109, 13);
			this->label20->TabIndex = 4;
			this->label20->Text = L"Gesamtförderbetrag  :";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(13, 39);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(218, 13);
			this->label14->TabIndex = 55;
			this->label14->Text = L"Förderungsunschädlicher Vorhabensbeginn :";
			// 
			// foeuvh
			// 
			this->foeuvh->Location = System::Drawing::Point(120, 58);
			this->foeuvh->Name = L"foeuvh";
			this->foeuvh->Size = System::Drawing::Size(190, 20);
			this->foeuvh->TabIndex = 2;
			this->foeuvh->TextChanged += gcnew System::EventHandler(this, &project_form::foeuvh_TextChanged);
			this->foeuvh->Leave += gcnew System::EventHandler(this, &project_form::foeuvh_Leave);
			// 
			// mehr_minderkosten
			// 
			this->mehr_minderkosten->BackColor = System::Drawing::SystemColors::Menu;
			this->mehr_minderkosten->Enabled = false;
			this->mehr_minderkosten->Location = System::Drawing::Point(433, 521);
			this->mehr_minderkosten->Name = L"mehr_minderkosten";
			this->mehr_minderkosten->Size = System::Drawing::Size(190, 20);
			this->mehr_minderkosten->TabIndex = 56;
			// 
			// stadt
			// 
			this->stadt->FormattingEnabled = true;
			this->stadt->Location = System::Drawing::Point(373, 35);
			this->stadt->Name = L"stadt";
			this->stadt->Size = System::Drawing::Size(253, 21);
			this->stadt->Sorted = true;
			this->stadt->TabIndex = 8;
			this->stadt->TextChanged += gcnew System::EventHandler(this, &project_form::stadt_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(329, 39);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(38, 13);
			this->label6->TabIndex = 62;
			this->label6->Text = L"Stadt :";
			// 
			// add_strasse
			// 
			this->add_strasse->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"add_strasse.Image")));
			this->add_strasse->Location = System::Drawing::Point(574, 94);
			this->add_strasse->Name = L"add_strasse";
			this->add_strasse->Size = System::Drawing::Size(23, 23);
			this->add_strasse->TabIndex = 11;
			this->add_strasse->UseVisualStyleBackColor = true;
			this->add_strasse->Click += gcnew System::EventHandler(this, &project_form::add_strasse_Click);
			// 
			// rem_strasse
			// 
			this->rem_strasse->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"rem_strasse.Image")));
			this->rem_strasse->Location = System::Drawing::Point(603, 94);
			this->rem_strasse->Name = L"rem_strasse";
			this->rem_strasse->Size = System::Drawing::Size(23, 23);
			this->rem_strasse->TabIndex = 12;
			this->rem_strasse->UseVisualStyleBackColor = true;
			this->rem_strasse->Click += gcnew System::EventHandler(this, &project_form::rem_strasse_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(330, 99);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(78, 13);
			this->label7->TabIndex = 69;
			this->label7->Text = L"neue Adresse :";
			// 
			// strasse
			// 
			this->strasse->FormattingEnabled = true;
			this->strasse->Location = System::Drawing::Point(414, 96);
			this->strasse->Name = L"strasse";
			this->strasse->Size = System::Drawing::Size(154, 21);
			this->strasse->Sorted = true;
			this->strasse->TabIndex = 10;
			// 
			// strassen
			// 
			this->strassen->ForeColor = System::Drawing::SystemColors::WindowText;
			this->strassen->FormattingEnabled = true;
			this->strassen->Location = System::Drawing::Point(332, 122);
			this->strassen->Name = L"strassen";
			this->strassen->Size = System::Drawing::Size(293, 82);
			this->strassen->Sorted = true;
			this->strassen->TabIndex = 13;
			this->strassen->DoubleClick += gcnew System::EventHandler(this, &project_form::strassen_DoubleClick);
			// 
			// gebiet
			// 
			this->gebiet->FormattingEnabled = true;
			this->gebiet->Location = System::Drawing::Point(373, 62);
			this->gebiet->Name = L"gebiet";
			this->gebiet->Size = System::Drawing::Size(253, 21);
			this->gebiet->Sorted = true;
			this->gebiet->TabIndex = 9;
			this->gebiet->TextChanged += gcnew System::EventHandler(this, &project_form::gebiet_TextChanged);
			// 
			// label21
			// 
			this->label21->Location = System::Drawing::Point(319, 62);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(48, 13);
			this->label21->TabIndex = 71;
			this->label21->Text = L"Gebiet :";
			this->label21->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// bemerkung
			// 
			this->bemerkung->Location = System::Drawing::Point(323, 561);
			this->bemerkung->Multiline = true;
			this->bemerkung->Name = L"bemerkung";
			this->bemerkung->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->bemerkung->Size = System::Drawing::Size(295, 92);
			this->bemerkung->TabIndex = 72;
			this->bemerkung->TextChanged += gcnew System::EventHandler(this, &project_form::bemerkung_TextChanged);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(321, 545);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(79, 13);
			this->label22->TabIndex = 73;
			this->label22->Text = L"Bemerkungen :";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(187, 144);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(71, 13);
			this->label23->TabIndex = 74;
			this->label23->Text = L"( Sachkonto :";
			// 
			// kostenart_nr
			// 
			this->kostenart_nr->AutoSize = true;
			this->kostenart_nr->Location = System::Drawing::Point(265, 144);
			this->kostenart_nr->Name = L"kostenart_nr";
			this->kostenart_nr->Size = System::Drawing::Size(0, 13);
			this->kostenart_nr->TabIndex = 75;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(11, 661);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(108, 13);
			this->label15->TabIndex = 76;
			this->label15->Text = L"FÖRDI  © 2012 MKS";
			// 
			// btn_print
			// 
			this->btn_print->Location = System::Drawing::Point(14, 534);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(296, 25);
			this->btn_print->TabIndex = 77;
			this->btn_print->Text = L"Drucken";
			this->btn_print->UseVisualStyleBackColor = true;
			this->btn_print->Click += gcnew System::EventHandler(this, &project_form::btn_print_Click);
			// 
			// project_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(637, 678);
			this->Controls->Add(this->btn_print);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->kostenart_nr);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->bemerkung);
			this->Controls->Add(this->gebiet);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->add_strasse);
			this->Controls->Add(this->rem_strasse);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->strasse);
			this->Controls->Add(this->strassen);
			this->Controls->Add(this->stadt);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->mehr_minderkosten);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->foeuvh);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->aenderungsbescheid);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->vn_geprueft);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->vn_eingereicht);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->kostengruppe);
			this->Controls->Add(this->btn_VN);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->btn_del);
			this->Controls->Add(this->btn_save);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->bew_ztr);
			this->Controls->Add(this->gB_gk);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->bezeichnung);
			this->Controls->Add(this->kostenart);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"project_form";
			this->Text = L"Projekt";
			this->Load += gcnew System::EventHandler(this, &project_form::project_form_Load);
			this->gB_gk->ResumeLayout(false);
			this->gB_gk->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: 
	// ComboBox Einträge laden
	System::Void project_form_Load(System::Object^  sender, System::EventArgs^  e);
	bool load_kostengruppe();
	bool load_kostenart();
	bool load_sachkonto_bha();
	bool load_stadt();
	bool load_gebiet();
	void load_strasse();
	void load_programm();

	// Text-Change ComboBox
	void kostengruppe_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void kostenart_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void bha_sk_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void stadt_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void programm_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void strasse_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void gebiet_TextChanged(System::Object^  sender, System::EventArgs^  e);

	// Text-Change TextBox
	void bezeichnung_TextChanged(System::Object^  sender, System::EventArgs^  e);

	void foeuvh_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void foeuvh_Leave(System::Object^  sender, System::EventArgs^  e);

	void bew_ztr_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void bew_ztr_Leave(System::Object^  sender, System::EventArgs^  e);

	void aenderungsbescheid_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void aenderungsbescheid_Leave(System::Object^  sender, System::EventArgs^  e);

	void vn_eingereicht_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void vn_eingereicht_Leave(System::Object^  sender, System::EventArgs^  e);

	void vn_geprueft_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void vn_geprueft_Leave(System::Object^  sender, System::EventArgs^  e);

	void bemerkung_TextChanged(System::Object^  sender, System::EventArgs^  e);

	void gk_real_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void gk_real_Leave(System::Object^  sender, System::EventArgs^  e);
	void gk_zuwendungsf_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void gk_zuwendungsf_Leave(System::Object^  sender, System::EventArgs^  e);

	// ListBox
	void programme_Click(System::Object^  sender, System::EventArgs^  e);
	void programme_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

	// Buttons
	void add_programm_Click(System::Object^  sender, System::EventArgs^  e);
	void del_programm_Click(System::Object^  sender, System::EventArgs^  e);	
	void add_strasse_Click(System::Object^  sender, System::EventArgs^  e);
	void rem_strasse_Click(System::Object^  sender, System::EventArgs^  e);
	void add_bewilligung_Click(System::Object^  sender, System::EventArgs^  e);
	void del_bewilligung_Click(System::Object^  sender, System::EventArgs^  e);
	void bewilligungen_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	void strassen_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	void btn_VN_Click(System::Object^  sender, System::EventArgs^  e);
	void button10_Click(System::Object^  sender, System::EventArgs^  e); // Fremdfoerderung
	void btn_save_Click(System::Object^  sender, System::EventArgs^  e);
	void btn_del_Click(System::Object^  sender, System::EventArgs^  e);
	void button5_Click(System::Object^  sender, System::EventArgs^  e);	// Close
	void btn_print_Click(System::Object^  sender, System::EventArgs^  e);

	// Projekt anzeigen
	void show_project();
	void show_programm_eintrag();

	// Swap Bewilligung
	void bewilligungen_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	void bewilligungen_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);

	// Typtest
	bool regular_entry();

	bool is_existent_in(List<String^>^ liste,String^ value);
};
}
