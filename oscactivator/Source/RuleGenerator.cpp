#include "RuleGenerator.h"

RuleGenerator::RuleGenerator(void) : Thread("RuleGenerator")
{
	ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");

	Pool::Instance()->reg("RuleGenerator", this);

	outputsHaveToGetUpdated=false;

	
	threadShouldBeRunning = true;

	savedOutputValue.remapTable(1024);
	inputTimersAreCounting = false;
	
	startThread();
}

RuleGenerator::~RuleGenerator(void)
{
	//delete all input timers
	for (int i=0; i<rules.size(); i++)
	{
		HashMap<int, InputTimer*>::Iterator ii(rules[i]->inputTimers);
		while (ii.next())
		{
			delete ii.getValue();
		}
	} 
}

void RuleGenerator::addExample(Example example)
{
	Example* newExample = new Example(example);
	queuedExamples.add(newExample);
}

void RuleGenerator::clearExamples()
{
	queuedExamples.clear();
}

int RuleGenerator::getNumberOfQueuedExamples()
{
	return queuedExamples.size();
}

void RuleGenerator::updateRulebase()
{
	if (queuedExamples.size())
		createRulesFromQueuedExamples();

	mergeNewRulesToRuleBase();
}

void RuleGenerator::createRulesFromQueuedExamples()
{
	queuedRules.clear();

	for (int i=0; i<queuedExamples.size(); i++) //iterate over the queued examples
	{
		Rule rule;
		rule.inputDegree = 1;
		
		for (int ii=0; ii<queuedExamples[i]->inputValues.size(); ii++) //iterate over the inputs of the example
		{
			if (queuedExamples[i]->inputValues[ii].relevance) //if input is relevant
			{
				int inputTermIndex=getIndexOfBestInputTerm(ii, queuedExamples[i]->inputValues[ii].value);
				rule.inputTermIndeces.add(inputTermIndex);
				
				TermManager* termManager=ipc->inputs[ii]->termManager;
				float membership = termManager->terms[inputTermIndex]->membership((float)queuedExamples[i]->inputValues[ii].value);
				
				rule.inputDegree*=membership;
				rule.inputMembership.add(membership);
				rule.inputValues.add(queuedExamples[i]->inputValues[ii].value);
			}
			else //if input is not relevant
			{
				rule.inputTermIndeces.add(-1);
				rule.inputMembership.add(-1);
				rule.inputValues.add(0);
			}
		}

		for (int ii=0; ii<queuedExamples[i]->outputValues.size(); ii++) //iterate over the outputs of the example
		{
			if (queuedExamples[i]->outputValues[ii].relevance) //if output is relevant
			{
				int outputTermIndex=getIndexOfBestOutputTerm(ii, queuedExamples[i]->outputValues[ii].value);
				rule.outputTermIndeces.add(outputTermIndex);
				
				TermManager* termManager=opc->outputs[ii]->termManager;
				float membership = 0;
				
				if (outputTermIndex>=0)
					membership = termManager->terms[outputTermIndex]->membership((float)queuedExamples[i]->outputValues[ii].value);
				
				rule.outputDegrees.add(rule.inputDegree*membership);
				rule.outputMembership.add(membership);
				rule.outputValues.add(queuedExamples[i]->outputValues[ii].value);
			}
			else //if output is not relevant
			{
				rule.outputDegrees.add(0);
				rule.outputTermIndeces.add(-1);
				rule.outputMembership.add(-1);
				rule.outputValues.add(0);
			}
		}

		Rule* newQueuedRule = new Rule(rule);
		queuedRules.add(newQueuedRule); //add a rule for each example
	}

	queuedExamples.clear();
}

