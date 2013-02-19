#pragma once

#include "Pool.h"

class ValueRelevance
{
public:
	double value;
	bool relevance;

	ValueRelevance & operator= (const ValueRelevance & other)
    {
		this->value = other.value;
		this->relevance = other.relevance;
    }
};

class Example
{
public:
	Array<ValueRelevance> inputValues;
	Array<ValueRelevance> outputValues;
	double importance;

	Example(void);
	~Example(void);

	void setExample(Array<ValueRelevance> InputValues, Array<ValueRelevance> OutputValues);
	void setImportance(double Importance);
};
