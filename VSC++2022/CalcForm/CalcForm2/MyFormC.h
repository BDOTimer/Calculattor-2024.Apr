#pragma once

#include "API_calculator.hpp"
#include <msclr\marshal_cppstd.h>

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

namespace $safeprojectname$ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace msclr::interop;

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
			this->richTextBox1->Text =
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
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	protected:
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::RichTextBox^ richTextBox2_Out;
	private: System::Windows::Forms::RichTextBox^ richTextBox3_Res;
	private: System::Windows::Forms::TextBox^ textBox1_Vars;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button1;







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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->richTextBox2_Out = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox3_Res = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox1_Vars = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"PT Mono", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1->Location = System::Drawing::Point(1, 52);
			this->richTextBox1->MaxLength = 200000;
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->richTextBox1->Size = System::Drawing::Size(708, 446);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::richTextBox1_MouseClick_1);
			this->richTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::richTextBox1_KeyDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"PT Mono", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->label1->Location = System::Drawing::Point(75, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(140, 24);
			this->label1->TabIndex = 1;
			this->label1->Text = L"ÐÅÇÓËÜÒÀÒ:";
			// 
			// richTextBox2_Out
			// 
			this->richTextBox2_Out->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->richTextBox2_Out->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->richTextBox2_Out->ForeColor = System::Drawing::Color::LimeGreen;
			this->richTextBox2_Out->Location = System::Drawing::Point(1, 504);
			this->richTextBox2_Out->Name = L"richTextBox2_Out";
			this->richTextBox2_Out->ReadOnly = true;
			this->richTextBox2_Out->Size = System::Drawing::Size(708, 107);
			this->richTextBox2_Out->TabIndex = 3;
			this->richTextBox2_Out->Text = L"";
			// 
			// richTextBox3_Res
			// 
			this->richTextBox3_Res->BackColor = System::Drawing::Color::WhiteSmoke;
			this->richTextBox3_Res->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->richTextBox3_Res->Font = (gcnew System::Drawing::Font(L"PT Mono", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox3_Res->Location = System::Drawing::Point(365, 5);
			this->richTextBox3_Res->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->richTextBox3_Res->MaxLength = 40;
			this->richTextBox3_Res->Multiline = false;
			this->richTextBox3_Res->Name = L"richTextBox3_Res";
			this->richTextBox3_Res->ReadOnly = true;
			this->richTextBox3_Res->RightMargin = 20;
			this->richTextBox3_Res->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Horizontal;
			this->richTextBox3_Res->Size = System::Drawing::Size(340, 38);
			this->richTextBox3_Res->TabIndex = 4;
			this->richTextBox3_Res->Text = L"...";
			// 
			// textBox1_Vars
			// 
			this->textBox1_Vars->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1_Vars->Font = (gcnew System::Drawing::Font(L"PT Mono", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1_Vars->Location = System::Drawing::Point(715, 0);
			this->textBox1_Vars->Multiline = true;
			this->textBox1_Vars->Name = L"textBox1_Vars";
			this->textBox1_Vars->ReadOnly = true;
			this->textBox1_Vars->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1_Vars->Size = System::Drawing::Size(166, 611);
			this->textBox1_Vars->TabIndex = 5;
			// 
			// panel1
			// 
			this->panel1->AutoSize = true;
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->richTextBox3_Res);
			this->panel1->Location = System::Drawing::Point(1, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(708, 46);
			this->panel1->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Snow;
			this->button1->Font = (gcnew System::Drawing::Font(L"PT Mono", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::DarkRed;
			this->button1->Location = System::Drawing::Point(3, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(62, 38);
			this->button1->TabIndex = 5;
			this->button1->Text = L"ÑÁÐÎÑ";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_Reset);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(884, 611);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox1_Vars);
			this->Controls->Add(this->richTextBox2_Out);
			this->Controls->Add(this->richTextBox1);
			this->MaximumSize = System::Drawing::Size(1200, 900);
			this->MinimumSize = System::Drawing::Size(400, 300);
			this->Name = L"MyForm";
			this->Text = L"Êàëüêóëÿòîð-2024";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	int cnt01 = 0;
	private: Void richTextBox1_MouseClick_1(Object^ sender, MouseEventArgs^ e)
	{
		if (cnt01 == 0)
		{	cnt01++; this->richTextBox1->Text = L"";
			this->richTextBox1->Font = (gcnew System::Drawing::Font(
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
			auto last = get_last_string(richTextBox1);
			richTextBox2_Out->Text += "\r\n";
			richTextBox2_Out->Text += last;

			run_calc();
		}
	}

	int pos_last_str = 0;

	private: Void run_calc()
	{
		auto input = get_last_string(richTextBox1);

		calc.recreate(marshal_as<std::string>(input));

		if(std::wstring s = build(calc); s.empty())
		{
            auto            res = calc.go_ext();
			Double result = res.second;

			label1->Text  = L"ÐÅÇÓËÜÒÀÒ: ";
			label1->Text += marshal_as<String^>(res.first);
			label1->Text += L" = ";

			richTextBox3_Res->Text   = result.ToString();
			richTextBox2_Out->Text   = L"Óñïåøíî.";

			richTextBox3_Res->ForeColor = System::Drawing::Color::SeaGreen;
			richTextBox2_Out->ForeColor = System::Drawing::Color::LimeGreen;

			color(0, richTextBox1->Text->Length, Color::Black);
		}
		else
		{
			richTextBox3_Res->Text = L"... èñïðàâüòå ñòðîêó ...";
			richTextBox2_Out->Text      = marshal_as<String^>(s);
			
			richTextBox3_Res->ForeColor = System::Drawing::Color::Red;
			richTextBox2_Out->ForeColor = System::Drawing::Color::Red;

			/// TODO ...
			color(pos_last_str + (INT)report.position, 
				                 (INT)report.name.size(), Color::Red);
		}

		pos_last_str = richTextBox1->Text->Length + 1;

		info_Vars();
	}

	String^ get_last_string(RichTextBox^ rtb)
	{	auto   arr = rtb->Text->Split(L'\n');
/*
		int a = 0;
		for(int i = 0; i < arr->Length - 1; ++i)
		{	a += arr[0]->Length;
		}

		richTextBox1->SelectionStart     = a;
		richTextBox1->SelectionLength    = arr[arr->Length - 1]->Length;
		richTextBox1->SelectionBackColor = Color::LightCyan;

		richTextBox1->SelectionStart     = richTextBox1->Text->Length-1;
		richTextBox1->SelectionLength    = 1;
		richTextBox1->SelectionBackColor = Color::White;
*/
		return arr [ arr->Length - 1 ];
	}

	Void info_Vars()
	{	std::wstring vars_info = API_calculator::get_vars_info();
		textBox1_Vars->Text    = marshal_as<String^>(vars_info);
	}

	Void color(INT a, INT b, Color C)
	{
		richTextBox1->SelectionStart  = a;
		richTextBox1->SelectionLength = b;
		richTextBox1->SelectionColor  = C;

		richTextBox1->SelectionStart  = richTextBox1->Text->Length;
		richTextBox1->SelectionLength = 0;
		richTextBox1->SelectionColor  = Color::Black;
	}

	private: Void button1_Click_Reset(Object^ sender, EventArgs^ e)
	{	calc.reset();
		info_Vars ();
		richTextBox1->Text = "";
	}
};
}
