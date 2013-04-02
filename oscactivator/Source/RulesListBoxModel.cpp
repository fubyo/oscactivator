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
		bool validRow=(rowNumber>=0 && rowNumber<rpc->ruleGenerator.rules.size());
	
		if (existingComponentToUpdate)
		{
			bool alreadyDeleted = false;
			if  (((RuleComponent*)existingComponentToUpdate)->hasToGetDeleted)
			{
				delete existingComponentToUpdate;
				alreadyDeleted = true;
				if (validRow)
					existingComponentToUpdate = new RuleComponent();
			}

			if (rpc->ruleGenerator.rules.size() && validRow)
			{
				((RuleComponent*)existingComponentToUpdate)->setRuleText(rpc->ruleGenerator.getRuleText(*rpc->ruleGenerator.rules[rowNumber]));
				((RuleComponent*)existingComponentToUpdate)->setRuleName(String("Rule ")+String(rowNumber));
				
				return existingComponentToUpdate;
			}
			else
			{
				if (!alreadyDeleted)
					delete existingComponentToUpdate;

				return 0;
			}
		}
		else
		{
			RuleComponent* newRuleComponent = new RuleComponent();

			if (rpc->ruleGenerator.rules.size() && validRow)
			{
				newRuleComponent->setRuleText(rpc->ruleGenerator.getRuleText(*rpc->ruleGenerator.rules[rowNumber]));
				newRuleComponent->setRuleName(String("Rule ")+String(rowNumber));
			}

			return newRuleComponent;
		}	
	}

	return 0;
}