void RuleGenerator::mergeNewRulesToRuleBase()
{
	for (int i=0; i<queuedRules.size(); i++) //for each new rule
	{
		int ruleIndex = 0;

		while (ruleIndex<rules.size())  //for each old rule
		{
			bool inputsConflicting = areInputsConflicting(*queuedRules[i], *rules[ruleIndex]);
			Array<int> outputsConflicting = areOutputsConflicting(*queuedRules[i], *rules[ruleIndex]);
			Array<int> outputsCorrelating = isHavingSimilarEffectsToSomeOutputs(*queuedRules[i], *rules[ruleIndex]);

			if (inputsConflicting && outputsConflicting.size())
			{
				while (outputsConflicting.size())
				{
					if (queuedRules[i]->outputDegrees[outputsConflicting[0]]>=rules[ruleIndex]->outputDegrees[outputsConflicting[0]])
					{
						rules[ruleIndex]->outputDegrees.set(outputsConflicting[0], 0);
						rules[ruleIndex]->outputMembership.set(outputsConflicting[0] ,-1);
						rules[ruleIndex]->outputTermIndeces.set(outputsConflicting[0] ,-1);
					}
					else
					{
						queuedRules[i]->outputDegrees.set(outputsConflicting[0], 0);
						queuedRules[i]->outputMembership.set(outputsConflicting[0] ,-1);
						queuedRules[i]->outputTermIndeces.set(outputsConflicting[0] ,-1);
					}
					outputsConflicting.remove(0);
				}
			}
			else if (outputsCorrelating.size())
			{
				while (outputsCorrelating.size())
				{
					int outputIndex = outputsCorrelating[0];

					if (queuedRules[i]->outputDegrees[outputIndex]>=rules[ruleIndex]->outputDegrees[outputIndex])
					{
						rules[ruleIndex]->outputMembership.set(outputIndex ,queuedRules[i]->outputMembership[outputIndex]);
						rules[ruleIndex]->outputValues.set(outputIndex, queuedRules[i]->outputValues[outputIndex]);
						rules[ruleIndex]->outputDegrees.set(outputIndex, rules[ruleIndex]->outputMembership[outputIndex]*rules[ruleIndex]->inputDegree);

						queuedRules[i]->outputDegrees.set(outputIndex, 0);
						queuedRules[i]->outputMembership.set(outputIndex ,-1);
						queuedRules[i]->outputTermIndeces.set(outputIndex ,-1);
					}
					else
					{
						queuedRules[i]->outputMembership.set(outputIndex ,rules[ruleIndex]->outputMembership[outputIndex]);
						queuedRules[i]->outputValues.set(outputIndex, rules[ruleIndex]->outputValues[outputIndex]);
						queuedRules[i]->outputDegrees.set(outputIndex, queuedRules[i]->outputMembership[outputIndex]*queuedRules[i]->inputDegree);

						rules[ruleIndex]->outputDegrees.set(outputIndex, 0);
						rules[ruleIndex]->outputMembership.set(outputIndex ,-1);
						rules[ruleIndex]->outputTermIndeces.set(outputIndex ,-1);
					}

					outputsCorrelating.remove(0);
				}
			}

			ruleIndex++;
		}

		Rule *newRule = new Rule(*queuedRules[i]);
		rules.add(newRule);
	}

	queuedRules.clear();

	//Clean up rules that contribute to no output
	int ruleIndex = 0;
	while (ruleIndex<rules.size())
	{
		bool outputContribution = false;
		for (int i=0; i<rules[ruleIndex]->outputTermIndeces.size(); i++)
		{
			if (rules[ruleIndex]->outputTermIndeces[i]!=-1)
				outputContribution=true;
		}

		if (rules[ruleIndex]->outputFromInput.size())
			outputContribution = true;

		if (outputContribution)
			ruleIndex++;
		else
			rules.remove(ruleIndex);
	}

	//Clean up rules that have no input
	ruleIndex = 0;
	while (ruleIndex<rules.size())
	{
		bool hasInputs = false;
		for (int i=0; i<rules[ruleIndex]->inputTermIndeces.size(); i++)
		{
			if (rules[ruleIndex]->inputTermIndeces[i]!=-1)
				hasInputs=true;
		}

		if (hasInputs)
			ruleIndex++;
		else
			rules.remove(ruleIndex);
	}
}

