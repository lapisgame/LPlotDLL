//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TImage *Image1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	//int xx1, xx2, yy1, yy2;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	//float x1, x2, y1, y2;
    //int n;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
