#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Pool.h"

class InputTimer
{
public:
	double inputTimeParameter;
	int inputIndex;
	int termIndex;

	double timeFactor;

	bool valueJustEnteredTerm;
	double timeOfChange;
	double timePassed;

	bool isChanging;

	void updateState();

	InputTimer();
	InputTimer(double InputTimeParameter, int InputIndex, int TermIndex);
	~InputTimer();

	InputTimer &operator= (const InputTimer &other)
	{
		inputTimeParameter = other.inputTimeParameter;
		inputIndex = other.inputIndex;
		timeFactor = other.timeFactor;
		timeOfChange = other.timeOfChange;
		termIndex = other.termIndex;
		valueJustEnteredTerm = other.valueJustEnteredTerm;
		timePassed = other.timePassed;

		return *this;
	}

	InputTimer(const InputTimer& other)
	{
		inputTimeParameter = other.inputTimeParameter;
		inputIndex = other.inputIndex;
		timeFactor = other.timeFactor;
		timeOfChange = other.timeOfChange;
		termIndex = other.termIndex;
		valueJustEnteredTerm = other.valueJustEnteredTerm;
		timePassed = other.timePassed;
	}
};