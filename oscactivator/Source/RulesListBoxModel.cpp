#include "RulesListBoxModel.h"
#include "RulesPanelComponent.h"

RulesListBoxModel::RulesListBoxModel()
{

}

RulesListBoxModel::~RulesListBoxModel()
{

}

int RulesListBoxModel::getNumRows()
{
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");

	if (rpc)
		return rpc->ruleGenerator.rules.size();
	else
		return 0;
}

void RulesListBoxModel::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	g.fillAll(Colours::lightgrey);
}

void RulesListBoxModel::selectedRowsChanged (int lastRowSelected)
{
	
}

Component* RulesListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	if (rpc)
	{
		if (existingComponentToUpdate)
		{
			if  (((RuleComponent*)existingComponentToUpdate)->hasToGetDeleted)
			{
				delete existingComponentToUpdate;
				return 0;
			}
		}
		else if (rowNumber>=rpc->ruleGenerator.rules.size() || rowNumber<0)
		{
			return 0;
		}
			
	}

	if (existingComponentToUpdate)
	{
		if (rpc)
		{
			if (rpc->ruleGenerator.rules.size() && rowNumber<rpc->ruleGenerator.rules.size())
			{
				((RuleComponent*)existingComponentToUpdate)->setRuleText(rpc->ruleGenerator.getRuleText(*rpc->ruleGenerator.rules[rowNumber]));
				((RuleComponent*)existingComponentToUpdate)->setRuleName(String("Rule ")+String(rowNumber));
			}
		}

		return existingComponentToUpdate;
	}
	else
	{
		RuleComponent* newRuleComponent = new RuleComponent();

		if (rpc)
		{
			if (rpc->ruleGenerator.rules.size() && rowNumber<rpc->ruleGenerator.rules.size())
			{
				newRuleComponent->setRuleText(rpc->ruleGenerator.getRuleText(*rpc->ruleGenerator.rules[rowNumber]));
				newRuleComponent->setRuleName(String("Rule ")+String(rowNumber));
			}
		}

		return newRuleComponent;
	}
}