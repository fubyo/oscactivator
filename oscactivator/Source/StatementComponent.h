/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  17 Jul 2013 1:07:07pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_STATEMENTCOMPONENT_STATEMENTCOMPONENT_452EFF1F__
#define __JUCER_HEADER_STATEMENTCOMPONENT_STATEMENTCOMPONENT_452EFF1F__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class StatementComponent  : public Component,
                            public LabelListener,
                            public ButtonListener
{
public:
    //==============================================================================
    StatementComponent (int OutputIndex );
    ~StatementComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	int outputIndex;
	void updateLabels();
	int getOutputIndex(int StatementIndex);
	void mouseUp(const MouseEvent& event);
	void mouseDoubleClick(const MouseEvent& event);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void labelTextChanged (Label* labelThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	int getStatementIndex();

	void updateStatementParameters(int OutputIndex);
    //[/UserVariables]

    //==============================================================================
    Label* label3;
    Label* label2;
    Label* label;
    Label* outputLabel;
    Label* termLabel;
    Label* secondsLabel;
    TextButton* deleteButton;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    StatementComponent (const StatementComponent&);
    const StatementComponent& operator= (const StatementComponent&);
};


#endif   // __JUCER_HEADER_STATEMENTCOMPONENT_STATEMENTCOMPONENT_452EFF1F__
