#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Pool.h"

class OutputTimer
{
public:
	double outputTimeParameter;
	int outputIndex;
	int termIndex;
	int ruleIndex;

	double timeFactor;
	double savedValue;
	double targetValue;

	bool conditionsJustFulfilled;
	double timeOfChange;
	double timePassed;

	bool isChanging;

	void updateState(double inputsTimeFactor);

	OutputTimer();
	OutputTimer(double OutputTimeParameter, int OutputIndex, int TermIndex, int RuleIndex);
	~OutputTimer();

	OutputTimer &operator= (const OutputTimer &other)
	{
		outputTimeParameter = other.outputTimeParameter;
		outputIndex = other.outputIndex;
		timeFactor = other.timeFactor;
		timeOfChange = other.timeOfChange;
		termIndex = other.termIndex;
		conditionsJustFulfilled = other.conditionsJustFulfilled;
		timePassed = other.timePassed;

		return *this;
	}

	OutputTimer(const OutputTimer& other)
	{
		outputTimeParameter = other.outputTimeParameter;
		outputIndex = other.outputIndex;
		timeFactor = other.timeFactor;
		timeOfChange = other.timeOfChange;
		termIndex = other.termIndex;
		conditionsJustFulfilled = other.conditionsJustFulfilled;
		timePassed = other.timePassed;
	}
};