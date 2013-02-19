#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "Pool.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"

class MultipleSelectionListBoxModel : public ListBoxModel
{
	bool outputList;
	InputsPanelComponent* ipc;
	OutputsPanelComponent* opc;

public:
	int getNumRows();
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	MultipleSelectionListBoxModel(bool isItForTheOutputs);
	~MultipleSelectionListBoxModel();
};