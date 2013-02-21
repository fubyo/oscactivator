#include "MultipleSelectionListBoxModel.h"

MultipleSelectionListBoxModel::MultipleSelectionListBoxModel(bool isItForTheOutputs)
{
	outputList = isItForTheOutputs;

	ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
}

MultipleSelectionListBoxModel::~MultipleSelectionListBoxModel()
{

}

int MultipleSelectionListBoxModel::getNumRows()
{
	if (outputList)
		return opc->outputs.size();
	else
		return ipc->inputs.size();
}

void MultipleSelectionListBoxModel::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
		g.fillAll(Colours::lightblue);
	else
		g.fillAll(Colours::lightgrey);

	g.setColour(Colours::black);
	
	if (outputList)
		g.drawText(opc->outputs[rowNumber]->name, 0, 0, width, height, juce::Justification::centredLeft, false);
	else
		g.drawText(ipc->inputs[rowNumber]->name, 0, 0, width, height, juce::Justification::centredLeft, false);
}

void MultipleSelectionListBoxModel::selectedRowsChanged (int lastRowSelected)
{
	if (outputList)
	{

	}
	else
	{

	}
}