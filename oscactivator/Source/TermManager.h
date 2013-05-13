#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "../fuzzylite/FuzzyLite.h"
#include <assert.h>

class TermManager
{
	double min;
	double max;
	
	void sortTerms();

	int getIndex(String termName);

public:
	Array<fl::TrapezoidalTerm*> terms;
	
	double getMidPointOfTrapezoidTable(int index);
	double getMidPointOfTrapezoidTable(String termName);

	void setMin(double Min);
	void setMax(double Max);

	double getMin();
	double getMax();

	void addTerm(String termName, double value);
	void removeTerm(int index);
	
	int getIndex(double value);
	

	TermManager(void);
	~TermManager(void);
};

