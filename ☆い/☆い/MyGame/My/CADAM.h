#ifndef CADAM
#define CADAM
#include <math.h>
/*
関数名  lnprm
機能    直線の方程式の計算
形式    int lnprm( double *pt1, double *pt2,
double a, double b, double c )
解説    指定された 2点  (pt1[1],  pt1[2])  と  (pt2[1],  pt2[2])  を通る
直線の方程式(ax  +  by  +  c  =  0)の係数(a,  b,  c)を求めます。
戻り値  lnprmは、成功すると0、失敗すると-1を返します。
*/
/*  
TO SET UP AN EQUATION OF LINE AND
CALCULATE THE COEFFICIENTS
( ax + by + c = 0 )
*/
int lnprm(double *pt1, double *pt2, double *a, double *b, double *c);
/*
関数名  lncl
機能    円と直線の交点の計算
形式    int lncl(  double  *pt1,  double  *pt2,  double  *xyr,
double  *pnear,  double  *xy)
解説    中心座標と半径  (xyr[0],  xyr[1],  xyr[2])  で定義される円と、指
定された 2点  (pt1[1],  pt1[2])  と  (pt2[1],  pt2[2])  を通る直
線との交点  (xy[0],  xy[1]) を計算します。交点が 2つ存在するとき
は指定した点  (pnear[0],  pnear[1]) に近い方の交点が選択されます。
戻り値  lnclは、成功すると交点の数、交点が存在しないと-1を返します。
*/
/*
INTERSECTING POINTS OF LINE AND CIRCLE
*/
int lncl(double *pt1, double *pt2, double *xyr, double *pnear, double *xy);
/*
関数名  lnln
機能    二直線の交点の計算
形式    int lnln( double (*pxy1)[2], double (*pxy2)[2], int *xy )
解説    直線  (pxy1[0][0], pxy1[0][1] - pxy1[1][0], pxy1[1][1])  と  直線
(pxy1[0][0], pxy1[0][1] - pxy1[1][0], pxy1[1][1])  の交点  (xy[0],
xy[1])  を計算します。
戻り値  lnlnは、成功すると0、交点が存在しないと-1を返します。
*/
int lnln(double(*pxy1)[2], double(*pxy2)[2], double *xy);
#endif