#ifndef __PLOTDLL_H
#define __PLOTDLL_H

#ifdef PLOTDLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif
DLL_SPEC void OXY(float x1, float x2,float y1, float y2, float xx2, float yy2, TImage * canv);
DLL_SPEC void LPlotF(float x1, float x2, float y1, float y2, int kf, double (*funct[])(double), TImage * canv);
DLL_SPEC int ZoomX(float x, float x1, float x2, int xx1, int xx2);
DLL_SPEC int ZoomY(float y, float y1, float y2, int yy1, int yy2);

#endif
