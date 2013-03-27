#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "Pool.h"
#include "RuleComponent.h"

class RulesListBoxModel : public ListBoxModel
{
public:
	int getNumRows();
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate); 

	RulesListBoxModel();
	~RulesListBoxModel();
};