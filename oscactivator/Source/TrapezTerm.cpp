#include "TrapezTerm.h"


TrapezTerm::TrapezTerm(void)
{
	A = 0;
	B = 0;
	C = 0;
	D = 0;
}

TrapezTerm::TrapezTerm(String name)
{
	Name = name;

	A = 0;
	B = 0;
	C = 0;
	D = 0;
}

void TrapezTerm::setA(double a)
{
	A = a;
}

void TrapezTerm::setB(double b)
{
	B = b;
}

void TrapezTerm::setC(double c)
{
	C = c;
}

void TrapezTerm::setD(double d)
{
	D = d;
}

void TrapezTerm::setName(String name)
{
	Name = name;
}

double TrapezTerm::a()
{
	return A;
}

double TrapezTerm::b()
{
	return B;
}

double TrapezTerm::c()
{
	return C;
}

double TrapezTerm::d()
{
	return D;
}

double TrapezTerm::membership(double crisp)
{
	double result=0;

	if (crisp <= A && A == B) //shoulder term
		result = 1;
	else if (crisp >= D && D==C) //shoulder term
		result = 1;
	else if (crisp >= A && crisp < B)
		result = (crisp-A)/(B-A);
	else if (crisp >=B && crisp < C)
		result = 1;
	else if (crisp >= C && crisp <= D)
		result = (D-crisp)/(D-C);

	return result;
}

void TrapezTerm::centroid(double &x, double &y)
{
	double a = C - B;
	double b = D - A;
	double c = B - A;
	double h = 1;

	x = (2*a*c + a*a + c*b + a*b + b*b)/(3*(a+b));
	y = h*(2*a + b)/(3*(a+b));
}

String TrapezTerm::name()
{
	return Name;
}


TrapezTerm::~TrapezTerm(void)
{
}
