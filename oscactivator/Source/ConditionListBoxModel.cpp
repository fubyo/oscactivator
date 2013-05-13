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
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ruleCopy)
	{
		int counter = 0;

		for (int i=0; i<ruleCopy->inputTermIndeces.size(); i++)
		{
			if (ruleCopy->inputTermIndeces[i]!=-1)
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
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ruleCopy)
	{
		int counter = -1;

		for (int i=0; i<ruleCopy->inputTermIndeces.size(); i++)
		{
			if (ruleCopy->inputTermIndeces[i]!=-1)
				counter++;

			if (counter == conditionIndex)
				return i;
		}
	}

	return -1;
}

Component* ConditionListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	int numOfRows = calculateNumRows();
	bool validRow=(rowNumber>=0 && rowNumber<numOfRows);
	
	if (existingComponentToUpdate)
	{
		if (validRow)
		{
			//update condition component
			int inputIndex = getInputIndex(rowNumber);
			((ConditionComponent*)existingComponentToUpdate)->inputIndex = inputIndex;
			((ConditionComponent*)existingComponentToUpdate)->updateLabels();

			return existingComponentToUpdate;
		}
		else
		{
			delete existingComponentToUpdate;
			return 0;
		}
	}
	else
	{
		int inputIndex = getInputIndex(rowNumber);
		ConditionComponent* newConditionComponent = 0;
			
		if (inputIndex!=-1)
		{
			newConditionComponent = new ConditionComponent(inputIndex);
			newConditionComponent->updateLabels();
		}

		return newConditionComponent;
	}	
	
	return 0;
}