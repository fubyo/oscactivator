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
};

class RuleGenerator
{
	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

	Array<Example> queuedExamples;
	Array<Rule> queuedRules;
	Array<Rule> rules;

	fl::FuzzyEngine engine;

	bool areInputsConflicting(Rule firstrule, Rule secondrule);
	Array<int> areOutputsConflicting(Rule firstrule, Rule secondrule);

	void createRulesFromQueuedExamples();
	void mergeNewRulesToRuleBase();
	int getIndexOfBestInputTerm(int inputIndex, double value);
	int getIndexOfBestOutputTerm(int outputIndex, double value);

public:
	RuleGenerator(void);
	~RuleGenerator(void);

	void addExample(Example example);
	void clearExamples();
	void updateRulebase();
	int getNumberOfQueuedExamples();
};
