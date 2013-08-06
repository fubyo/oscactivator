#pragma once

#include "Pool.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "Example.h"
#include "InputTimer.h"
#include "OutputTimer.h"

class Rule
{
public:
	double importance;
	double inputDegree;
	Array<double> outputDegrees;
	Array<int> inputTermIndeces;
	Array<double> inputMembership;
	Array<double> inputValues;
	Array<int> outputTermIndeces;
	HashMap<int, int> outputFromInput;
	Array<double> outputMembership;
	Array<double> outputValues;

	HashMap<int, InputTimer*> inputTimers;
	HashMap<int, OutputTimer*> outputTimers;
	HashMap<int, double> savedOutputValues;

	int weightInputConnection;

	bool locked;

	Rule();
	~Rule();

	Rule &operator= (const Rule &other)
	{
		importance = other.importance;
		inputDegree = other.inputDegree;
		outputDegrees = other.outputDegrees;
		inputTermIndeces = other.inputTermIndeces;
		inputMembership = other.inputMembership;
		outputTermIndeces = other.outputTermIndeces;

		outputFromInput.clear();
		outputFromInput.remapTable(1024);
		for (int i=0; i<outputTermIndeces.size(); i++)
		{
			if (other.outputFromInput.contains(i))
				outputFromInput.set(i, other.outputFromInput[i]);
		}

		inputTimers.clear();
		inputTimers.remapTable(1024);
		for (int i=0; i<other.inputTermIndeces.size(); i++)
		{
			if (other.inputTimers.contains(i))
				inputTimers.set(i, other.inputTimers[i]);
		}

		outputTimers.clear();
		outputTimers.remapTable(1024);
		for (int i=0; i<other.outputTermIndeces.size(); i++)
		{
			if (other.outputTimers.contains(i))
				outputTimers.set(i, other.outputTimers[i]);
		}

		savedOutputValues.clear();
		savedOutputValues.remapTable(1024);
		for (int i=0; i<other.outputTermIndeces.size(); i++)
		{
			if (other.savedOutputValues.contains(i))
				savedOutputValues.set(i, other.savedOutputValues[i]);
		}

		outputMembership = other.outputMembership;
		inputValues = other.inputValues;
		outputValues = other.outputValues;
		locked = other.locked;

		weightInputConnection = other.weightInputConnection;

		return *this;
	};

	Rule(const Rule& other)
	{
		importance = other.importance;
		inputDegree = other.inputDegree;
		outputDegrees = other.outputDegrees;
		inputTermIndeces = other.inputTermIndeces;
		inputMembership = other.inputMembership;
		outputTermIndeces = other.outputTermIndeces;
	
		outputFromInput.clear();
		outputFromInput.remapTable(1024);
		for (int i=0; i<outputTermIndeces.size(); i++)
		{
			if (other.outputFromInput.contains(i))
				outputFromInput.set(i, other.outputFromInput[i]);
		}

		inputTimers.clear();
		inputTimers.remapTable(1024);
		for (int i=0; i<other.inputTermIndeces.size(); i++)
		{
			if (other.inputTimers.contains(i))
				inputTimers.set(i, other.inputTimers[i]);
		}

		outputTimers.clear();
		outputTimers.remapTable(1024);
		for (int i=0; i<other.outputTermIndeces.size(); i++)
		{
			if (other.outputTimers.contains(i))
				outputTimers.set(i, other.outputTimers[i]);
		}

		savedOutputValues.clear();
		savedOutputValues.remapTable(1024);
		for (int i=0; i<other.outputTermIndeces.size(); i++)
		{
			if (other.savedOutputValues.contains(i))
				savedOutputValues.set(i, other.savedOutputValues[i]);
		}

		outputMembership = other.outputMembership;
		inputValues = other.inputValues;
		outputValues = other.outputValues;

		weightInputConnection = other.weightInputConnection;

		locked = other.locked;
	};
};

class RuleGenerator : public juce::Thread
{
	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

	OwnedArray<Example> queuedExamples;
	OwnedArray<Rule> queuedRules;

	bool outputsHaveToGetUpdated;

	bool areInputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> areOutputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> isHavingSimilarEffectsToSomeOutputs(Rule newrule, Rule oldrule);

	void createRulesFromQueuedExamples();
	void mergeNewRulesToRuleBase();
	
	void updateMembershipAndTermIndeces(int index);

	bool isRuleRelevantToOutput(int ruleIndex, int outputIndex);

	HashMap<int, double> savedOutputValue;

public:
	OwnedArray<Rule, CriticalSection> rules;
	String getRuleText(Rule rule);

	RuleGenerator(void);
	~RuleGenerator(void);

	void addExample(Example example);
	void clearExamples();
	void updateRulebase();
	int getNumberOfQueuedExamples();
	void deleteAllRules();

	void recalculateDegrees(int ruleIndex);

	void removeInput(int index);
	void removeOutput(int index);

	void updateRulesBecauseOfTermChangesOnInput(int index);
	void updateRulesBecauseOfTermChangesOnOutput(int index);

	void updateRulesBecauseOfNewTerm(TermManager* termManager, int newTermIndex); 

	void updateRulesDueToAddingNewOutput();
	void updateRulesDueToAddingNewInput();

	double calculateOutput(int index);
	void requestOutputUpdate();
	void updateOutputs();

	int getIndexOfBestInputTerm(int inputIndex, double value);
	int getIndexOfBestOutputTerm(int outputIndex, double value);

	String getRuleText();

	void run();

	void deleteAllTimers();

	bool timersAreCounting;
	bool valuesAreChanging;
	bool interactionIsOn;

	CriticalSection cs;
};
