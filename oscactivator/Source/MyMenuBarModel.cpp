#include "MyMenuBarModel.h"

MyMenuBarModel::MyMenuBarModel()
{

}

MyMenuBarModel::~MyMenuBarModel()
{

}

StringArray MyMenuBarModel::getMenuBarNames()
{
	StringArray result;
	result.add("File");
	result.add("Help");

	return result;
} 

PopupMenu MyMenuBarModel::getMenuForIndex (int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;

	if (topLevelMenuIndex == 0)
	{
		menu.addItem(1, "Load...");
		menu.addItem(2, "Save...");
		menu.addSeparator();
		menu.addItem(3, "Quit");
	}
	else if (topLevelMenuIndex == 1)
	{
		menu.addItem(1, "Go to homepage");
		menu.addItem(2, "Info...");
	}

	return menu;
}

void MyMenuBarModel::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{

}