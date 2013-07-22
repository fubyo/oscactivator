/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  24 Apr 2013 3:51:54pm

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

#include "RuleEditorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "RulesPanelComponent.h"
//[/MiscUserDefs]

//==============================================================================
RuleEditorComponent::RuleEditorComponent (int RuleIndex)
    : label (0),
      conditionListBox (0),
      label2 (0),
      statementListBox (0),
      addConditionButton (0),
      addStatementButton (0),
      acceptButton (0),
      cancelButton (0)
{
    addAndMakeVisible (label = new Label (L"new label",
                                          L"IF"));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (conditionListBox = new ListBox());
    conditionListBox->setName (L"new component");

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"THEN"));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (statementListBox = new ListBox());
    statementListBox->setName (L"new component");

    addAndMakeVisible (addConditionButton = new TextButton (L"new button"));
    addConditionButton->setButtonText (L"Add condition");
    addConditionButton->addListener (this);

    addAndMakeVisible (addStatementButton = new TextButton (L"new button"));
    addStatementButton->setButtonText (L"Add statement");
    addStatementButton->addListener (this);

    addAndMakeVisible (acceptButton = new TextButton (L"new button"));
    acceptButton->setButtonText (L"Accept");
    acceptButton->addListener (this);
    acceptButton->setColour (TextButton::buttonColourId, Colour (0xff29d02b));
    acceptButton->setColour (TextButton::buttonOnColourId, Colour (0xff7dff44));

    addAndMakeVisible (cancelButton = new TextButton (L"new button"));
    cancelButton->setButtonText (L"Cancel");
    cancelButton->addListener (this);
    cancelButton->setColour (TextButton::buttonColourId, Colour (0xffda7121));
    cancelButton->setColour (TextButton::buttonOnColourId, Colour (0xffee3815));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 450);


    //[Constructor] You can add your own custom stuff here..
	okClicked = false;
	ruleIndex = RuleIndex;
		
	RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
	if (rpc)
	{
		ruleCopy = *(rpc->ruleGenerator.rules[ruleIndex]);
		Pool::Instance()->reg("ruleForEditing", &ruleCopy);
	}

	Pool::Instance()->reg("RuleEditorComponent", this);

	conditionListBox->setModel(new ConditionListBoxModel());
	conditionListBox->setColour(conditionListBox->backgroundColourId, Colours::lightgrey);
	conditionListBox->setRowHeight(25);

	statementListBox->setModel(new StatementListBoxModel());
	statementListBox->setColour(statementListBox->backgroundColourId, Colours::lightgrey);
	statementListBox->setRowHeight(25);
    //[/Constructor]
}

