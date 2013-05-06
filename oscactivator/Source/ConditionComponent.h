/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Apr 2013 1:22:35pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CONDITIONCOMPONENT_CONDITIONCOMPONENT_B8C735AC__
#define __JUCER_HEADER_CONDITIONCOMPONENT_CONDITIONCOMPONENT_B8C735AC__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "Pool.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConditionComponent  : public Component,
                            public LabelListener,
                            public ButtonListener
{
public:
    //==============================================================================
    ConditionComponent (int InputIndex );
    ~ConditionComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int inputIndex;

	void updateLabels();

	int getInputIndex(int ConditionIndex);

	void mouseUp(const MouseEvent& event);	

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	int getConditionIndex();

	void updateConditionParameters(int InputIndex);
    //[/UserVariables]

    //==============================================================================
    Label* label3;
    Label* label2;
    Label* label;
    Label* inputLabel;
    Label* termLabel;
    Label* secondsLabel;
    TextButton* deleteButton;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    ConditionComponent (const ConditionComponent&);
    const ConditionComponent& operator= (const ConditionComponent&);
};


#endif   // __JUCER_HEADER_CONDITIONCOMPONENT_CONDITIONCOMPONENT_B8C735AC__
