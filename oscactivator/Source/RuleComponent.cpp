/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 May 2013 4:09:06pm

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

#include "RuleComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "RulesPanelComponent.h"
//[/MiscUserDefs]

//==============================================================================
RuleComponent::RuleComponent ()
    : deleteButton (0),
      editButton (0),
      lockButton (0),
      ruleNameLabel (0),
      ruleTextEditor (0),
      wlabel (0),
      weightLabel (0)
{
    addAndMakeVisible (deleteButton = new TextButton (L"new button"));
    deleteButton->setButtonText (L"Delete");
    deleteButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    deleteButton->addListener (this);
    deleteButton->setColour (TextButton::buttonColourId, Colour (0xffffcbbb));
    deleteButton->setColour (TextButton::buttonOnColourId, Colour (0xffff8644));

    addAndMakeVisible (editButton = new TextButton (L"new button"));
    editButton->setButtonText (L"Edit");
    editButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    editButton->addListener (this);

    addAndMakeVisible (lockButton = new ToggleButton (L"new toggle button"));
    lockButton->setButtonText (L"Lock");
    lockButton->addListener (this);

    addAndMakeVisible (ruleNameLabel = new Label (L"new label",
                                                  L"Rule 0"));
    ruleNameLabel->setFont (Font (13.0000f, Font::plain));
    ruleNameLabel->setJustificationType (Justification::centredLeft);
    ruleNameLabel->setEditable (false, false, false);
    ruleNameLabel->setColour (TextEditor::textColourId, Colours::black);
    ruleNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (ruleTextEditor = new TextEditor (L"new text editor"));
    ruleTextEditor->setMultiLine (true);
    ruleTextEditor->setReturnKeyStartsNewLine (false);
    ruleTextEditor->setReadOnly (true);
    ruleTextEditor->setScrollbarsShown (true);
    ruleTextEditor->setCaretVisible (false);
    ruleTextEditor->setPopupMenuEnabled (true);
    ruleTextEditor->setText (String::empty);

    addAndMakeVisible (wlabel = new Label (L"new label",
                                           L"Importance = "));
    wlabel->setFont (Font (13.0000f, Font::plain));
    wlabel->setJustificationType (Justification::centredLeft);
    wlabel->setEditable (false, false, false);
    wlabel->setColour (TextEditor::textColourId, Colours::black);
    wlabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (weightLabel = new Label (L"new label",
                                                L"1.0"));
    weightLabel->setFont (Font (13.0000f, Font::plain));
    weightLabel->setJustificationType (Justification::centredLeft);
    weightLabel->setEditable (false, true, false);
    weightLabel->setColour (TextEditor::textColourId, Colours::black);
    weightLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));
    weightLabel->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (574, 80);


    //[Constructor] You can add your own custom stuff here..
	hasToGetDeleted = false;

	weightLabel->addMouseListener(this, false);
    //[/Constructor]
}

