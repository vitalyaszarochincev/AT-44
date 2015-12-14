//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
    TEdit *ax;
    TEdit *ay;
    TEdit *bx;
    TEdit *by;
    TEdit *ax2;
    TEdit *ay2;
    TEdit *bx2;
    TEdit *by2;
    TEdit *cx;
    TEdit *cy;
    TEdit *r;
        TButton *Button4;
    TEdit *axt;
    TEdit *ayt;
    TEdit *bxt;
    TEdit *byt;
    TEdit *cxt;
    TEdit *cyt;
        TButton *Button5;
        TButton *Button6;
        void __fastcall drawCDA(TObject *Sender);
        void __fastcall drawBrez(TObject *Sender);
        void __fastcall drawCircle(TObject *Sender);
        void __fastcall drawTriangle(TObject *Sender);
        void __fastcall drawPicture(TObject *Sender);
        void __fastcall clean(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
