/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Jan 2013 3:11:43pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_INPUTCOMPONENT_INPUTCOMPONENT_B3DD726F__
#define __JUCER_HEADER_INPUTCOMPONENT_INPUTCOMPONENT_B3DD726F__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "TermManager.h"
#include "OscManager.h"

class Input
{
public:
	String name;
	String oscaddress;
	int port;
	int parameterindex;
	double* pValue;
	TermManager* termManager;

	Input()
	{
		name = String("New input");
		oscaddress = String("/address");
		port = 3333;
		parameterindex = 0;
		pValue = new double[1];
		*pValue = 0;
		termManager = new TermManager();
	};

	~Input()
	{
		OscManager::getInstance()->unregisterReceiver(pValue);
	};
};

class InputInfo
{
public:
	String name;
	String oscaddress;
	int port;
	int parameterindex;

	InputInfo() {};

	InputInfo(Input* input)
	{
		name = input->name;
		oscaddress = input->oscaddress;
		port = input->port;
		parameterindex = input->parameterindex;
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
class InputComponent  : public Component,
                        public TextEditor::Listener,
                        public ChangeBroadcaster,
                        public ComboBoxListener
{
public:
    //==============================================================================
    InputComponent ();
    ~InputComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setInputInfo(InputInfo input);
	InputInfo getInputInfo();

	void textEditorTextChanged (TextEditor& editor);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Label* namelabel;
    Label* addresslabel;
    Label* portlabel;
    Label* parameterindexlabel;
    TextEditor* nameEditor;
    TextEditor* addressEditor;
    TextEditor* portEditor;
    ComboBox* parameterIndexComboBox;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    InputComponent (const InputComponent&);
    const InputComponent& operator= (const InputComponent&);
};


#endif   // __JUCER_HEADER_INPUTCOMPONENT_INPUTCOMPONENT_B3DD726F__
