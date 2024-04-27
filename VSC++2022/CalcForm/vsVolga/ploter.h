#pragma once

#include <cstdlib>

#include "API_calculator.hpp"

struct Vec2 { float x, y; };

//#include <msclr\marshal_cppstd.h>

namespace _ploter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Config
	{
		public: Config(PictureBox^ pb, int sz)
		{	  reconfig(            pb,     sz);
		}

		int   sz_cell;
		public:int w2;
		public:int h2;
		public:int w ;
		public:int h ;

		public: void reconfig(PictureBox^ pb, int sz)
		{
			sz_cell = sz;
			w  = pb->ClientRectangle.Width ;
			h  = pb->ClientRectangle.Height;
			w2 = w / 2;
			h2 = h / 2;
		}

	};

	public ref class Ploter
	{
		public: Ploter(PictureBox^ p, int sz)
		{
			pb  = p;
			cfg = gcnew Config(pb, sz);

			pen    = gcnew Pen(Color::Silver);
			redPen = gcnew Pen(Color::Blue);

			pen->Width    = 1;
			redPen->Width = 2;
		}

		public: void reconfig(int _sz)
		{	    cfg->reconfig(pb, _sz);
		}
		
		PictureBox^  pb;
		Config^     cfg;
		Pen^        pen;
		Pen^     redPen;

		const int T = 2;

	    public: void draw_axes(Graphics^ g)
		{	
			int ny = cfg->h2 - (cfg->h2 % cfg->sz_cell);

			for (int y = -ny; y < cfg->h2; y += cfg->sz_cell)
			{	g->DrawLine(pen, 0, y + cfg->h2, cfg->w, y + cfg->h2);
			}

			int nx = cfg->w2 - (cfg->w2 % cfg->sz_cell);

			for (int x = -nx; x < cfg->w2; x += cfg->sz_cell)
			{	g->DrawLine(pen, x + cfg->w2, 0, x + cfg->w2, cfg->h);
			}

			g->DrawLine(redPen, cfg->w2, 0, cfg->w2, cfg->h);
			g->DrawLine(redPen, 0, cfg->h2, cfg->w,  cfg->h2);

		/// pb->Invalidate();
		}

		public: void draw_plots(Graphics^ g, int amount)
		{	
			for (int i = 0; i < amount; ++i)
			{	
				Vec2 p = getPlot();

				float x = (cfg->w2 + p.x * cfg->sz_cell);
				float y = (cfg->h2 + p.y * cfg->sz_cell);

				g->DrawLine(redPen, x, y, x + T, y + T);
			}
		}

		public: void draw_plot(Graphics^ g, Vec2 p)
		{	
			float x =  cfg->w2 + p.x * cfg->sz_cell;
			float y = (cfg->h2 - p.y * cfg->sz_cell);

			g->DrawLine(redPen, x, y, x + T, y + T);
		}

		public: Vec2 getPlot()
		{
			float x = float(rand() % cfg->w) - cfg->w2;
			float y = float(rand() % cfg->h) - cfg->h2;

			return { x / cfg->sz_cell, y / cfg->sz_cell };
		}
	};
}


