#include "RuleGenerator.h"

RuleGenerator::RuleGenerator(void)
{
	ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
}

RuleGenerator::~RuleGenerator(void)
{

}

void RuleGenerator::addExample(Example example)
{
	queuedExamples.add(example);
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
		
		for (int ii=0; ii<queuedExamples[i].inputValues.size(); ii++) //iterate over the inputs of the example
		{
			if (queuedExamples[i].inputValues[ii].relevance) //if input is relevant
			{
				int inputTermIndex=getIndexOfBestInputTerm(ii, queuedExamples[i].inputValues[ii].value);
				rule.inputTermIndeces.add(inputTermIndex);
				
				TermManager* termManager=ipc->inputs[ii]->termManager;
				float membership = termManager->terms[inputTermIndex]->membership((float)queuedExamples[i].inputValues[ii].value);
				
				rule.inputDegree*=membership;
				rule.inputMembership.add(membership);
			}
			else //if input is not relevant
			{
				rule.inputTermIndeces.add(-1);
				rule.inputMembership.add(-1);
			}
		}

		for (int ii=0; ii<queuedExamples[i].outputValues.size(); ii++) //iterate over the outputs of the example
		{
			if (queuedExamples[i].outputValues[ii].relevance) //if output is relevant
			{
				int outputTermIndex=getIndexOfBestOutputTerm(ii, queuedExamples[i].outputValues[ii].value);
				rule.outputTermIndeces.add(outputTermIndex);
				
				TermManager* termManager=opc->outputs[ii]->termManager;
				float membership = termManager->terms[outputTermIndex]->membership(queuedExamples[i].outputValues[ii].value);
				
				rule.outputDegrees.add(rule.inputDegree*membership);
				rule.outputMembership.add(membership);
			}
			else //if output is not relevant
			{
				rule.outputDegrees.add(0);
				rule.outputTermIndeces.add(-1);
				rule.outputMembership.add(-1);
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
						rules[ruleIndex]->outputDegrees.set(outputIndex, rules[ruleIndex]->outputMembership[outputIndex]*rules[ruleIndex]->inputDegree);

						queuedRules[i]->outputDegrees.set(outputIndex, 0);
						queuedRules[i]->outputMembership.set(outputIndex ,-1);
						queuedRules[i]->outputTermIndeces.set(outputIndex ,-1);
					}
					else
					{
						queuedRules[i]->outputMembership.set(outputIndex ,rules[ruleIndex]->outputMembership[outputIndex]);
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

		if (outputContribution)
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
		if (firstrule.inputTermIndeces[i]!=-1 && secondrule.inputTermIndeces[i]!=-1)
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
			text +=String(ipc->inputs[i]->termManager->terms[rule.inputTermIndeces[i]]->name().c_str());
			
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
			text +=String(opc->outputs[i]->termManager->terms[rule.outputTermIndeces[i]]->name().c_str());
			
			if (!firstResultAdded)
				firstResultAdded = true;
		}
	}

	text += String(".\n");

	return text;
}

void RuleGenerator::deleteAllRules()
{
	rules.clear();
}

Rule::Rule()
{
	importance=1;
}

Rule::~Rule()
{
}