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
	Array<double> outputMembership;
	Array<double> outputValues;

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
		outputMembership = other.outputMembership;
		inputValues = other.inputValues;
		outputValues = other.outputValues;
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
		outputMembership = other.outputMembership;
		inputValues = other.inputValues;
		outputValues = other.outputValues;
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
	void recalculateDegrees(int ruleIndex);
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

	void removeInput(int index);
	void removeOutput(int index);

	double calculateOutput(int index);
	void requestOutputUpdate();
	void updateOutputs();

	String getRuleText();

	void run();
	bool threadShouldBeRunning;
};
