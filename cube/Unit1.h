//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPaintBox *PaintBox1;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox3;
        TButton *Button9;
        TButton *Button8;
        TButton *Button10;
        TGroupBox *GroupBox4;
        TButton *Button7;
        TButton *Button6;
        TButton *Button1;
        TUpDown *UpDown1;
        TUpDown *UpDown2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall UpDown2Click(TObject *Sender, TUDBtnType Button);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
