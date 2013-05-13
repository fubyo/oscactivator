/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 May 2013 4:03:34pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_RULESPANELCOMPONENT_RULESPANELCOMPONENT_F0519140__
#define __JUCER_HEADER_RULESPANELCOMPONENT_RULESPANELCOMPONENT_F0519140__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "MultipleSelectionListBoxModel.h"
#include "RuleGenerator.h"
#include "Pool.h"
#include "InputsPanelComponent.h"
#include "OutputsPanelComponent.h"
#include "RulesListBoxModel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RulesPanelComponent  : public Component,
                             public ChangeListener,
                             public TextEditor::Listener,
                             public ButtonListener
{
public:
    //==============================================================================
    RulesPanelComponent ();
    ~RulesPanelComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback (ChangeBroadcaster* source);

	void inputRemoved(int index);
	void outputRemoved(int index);

	bool interactionOn;
	RuleGenerator ruleGenerator;

	int getRuleIndex(Component* ruleComponent);
	void updateRuleList();

	void executeSetExample();

	void updateContent();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    bool keyPressed (const KeyPress& key);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	void addExample();
	void updateRules();
	void clearExamples();
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;
    ListBox* outputsListBox;
    ListBox* inputsListBox;
    Label* label;
    Label* label2;
    TextButton* addExampleButton;
    TextButton* updateRulesButton;
    Label* examplesNumberLabel;
    TextButton* clearExamplesButton;
    TextButton* deleteRulesButton;
    ToggleButton* applyToggleButton;
    ListBox* rulesListBox;
    TextButton* addRuleButton;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    RulesPanelComponent (const RulesPanelComponent&);
    const RulesPanelComponent& operator= (const RulesPanelComponent&);
};


#endif   // __JUCER_HEADER_RULESPANELCOMPONENT_RULESPANELCOMPONENT_F0519140__
