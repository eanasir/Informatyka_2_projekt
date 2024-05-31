#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"
#include "winbgi2.h"

#define NSTATE 2

//deklaracja sta³ych
#define m 1
#define k1 5
#define k2 3
#define c 0.3

void rhs_fun(double t, double* X, double* F)
{
	double k;
	k = k1 * (1 + k2 * X[1] * X[1]);
	F[0] = (( - k * X[1]) / m ) - c*X[0];
	F[1] = X[0];
}
int main()
{
	FILE* g;
	g = fopen("wynik.txt", "w");
	double tp, tk, h, t;
	double X[NSTATE], X1[NSTATE];
	int nstep;
	double Emech;
	double F, k;
	double v = 0, x = 0;
	tp = 0;
	tk = 20;
	h = 0.001;
	nstep = (tk - tp) / h;
	t = tp;
	//deklaracja warunkow poczatkowych 
	x = 1;
	v = 1;
	//koniec deklaracji
	X[0] = v;//prêdkoœæ
	X[1] = x;//po³o¿enie
	for (int i = 1; i < nstep; i++)
	{
		k = k1 * (1 + k2 * X1[1] * X1[1]);
		vrk4(t, X, h, NSTATE, rhs_fun, X1);
		Emech = (m * X1[0] * X1[0]) / 2 + (k1 * X1[1] * X1[1]) / 2 + (k1 * k2 * X1[1] * X1[1] * X1[1] * X1[1]) / 4;
		F = (-k * X1[1]);
		t = t + h;
		fprintf(g,"%6.2lf\t%6.2lf\t%6.2lf\t%6.2lf\n", t, X1[0], X1[1], F);
		X[0] = X1[0];
		X[1] = X1[1];
	}
	return 0;

}