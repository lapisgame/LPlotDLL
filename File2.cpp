#include <vcl.h>
#include <windows.h>
#include <cstdlib>
#include <math.h>
#include <cmath>

#pragma hdrstop
#pragma argsused

#include "PlotDLL.h"


extern "C" __declspec(dllexport)
int ZoomX(float x, float x1, float x2, int xx1, int xx2)
{
	return (xx1 + (int)((x-x1)*(xx2-xx1)/(x2-x1)));
}

extern "C" __declspec(dllexport)
int ZoomY(float y, float y1, float y2, int yy1, int yy2)
{
	return (yy2 + (int)((y-y1)*(yy1-yy2)/(y2-y1)));
}

extern "C" __declspec(dllexport)
void OXY(float x1, float x2,float y1, float y2, float xx2, float yy2, TImage * canv)
{
	int tx, ty;
	int xx1 = 0;
	int yy1 = 0;


	tx = ZoomX(0, x1, x2, xx1, xx2);
	int cx = tx;
	ty = ZoomY(y1, y1, y2, yy1, yy2);
	canv->Canvas->MoveTo(tx,ty);


	tx = ZoomX(0, x1, x2, xx1, xx2);
	ty = ZoomY(y2, y1, y2, yy1, yy2);
	canv->Canvas->LineTo(tx,ty);


	canv->Canvas->Pen->Color = clBlack;
	tx = ZoomX(x1, x1, x2, xx1, xx2);
	ty = ZoomY(0, y1, y2, yy1, yy2);
	int cy = ty;
	canv->Canvas->MoveTo(tx,ty);


	tx = ZoomX(x2, x1, x2, xx1, xx2);
	ty = ZoomY(0, y1, y2, yy1, yy2);
	canv->Canvas->LineTo(tx,ty);

	 //??? ?
	int x1x2=(fabs(x1)+fabs(x2));
	int shagx = xx2/x1x2;

	int k=0;
	bool flag = true;
	while (flag)
	{
		int xm=cx-shagx*k;
		int xp=cx+shagx*k;
		if (xm>0)
		{
			canv->Canvas->MoveTo(xm,cy-8);
			canv->Canvas->LineTo(xm,cy+8);
			canv->Canvas->TextOut(xm,cy+15,IntToStr(-k));
		}
		if (xp<xx2)
		{
			canv->Canvas->MoveTo(xp,cy-8);
			canv->Canvas->LineTo(xp,cy+8);
			canv->Canvas->TextOut(xp,cy+15,IntToStr(k));
		}

		if (xm<0 and xp>xx2)
			flag=false;
		k++;
	}


	 //??? ?
	int y1y2=(fabs(y1)+fabs(y2));
	int shagy = yy2/y1y2;

	k=0;
	flag = true;
	while (flag)
	{
		int ym=cy-shagy*k;
		int yp=cy+shagy*k;
		if (ym>0)
		{
			canv->Canvas->MoveTo(cx-8,ym);
			canv->Canvas->LineTo(cx+8,ym);
			canv->Canvas->TextOut(cx+15,ym-5,IntToStr(k));
		}
		if (yp<yy2)
		{
			canv->Canvas->MoveTo(cx-8,yp);
			canv->Canvas->LineTo(cx+8,yp);
			canv->Canvas->TextOut(cx+15,yp-5,IntToStr(-k));
		}

		if (ym<0 and yp>yy2)
			flag=false;
		k++;
	}
}

extern "C" __declspec(dllexport)
void LPlotF(float x1, float x2, float y1, float y2, int kf, double (*funct[])(double), TImage * canv)
{
     srand(4541);

	 int tx, ty;
	 int i;
	 const double h = 0.00001;
	 const double pr = 0.00001;
	 double x, y;
	 int xx1, xx2, yy1, yy2;
	 const int ar=0;
	 const int br=255;

	 double flp, flm;

	 //??????? ??????
	 xx1 = 0;
	 yy1 = 0;
	 xx2 = canv->Width;
	 yy2 = canv->Height;

     //?????? ?????????
	 canv->Canvas->Pen->Color = clBlue;
	 canv->Canvas->Brush->Color = clWhite;
	 canv->Canvas->Rectangle(0, 0, canv->Width, canv->Height);


	 canv->Canvas->Pen->Color = clBlack;

	 OXY(x1,x2,y1,y2,xx2,yy2,canv);

	 canv->Canvas->Pen->Width = 2; // ??????? ?????

	 // ???? ???????? ????? ? ????????? ?????????????? ?????
	 int gh;
	 int rc,gc,bc;

	 for (gh = 0; gh<kf; gh++)
		 {
			//????????? ???? ??? ????????? ?????
			rc=ar+rand()%(br-ar+1);
			gc=ar+rand()%(br-ar+1);
			bc=ar+rand()%(br-ar+1);
			canv->Canvas->Pen->Color = (TColor)RGB(rc,gc,bc);

			//?????? ?????
			y = funct[gh](x1);
			tx = ZoomX(x1, x1, x2, xx1, xx2);
			ty = ZoomY(y, y1, y2, yy1, yy2);
			canv->Canvas->MoveTo(tx,ty);

            //???????? ????????? ?? x1+h ?? x2-h
			for (x = x1+h; x < x2; x+=h)
				{
					 flp=(round(funct[gh](x+h)*pr)/pr);
					 flm=(round(funct[gh](x-h)*pr)/pr);

					 if (flp!=flm)
					 {
						y = funct[gh](x);
						if (y<y1)
							y=y1;
						if (y>y2)
                            y=y2;
						tx = ZoomX(x, x1, x2, xx1, xx2);
						ty = ZoomY(y, y1, y2, yy1, yy2);
						canv->Canvas->MoveTo(tx,ty);

					 }
					 else
					 {
						 y = funct[gh](x);
						 if (y<y1)
						 {
							y=y1;
                            tx = ZoomX(x, x1, x2, xx1, xx2);
							ty = ZoomY(y, y1, y2, yy1, yy2);
							canv->Canvas->MoveTo(tx,ty);
						 }
						 else
							if (y>y2)
							{
								y=y2;
                                tx = ZoomX(x, x1, x2, xx1, xx2);
								ty = ZoomY(y, y1, y2, yy1, yy2);
								canv->Canvas->MoveTo(tx,ty);
							}
							else
							{
                                tx = ZoomX(x, x1, x2, xx1, xx2);
								ty = ZoomY(y, y1, y2, yy1, yy2);
								canv->Canvas->LineTo(tx,ty);
							}

					 }
				}
		 }


}

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}



