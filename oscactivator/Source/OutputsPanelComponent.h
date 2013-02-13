/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Feb 2013 6:02:40pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_OUTPUTSPANELCOMPONENT_OUTPUTSPANELCOMPONENT_3EA1FB3E__
#define __JUCER_HEADER_OUTPUTSPANELCOMPONENT_OUTPUTSPANELCOMPONENT_3EA1FB3E__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
//[/Headers]

#include "MembershipGraphComponent.h"
#include "OutputComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OutputsPanelComponent  : public Component,
                               public ListBoxModel,
                               public ChangeListener,
                               public TextEditor::Listener,
                               public ButtonListener
{
public:
    //==============================================================================
    OutputsPanelComponent ();
    ~OutputsPanelComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getNumRows() {return (int)outputs.size();};
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	void changeListenerCallback (ChangeBroadcaster* source);
	void textEditorReturnKeyPressed (TextEditor &editor);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    bool keyPressed (const KeyPress& key);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	int numberOfOutputs;
	OwnedArray<Output> outputs;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;
    ListBox* outputsListBox;
    TextButton* addButton;
    TextButton* removeButton;
    MembershipGraphComponent* membershipGraph;
    Label* label;
    TextEditor* currentValueEditor;
    TextEditor* termEditor;
    Label* label2;
    TextButton* setButton;
    TextEditor* minEditor;
    TextEditor* maxEditor;
    OutputComponent* outputComponent;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    OutputsPanelComponent (const OutputsPanelComponent&);
    const OutputsPanelComponent& operator= (const OutputsPanelComponent&);
};


#endif   // __JUCER_HEADER_OUTPUTSPANELCOMPONENT_OUTPUTSPANELCOMPONENT_3EA1FB3E__
