/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Feb 2013 6:02:41pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_OUTPUTCOMPONENT_OUTPUTCOMPONENT_28E3A54D__
#define __JUCER_HEADER_OUTPUTCOMPONENT_OUTPUTCOMPONENT_28E3A54D__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "TermManager.h"

class Output
{
public:
	String name;
	String oscaddress;
	int port;
	int parameterindex;
	double* pValue;
	TermManager* termManager;

	Output()
	{
		name = String("New input");
		oscaddress = String("/address");
		port = 3333;
		parameterindex = 0;
		pValue = new double[1];
		*pValue = 0;
		termManager = new TermManager();
	};

	~Output()
	{

	};
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OutputComponent  : public Component,
                         public TextEditor::Listener,
                         public ChangeBroadcaster,
                         public ButtonListener
{
public:
    //==============================================================================
    OutputComponent ();
    ~OutputComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
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
    Label* namelabel;
    Label* addresslabel;
    Label* portlabel;
    Label* hostlabel;
    TextEditor* nameEditor;
    TextEditor* addressEditor;
    TextEditor* portEditor;
    TextEditor* textEditor;
    ToggleButton* statesToggleButton;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    OutputComponent (const OutputComponent&);
    const OutputComponent& operator= (const OutputComponent&);
};


#endif   // __JUCER_HEADER_OUTPUTCOMPONENT_OUTPUTCOMPONENT_28E3A54D__