int RuleGenerator::getIndexOfBestInputTerm(int inputIndex, double value)
{
	TermManager* termManager=ipc->inputs[inputIndex]->termManager;

	return termManager->getIndex(value);
}

int RuleGenerator::getIndexOfBestOutputTerm(int outputIndex, double value)
{
	TermManager* termManager=opc->outputs[outputIndex]->termManager;

	return termManager->getIndex(value);
}

bool RuleGenerator::areInputsConflicting(Rule firstrule, Rule secondrule)
{
	bool result = false;
	bool allTermIndecesTheSame = true;

	for (int i=0; i<firstrule.inputTermIndeces.size(); i++)
	{
		if (firstrule.inputTermIndeces[i]!=secondrule.inputTermIndeces[i])
			allTermIndecesTheSame = false;
	}

	if (allTermIndecesTheSame)
		result = true;

	return result;
}

Array<int> RuleGenerator::areOutputsConflicting(Rule firstrule, Rule secondrule)
{
	Array<int> result;

	for (int i=0; i<firstrule.outputTermIndeces.size(); i++)
	{
		if (firstrule.outputTermIndeces[i]!=-1 && secondrule.outputTermIndeces[i]!=-1)
			if (firstrule.outputTermIndeces[i]!=secondrule.outputTermIndeces[i])
				result.add(i);

	}

	return result;
}

Array<int> RuleGenerator::isHavingSimilarEffectsToSomeOutputs(Rule newrule, Rule oldrule)
{
	bool inputsAreSimilar = (newrule.inputTermIndeces == oldrule.inputTermIndeces);

	Array<int> result;

	if (inputsAreSimilar)
	{
		for (int i=0; i < newrule.outputTermIndeces.size(); i++)
		{
			if (newrule.outputTermIndeces[i]!=-1 && newrule.outputTermIndeces[i]==oldrule.outputTermIndeces[i])
				result.add(i);
		}
	}

	return result;
}

String RuleGenerator::getRuleText()
{
	String text;

	for (int i=0; i<rules.size(); i++)
	{
		text+=getRuleText(*rules[i]);
	}

	return text;
}

String RuleGenerator::getRuleText(Rule rule)
{
	String text;
	text += String("If ");

	bool firstConditionAdded = false;
	for (int i=0; i<rule.inputTermIndeces.size(); i++)
	{
		if (rule.inputTermIndeces[i]!=-1)
		{
			if (firstConditionAdded)
				text += String(" and ");

			text += ipc->inputs[i]->name+String(" is ");
			text += String(ipc->inputs[i]->termManager->terms[rule.inputTermIndeces[i]]->name());

			if (rule.inputTimers.contains(i))
			{
				text+= String(" for ");
				text+= String(rule.inputTimers[i]->inputTimeParameter);
				text+= String(" seconds");
			}
			
			if (!firstConditionAdded)
				firstConditionAdded = true;
		}
	}

	text += String(", then ");

	bool firstResultAdded = false;
	for (int i=0; i<rule.outputTermIndeces.size(); i++)
	{
		if (rule.outputTermIndeces[i]!=-1)
		{
			if (firstResultAdded)
				text += String(" and ");

			text += opc->outputs[i]->name+String(" is ");
			text += String(opc->outputs[i]->termManager->terms[rule.outputTermIndeces[i]]->name());

			if (rule.outputTimeParameter.contains(i))
			{
				text+= String(" in ");
				text+= String(rule.outputTimeParameter[i]);
				text+= String(" seconds");
			}
			
			if (!firstResultAdded)
				firstResultAdded = true;
		}
		else if (rule.outputFromInput.contains(i))
		{
			if (firstResultAdded)
				text += String(" and ");

			text += opc->outputs[i]->name+String(" is same as ");
			text += String(ipc->inputs[rule.outputFromInput[i]]->name);

			if (rule.outputTimeParameter.contains(i))
			{
				text+= String(" in ");
				text+= String(rule.outputTimeParameter[i]);
				text+= String(" seconds");
			}
			
			if (!firstResultAdded)
				firstResultAdded = true;
		}
	}

	text += String(".\n");

	return text;
}

