/// https://www.cyberforum.ru/cpp-beginners/thread3017681.html
/// !((4-fabs(x)) > (fabs(y))) && ((8-fabs(x)) > fabs(y))
/// 
/// https://www.cyberforum.ru/cpp-beginners/thread1199000.html
/// (fabs(x) < 2 && fabs(y) < 1.5 && (fabs(x) > 1 && x * y < 0 || fabs(y) > 1 && fabs(y) > (fabs(x) + 1) / 2 || fabs(x) < 1 && fabs(y) < fabs(x) && x * y > 0))
///
/// https://www.cyberforum.ru/cpp-beginners/thread3148273.html
/// (fabs(x) < 3 && fabs(y - 2) < 3 && (fabs(x) > 2 || fabs(y - 2) > 2))

#pragma once

#include "ploter.h"

Example_02 calc_exm02;

#include <msclr\marshal_cppstd.h>

namespace $safeprojectname$ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	using namespace _ploter;

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

			this->Icon = gcnew System::Drawing::Icon(L"mainiconproject.ico");

			ploter = gcnew Ploter(pictureBox1, trackBar1->Value);

			color(0, richTextBox1_Edit->Text->Length, Color::Black);
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
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TrackBar^ trackBar1;
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
			this->richTextBox1_Edit = (gcnew System::Windows::Forms::RichTextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// richTextBox1_Edit
			// 
			this->richTextBox1_Edit->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->richTextBox1_Edit->Font = (gcnew System::Drawing::Font(L"JetBrains Mono Medium", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1_Edit->Location = System::Drawing::Point(0, 599);
			this->richTextBox1_Edit->Multiline = false;
			this->richTextBox1_Edit->Name = L"richTextBox1_Edit";
			this->richTextBox1_Edit->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Horizontal;
			this->richTextBox1_Edit->Size = System::Drawing::Size(584, 27);
			this->richTextBox1_Edit->TabIndex = 0;
			this->richTextBox1_Edit->Text = L"";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Ivory;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->MaximumSize = System::Drawing::Size(1200, 900);
			this->pictureBox1->MinimumSize = System::Drawing::Size(500, 500);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(584, 626);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::AliceBlue;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button1->Location = System::Drawing::Point(520, 543);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(53, 45);
			this->button1->TabIndex = 2;
			this->button1->Text = L"пуск";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->BackColor = System::Drawing::Color::AliceBlue;
			this->trackBar1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->trackBar1->Location = System::Drawing::Point(10, 543);
			this->trackBar1->Maximum = 200;
			this->trackBar1->Minimum = 20;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(200, 45);
			this->trackBar1->TabIndex = 3;
			this->trackBar1->TickFrequency = 10;
			this->trackBar1->Value = 100;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 626);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->richTextBox1_Edit);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->DoubleBuffered = true;
			this->MaximumSize = System::Drawing::Size(1200, 900);
			this->MinimumSize = System::Drawing::Size(600, 600);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Фильтр попадания точек...";
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Ploter^ ploter;

		bool ready = false;
		private: Void pictureBox1_Paint(Object^ sender, PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;
			          g->Clear(pictureBox1->BackColor);

			if (!ready)
			{	ploter->draw_plots(g, 1000);
			}
			else
			for (int i = 0; i < 30000; ++i)
			{
				Vec2 args = ploter->getPlot();

				double result = calc_exm02.go(args.x, args.y);

				if (result == 1.0)
				{	ploter->draw_plot(g, args);
				}
			}

			ploter->draw_axes(g);
		}

		private: Void button1_Click(Object^ sender, EventArgs^ e)
		{	ready = run_calc       ();
			pictureBox1->Invalidate();
		}

		///--------------------------------------------------------------------|
		/// ...
		///--------------------------------------------------------------------:
		private: bool run_calc()
		{
			color(0, richTextBox1_Edit->Text->Length, Color::Black);

			auto input = richTextBox1_Edit->Text;

			if(std::wstring s = 
				calc_exm02.build(marshal_as<std::string>(input)); s.empty())
			{
				if (calc_exm02.bindvar())
				{
					richTextBox1_Edit->ForeColor = System::Drawing::Color::Green;

					color(0, richTextBox1_Edit->Text->Length, Color::Green);
					return true;
				}
			}
			else
			{
				const auto& [pos, size] = calc_exm02.report();
				color       (pos, size, Color::Red);
			}
			return false;
		}

		Void color(INT a, INT b,  Color C)
		{	richTextBox1_Edit->SelectionStart  = a;
			richTextBox1_Edit->SelectionLength = b;
			richTextBox1_Edit->SelectionColor  = C;

			richTextBox1_Edit->SelectionStart  = richTextBox1_Edit->Text->Length;
			richTextBox1_Edit->SelectionLength = 0;
			richTextBox1_Edit->SelectionColor  = Color::Black;
		}
		
		private: Void MyForm_Resize(Object^ sender, EventArgs^ e) 
		{	resize();
		}

		private: Void trackBar1_Scroll(Object^ sender, EventArgs^ e)
		{	resize();
		}

		private: Void resize()
		{
			int  w = this->ClientRectangle.Width ;
			int  h = this->ClientRectangle.Height;

			button1  ->Location = System::Drawing::Point(w - 64, h - 82);
			trackBar1->Location = System::Drawing::Point(    10, h - 82);

			ploter->reconfig(trackBar1->Value);

			pictureBox1->Invalidate();
		}


	};
}
