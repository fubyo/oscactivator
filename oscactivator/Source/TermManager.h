#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "../fuzzylite/FuzzyLite.h"
#include <assert.h>

class TermManager
{
	double min;
	double max;
	
	double getMidPointOfTrapezoidTable(int index);
	double getMidPointOfTrapezoidTable(String termName);
	void sortTerms();
	int getIndex(String termName);
	int getIndex(double value);

public:
	
	Array<fl::TrapezoidalTerm*> terms;

	void setMin(double Min);
	void setMax(double Max);

	double getMin();
	double getMax();

	void addTerm(String termName, double value);
	void removeTerm(int index); 

	TermManager(void);
	~TermManager(void);
};

