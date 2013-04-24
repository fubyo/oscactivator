#include "ConditionListBoxModel.h"
#include "RulesPanelComponent.h"

ConditionListBoxModel::ConditionListBoxModel()
{

}

ConditionListBoxModel::~ConditionListBoxModel()
{

}

int ConditionListBoxModel::calculateNumRows()
{
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");

	int ruleIndex = Pool::Instance()->getValue("ruleIndexForEditing");
	if (ruleIndex!=-1 && rpc)
	{
		int counter = 0;

		for (int i=0; i<rpc->ruleGenerator.rules[ruleIndex]->inputTermIndeces.size(); i++)
		{
			if (rpc->ruleGenerator.rules[ruleIndex]->inputTermIndeces[i]!=-1)
				counter++;
		}

		return counter;
	}

	
	return 0;
}

int ConditionListBoxModel::getNumRows()
{	
	return calculateNumRows();
}

void ConditionListBoxModel::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	g.fillAll(Colours::lightgrey);
}

void ConditionListBoxModel::selectedRowsChanged (int lastRowSelected)
{
	
}

int ConditionListBoxModel::getInputIndex(int conditionIndex)
{
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	int ruleIndex = Pool::Instance()->getValue("ruleIndexForEditing");

	if (ruleIndex!=-1 && rpc)
	{
		int counter = -1;

		vector<int> test;

		for (int i=0; i<rpc->ruleGenerator.rules[ruleIndex]->inputTermIndeces.size(); i++)
		{
			test.push_back(rpc->ruleGenerator.rules[ruleIndex]->inputTermIndeces[i]);

			if (rpc->ruleGenerator.rules[ruleIndex]->inputTermIndeces[i]!=-1)
				counter++;

			if (counter == conditionIndex)
				return i;
		}
	}

	return -1;
}

Component* ConditionListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	
	if (rpc)
	{
		int numOfRows = calculateNumRows();
		bool validRow=(rowNumber>=0 && rowNumber<numOfRows);
	
		if (existingComponentToUpdate)
		{
			bool alreadyDeleted = false;
			if  (((ConditionComponent*)existingComponentToUpdate)->hasToGetDeleted)
			{
				delete existingComponentToUpdate;
				alreadyDeleted = true;
				if (validRow)
				{
					int ruleIndex = Pool::Instance()->getValue("ruleIndexForEditing");
					int inputIndex = getInputIndex(rowNumber);
					existingComponentToUpdate = new ConditionComponent(ruleIndex, inputIndex);
				}
			}

			if (rpc->ruleGenerator.rules.size() && validRow)
			{
				//update condition component
				int ruleIndex = Pool::Instance()->getValue("ruleIndexForEditing");
				int inputIndex = getInputIndex(rowNumber);
				((ConditionComponent*)existingComponentToUpdate)->ruleIndex = ruleIndex;
				((ConditionComponent*)existingComponentToUpdate)->inputIndex = inputIndex;
				((ConditionComponent*)existingComponentToUpdate)->updateLabels();

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
			int ruleIndex = Pool::Instance()->getValue("ruleIndexForEditing");
			int inputIndex = getInputIndex(rowNumber);
			ConditionComponent* newConditionComponent = 0;
			
			if (inputIndex!=-1)
			{
				newConditionComponent = new ConditionComponent(ruleIndex, inputIndex);
			}

			return newConditionComponent;
		}	
	}

	return 0;
}