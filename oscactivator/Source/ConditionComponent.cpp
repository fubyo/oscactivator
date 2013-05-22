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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ConditionComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "RulesPanelComponent.h"
#include "InputsPanelComponent.h"
#include "RuleEditorComponent.h"
//[/MiscUserDefs]

//==============================================================================
ConditionComponent::ConditionComponent (int InputIndex )
    : label3 (0),
      label2 (0),
      label (0),
      inputLabel (0),
      termLabel (0),
      secondsLabel (0),
      deleteButton (0)
{
    addAndMakeVisible (label3 = new Label (L"new label",
                                           L"seconds"));
    label3->setFont (Font (15.0000f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"for"));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label = new Label (L"new label",
                                          L"is"));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (inputLabel = new Label (L"new label",
                                               L"- - -"));
    inputLabel->setFont (Font (15.0000f, Font::plain));
    inputLabel->setJustificationType (Justification::centredLeft);
    inputLabel->setEditable (false, false, false);
    inputLabel->setColour (Label::backgroundColourId, Colours::beige);
    inputLabel->setColour (Label::outlineColourId, Colour (0x0));
    inputLabel->setColour (TextEditor::textColourId, Colours::black);
    inputLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (termLabel = new Label (L"new label",
                                              L"- - -"));
    termLabel->setFont (Font (15.0000f, Font::plain));
    termLabel->setJustificationType (Justification::centredLeft);
    termLabel->setEditable (false, false, false);
    termLabel->setColour (Label::backgroundColourId, Colours::beige);
    termLabel->setColour (Label::outlineColourId, Colour (0x0));
    termLabel->setColour (TextEditor::textColourId, Colours::black);
    termLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (secondsLabel = new Label (L"new label",
                                                 L"0"));
    secondsLabel->setFont (Font (15.0000f, Font::plain));
    secondsLabel->setJustificationType (Justification::centredLeft);
    secondsLabel->setEditable (false, true, false);
    secondsLabel->setColour (Label::backgroundColourId, Colours::beige);
    secondsLabel->setColour (Label::outlineColourId, Colour (0x0));
    secondsLabel->setColour (TextEditor::textColourId, Colours::black);
    secondsLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
    secondsLabel->addListener (this);

    addAndMakeVisible (deleteButton = new TextButton (L"new button"));
    deleteButton->setButtonText (L"X");
    deleteButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    deleteButton->addListener (this);
    deleteButton->setColour (TextButton::buttonColourId, Colour (0xffd27a0e));
    deleteButton->setColour (TextButton::buttonOnColourId, Colour (0xffbfa218));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (576, 25);


    //[Constructor] You can add your own custom stuff here..
	inputIndex = InputIndex;
	updateLabels();

	inputLabel->addMouseListener(this, true);
	termLabel->addMouseListener(this, true);
    //[/Constructor]
}

