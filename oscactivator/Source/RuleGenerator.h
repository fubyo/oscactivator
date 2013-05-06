#pragma once

#include "Pool.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "Example.h"
#include "../fuzzylite/FuzzyLite.h"

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
		
		outputMembership = other.outputMembership;
		inputValues = other.inputValues;
		outputValues = other.outputValues;
		locked = other.locked;
		return *this;
	}

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

		outputMembership = other.outputMembership;
		inputValues = other.inputValues;
		outputValues = other.outputValues;
		locked = other.locked;
	}
};

class RuleGenerator : public juce::Thread
{
	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

	OwnedArray<Example> queuedExamples;
	OwnedArray<Rule> queuedRules;

	fl::FuzzyEngine engine;

	bool outputsHaveToGetUpdated;

	bool areInputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> areOutputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> isHavingSimilarEffectsToSomeOutputs(Rule newrule, Rule oldrule);

	void createRulesFromQueuedExamples();
	void mergeNewRulesToRuleBase();
	int getIndexOfBestInputTerm(int inputIndex, double value);
	int getIndexOfBestOutputTerm(int outputIndex, double value);
	
	void updateMembershipAndTermIndeces(int index);

	bool isRuleRelevantToOutput(int ruleIndex, int outputIndex);

public:
	OwnedArray<Rule> rules;
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

	void updateRulesDueToAddingNewIO();

	double calculateOutput(int index);
	void requestOutputUpdate();
	void updateOutputs();

	String getRuleText();

	void run();
	bool threadShouldBeRunning;
};
