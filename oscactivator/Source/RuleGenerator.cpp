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

void RuleGenerator::updateRulebase()
{
	
}

