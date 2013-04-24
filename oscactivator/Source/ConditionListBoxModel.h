#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "Pool.h"
#include "ConditionComponent.h"

class ConditionListBoxModel : public ListBoxModel
{
	int calculateNumRows();
	int getInputIndex(int conditionIndex);

public:
	int getNumRows();
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate); 

	ConditionListBoxModel();
	~ConditionListBoxModel();
};