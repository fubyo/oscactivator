#include "Example.h"

Example::Example(void)
{	
}

Example::~Example(void)
{
}

void Example::setExample(Array<ValueRelevance> InputValues, Array<ValueRelevance> OutputValues)
{
	inputValues = InputValues;
	outputValues = OutputValues;
}

void Example::setImportance(double Importance)
{
	importance = Importance;
}
