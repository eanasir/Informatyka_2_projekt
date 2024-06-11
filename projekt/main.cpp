#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"
#include "winbgi2.h"


//deklaracja sta�ych
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
double analytic_solution(double x) {
	double omega, tau;
	omega = sqrt(k1/m);
	//tau = m / c;
	
	return 0.1*( exp(-0.5*c* x) * cos(sqrt(k1 - 4 * c * c) * x));
}
int main()
{
	FILE* g;
	g = fopen("wynik.txt", "w");
	double tp, tk, h, t;
	double X[2], X1[2];
	int nstep;
	double Emech;
	double F, k;
	double v = 0, x = 0;
	tp = 0;
	tk = 10;
	h = 0.001;
	nstep = (tk - tp) / h;
	t = tp;
	//deklaracja warunkow poczatkowych 
	x = 0.1;
	v = 0;
	//koniec deklaracji
	X[0] = v;//pr�dko��
	X[1] = x;//po�o�enie
	for (int i = 1; i < nstep; i++)
	{
		
		vrk4(x, X, h, 2, rhs_fun, X1);
		Emech = (m * X1[0] * X1[0]) / 2 + (k1 * X1[1] * X1[1]) / 2 + (k1 * k2 * X1[1] * X1[1] * X1[1] * X1[1]) / 4;
		
		t = t + h;
		X[0] = X1[0];
		X[1] = X1[1];
		k = k1 * (1 + k2 * X1[1] * X1[1]);
		F = (-k * X1[1]);
		fprintf(g, "%lf\t%lf\t%lf\t%lf\t%lf\n", t, X1[0], X1[1], F,analytic_solution(t));
	}
	return 0;

}