/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 Apr 2013 10:55:21am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "RulesPanelComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
    : tabbedComponent (0)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (30);
    tabbedComponent->addTab (L"Inputs", Colours::white, new InputsPanelComponent(), true);
    tabbedComponent->addTab (L"Outputs", Colours::white, new OutputsPanelComponent(), true);
    tabbedComponent->addTab (L"Rules", Colours::white, new RulesPanelComponent(), true);
    tabbedComponent->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (620, 700);


    //[Constructor] You can add your own custom stuff here..
	Pool::Instance()->reg("MainComponent", this);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (tabbedComponent);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    tabbedComponent->setBounds (0, 0, 616, 664);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::executeSetExample()
{
	int tabIndex = tabbedComponent->getCurrentTabIndex();

	if (tabIndex==0)
	{
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
		if (ipc)
		{
			ipc->executeSetExample();
		}
	}
	else if (tabIndex==1)
	{
		OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
		if (opc)
		{
			opc->executeSetExample();
		}
	}
	else if (tabIndex==2)
	{
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (rpc)
		{
			rpc->executeSetExample();
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="620" initialHeight="700">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TABBEDCOMPONENT name="new tabbed component" id="9963c9520c37d7c6" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 0 616 664" orientation="top"
                   tabBarDepth="30" initialTab="0">
    <TAB name="Inputs" colour="ffffffff" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="InputsPanelComponent.cpp"/>
    <TAB name="Outputs" colour="ffffffff" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="OutputsPanelComponent.cpp"/>
    <TAB name="Rules" colour="ffffffff" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="RulesPanelComponent.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
