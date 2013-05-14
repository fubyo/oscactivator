#include "InputTimer.h"
#include "RulesPanelComponent.h"
#include "InputsPanelComponent.h"

InputTimer::InputTimer()
{
	inputTimeParameter = 0;
	inputIndex = -1;

	timeFactor = 0;
	valueJustEnteredTerm = false;

	timePassed = 0;
}

InputTimer::InputTimer(double InputTimeParameter, int InputIndex, int TermIndex)
{
	inputTimeParameter = InputTimeParameter;
	inputIndex = InputIndex;
	termIndex = TermIndex;

	timeFactor = 0;
	valueJustEnteredTerm = false;

	timePassed = 0;
}

InputTimer::~InputTimer()
{

}

void InputTimer::updateState()
{
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	
	double currentValue = *ipc->inputs[inputIndex]->pValue;
	double membershipValue = ipc->inputs[inputIndex]->termManager->getIndex(currentValue);

	double currentTime = Time::getMillisecondCounterHiRes()/1000.0;
	double timeDifference = currentTime - timeOfChange;
	timeOfChange = currentTime;

	if (membershipValue==0)
	{
		timeFactor = 0;
		valueJustEnteredTerm = false;
		rpc->ruleGenerator.inputsAreChanging=false;
	}
	else if (!valueJustEnteredTerm)
	{
		valueJustEnteredTerm = true;
		timePassed=0;
		timeFactor=0;
		rpc->ruleGenerator.inputsAreChanging=true;
	}
	else if (valueJustEnteredTerm)
	{
		timePassed+=timeDifference*membershipValue;

		if (timePassed >= inputTimeParameter)
		{
			timeFactor = 1.0;
			rpc->ruleGenerator.inputsAreChanging=false;
		}
		else
		{
			timeFactor = 0;
			rpc->ruleGenerator.inputsAreChanging=true;
		}
	}
}