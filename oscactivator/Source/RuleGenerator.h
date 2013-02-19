#pragma once

#include "Pool.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "Example.h"
#include "../fuzzylite/FuzzyLite.h"

class RuleGenerator
{
	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

	Array<Example> queuedExamples;

public:
	RuleGenerator(void);
	~RuleGenerator(void);

	void addExample(Example example);
	void clearExamples();
	void updateRulebase();
};
