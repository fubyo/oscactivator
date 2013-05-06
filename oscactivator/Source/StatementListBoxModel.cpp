#include "StatementListBoxModel.h"
#include "RulesPanelComponent.h"

StatementListBoxModel::StatementListBoxModel()
{

}

StatementListBoxModel::~StatementListBoxModel()
{

}

int StatementListBoxModel::calculateNumRows()
{
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ruleCopy)
	{
		int counter = 0;

		for (int i=0; i<ruleCopy->outputTermIndeces.size(); i++)
		{
			if (ruleCopy->outputTermIndeces[i]!=-1)
				counter++;
		}

		counter += ruleCopy->outputFromInput.size();

		return counter;
	}
	
	return 0;
}

int StatementListBoxModel::getNumRows()
{	
	return calculateNumRows();
}

void StatementListBoxModel::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	g.fillAll(Colours::lightgrey);
}

void StatementListBoxModel::selectedRowsChanged (int lastRowSelected)
{
	
}

int StatementListBoxModel::getOutputIndex(int statementIndex)
{
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ruleCopy)
	{
		int counter = -1;

		for (int i=0; i<ruleCopy->outputTermIndeces.size(); i++)
		{
			if (ruleCopy->outputTermIndeces[i]!=-1 || ruleCopy->outputFromInput.contains(i))
				counter++;

			if (counter == statementIndex)
				return i;
		}
	}

	return -1;
}

Component* StatementListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	int numOfRows = calculateNumRows();
	bool validRow=(rowNumber>=0 && rowNumber<numOfRows);
	
	if (existingComponentToUpdate)
	{
		if (validRow)
		{
			//update condition component
			int outputIndex = getOutputIndex(rowNumber);
			((StatementComponent*)existingComponentToUpdate)->outputIndex = outputIndex;
			((StatementComponent*)existingComponentToUpdate)->updateLabels();

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
		int outputIndex = getOutputIndex(rowNumber);
		StatementComponent* newStatementComponent = 0;
			
		if (outputIndex!=-1)
		{
			newStatementComponent = new StatementComponent(outputIndex);
		}

		return newStatementComponent;
	}	
	
	return 0;
}