ConditionComponent::~ConditionComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (label3);
    deleteAndZero (label2);
    deleteAndZero (label);
    deleteAndZero (inputLabel);
    deleteAndZero (termLabel);
    deleteAndZero (secondsLabel);
    deleteAndZero (deleteButton);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConditionComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConditionComponent::resized()
{
    label3->setBounds (492, 0, 56, 24);
    label2->setBounds (399, 0, 32, 24);
    label->setBounds (190, 0, 24, 24);
    inputLabel->setBounds (4, 0, 184, 24);
    termLabel->setBounds (214, 0, 182, 24);
    secondsLabel->setBounds (431, 0, 64, 24);
    deleteButton->setBounds (549, 5, 24, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConditionComponent::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == secondsLabel)
    {
        //[UserLabelCode_secondsLabel] -- add your label text handling code here..
		Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");
		if (ruleCopy)
		{
			RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
			if (rec)
			{
				int conditionIndex = rec->getConditionIndex((Component*)this);
				int inputIndex = getInputIndex(conditionIndex);
				double timeParameter = secondsLabel->getText().getDoubleValue();

				if (timeParameter>0)
				{
					ruleCopy->inputTimers.remove(inputIndex);
					ruleCopy->inputTimers.set(inputIndex, new InputTimer(timeParameter, inputIndex, ruleCopy->inputTermIndeces[inputIndex]));
				}
				else
				{
					InputTimer* it = ruleCopy->inputTimers[inputIndex];
					delete it;
					ruleCopy->inputTimers.remove(inputIndex);
				}
			}
		}
        //[/UserLabelCode_secondsLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void ConditionComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == deleteButton)
    {
        //[UserButtonCode_deleteButton] -- add your button handler code here..
		RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
		if (rec)
		{
			int conditionIndex = rec->getConditionIndex((Component*)this);

			int inputIndex = getInputIndex(conditionIndex);

			Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");
			if (ruleCopy)
				ruleCopy->inputTermIndeces.set(inputIndex, -1);

			rec->updateConditionList();
		}
        //[/UserButtonCode_deleteButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ConditionComponent::updateLabels()
{
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ipc && inputIndex!=-1 && ruleCopy)
	{
		String inputName = ipc->inputs[inputIndex]->name;
		inputLabel->setText(inputName, true);

		int termIndex = ruleCopy->inputTermIndeces[inputIndex];
		String termName = String("- - - ");
		if (termIndex!=-1)
		{
			if (ipc->inputs[inputIndex]->termManager->terms.size())
				termName = String(ipc->inputs[inputIndex]->termManager->terms[termIndex]->name());
		}

		termLabel->setText(termName, true);
		
		if (ruleCopy->inputTimers.contains(inputIndex))
		{
			secondsLabel->setText(String(ruleCopy->inputTimers[inputIndex]->inputTimeParameter), true);
		}
	}
}

int ConditionComponent::getInputIndex(int ConditionIndex)
{
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ruleCopy)
	{
		int counter = -1;
		for (int i=0; i<ruleCopy->inputTermIndeces.size(); i++)
		{
			if (ruleCopy->inputTermIndeces[i]!=-1)
				counter++;

			if (counter == ConditionIndex)
				return i;
		}
	}

	return -1;
}

void ConditionComponent::mouseUp(const MouseEvent& event)
{
	if (event.eventComponent == inputLabel)
	{
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");

		int conditionIndex = getConditionIndex();
		int previousInputIndex = getInputIndex(conditionIndex);

		Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

		if (ruleCopy)
		{
			PopupMenu m;
			for (int i=0; i<ipc->inputs.size(); i++)
			{
				if (i!=previousInputIndex && ruleCopy->inputTermIndeces[i]==-1)
					m.addItem(i+1, ipc->inputs[i]->name);
			}

			const int result = m.show();
			if (result)
			{
				int newInputIndex = result-1;

				ruleCopy->inputTermIndeces.set(previousInputIndex, -1);
				ruleCopy->inputTermIndeces.set(newInputIndex, 0);

				updateConditionParameters(newInputIndex);

				RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
				if (rec)
				{
					rec->updateConditionList();
				}
			}
		}
	}

	if (event.eventComponent == termLabel)
	{
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");

		int conditionIndex = getConditionIndex();
		int inputIndex = getInputIndex(conditionIndex);

		Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

		if (ruleCopy)
		{
			PopupMenu m;
			for (int i=0; i<ipc->inputs[inputIndex]->termManager->terms.size(); i++)
			{
				m.addItem(i+1, String(ipc->inputs[inputIndex]->termManager->terms[i]->name()));
			}

			const int result = m.show();

			if (result)
			{
				int newTermIndex = result-1;

				ruleCopy->inputTermIndeces.set(inputIndex, newTermIndex);

				updateConditionParameters(inputIndex);

				RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
				if (rec)
				{
					rec->updateConditionList();
				}
			}
		}
	}
}

int ConditionComponent::getConditionIndex()
{
	int result = -1;

	RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
	if (rec)
	{
		result = rec->getConditionIndex((Component*)this);
	}

	return result;
}

void ConditionComponent::updateConditionParameters(int InputIndex)
{
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	int termIndex = ruleCopy->inputTermIndeces[InputIndex];

	if (termIndex!=-1)
	{
		ruleCopy->inputValues.set(InputIndex, ipc->inputs[InputIndex]->termManager->getMidPointOfTrapezoidTable(termIndex));
		ruleCopy->inputMembership.set(InputIndex, 1);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConditionComponent" componentName=""
                 parentClasses="public Component" constructorParams="int InputIndex "
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="576"
                 initialHeight="25">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="a10744e25a536a55" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="492 0 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="seconds" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="aa5fd8b0147355c" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="399 0 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="for" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7d26e18983d8e3e5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="190 0 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="is" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="17ae89b946a8eb99" memberName="inputLabel"
         virtualName="" explicitFocusOrder="0" pos="4 0 184 24" bkgCol="fff5f5dc"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="- - -"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f4522224c225ee79" memberName="termLabel"
         virtualName="" explicitFocusOrder="0" pos="214 0 182 24" bkgCol="fff5f5dc"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="- - -"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6ba9218289530191" memberName="secondsLabel"
         virtualName="" explicitFocusOrder="0" pos="431 0 64 24" bkgCol="fff5f5dc"
         outlineCol="0" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="3bc70fda28d75d0e" memberName="deleteButton"
              virtualName="" explicitFocusOrder="0" pos="549 5 24 16" bgColOff="ffd27a0e"
              bgColOn="ffbfa218" buttonText="X" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
