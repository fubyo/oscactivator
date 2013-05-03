#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "Pool.h"
#include "StatementComponent.h"

class StatementListBoxModel : public ListBoxModel
{
	int calculateNumRows();
	int getOutputIndex(int conditionIndex);

public:
	int getNumRows();
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate); 

	StatementListBoxModel();
	~StatementListBoxModel();
};