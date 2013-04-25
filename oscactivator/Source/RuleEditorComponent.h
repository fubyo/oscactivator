/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  24 Apr 2013 3:51:54pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_RULEEDITORCOMPONENT_RULEEDITORCOMPONENT_13CB5999__
#define __JUCER_HEADER_RULEEDITORCOMPONENT_RULEEDITORCOMPONENT_13CB5999__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "ConditionListBoxModel.h"
#include "RuleGenerator.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RuleEditorComponent  : public Component,
                             public ButtonListener
{
public:
    //==============================================================================
    RuleEditorComponent (int RuleIndex);
    ~RuleEditorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	bool okClicked;
	int ruleIndex;

	Rule ruleCopy;
	int getConditionIndex(Component* conditionComponent);
	void updateConditionList();

	bool isEditedRuleValid();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	
    //[/UserVariables]

    //==============================================================================
    Label* label;
    ListBox* conditionListBox;
    Label* label2;
    ListBox* statementListBox;
    TextButton* addConditionButton;
    TextButton* addStatementButton;
    TextButton* acceptButton;
    TextButton* cancelButton;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    RuleEditorComponent (const RuleEditorComponent&);
    const RuleEditorComponent& operator= (const RuleEditorComponent&);
};


#endif   // __JUCER_HEADER_RULEEDITORCOMPONENT_RULEEDITORCOMPONENT_13CB5999__
