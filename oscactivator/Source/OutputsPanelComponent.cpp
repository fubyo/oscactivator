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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "OutputsPanelComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OutputsPanelComponent::OutputsPanelComponent ()
    : groupComponent (0),
      outputsListBox (0),
      addButton (0),
      removeButton (0),
      membershipGraph (0),
      label (0),
      currentValueEditor (0),
      termEditor (0),
      label2 (0),
      setButton (0),
      minEditor (0),
      maxEditor (0),
      outputComponent (0)
{
    addAndMakeVisible (groupComponent = new GroupComponent (L"new group",
                                                            L"Output properties"));

    addAndMakeVisible (outputsListBox = new ListBox());
    outputsListBox->setName (L"new component");

    addAndMakeVisible (addButton = new TextButton (L"new button"));
    addButton->setButtonText (L"Add");
    addButton->addListener (this);

    addAndMakeVisible (removeButton = new TextButton (L"new button"));
    removeButton->setButtonText (L"Remove");
    removeButton->addListener (this);

    addAndMakeVisible (membershipGraph = new MembershipGraphComponent());
    addAndMakeVisible (label = new Label (L"new label",
                                          L"Current value\n"));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (currentValueEditor = new TextEditor (L"new text editor"));
    currentValueEditor->setMultiLine (false);
    currentValueEditor->setReturnKeyStartsNewLine (false);
    currentValueEditor->setReadOnly (false);
    currentValueEditor->setScrollbarsShown (true);
    currentValueEditor->setCaretVisible (true);
    currentValueEditor->setPopupMenuEnabled (true);
    currentValueEditor->setText (String::empty);

    addAndMakeVisible (termEditor = new TextEditor (L"new text editor"));
    termEditor->setMultiLine (false);
    termEditor->setReturnKeyStartsNewLine (false);
    termEditor->setReadOnly (false);
    termEditor->setScrollbarsShown (true);
    termEditor->setCaretVisible (true);
    termEditor->setPopupMenuEnabled (true);
    termEditor->setText (String::empty);

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"is"));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (setButton = new TextButton (L"new button"));
    setButton->setButtonText (L"Set");
    setButton->addListener (this);

    addAndMakeVisible (minEditor = new TextEditor (L"new text editor"));
    minEditor->setMultiLine (false);
    minEditor->setReturnKeyStartsNewLine (false);
    minEditor->setReadOnly (false);
    minEditor->setScrollbarsShown (true);
    minEditor->setCaretVisible (true);
    minEditor->setPopupMenuEnabled (true);
    minEditor->setText (String::empty);

    addAndMakeVisible (maxEditor = new TextEditor (L"new text editor"));
    maxEditor->setMultiLine (false);
    maxEditor->setReturnKeyStartsNewLine (false);
    maxEditor->setReadOnly (false);
    maxEditor->setScrollbarsShown (true);
    maxEditor->setCaretVisible (true);
    maxEditor->setPopupMenuEnabled (true);
    maxEditor->setText (String::empty);

    addAndMakeVisible (outputComponent = new OutputComponent());

    //[UserPreSize]
    //[/UserPreSize]

    setSize (609, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OutputsPanelComponent::~OutputsPanelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponent);
    deleteAndZero (outputsListBox);
    deleteAndZero (addButton);
    deleteAndZero (removeButton);
    deleteAndZero (membershipGraph);
    deleteAndZero (label);
    deleteAndZero (currentValueEditor);
    deleteAndZero (termEditor);
    deleteAndZero (label2);
    deleteAndZero (setButton);
    deleteAndZero (minEditor);
    deleteAndZero (maxEditor);
    deleteAndZero (outputComponent);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OutputsPanelComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.fillRect (8, 458, 1, 28);

    g.setColour (Colours::black);
    g.fillRect (600, 458, 1, 28);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OutputsPanelComponent::resized()
{
    groupComponent->setBounds (168, 8, 432, 200);
    outputsListBox->setBounds (8, 48, 150, 160);
    addButton->setBounds (8, 16, 47, 24);
    removeButton->setBounds (64, 16, 64, 24);
    membershipGraph->setBounds (8, 257, 592, 200);
    label->setBounds (8, 219, 120, 24);
    currentValueEditor->setBounds (104, 219, 144, 24);
    termEditor->setBounds (272, 219, 232, 24);
    label2->setBounds (248, 219, 24, 24);
    setButton->setBounds (512, 219, 86, 24);
    minEditor->setBounds (14, 461, 150, 24);
    maxEditor->setBounds (447, 462, 150, 24);
    outputComponent->setBounds (184, 32, 400, 168);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OutputsPanelComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == addButton)
    {
        //[UserButtonCode_addButton] -- add your button handler code here..
        //[/UserButtonCode_addButton]
    }
    else if (buttonThatWasClicked == removeButton)
    {
        //[UserButtonCode_removeButton] -- add your button handler code here..
        //[/UserButtonCode_removeButton]
    }
    else if (buttonThatWasClicked == setButton)
    {
        //[UserButtonCode_setButton] -- add your button handler code here..
        //[/UserButtonCode_setButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool OutputsPanelComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OutputsPanelComponent::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{

}

void OutputsPanelComponent::selectedRowsChanged (int lastRowSelected)
{
	
}

void OutputsPanelComponent::changeListenerCallback (ChangeBroadcaster* source)
{
	
}

void OutputsPanelComponent::textEditorReturnKeyPressed (TextEditor &editor)
{
	
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OutputsPanelComponent" componentName=""
                 parentClasses="public Component, public ListBoxModel, public ChangeListener, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="609"
                 initialHeight="600">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="8 458 1 28" fill="solid: ff000000" hasStroke="0"/>
    <RECT pos="600 458 1 28" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="new group" id="36cc91e9cc81f4f4" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="168 8 432 200" title="Output properties"/>
  <GENERICCOMPONENT name="new component" id="9e399de4bf88af70" memberName="outputsListBox"
                    virtualName="" explicitFocusOrder="0" pos="8 48 150 160" class="ListBox"
                    params=""/>
  <TEXTBUTTON name="new button" id="300ff6cf19f0c4af" memberName="addButton"
              virtualName="" explicitFocusOrder="0" pos="8 16 47 24" buttonText="Add"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="3b07aa10e6414a55" memberName="removeButton"
              virtualName="" explicitFocusOrder="0" pos="64 16 64 24" buttonText="Remove"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="67fcacf009fa4790" memberName="membershipGraph" virtualName=""
             explicitFocusOrder="0" pos="8 257 592 200" sourceFile="MembershipGraphComponent.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="d65c34a4a966a503" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 219 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Current value&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="74e2d0b5591a67da" memberName="currentValueEditor"
              virtualName="" explicitFocusOrder="0" pos="104 219 144 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="76a41ecfc22e8bd1" memberName="termEditor"
              virtualName="" explicitFocusOrder="0" pos="272 219 232 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="a9860cbed91414aa" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="248 219 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="is" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="c4309cd0fddcd2aa" memberName="setButton"
              virtualName="" explicitFocusOrder="0" pos="512 219 86 24" buttonText="Set"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="7527e80cac92e6bf" memberName="minEditor"
              virtualName="" explicitFocusOrder="0" pos="14 461 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="e86da1c8d0ae8716" memberName="maxEditor"
              virtualName="" explicitFocusOrder="0" pos="447 462 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <JUCERCOMP name="" id="669420e8ddc78026" memberName="outputComponent" virtualName=""
             explicitFocusOrder="0" pos="184 32 400 168" sourceFile="OutputComponent.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
