
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace myl
{
    public ref class FormGeom
    {
        public:  FormGeom(Form^ f)
        {
            F = f;
            F->SizeChanged += gcnew EventHandler(this, &FormGeom::resize);
        }

        Form^  F;

        private: Void resize(Object^ sender, EventArgs^ e)
        {
              
        }
    };
}
