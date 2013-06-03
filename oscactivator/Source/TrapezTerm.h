#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TrapezTerm
{
	double A;
	double B;
	double C;
	double D;

	String Name;

public:

	void setA(double a);
	void setB(double b);
	void setC(double c);
	void setD(double d);

	void setName(String name);

	double a();
	double b();
	double c();
	double d();

	double membership(double crisp);

	void centroid(double &x, double &y);

	String name();

	TrapezTerm(void);
	TrapezTerm(String name);
	~TrapezTerm(void);

	TrapezTerm & operator= (const TrapezTerm & other)
    {
        if (this != &other) // protect against invalid self-assignment
        {
			A = other.A;
			B = other.B;
			C = other.C;
			D = other.D;

			Name = other.Name;
        }

        // by convention, always return *this
        return *this;
    };
};
