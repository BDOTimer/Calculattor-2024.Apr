#pragma once

#include "API_calculator.hpp"
#include <msclr\marshal_cppstd.h>

extern API_calculator calc;

using namespace msclr::interop;

namespace CalcForm2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for MyFormHelp
	/// </summary>
	public ref class MyFormHelp : public System::Windows::Forms::Form
	{
	public:
		MyFormHelp(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			this->HScroll = false;
			this->VScroll = false;

			//richTextBox1->LoadFile("Help.rtf");

			richTextBox1->Text += "\r\n";
			richTextBox1->Text += "\r\n";
			richTextBox1->Text += marshal_as<String^>(calc.report_help());

			richTextBox1->SelectionStart  = 0;
			richTextBox1->SelectionLength = richTextBox1->Text->Length;
			richTextBox1->SelectionColor  = Color::DarkBlue;
			richTextBox1->SelectionFont   = 
				(gcnew System::Drawing::Font(L"PT Mono", 12.25F,
					System::Drawing::FontStyle::Regular ,
					System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));

			richTextBox1->SelectionStart  = richTextBox1->Text->Length;
			richTextBox1->SelectionLength = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyFormHelp()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	protected:

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
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::Ivory;
			this->richTextBox1->Location = System::Drawing::Point(12, 12);
			this->richTextBox1->MaxLength = 5000;
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->richTextBox1->Size = System::Drawing::Size(483, 487);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// MyFormHelp
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Navy;
			this->ClientSize = System::Drawing::Size(507, 511);
			this->Controls->Add(this->richTextBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyFormHelp";
			this->Text = L"MyFormHelp";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