void RuleGenerator::deleteAllRules()
{
	int iter = 0;
	bool unlockedFound = false;
	while (iter<rules.size() && !unlockedFound)
	{
		if (!rules[iter]->locked)
			rules.remove(iter);
		else
			iter++;
	}
}

void RuleGenerator::removeInput(int index)
{
	for (int i=0; i<queuedExamples.size(); i++)
	{
		queuedExamples[i]->inputValues.remove(index);
	}

	for (int i=0; i<rules.size(); i++)
	{
		rules[i]->inputMembership.remove(index);
		rules[i]->inputTermIndeces.remove(index);
		rules[i]->inputValues.remove(index);

		recalculateDegrees(i);
	}
}

void RuleGenerator::removeOutput(int index)
{
	for (int i=0; i<queuedExamples.size(); i++)
	{
		queuedExamples[i]->outputValues.remove(index);
	}

	for (int i=0; i<rules.size(); i++)
	{
		rules[i]->outputMembership.remove(index);
		rules[i]->outputTermIndeces.remove(index);
		rules[i]->outputDegrees.remove(index);
		rules[i]->outputValues.remove(index);

		recalculateDegrees(i);
	}
}

void RuleGenerator::recalculateDegrees(int ruleIndex)
{
	double inputDegree = 1;
	for (int i=0; i<rules[ruleIndex]->inputTermIndeces.size(); i++)
	{
		if (rules[ruleIndex]->inputTermIndeces[i]!=-1)
		{
			inputDegree*=rules[ruleIndex]->inputMembership[i];
		}
	}
	rules[ruleIndex]->inputDegree = inputDegree;


	double outputDegree = inputDegree;
	for (int i=0; i<rules[ruleIndex]->outputTermIndeces.size(); i++)
	{
		if (rules[ruleIndex]->outputTermIndeces[i]!=-1)
		{
			outputDegree*=rules[ruleIndex]->outputMembership[i];
			rules[ruleIndex]->outputDegrees.set(i,outputDegree);
		}
	}	
}

void RuleGenerator::updateMembershipAndTermIndeces(int index)
{
	for (int i=0; i<rules[index]->inputTermIndeces.size(); i++)
	{
		if (rules[index]->inputTermIndeces[i]!=-1)
		{
			rules[index]->inputTermIndeces.set(i, ipc->inputs[i]->termManager->getIndex(rules[index]->inputValues[i]));
			rules[index]->inputMembership.set(i, ipc->inputs[i]->termManager->terms[rules[index]->inputTermIndeces[i]]->membership((float)rules[index]->inputValues[i]));
		}
	}

	for (int i=0; i<rules[index]->outputTermIndeces.size(); i++)
	{
		if (rules[index]->outputTermIndeces[i]!=-1)
		{
			rules[index]->outputTermIndeces.set(i, opc->outputs[i]->termManager->getIndex(rules[index]->outputValues[i]));
			rules[index]->outputMembership.set(i, opc->outputs[i]->termManager->terms[rules[index]->outputTermIndeces[i]]->membership((float)rules[index]->outputValues[i]));
		}
	}

	recalculateDegrees(index);
}

bool RuleGenerator::isRuleRelevantToOutput(int ruleIndex, int outputIndex)
{
	if (rules[ruleIndex]->outputTermIndeces[outputIndex]!=-1 || rules[ruleIndex]->outputFromInput.contains(outputIndex))
		return true;
	else
		return false;
}

