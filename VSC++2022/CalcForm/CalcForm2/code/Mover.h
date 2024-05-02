
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace myl
{
    public ref class Mover
    {
        public:  Mover(Form^ f, Control^ c)
        {
            F = f;
            C = c;
            C->MouseDown += gcnew MouseEventHandler(this, &Mover::MouseDown);
            C->MouseMove += gcnew MouseEventHandler(this, &Mover::MouseMove);
            C->MouseUp   += gcnew MouseEventHandler(this, &Mover::MouseUp);
        }

          private: Void MouseDown(Object^ sender, MouseEventArgs^ e)
          {
              mcur = true;
              Cursorpos = Cursor::Position;
              C->Cursor = System::Windows::Forms::Cursors::SizeAll;
          }

          bool mcurdone = true;
          private: Void MouseMove(Object^ sender, MouseEventArgs^ e)
          {
              if (mcur)
              {
                  Point cp = Cursor::Position;
                  cp.X -= Cursorpos.X;
                  cp.Y -= Cursorpos.Y;

                  if (cp.X == 0 &&
                      cp.Y == 0) return;
                  else mcurdone = false;

                  Point dl = F->DesktopLocation;
                  dl.X += cp.X;
                  dl.Y += cp.Y;

                  Cursorpos = Cursor::Position;
                  F->SetDesktopLocation(dl.X, dl.Y);
              }
          }

          private: Void MouseUp(Object^ sender, MouseEventArgs^ e)
          {
              mcur = false;
              C->Cursor = System::Windows::Forms::Cursors::Default;

              if (mcurdone)
              {
                  if (((Control^)sender)->Name == "buttonShow")
                  {
                      switch (e->Button)
                      {
                      case MouseButtons::Left:
                      {
                          //sounds.play(MySounds.eSND.SHOW);
                          break;
                      }
                      case MouseButtons::Right:
                      {
                          //sounds.play(MySounds.eSND.SHOWRIGHT);
                          break;
                      }
                      }
                  }
              }
              else mcurdone = true;
          }

          Form^    F;
          Control^ C;

          bool  mcur = false;
          Point Cursorpos;
    };
}
