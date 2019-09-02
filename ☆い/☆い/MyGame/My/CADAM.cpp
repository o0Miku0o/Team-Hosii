#include "CADAM.h"
/*
TO SET UP AN EQUATION OF LINE AND
CALCULATE THE COEFFICIENTS
( ax + by + c = 0 )
*/
int lnprm(double *pt1, double *pt2, double *a, double *b, double *c)
{
	double  xlk, ylk, rsq, rinv;
	double  accy = 1.0E-15;

	xlk = pt2[0] - pt1[0];
	ylk = pt2[1] - pt1[1];
	rsq = pow(xlk, 2.0) + pow(ylk, 2.0);

	if (rsq < accy) {
		return (-1);
	}
	else {
		rinv = 1.0 / sqrt(rsq);
		*a = -ylk * rinv;
		*b = xlk * rinv;
		*c = (pt1[0] * pt2[1] - pt2[0] * pt1[1]) * rinv;
	}  /* end if */

	return (0);
}  /* lnprm */
   /*
   INTERSECTING POINTS OF LINE AND CIRCLE
   */
int lncl(double *pt1, double *pt2, double *xyr, double *pnear, double *xy)
{
	double  root, factor, xo, yo, f, g, fsq, gsq, fgsq, xjo, yjo, a, b, c;
	double  fygx, fxgy, t, fginv, t1, t2, x1, y1, x2, y2, sqdst1, sqdst2;
	double  accy = 1.0E-15;

	if (lnprm(pt1, pt2, &a, &b, &c)) return (-1);

	root = 1.0 / (a*a + b * b);
	factor = -c * root;
	xo = a * factor;
	yo = b * factor;
	root = sqrt(root);
	f = b * root;
	g = -a * root;

	fsq = f * f;
	gsq = g * g;
	fgsq = fsq + gsq;

	if (fgsq < accy) {
		return (3);
	}
	else {
		xjo = xyr[0] - xo;
		yjo = xyr[1] - yo;
		fygx = f * yjo - g * xjo;
		root = xyr[2] * xyr[2] * fgsq - fygx * fygx;

		if (root < -accy) {  /* 交点なし */
			return (-1);
		}
		else {
			fxgy = f * xjo + g * yjo;

			if (root < accy) {  /* 直線と円は接する。*/
				t = fxgy / fgsq;
				xy[0] = xo + f * t;
				xy[1] = yo + g * t;
				return (1);
			}
			else {
				root = sqrt(root);
				fginv = 1.0 / fgsq;
				t1 = (fxgy - root)*fginv;
				t2 = (fxgy + root)*fginv;
				x1 = xo + f * t1;
				y1 = yo + g * t1;
				x2 = xo + f * t2;
				y2 = yo + g * t2;
			}  /* end if */

		}  /* end if */

	}  /* end if */

	sqdst1 = pow((pnear[0] - x1), 2.0) + pow((pnear[1] - y1), 2.0);
	sqdst2 = pow((pnear[0] - x2), 2.0) + pow((pnear[1] - y2), 2.0);

	if (sqdst1 < sqdst2) {  /* pnearに近い方の交点を返す。*/
		xy[0] = x1;
		xy[1] = y1;
	}
	else {
		xy[0] = x2;
		xy[1] = y2;
	}  /* end if */

	return (2);
}  /* lncl */
/*
INTERSECTING POINT OF LINES
*/
int lnln(double(*pxy1)[2], double(*pxy2)[2], double *xy)
{
	double  pt1[2], pt2[2], a1, b1, c1, a2, b2, c2, det, dinv;
	double  accy = 1.0E-15;

	pt1[0] = pxy1[0][0];
	pt1[1] = pxy1[0][1];
	pt2[0] = pxy1[1][0];
	pt2[1] = pxy1[1][1];

	if (lnprm(pt1, pt2, &a1, &b1, &c1)) return (-1);  /* 2点は一致する。 */

	pt1[0] = pxy2[0][0];
	pt1[1] = pxy2[0][1];
	pt2[0] = pxy2[1][0];
	pt2[1] = pxy2[1][1];

	if (lnprm(pt1, pt2, &a2, &b2, &c2)) return (-1);  /* 2点は一致する。 */

	det = a1 * b2 - a2 * b1;

	if (fabs(det) < accy) {
		return (-1);   /* 交点は、存在しない。 */
	}
	else {
		dinv = 1.0 / det;
		xy[0] = (b1*c2 - b2 * c1) * dinv;
		xy[1] = (a2*c1 - a1 * c2) * dinv;
	} /* end if */

	return (0);
} /* lnln */