double RuleGenerator::calculateOutput(int index)
{
	double numerator = 0;
	double denominator = 0;
	double timeFactorProduct = 1;

	inputTimersAreCounting = false;

	Array<double> timeFactors;
	Array<double> numerators;
	Array<double> denominators;

	for (int i=0; i<rules.size(); i++)
	{
		if (isRuleRelevantToOutput(i, index))
		{
			double tempNumerator;
			double tempDenominator;
			double tempTimeFactor=1;
			
			tempNumerator = rules[i]->importance;

			for (int ii=0; ii<rules[i]->inputTermIndeces.size(); ii++)
			{
				if (rules[i]->inputTermIndeces[ii]!=-1)
				{
					double timeFactor = 1;
					if (rules[i]->inputTimers.contains(ii))
					{
						rules[i]->inputTimers[ii]->updateState();
						timeFactor = rules[i]->inputTimers[ii]->timeFactor;

						if (rules[i]->inputTimers[ii]->isChanging)
							inputTimersAreCounting = true;
					}
					tempTimeFactor*=timeFactor;

					tempNumerator*=timeFactor;
					tempNumerator*=ipc->inputs[ii]->termManager->terms[rules[i]->inputTermIndeces[ii]]->membership((float)*ipc->inputs[ii]->pValue);
				}
			}

			tempDenominator = tempNumerator;

			double output;

			if (rules[i]->outputFromInput.contains(index))
			{
				output = *ipc->inputs[rules[i]->outputFromInput[index]]->pValue;
			}
			else
			{
				int outputTermIndex = rules[i]->outputTermIndeces[index];
				output = (opc->outputs[index]->termManager->terms[outputTermIndex]->b() + opc->outputs[index]->termManager->terms[outputTermIndex]->c())/2;
			}

			tempNumerator *= output;

			numerators.add(tempNumerator);
			denominators.add(tempDenominator);
			timeFactors.add(tempTimeFactor);
		}
	}

	for (unsigned int i=0; i<numerators.size(); i++)
	{
		numerator+=numerators[i];
		denominator+=denominators[i];
		timeFactorProduct*=timeFactors[i];
	}

	double result;

	if (timeFactorProduct==1.0)
	{
		result = numerator/denominator;
		savedOutputValue.set(index, result);
	}
	else
	{
		result = timeFactorProduct*numerator/denominator + (1-timeFactorProduct)*savedOutputValue[index];
	}

	return result;
}

void RuleGenerator::requestOutputUpdate()
{
	outputsHaveToGetUpdated = true;
}

void RuleGenerator::updateOutputs()
{
	//get rule weights from inputs
	for (int i=0; i<rules.size(); i++)
	{
		int weightConnection = rules[i]->weightInputConnection;
		if (weightConnection!=-1)
		{
			rules[i]->importance = *ipc->inputs[weightConnection]->pValue;
		}
	}

	//calculate each output
	for (int i=0; i<opc->outputs.size(); i++)
	{
		*opc->outputs[i]->pValue = calculateOutput(i);
	}

	opc->sendOuputValues();
}

void RuleGenerator::updateRulesDueToAddingNewIO()
{
	int numOfInputs = ipc->inputs.size();
	int numOfOutputs = opc->outputs.size();

	for (int i=0; i<rules.size(); i++)
	{
		while (rules[i]->inputTermIndeces.size()<numOfInputs)
		{
			rules[i]->inputTermIndeces.add(-1);
			rules[i]->inputMembership.add(0);
			rules[i]->inputValues.add(0);
		}
	}

	for (int i=0; i<rules.size(); i++)
	{
		while (rules[i]->outputTermIndeces.size()<numOfOutputs)
		{
			rules[i]->outputTermIndeces.add(-1);
			rules[i]->outputMembership.add(0);
			rules[i]->outputValues.add(0);
			rules[i]->outputDegrees.add(0);
		}
	}
}

void RuleGenerator::run()
{
	while (threadShouldBeRunning)
	{
		if (outputsHaveToGetUpdated)
		{
			updateOutputs();

			if (!inputTimersAreCounting)
				outputsHaveToGetUpdated = false;
		}

		sleep(10);
	}
}

Rule::Rule()
{
	importance=1;
	locked = false;
	outputFromInput.remapTable(1024);
	inputTimers.remapTable(1024);
	outputTimeParameter.remapTable(1024);

	weightInputConnection = -1;
}

Rule::~Rule()
{
}