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
	Array<int> outputTermIndeces;
	Array<double> outputMembership;

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
	}
};

class RuleGenerator
{
	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

	Array<Example> queuedExamples;
	OwnedArray<Rule> queuedRules;
	OwnedArray<Rule> rules;

	fl::FuzzyEngine engine;

	bool areInputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> areOutputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> isHavingSimilarEffectsToSomeOutputs(Rule newrule, Rule oldrule);

	void createRulesFromQueuedExamples();
	void mergeNewRulesToRuleBase();
	int getIndexOfBestInputTerm(int inputIndex, double value);
	int getIndexOfBestOutputTerm(int outputIndex, double value);

	String getRuleText(Rule rule);

public:
	RuleGenerator(void);
	~RuleGenerator(void);

	void addExample(Example example);
	void clearExamples();
	void updateRulebase();
	int getNumberOfQueuedExamples();
	void deleteAllRules();

	String getRuleText();
};