RuleEditorComponent::~RuleEditorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	delete conditionListBox->getModel();
	delete statementListBox->getModel();
    //[/Destructor_pre]

    deleteAndZero (label);
    deleteAndZero (conditionListBox);
    deleteAndZero (label2);
    deleteAndZero (statementListBox);
    deleteAndZero (addConditionButton);
    deleteAndZero (addStatementButton);
    deleteAndZero (acceptButton);
    deleteAndZero (cancelButton);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RuleEditorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RuleEditorComponent::resized()
{
    label->setBounds (9, 9, 150, 24);
    conditionListBox->setBounds (16, 36, 576, 160);
    label2->setBounds (8, 221, 150, 24);
    statementListBox->setBounds (16, 248, 576, 160);
    addConditionButton->setBounds (482, 6, 110, 24);
    addStatementButton->setBounds (482, 219, 110, 24);
    acceptButton->setBounds (416, 416, 86, 24);
    cancelButton->setBounds (506, 416, 86, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void RuleEditorComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == addConditionButton)
    {
        //[UserButtonCode_addConditionButton] -- add your button handler code here..
		
		//find first not used input.
		bool firstUnusedInputFound = false;
		int iter = 0;
		int firstUnusedInput = -1;
		while (!firstUnusedInputFound && iter<ruleCopy.inputTermIndeces.size())
		{
			if (ruleCopy.inputTermIndeces[iter]==-1)
			{
				firstUnusedInput = iter;
				firstUnusedInputFound = true;
			}

			iter++;
		}

		if (firstUnusedInputFound)
		{
			ruleCopy.inputTermIndeces.set(firstUnusedInput, 0);
			conditionListBox->updateContent();
		}
        //[/UserButtonCode_addConditionButton]
    }
    else if (buttonThatWasClicked == addStatementButton)
    {
        //[UserButtonCode_addStatementButton] -- add your button handler code here..
		bool firstUnusedOutputFound = false;
		int iter = 0;
		int firstUnusedOutput = -1;
		while (!firstUnusedOutputFound && iter<ruleCopy.outputTermIndeces.size())
		{
			if (ruleCopy.outputTermIndeces[iter]==-1 && !ruleCopy.outputFromInput.contains(iter))
			{
				firstUnusedOutput = iter;
				firstUnusedOutputFound = true;
			}

			iter++;
		}

		if (firstUnusedOutputFound)
		{
			ruleCopy.outputTermIndeces.set(firstUnusedOutput, 0);
			statementListBox->updateContent();
		}
        //[/UserButtonCode_addStatementButton]
    }
    else if (buttonThatWasClicked == acceptButton)
    {
        //[UserButtonCode_acceptButton] -- add your button handler code here..
		if (isEditedRuleValid())
		{
			okClicked = true;
			getParentComponent()->exitModalState(1);
		}
		else
		{
			ScopedPointer<Label> label = new Label(String::empty, "Rule is incomplete");
			label->setBounds(0, 0, 200, 80);

			DialogWindow::showModalDialog("Rule not accepted", label, NULL, juce::Colours::lightgrey, true);
		}
        //[/UserButtonCode_acceptButton]
    }
    else if (buttonThatWasClicked == cancelButton)
    {
        //[UserButtonCode_cancelButton] -- add your button handler code here..
		getParentComponent()->exitModalState(0);
        //[/UserButtonCode_cancelButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int RuleEditorComponent::getConditionIndex(Component* conditionComponent)
{
	for (int i=0; i<conditionListBox->getModel()->getNumRows(); i++)
	{
		Component* rowComponent = conditionListBox->getComponentForRowNumber(i);

		if (rowComponent == conditionComponent)
			return i;
	}

	return -1;
}

int RuleEditorComponent::getStatementIndex(Component* statementComponent)
{
	for (int i=0; i<statementListBox->getModel()->getNumRows(); i++)
	{
		Component* rowComponent = statementListBox->getComponentForRowNumber(i);

		if (rowComponent == statementComponent)
			return i;
	}

	return -1;
}

void RuleEditorComponent::updateConditionList()
{
	conditionListBox->updateContent();
}

void RuleEditorComponent::updateStatementList()
{
	statementListBox->updateContent();
}

bool RuleEditorComponent::isEditedRuleValid()
{
	bool conditionValid = false;
	bool statementsValid = false;

	for (int i=0; i<ruleCopy.inputTermIndeces.size(); i++)
	{
		if (ruleCopy.inputTermIndeces[i]!=-1)
			conditionValid = true;
	}

	for (int i=0; i<ruleCopy.outputTermIndeces.size(); i++)
	{
		if (ruleCopy.outputTermIndeces[i]!=-1 || ruleCopy.outputFromInput.contains(i))
			statementsValid = true;
	}

	return conditionValid && statementsValid;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RuleEditorComponent" componentName=""
                 parentClasses="public Component" constructorParams="int RuleIndex"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="600"
                 initialHeight="450">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="929554693ba7ef9f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="9 9 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IF" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="new component" id="97165fe6cc71e649" memberName="conditionListBox"
                    virtualName="" explicitFocusOrder="0" pos="16 36 576 160" class="ListBox"
                    params=""/>
  <LABEL name="new label" id="42d0730bf76972e8" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 221 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="THEN" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="new component" id="6d6072def6f7245" memberName="statementListBox"
                    virtualName="" explicitFocusOrder="0" pos="16 248 576 160" class="ListBox"
                    params=""/>
  <TEXTBUTTON name="new button" id="627fe4743f5d3b01" memberName="addConditionButton"
              virtualName="" explicitFocusOrder="0" pos="482 6 110 24" buttonText="Add condition"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="eaef0225c26a9e96" memberName="addStatementButton"
              virtualName="" explicitFocusOrder="0" pos="482 219 110 24" buttonText="Add statement"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="27bfa7ec84e11337" memberName="acceptButton"
              virtualName="" explicitFocusOrder="0" pos="416 416 86 24" bgColOff="ff29d02b"
              bgColOn="ff7dff44" buttonText="Accept" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="a897a7fe29fb7603" memberName="cancelButton"
              virtualName="" explicitFocusOrder="0" pos="506 416 86 24" bgColOff="ffda7121"
              bgColOn="ffee3815" buttonText="Cancel" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
