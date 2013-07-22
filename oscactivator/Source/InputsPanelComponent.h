/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Jan 2013 3:12:23pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_INPUTSPANELCOMPONENT_INPUTSPANELCOMPONENT_2A14F424__
#define __JUCER_HEADER_INPUTSPANELCOMPONENT_INPUTSPANELCOMPONENT_2A14F424__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include <vector>
using namespace std;

#include "Pool.h"
#include "OscManager.h"
#include "OutputComponent.h"
//[/Headers]

#include "C:/Users/marinos/Promotion/Tools/oscactivator/oscactivator/Source/InputComponent.h"
#include "MembershipGraphComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class InputsPanelComponent  : public Component,
                              public ListBoxModel,
                              public ChangeListener,
                              public TextEditor::Listener,
                              public ButtonListener
{
public:
    //==============================================================================
    InputsPanelComponent ();
    ~InputsPanelComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getNumRows() {return getNumberOfNonFeedbackInputs();};
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected);
	void selectedRowsChanged (int lastRowSelected);

	void changeListenerCallback (ChangeBroadcaster* source);

	void textEditorReturnKeyPressed (TextEditor &editor);

	void updateCurrentValue();

	void executeSetExample();

	OwnedArray<Input, CriticalSection> inputs;
	int numberOfInputs;

	void updateContent();

	void clearInputs();

	void disconnectTermManagerFromMembershipGraphComponent();

	int getInputIndex(TermManager* tm);

	void updateMinMax();

	int getNumberOfNonFeedbackInputs();
	void addFeedbackInput(Output* output);
	void removeFeedbackInput(int outputIndex);
	void changeFeedbackInputName(int outputIndex, String name);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    bool keyPressed (const KeyPress& key);

	

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	
	
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent;
    InputComponent* inputComponent;
    ListBox* inputsListBox;
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


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    InputsPanelComponent (const InputsPanelComponent&);
    const InputsPanelComponent& operator= (const InputsPanelComponent&);
};


#endif   // __JUCER_HEADER_INPUTSPANELCOMPONENT_INPUTSPANELCOMPONENT_2A14F424__
