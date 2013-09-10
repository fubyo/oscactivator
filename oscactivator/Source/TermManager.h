#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "TrapezTerm.h"
#include "Pool.h"
#include <assert.h>

class TermManager
{
	double min;
	double max;
	
	void sortTerms();

	int getIndex(String termName);

public:
	OwnedArray<TrapezTerm> terms;
	
	double getMidPointOfTrapezoidTable(int index);
	double getMidPointOfTrapezoidTable(String termName);

	void setMin(double Min);
	void setMax(double Max);

	double getMin();
	double getMax();

	void addTerm(String termName, double value);
	void removeTerm(int index);
	
	int getIndex(double value);

	void moveBtoTheLeft(int termIndex);
	void moveBtoTheRight(int termIndex);
	void moveCtoTheLeft(int termIndex);
	void moveCtoTheRight(int termIndex);
	
	TermManager(void);
	~TermManager(void);
};

