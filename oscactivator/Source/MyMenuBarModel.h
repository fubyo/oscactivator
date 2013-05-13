#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MyMenuBarModel : public MenuBarModel
{
public:
	MyMenuBarModel(); 
	~MyMenuBarModel();

	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex (int topLevelMenuIndex, const String &menuName);
	void menuItemSelected (int menuItemID, int topLevelMenuIndex);
};