RuleComponent::~RuleComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (deleteButton);
    deleteAndZero (editButton);
    deleteAndZero (lockButton);
    deleteAndZero (ruleNameLabel);
    deleteAndZero (ruleTextEditor);
    deleteAndZero (wlabel);
    deleteAndZero (weightLabel);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RuleComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::white);
    g.fillRect (0, 0, 576, 88);

    g.setColour (Colours::black);
    g.drawRect (0, 0, 576, 88, 1);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RuleComponent::resized()
{
    deleteButton->setBounds (488, 8, 64, 16);
    editButton->setBounds (488, 32, 64, 16);
    lockButton->setBounds (513, 56, 40, 16);
    ruleNameLabel->setBounds (3, 0, 125, 24);
    ruleTextEditor->setBounds (8, 24, 472, 48);
    wlabel->setBounds (268, 0, 88, 24);
    weightLabel->setBounds (347, 0, 128, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void RuleComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == deleteButton)
    {
        //[UserButtonCode_deleteButton] -- add your button handler code here..
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (rpc)
		{
			int rowNumber = rpc->getRuleIndex((Component*)this);

			//delete the inputtimers
			HashMap<int, InputTimer*>::Iterator i(rpc->ruleGenerator.rules[rowNumber]->inputTimers);
			while (i.next())
			{
				delete i.getValue();
			}

			//delete the outputtimers
			HashMap<int, OutputTimer*>::Iterator j(rpc->ruleGenerator.rules[rowNumber]->outputTimers);
			while (j.next())
			{
				delete j.getValue();
			}

			rpc->ruleGenerator.rules.remove(rowNumber);
			hasToGetDeleted = true;
			rpc->updateRuleList();
		}

        //[/UserButtonCode_deleteButton]
    }
    else if (buttonThatWasClicked == editButton)
    {
        //[UserButtonCode_editButton] -- add your button handler code here..
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		int ruleIndex = -1;
		if (rpc)
		{
			ruleIndex = rpc->getRuleIndex((Component*)this);
		}
		String title = String("Editor: Rule ") + String(ruleIndex);

		Pool::Instance()->reg("ruleIndexForEditing", ruleIndex);

		ScopedPointer<RuleEditorComponent> rec = new RuleEditorComponent(ruleIndex);
		DialogWindow::showModalDialog(title, rec, this->getParentComponent(), Colours::lightgrey, false);

		if (rec->okClicked)
		{
			rpc->ruleGenerator.rules.set(ruleIndex, new Rule(rec->ruleCopy));
			rpc->ruleGenerator.recalculateDegrees(ruleIndex);

			rpc->updateRuleList();
		}
		else
		{
			//Delete the input and output timers of the rule copy if no longer relevant
			HashMap<int, InputTimer*>::Iterator i(rec->ruleCopy.inputTimers);
			while (i.next())
			{
				if (!rpc->ruleGenerator.rules[ruleIndex]->inputTimers.containsValue(i.getValue()))
					delete i.getValue();
			}

			HashMap<int, OutputTimer*>::Iterator j(rec->ruleCopy.outputTimers);
			while (j.next())
			{
				if (!rpc->ruleGenerator.rules[ruleIndex]->outputTimers.containsValue(j.getValue()))
					delete j.getValue();
			}
		}


        //[/UserButtonCode_editButton]
    }
    else if (buttonThatWasClicked == lockButton)
    {
        //[UserButtonCode_lockButton] -- add your button handler code here..
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (rpc)
		{
			int rowNumber = rpc->getRuleIndex((Component*)this);

			if (rowNumber!=-1)
				rpc->ruleGenerator.rules[rowNumber]->locked = lockButton->getToggleState();

			if (lockButton->getToggleState())
			{
				deleteButton->setEnabled(false);
				editButton->setEnabled(false);
			}
			else
			{
				deleteButton->setEnabled(true);
				editButton->setEnabled(true);
			}
		}
        //[/UserButtonCode_lockButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void RuleComponent::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == weightLabel)
    {
        //[UserLabelCode_weightLabel] -- add your label text handling code here..
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (rpc)
		{
			int ruleIndex = rpc->getRuleIndex((Component*)this);

			if (ruleIndex!=-1)
				if (rpc->ruleGenerator.rules[ruleIndex]->weightInputConnection==-1)
				{
					double NewWeight = weightLabel->getText().getDoubleValue();
					if (NewWeight>1)
					{
						NewWeight=1;
						weightLabel->setText(String(NewWeight), false);
					}
					else if (NewWeight<0)
					{
						NewWeight=0;
						weightLabel->setText(String(NewWeight), false);
					}

					rpc->ruleGenerator.rules[ruleIndex]->importance = NewWeight;
				}
		}

        //[/UserLabelCode_weightLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void RuleComponent::setRuleText(String ruleText)
{
	ruleTextEditor->setText(ruleText);
}

void RuleComponent::setRuleName(String ruleName)
{
	ruleNameLabel->setText(ruleName, true);
}

void RuleComponent::setLock(bool lock)
{
	lockButton->setToggleState(lock, true);
}

void RuleComponent::mouseUp(const MouseEvent& event)
{
	if (event.eventComponent == weightLabel && event.mods.isRightButtonDown())
	{
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		int ruleIndex = rpc->getRuleIndex((Component*)this);

		if (ipc)
		{
			PopupMenu m;

			m.addItem(1, String(rpc->ruleGenerator.rules[ruleIndex]->importance));

			for (int i=0; i<ipc->inputs.size(); i++)
			{
				m.addItem(i+2, ipc->inputs[i]->name);
			}

			int result = m.show();

			if (result)
			{
				if (result == 1)
				{
					rpc->ruleGenerator.rules[ruleIndex]->weightInputConnection = -1;
					weightLabel->setText(String(rpc->ruleGenerator.rules[ruleIndex]->importance), true);
				}
				else
				{
					int inputIndex=result-2;
	
					rpc->ruleGenerator.rules[ruleIndex]->weightInputConnection = inputIndex;
					weightLabel->setText(ipc->inputs[inputIndex]->name, true);
				}
			}
		}
	}
}

void RuleComponent::updateWeightLabel(int RuleIndex)
{
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");

	if (rpc->ruleGenerator.rules[RuleIndex]->weightInputConnection==-1)
		weightLabel->setText(String(rpc->ruleGenerator.rules[RuleIndex]->importance), true);
	else
		weightLabel->setText(ipc->inputs[rpc->ruleGenerator.rules[RuleIndex]->weightInputConnection]->name, true);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RuleComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="574" initialHeight="80">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 576 88" fill="solid: ffffffff" hasStroke="1" stroke="1.29999995, mitered, butt"
          strokeColour="solid: ff000000"/>
  </BACKGROUND>
  <TEXTBUTTON name="new button" id="1af03cca41ed72e4" memberName="deleteButton"
              virtualName="" explicitFocusOrder="0" pos="488 8 64 16" bgColOff="ffffcbbb"
              bgColOn="ffff8644" buttonText="Delete" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="6ea4b10171856957" memberName="editButton"
              virtualName="" explicitFocusOrder="0" pos="488 32 64 16" buttonText="Edit"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="7cdf6f11649fdd9a" memberName="lockButton"
                virtualName="" explicitFocusOrder="0" pos="513 56 40 16" buttonText="Lock"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="a72fd0a02bfa4e7" memberName="ruleNameLabel"
         virtualName="" explicitFocusOrder="0" pos="3 0 125 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rule 0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="691194d341a1c881" memberName="ruleTextEditor"
              virtualName="" explicitFocusOrder="0" pos="8 24 472 48" initialText=""
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <LABEL name="new label" id="4807fa4dbd6f6c86" memberName="wlabel" virtualName=""
         explicitFocusOrder="0" pos="268 0 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Importance = " editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a11026b817798207" memberName="weightLabel"
         virtualName="" explicitFocusOrder="0" pos="347 0 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="1.0" editableSingleClick="0" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
