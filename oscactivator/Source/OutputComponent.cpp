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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "OutputComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OutputComponent::OutputComponent ()
    : namelabel (0),
      addresslabel (0),
      portlabel (0),
      hostlabel (0),
      nameEditor (0),
      addressEditor (0),
      portEditor (0),
      textEditor (0),
      statesToggleButton (0)
{
    addAndMakeVisible (namelabel = new Label (L"new label",
                                              L"Name"));
    namelabel->setFont (Font (15.0000f, Font::plain));
    namelabel->setJustificationType (Justification::centredLeft);
    namelabel->setEditable (false, false, false);
    namelabel->setColour (TextEditor::textColourId, Colours::black);
    namelabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (addresslabel = new Label (L"new label",
                                                 L"OSC Address\n"));
    addresslabel->setFont (Font (15.0000f, Font::plain));
    addresslabel->setJustificationType (Justification::centredLeft);
    addresslabel->setEditable (false, false, false);
    addresslabel->setColour (TextEditor::textColourId, Colours::black);
    addresslabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (portlabel = new Label (L"new label",
                                              L"OSC Port\n"));
    portlabel->setFont (Font (15.0000f, Font::plain));
    portlabel->setJustificationType (Justification::centredLeft);
    portlabel->setEditable (false, false, false);
    portlabel->setColour (TextEditor::textColourId, Colours::black);
    portlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (hostlabel = new Label (L"new label",
                                              L"Host\n"));
    hostlabel->setFont (Font (15.0000f, Font::plain));
    hostlabel->setJustificationType (Justification::centredLeft);
    hostlabel->setEditable (false, false, false);
    hostlabel->setColour (TextEditor::textColourId, Colours::black);
    hostlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (nameEditor = new TextEditor (L"new text editor"));
    nameEditor->setMultiLine (false);
    nameEditor->setReturnKeyStartsNewLine (false);
    nameEditor->setReadOnly (false);
    nameEditor->setScrollbarsShown (true);
    nameEditor->setCaretVisible (true);
    nameEditor->setPopupMenuEnabled (true);
    nameEditor->setText (String::empty);

    addAndMakeVisible (addressEditor = new TextEditor (L"new text editor"));
    addressEditor->setExplicitFocusOrder (1);
    addressEditor->setMultiLine (false);
    addressEditor->setReturnKeyStartsNewLine (false);
    addressEditor->setReadOnly (false);
    addressEditor->setScrollbarsShown (true);
    addressEditor->setCaretVisible (true);
    addressEditor->setPopupMenuEnabled (true);
    addressEditor->setText (String::empty);

    addAndMakeVisible (portEditor = new TextEditor (L"new text editor"));
    portEditor->setExplicitFocusOrder (2);
    portEditor->setMultiLine (false);
    portEditor->setReturnKeyStartsNewLine (false);
    portEditor->setReadOnly (false);
    portEditor->setScrollbarsShown (true);
    portEditor->setCaretVisible (true);
    portEditor->setPopupMenuEnabled (true);
    portEditor->setText (String::empty);

    addAndMakeVisible (textEditor = new TextEditor (L"new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String::empty);

    addAndMakeVisible (statesToggleButton = new ToggleButton (L"new toggle button"));
    statesToggleButton->setButtonText (L"Send state changes");
    statesToggleButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 160);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OutputComponent::~OutputComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (namelabel);
    deleteAndZero (addresslabel);
    deleteAndZero (portlabel);
    deleteAndZero (hostlabel);
    deleteAndZero (nameEditor);
    deleteAndZero (addressEditor);
    deleteAndZero (portEditor);
    deleteAndZero (textEditor);
    deleteAndZero (statesToggleButton);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OutputComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OutputComponent::resized()
{
    namelabel->setBounds (8, 8, 48, 24);
    addresslabel->setBounds (8, 40, 96, 24);
    portlabel->setBounds (8, 72, 72, 24);
    hostlabel->setBounds (8, 104, 150, 24);
    nameEditor->setBounds (112, 8, 272, 24);
    addressEditor->setBounds (112, 40, 272, 24);
    portEditor->setBounds (304, 72, 80, 24);
    textEditor->setBounds (112, 104, 272, 24);
    statesToggleButton->setBounds (243, 136, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OutputComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == statesToggleButton)
    {
        //[UserButtonCode_statesToggleButton] -- add your button handler code here..
        //[/UserButtonCode_statesToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OutputComponent" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public ChangeBroadcaster"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="400"
                 initialHeight="160">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="8b91ab820fec2077" memberName="namelabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="53cb9bf847154e73" memberName="addresslabel"
         virtualName="" explicitFocusOrder="0" pos="8 40 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="OSC Address&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b713421174985810" memberName="portlabel"
         virtualName="" explicitFocusOrder="0" pos="8 72 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="OSC Port&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8afa19e704f9b92f" memberName="hostlabel"
         virtualName="" explicitFocusOrder="0" pos="8 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Host&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="746ecf8e625aeb60" memberName="nameEditor"
              virtualName="" explicitFocusOrder="0" pos="112 8 272 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="bd3860dcf420b130" memberName="addressEditor"
              virtualName="" explicitFocusOrder="1" pos="112 40 272 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="a8c237881d13ade9" memberName="portEditor"
              virtualName="" explicitFocusOrder="2" pos="304 72 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="dba648f8c79b927f" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="112 104 272 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="new toggle button" id="931f67321e950679" memberName="statesToggleButton"
                virtualName="" explicitFocusOrder="0" pos="243 136 150 24" buttonText="Send state changes"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
