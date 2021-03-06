//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <math.h>
#include "PlotDLL.h"
int Summa(int a, int b);
float podstav(float x, float (*f)(float));
int ZoomX(float x);
int ZoomY(float y);
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

double f1(double x)
{
	return 3*fabs(x)-2*x*x+26;
}

double f2(double x)
{
	return 3*x*x*x*x-8;
}

double f3(double x)
{
	return 3*x+26*x*x;
}

double f4(double x)
{
	return 1/(x*x);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	 const int kf=4;

	 double (*funct[kf])(double) = {f1,f2,f3,f4};

	 LPlotF(-10, 10, -20, 30, kf, funct, Form1->Image1);
}
//---------------------------------------------------------------------------

