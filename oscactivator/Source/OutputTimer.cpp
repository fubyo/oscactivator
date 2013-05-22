#include "OutputTimer.h"
#include "RulesPanelComponent.h"
#include "InputsPanelComponent.h"

OutputTimer::OutputTimer()
{
	outputTimeParameter = 0;
	outputIndex = -1;
	ruleIndex = -1;

	timeFactor = 0;
	conditionsJustFulfilled = false;

	timePassed = 0;
}

OutputTimer::OutputTimer(double InputTimeParameter, int InputIndex, int TermIndex, int RuleIndex)
{
	outputTimeParameter = InputTimeParameter;
	outputIndex = InputIndex;
	termIndex = TermIndex;
	ruleIndex = RuleIndex;

	timeFactor = 0;
	conditionsJustFulfilled = false;

	timePassed = 0;
}

OutputTimer::~OutputTimer()
{

}

void OutputTimer::updateState(double inputsTimeFactor)
{
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
	RulesPanelComponent *rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	
	if (rpc->ruleGenerator.rules[ruleIndex]->outputFromInput.contains(outputIndex))
	{
		int inputIndex = rpc->ruleGenerator.rules[ruleIndex]->outputFromInput[outputIndex];
		targetValue = *ipc->inputs[inputIndex]->pValue;
	}
	else
	{
		targetValue = (opc->outputs[outputIndex]->termManager->terms[termIndex]->b()+opc->outputs[outputIndex]->termManager->terms[termIndex]->c())/2;
	}

	if (opc)
	{
		double currentTime = Time::getMillisecondCounterHiRes()/1000.0;
		double timeDifference = currentTime - timeOfChange;
		timeOfChange = currentTime;

		if (inputsTimeFactor!=1)
		{
			timeFactor=0;
			conditionsJustFulfilled = false;
			isChanging = false;
		}
		else if (!conditionsJustFulfilled)
		{
			conditionsJustFulfilled = true;
			timePassed = 0;
			isChanging = true;
			savedValue = *opc->outputs[outputIndex]->pValue;
		}
		else if (conditionsJustFulfilled)
		{
			timePassed+=timeDifference;

			if (timePassed >= outputTimeParameter)
			{
				timeFactor = 1.0;
				isChanging = false;
			}
			else
			{
				timeFactor = timePassed/outputTimeParameter;
				isChanging = true;
			}

		}
	}
}