#pragma once

#include "MyFormHelp.h"

API_calculator calc;
Report_token report;

std::wstring build(API_calculator& c)
{
	std::wstringstream WCOUT;
	try
	{	c.build();
	}
	catch (const EXEPTION_LUSER& e)
	{	WCOUT << "\nERROR_LUSER: " << e << ENDL << ENDL;
		report = e.report();
	}
	return WCOUT.str();
}


#include "code/mover.h"
#include "code/form_geom.h"


namespace $safeprojectname$ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//using namespace msclr::interop;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		/// this->Icon  = gcnew System::Drawing::Icon(L"mainiconproject.ico");
			this->mover = gcnew myl::Mover(this, label1);

			//auto bmp = Properties::Resources->myimage;

			good();

			this->richTextBox1_Edit->Text =
				marshal_as<String^>(API_calculator::example_01());

			info_Vars();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1_Edit;
	protected:


	private: System::Windows::Forms::RichTextBox^ richTextBox2_Log;

	private: System::Windows::Forms::TextBox^ textBox1_Vars;


	private: System::Windows::Forms::Button^ button2_Exit;
	private: System::Windows::Forms::Button^ button3_minimize;


	private: System::Windows::Forms::RichTextBox^ richTextBox3_Res;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1_reset;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button2_help;

	private: System::Windows::Forms::RichTextBox^ richTextBox1_Res;
	private: System::Windows::Forms::Button^ button1_topmost;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1_Edit = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox2_Log = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox1_Vars = (gcnew System::Windows::Forms::TextBox());
			this->button2_Exit = (gcnew System::Windows::Forms::Button());
			this->button3_minimize = (gcnew System::Windows::Forms::Button());
			this->richTextBox3_Res = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1_reset = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1_Res = (gcnew System::Windows::Forms::RichTextBox());
			this->button2_help = (gcnew System::Windows::Forms::Button());
			this->button1_topmost = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox1_Edit
			// 
			this->richTextBox1_Edit->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->richTextBox1_Edit->BackColor = System::Drawing::Color::Ivory;
			this->richTextBox1_Edit->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1_Edit->Location = System::Drawing::Point(3, 58);
			this->richTextBox1_Edit->MaxLength = 200000;
			this->richTextBox1_Edit->Name = L"richTextBox1_Edit";
			this->richTextBox1_Edit->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->richTextBox1_Edit->Size = System::Drawing::Size(706, 460);
			this->richTextBox1_Edit->TabIndex = 0;
			this->richTextBox1_Edit->Text = L"";
			this->richTextBox1_Edit->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::richTextBox1_MouseClick_1);
			this->richTextBox1_Edit->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::richTextBox1_KeyDown);
			// 
			// richTextBox2_Log
			// 
			this->richTextBox2_Log->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->richTextBox2_Log->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->richTextBox2_Log->ForeColor = System::Drawing::Color::LimeGreen;
			this->richTextBox2_Log->Location = System::Drawing::Point(3, 524);
			this->richTextBox2_Log->Name = L"richTextBox2_Log";
			this->richTextBox2_Log->ReadOnly = true;
			this->richTextBox2_Log->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox2_Log->Size = System::Drawing::Size(705, 83);
			this->richTextBox2_Log->TabIndex = 3;
			this->richTextBox2_Log->Text = L"";
			// 
			// textBox1_Vars
			// 
			this->textBox1_Vars->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1_Vars->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->textBox1_Vars->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1_Vars->Location = System::Drawing::Point(715, 58);
			this->textBox1_Vars->Multiline = true;
			this->textBox1_Vars->Name = L"textBox1_Vars";
			this->textBox1_Vars->ReadOnly = true;
			this->textBox1_Vars->Size = System::Drawing::Size(166, 549);
			this->textBox1_Vars->TabIndex = 5;
			// 
			// button2_Exit
			// 
			this->button2_Exit->BackColor = System::Drawing::Color::Navy;
			this->button2_Exit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2_Exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2_Exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2_Exit->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->button2_Exit->Location = System::Drawing::Point(844, 8);
			this->button2_Exit->Name = L"button2_Exit";
			this->button2_Exit->Size = System::Drawing::Size(28, 20);
			this->button2_Exit->TabIndex = 7;
			this->button2_Exit->Text = L"X";
			this->button2_Exit->UseVisualStyleBackColor = false;
			this->button2_Exit->Click += gcnew System::EventHandler(this, &MyForm::button2_Exit_Click);
			// 
			// button3_minimize
			// 
			this->button3_minimize->BackColor = System::Drawing::Color::Navy;
			this->button3_minimize->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3_minimize->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3_minimize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3_minimize->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->button3_minimize->Location = System::Drawing::Point(810, 8);
			this->button3_minimize->Name = L"button3_minimize";
			this->button3_minimize->Size = System::Drawing::Size(28, 20);
			this->button3_minimize->TabIndex = 8;
			this->button3_minimize->Text = L"-";
			this->button3_minimize->UseVisualStyleBackColor = false;
			this->button3_minimize->Click += gcnew System::EventHandler(this, &MyForm::button3_Mini_Click);
			// 
			// richTextBox3_Res
			// 
			this->richTextBox3_Res->BackColor = System::Drawing::Color::WhiteSmoke;
			this->richTextBox3_Res->Enabled = false;
			this->richTextBox3_Res->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->richTextBox3_Res->Location = System::Drawing::Point(360, 3);
			this->richTextBox3_Res->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->richTextBox3_Res->MaxLength = 40;
			this->richTextBox3_Res->Multiline = false;
			this->richTextBox3_Res->Name = L"richTextBox3_Res";
			this->richTextBox3_Res->ReadOnly = true;
			this->richTextBox3_Res->RightMargin = 20;
			this->richTextBox3_Res->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Horizontal;
			this->richTextBox3_Res->Size = System::Drawing::Size(346, 47);
			this->richTextBox3_Res->TabIndex = 4;
			this->richTextBox3_Res->Text = L"";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->label1->Location = System::Drawing::Point(75, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(151, 25);
			this->label1->TabIndex = 1;
			this->label1->Text = L"���������:";
			// 
			// button1_reset
			// 
			this->button1_reset->BackColor = System::Drawing::Color::LightSteelBlue;
			this->button1_reset->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1_reset->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1_reset->ForeColor = System::Drawing::Color::MediumBlue;
			this->button1_reset->Location = System::Drawing::Point(3, 3);
			this->button1_reset->Name = L"button1_reset";
			this->button1_reset->Size = System::Drawing::Size(50, 47);
			this->button1_reset->TabIndex = 5;
			this->button1_reset->Text = L"�����";
			this->button1_reset->UseVisualStyleBackColor = false;
			this->button1_reset->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_Reset);
			// 
			// panel1
			// 
			this->panel1->AutoSize = true;
			this->panel1->BackColor = System::Drawing::Color::Navy;
			this->panel1->Controls->Add(this->richTextBox1_Res);
			this->panel1->Controls->Add(this->button1_reset);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->richTextBox3_Res);
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(709, 53);
			this->panel1->TabIndex = 6;
			// 
			// richTextBox1_Res
			// 
			this->richTextBox1_Res->BackColor = System::Drawing::Color::WhiteSmoke;
			this->richTextBox1_Res->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1_Res->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1_Res->Location = System::Drawing::Point(371, 15);
			this->richTextBox1_Res->MaxLength = 100;
			this->richTextBox1_Res->Multiline = false;
			this->richTextBox1_Res->Name = L"richTextBox1_Res";
			this->richTextBox1_Res->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Horizontal;
			this->richTextBox1_Res->Size = System::Drawing::Size(330, 28);
			this->richTextBox1_Res->TabIndex = 10;
			this->richTextBox1_Res->Text = L"...";
			this->richTextBox1_Res->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::richTextBox1_Res_MouseDoubleClick);
			// 
			// button2_help
			// 
			this->button2_help->BackColor = System::Drawing::Color::Navy;
			this->button2_help->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2_help->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2_help->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2_help->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->button2_help->Location = System::Drawing::Point(776, 8);
			this->button2_help->Name = L"button2_help";
			this->button2_help->Size = System::Drawing::Size(28, 20);
			this->button2_help->TabIndex = 9;
			this->button2_help->Text = L"\?";
			this->button2_help->UseVisualStyleBackColor = false;
			this->button2_help->Click += gcnew System::EventHandler(this, &MyForm::button2_help_Click);
			// 
			// button1_topmost
			// 
			this->button1_topmost->BackColor = System::Drawing::Color::Navy;
			this->button1_topmost->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1_topmost->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1_topmost->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1_topmost->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->button1_topmost->Location = System::Drawing::Point(742, 8);
			this->button1_topmost->Name = L"button1_topmost";
			this->button1_topmost->Size = System::Drawing::Size(28, 20);
			this->button1_topmost->TabIndex = 10;
			this->button1_topmost->Text = L"T";
			this->button1_topmost->UseVisualStyleBackColor = false;
			this->button1_topmost->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Navy;
			this->ClientSize = System::Drawing::Size(884, 611);
			this->Controls->Add(this->button1_topmost);
			this->Controls->Add(this->button2_help);
			this->Controls->Add(this->button3_minimize);
			this->Controls->Add(this->button2_Exit);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox1_Vars);
			this->Controls->Add(this->richTextBox2_Log);
			this->Controls->Add(this->richTextBox1_Edit);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximumSize = System::Drawing::Size(1200, 900);
			this->MinimumSize = System::Drawing::Size(400, 300);
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"�����������-2024";
			this->TransparencyKey = System::Drawing::Color::Pink;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	myl::Mover^                 mover;
	CalcForm2::MyFormHelp^ myFormHelp = nullptr;

	int cnt01 = 0;
	private: Void richTextBox1_MouseClick_1(Object^ sender, MouseEventArgs^ e)
	{
		if (cnt01 == 0)
		{	cnt01++; this->richTextBox1_Edit->Text = L"";
			this->richTextBox1_Edit->Font = (gcnew System::Drawing::Font(
				L"PT Mono", 15.75F, 
				System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		}
	}

	private: Void richTextBox1_KeyDown( Object^ sender, KeyEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
		{	
			auto last = get_last_string(richTextBox1_Edit);
			richTextBox2_Log->Text += "\r\n";
			richTextBox2_Log->Text += last;

			bool error = run_calc();

			if(error) e->Handled = true;
		}
	}

	int pos_last_str = 0;

	private: bool run_calc()
	{
		auto input = get_last_string(richTextBox1_Edit);

		calc.recreate(marshal_as<std::string>(input));

		bool error = false;

		color(0, richTextBox1_Edit->Text->Length, Color::Black);

		if(std::wstring s = build(calc); s.empty())
		{
			good();

            auto            res = calc.go_ext();
			Double result = res.second;

			label1->Text  = L"���������: ";
			label1->Text += marshal_as<String^>(res.first);
			label1->Text += L" = ";

			richTextBox1_Res->Text      = result.ToString();
			richTextBox2_Log->Text      = L"�������.";

			richTextBox1_Res->ForeColor = System::Drawing::Color::SeaGreen;
			richTextBox2_Log->ForeColor = System::Drawing::Color::LimeGreen;

			pos_last_str = richTextBox1_Edit->Text->Length + 1;
		}
		else
		{	bad();

			richTextBox1_Res->Text = L"��� ...";
			richTextBox2_Log->Text =  marshal_as<String^>(s);
			
			richTextBox1_Res->ForeColor = System::Drawing::Color::Purple;
			richTextBox2_Log->ForeColor = System::Drawing::Color::Red;

			/// TODO ...
			color(pos_last_str + (INT)report.position, 
				                 (INT)report.name.size(), Color::Red);

			error = true;
		}

		info_Vars();

		return error;
	}

	String^ get_last_string(RichTextBox^ rtb)
	{	auto   arr = rtb->Text->Split(L'\n');
		return arr [ arr->Length - 1 ];
	}

	Void info_Vars()
	{	std::wstring vars_info = API_calculator::get_vars_info();

		if(!vars_info.empty())
		{	textBox1_Vars->Text = marshal_as<String^>(vars_info);
		}
	}

	Void color(INT a, INT b, Color C)
	{
		richTextBox1_Edit->SelectionStart  = a;
		richTextBox1_Edit->SelectionLength = b;
		richTextBox1_Edit->SelectionColor  = C;

		richTextBox1_Edit->SelectionStart  = richTextBox1_Edit->Text->Length;
		richTextBox1_Edit->SelectionLength = 0;
		richTextBox1_Edit->SelectionColor  = Color::Black;
	}

	private: Void button1_Click_Reset(Object^ sender, EventArgs^ e)
	{	calc.reset();
		label1->Text = L"���������: ...";
        textBox1_Vars     ->Text = "...";
		richTextBox1_Res  ->Text = "...";
		richTextBox2_Log  ->Text = "...";
		richTextBox1_Edit ->Text = "";
		richTextBox1_Edit ->Focus();
	}

	private: Void MyForm_Load(Object^ sender, EventArgs^ e)
	{
	}

	private: Void button2_Exit_Click(Object^ sender, EventArgs^ e)
	{	this->Close();
	}

	private: Void button3_Mini_Click(Object^ sender, EventArgs^ e)
	{	this->WindowState = FormWindowState::Minimized;
	}

	void good()
	{	richTextBox2_Log->Visible = false;
		richTextBox1_Edit->Height =   548;
	}

	void bad()
	{	richTextBox2_Log->Visible = true;
		richTextBox1_Edit->Height =  460;
	}

	private: Void richTextBox1_Res_MouseDoubleClick(Object^ sender, MouseEventArgs^ e)
	{	richTextBox1_Edit->Text += richTextBox1_Res->Text;
		richTextBox1_Edit->Focus();

		richTextBox1_Edit->SelectionStart  = richTextBox1_Edit->Text->Length;
		richTextBox1_Edit->SelectionLength = 0;
	}

	private: Void button1_Click(Object^ sender, EventArgs^ e)
	{	this->TopMost = !this->TopMost;
		button1_topmost->ForeColor = this->TopMost ? Color::Green :
			                                         Color::LightSteelBlue;
	}

	private: Void button2_help_Click(Object^ sender, EventArgs^ e)
	{   if (nullptr  != myFormHelp)
        {   myFormHelp->Close();
            myFormHelp = nullptr;
        }
        else
        {   myFormHelp = gcnew CalcForm2::MyFormHelp();
            myFormHelp->Owner = this;
            myFormHelp->Show();
        }
	}
};
}
