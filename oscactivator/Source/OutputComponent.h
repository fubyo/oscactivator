/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  14 Feb 2013 5:25:35pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_OUTPUTCOMPONENT_OUTPUTCOMPONENT_2134744C__
#define __JUCER_HEADER_OUTPUTCOMPONENT_OUTPUTCOMPONENT_2134744C__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "TermManager.h"
#include "OscManager.h"

class Output
{
public:
	String name;
	String oscaddress;
	int port;
	String host;
	double* pValue;
	TermManager* termManager;

	bool sendStateChanges;
	int lastState;

	char* buffer;
	UdpTransmitSocket* socket;

	Output()
	{
		name = String("New output");
		oscaddress = String("/address");
		port = 4444;
		host = String("127.0.0.1");
		pValue = new double[1];
		*pValue = 0;
		termManager = new TermManager();

		socket = 0;
		buffer = new char[128];

		sendStateChanges=false;
		lastState = -1;
	};

	void prepareSocket()
	{
		if (socket)
			delete socket;

		socket = new UdpTransmitSocket(IpEndpointName(host.toUTF8(), port));
	}

	~Output()
	{
		delete [] buffer;
		delete [] pValue;
		delete socket;
		delete termManager;
	};
};

class OutputInfo
{
public:
	String name;
	String oscaddress;
	int port;
	String host;
	bool sendStateChanges;

	OutputInfo() {};

	OutputInfo(Output* output)
	{
		name = output->name;
		oscaddress = output->oscaddress;
		port = output->port;
		host = output->host;
		sendStateChanges = output->sendStateChanges;
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
	void setOutputInfo(OutputInfo output);
	OutputInfo getOutputInfo();

	void textEditorTextChanged (TextEditor& editor);
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
    TextEditor* hostEditor;
    ToggleButton* statesToggleButton;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    OutputComponent (const OutputComponent&);
    const OutputComponent& operator= (const OutputComponent&);
};


#endif   // __JUCER_HEADER_OUTPUTCOMPONENT_OUTPUTCOMPONENT_2134744C__
