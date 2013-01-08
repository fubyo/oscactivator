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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "InputComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InputComponent::InputComponent ()
    : namelabel (0),
      addresslabel (0),
      portlabel (0),
      parameterindexlabel (0),
      nameEditor (0),
      addressEditor (0),
      portEditor (0),
      parameterIndexComboBox (0)
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

    addAndMakeVisible (parameterindexlabel = new Label (L"new label",
                                                        L"OSC Parameter Index\n"));
    parameterindexlabel->setFont (Font (15.0000f, Font::plain));
    parameterindexlabel->setJustificationType (Justification::centredLeft);
    parameterindexlabel->setEditable (false, false, false);
    parameterindexlabel->setColour (TextEditor::textColourId, Colours::black);
    parameterindexlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

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

    addAndMakeVisible (parameterIndexComboBox = new ComboBox (L"new combo box"));
    parameterIndexComboBox->setExplicitFocusOrder (3);
    parameterIndexComboBox->setEditableText (false);
    parameterIndexComboBox->setJustificationType (Justification::centredLeft);
    parameterIndexComboBox->setTextWhenNothingSelected (String::empty);
    parameterIndexComboBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    parameterIndexComboBox->addItem (L"0", 1);
    parameterIndexComboBox->addItem (L"1", 2);
    parameterIndexComboBox->addItem (L"2", 3);
    parameterIndexComboBox->addItem (L"3", 4);
    parameterIndexComboBox->addItem (L"4", 5);
    parameterIndexComboBox->addItem (L"5", 6);
    parameterIndexComboBox->addItem (L"6", 7);
    parameterIndexComboBox->addItem (L"7", 8);
    parameterIndexComboBox->addItem (L"8", 9);
    parameterIndexComboBox->addItem (L"9", 10);
    parameterIndexComboBox->addItem (L"10", 11);
    parameterIndexComboBox->addItem (L"11", 12);
    parameterIndexComboBox->addItem (L"12", 13);
    parameterIndexComboBox->addItem (L"13", 14);
    parameterIndexComboBox->addItem (L"14", 15);
    parameterIndexComboBox->addItem (L"15", 16);
    parameterIndexComboBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 140);

	nameEditor->addListener(this);
	addressEditor->addListener(this);
	portEditor->addListener(this);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InputComponent::~InputComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (namelabel);
    deleteAndZero (addresslabel);
    deleteAndZero (portlabel);
    deleteAndZero (parameterindexlabel);
    deleteAndZero (nameEditor);
    deleteAndZero (addressEditor);
    deleteAndZero (portEditor);
    deleteAndZero (parameterIndexComboBox);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InputComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InputComponent::resized()
{
    namelabel->setBounds (8, 8, 48, 24);
    addresslabel->setBounds (8, 40, 96, 24);
    portlabel->setBounds (8, 72, 72, 24);
    parameterindexlabel->setBounds (8, 104, 150, 24);
    nameEditor->setBounds (112, 8, 272, 24);
    addressEditor->setBounds (112, 40, 272, 24);
    portEditor->setBounds (304, 72, 80, 24);
    parameterIndexComboBox->setBounds (304, 104, 80, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void InputComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == parameterIndexComboBox)
    {
        //[UserComboBoxCode_parameterIndexComboBox] -- add your combo box handling code here..
		sendChangeMessage();
        //[/UserComboBoxCode_parameterIndexComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void InputComponent::setInput(Input input)
{
	nameEditor->setText(input.name);
	addressEditor->setText(input.oscaddress);
	portEditor->setText(String(input.port));
	parameterIndexComboBox->setSelectedItemIndex(input.parameterindex);
}

Input InputComponent::getInput()
{
	Input input;
	input.name = nameEditor->getText();
	input.oscaddress = addressEditor->getText();
	input.parameterindex = parameterIndexComboBox->getSelectedItemIndex();
	input.port = portEditor->getText().getIntValue();

	return input;
}

void InputComponent::textEditorTextChanged(TextEditor& editor)
{
	sendChangeMessage();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InputComponent" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public ChangeBroadcaster"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="400"
                 initialHeight="140">
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
  <LABEL name="new label" id="8afa19e704f9b92f" memberName="parameterindexlabel"
         virtualName="" explicitFocusOrder="0" pos="8 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="OSC Parameter Index&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
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
  <COMBOBOX name="new combo box" id="99c6d6af021510a" memberName="parameterIndexComboBox"
            virtualName="" explicitFocusOrder="3" pos="304 104 80 24" editable="0"
            layout="33" items="0&#10;1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
