/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 May 2013 4:09:06pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_RULECOMPONENT_RULECOMPONENT_255D3FE4__
#define __JUCER_HEADER_RULECOMPONENT_RULECOMPONENT_255D3FE4__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "Pool.h"
#include "RuleEditorComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class RuleComponent  : public Component,
                       public ButtonListener,
                       public LabelListener
{
public:
    //==============================================================================
    RuleComponent ();
    ~RuleComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setRuleText(String ruleText);
	void setRuleName(String ruleName);
	void setLock(bool lock);

	bool hasToGetDeleted;

	void mouseUp(const MouseEvent& event);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    TextButton* deleteButton;
    TextButton* editButton;
    ToggleButton* lockButton;
    Label* ruleNameLabel;
    TextEditor* ruleTextEditor;
    Label* wlabel;
    Label* weightLabel;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    RuleComponent (const RuleComponent&);
    const RuleComponent& operator= (const RuleComponent&);
};


#endif   // __JUCER_HEADER_RULECOMPONENT_RULECOMPONENT_255D3FE4__
