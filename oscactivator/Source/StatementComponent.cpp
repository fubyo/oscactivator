/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  3 May 2013 3:48:58pm

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

#include "StatementComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "OutputsPanelComponent.h"
#include "RulesPanelComponent.h"
#include "RuleEditorComponent.h"
//[/MiscUserDefs]

//==============================================================================
StatementComponent::StatementComponent (int OutputIndex )
    : label3 (0),
      label2 (0),
      label (0),
      outputLabel (0),
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
                                           L"in"));
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

    addAndMakeVisible (outputLabel = new Label (L"new label",
                                                L"- - -"));
    outputLabel->setFont (Font (15.0000f, Font::plain));
    outputLabel->setJustificationType (Justification::centredLeft);
    outputLabel->setEditable (false, false, false);
    outputLabel->setColour (Label::backgroundColourId, Colours::beige);
    outputLabel->setColour (Label::outlineColourId, Colour (0x0));
    outputLabel->setColour (TextEditor::textColourId, Colours::black);
    outputLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

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
	outputIndex = OutputIndex;
	updateLabels();

	outputLabel->addMouseListener(this, true);
	termLabel->addMouseListener(this, true);
    //[/Constructor]
}

StatementComponent::~StatementComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (label3);
    deleteAndZero (label2);
    deleteAndZero (label);
    deleteAndZero (outputLabel);
    deleteAndZero (termLabel);
    deleteAndZero (secondsLabel);
    deleteAndZero (deleteButton);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StatementComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StatementComponent::resized()
{
    label3->setBounds (492, 0, 56, 24);
    label2->setBounds (399, 0, 32, 24);
    label->setBounds (190, 0, 24, 24);
    outputLabel->setBounds (4, 0, 184, 24);
    termLabel->setBounds (214, 0, 182, 24);
    secondsLabel->setBounds (431, 0, 64, 24);
    deleteButton->setBounds (549, 5, 24, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StatementComponent::labelTextChanged (Label* labelThatHasChanged)
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
				int statementIndex = rec->getStatementIndex((Component*)this);
				int outputIndex = getOutputIndex(statementIndex);
				double timeParameter = secondsLabel->getText().getDoubleValue();

				if (timeParameter>0)
					ruleCopy->outputTimeParameter.set(outputIndex, timeParameter);
				else
					ruleCopy->outputTimeParameter.remove(outputIndex);
			}
		}
        //[/UserLabelCode_secondsLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void StatementComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == deleteButton)
    {
        //[UserButtonCode_deleteButton] -- add your button handler code here..
		RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
		if (rec)
		{
			int statementIndex = rec->getStatementIndex((Component*)this);

			int outputIndex = getOutputIndex(statementIndex);

			Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");
			if (ruleCopy)
			{
				ruleCopy->outputTermIndeces.set(outputIndex, -1);
				ruleCopy->outputFromInput.remove(outputIndex);
			}

			rec->updateStatementList();
		}
        //[/UserButtonCode_deleteButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void StatementComponent::updateLabels()
{
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (opc && outputIndex!=-1 && ruleCopy)
	{
		String outputName = opc->outputs[outputIndex]->name;
		outputLabel->setText(outputName, true);

		int termIndex = ruleCopy->outputTermIndeces[outputIndex];

		String termName = String("- - - ");
		if (termIndex!=-1)
		{
			if (opc->outputs[outputIndex]->termManager->terms.size())
				termName = String(opc->outputs[outputIndex]->termManager->terms[termIndex]->name().c_str());
		}
		else if (ruleCopy->outputFromInput.contains(outputIndex))
		{
			int connectedInputIndex = ruleCopy->outputFromInput[outputIndex];
			termName = String("same as ")+String(ipc->inputs[connectedInputIndex]->name);
		}

		termLabel->setText(termName, true);

		if (ruleCopy->outputTimeParameter.contains(outputIndex))
		{
			secondsLabel->setText(String(ruleCopy->outputTimeParameter[outputIndex]), true);
		}
	}
}

int StatementComponent::getOutputIndex(int StatementIndex)
{
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	if (ruleCopy)
	{
		int counter = -1;
		for (int i=0; i<ruleCopy->outputTermIndeces.size(); i++)
		{
			if (ruleCopy->outputTermIndeces[i]!=-1 || ruleCopy->outputFromInput.contains(i))
				counter++;

			if (counter == StatementIndex)
				return i;
		}
	}

	return -1;
}

void StatementComponent::mouseUp(const MouseEvent& event)
{
	if (event.eventComponent == outputLabel)
	{
		OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");

		int statementIndex = getStatementIndex();
		int previousOutputIndex = getOutputIndex(statementIndex);

		Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

		if (ruleCopy)
		{
			PopupMenu m;
			for (int i=0; i<opc->outputs.size(); i++)
			{
				if (i!=previousOutputIndex && ruleCopy->outputTermIndeces[i]==-1)
					m.addItem(i+1, opc->outputs[i]->name);
			}

			const int result = m.show();
			if (result)
			{
				int newOutputIndex = result-1;

				ruleCopy->outputTermIndeces.set(previousOutputIndex, -1);
				ruleCopy->outputTermIndeces.set(newOutputIndex, 0);

				updateStatementParameters(newOutputIndex);

				RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
				if (rec)
				{
					rec->updateStatementList();
				}
			}
		}
	}

	if (event.eventComponent == termLabel)
	{
		OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
		InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");

		int conditionIndex = getStatementIndex();
		int outputIndex = getOutputIndex(conditionIndex);

		Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

		if (ruleCopy)
		{
			PopupMenu m;
			int i=0;

			int numberOfTerms=opc->outputs[outputIndex]->termManager->terms.size();

			for (int i=0; i<numberOfTerms; i++)
			{
				m.addItem(i+1, String(opc->outputs[outputIndex]->termManager->terms[i]->name().c_str()));
			}

			PopupMenu sub;
			for (i=numberOfTerms; i<ipc->inputs.size()+numberOfTerms; i++)
			{
				sub.addItem(i+1, ipc->inputs[i-numberOfTerms]->name);
			}

			m.addSubMenu("same as...", sub);

			const int result = m.show();

			if (result>0 && result<=numberOfTerms)
			{
				int newTermIndex = result-1;

				ruleCopy->outputTermIndeces.set(outputIndex, newTermIndex);

				updateStatementParameters(outputIndex);

				RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
				if (rec)
				{
					rec->updateStatementList();
				}
			}
			else if (result>numberOfTerms)
			{
				int inputIndex = result-1-numberOfTerms;

				ruleCopy->outputTermIndeces.set(outputIndex, -1);

				ruleCopy->outputFromInput.set(outputIndex, inputIndex);

				RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
				if (rec)
				{
					rec->updateStatementList();
				}
			}
		}
	}
}

int StatementComponent::getStatementIndex()
{
	int result = -1;

	RuleEditorComponent* rec = (RuleEditorComponent*)Pool::Instance()->getObject("RuleEditorComponent");
	if (rec)
	{
		result = rec->getStatementIndex((Component*)this);
	}

	return result;
}

void StatementComponent::updateStatementParameters(int OutputIndex)
{
	OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");
	Rule* ruleCopy = (Rule*)Pool::Instance()->getObject("ruleForEditing");

	int termIndex = ruleCopy->outputTermIndeces[OutputIndex];

	if (termIndex!=-1)
	{
		ruleCopy->outputValues.set(OutputIndex, opc->outputs[OutputIndex]->termManager->getMidPointOfTrapezoidTable(termIndex));
		ruleCopy->outputMembership.set(OutputIndex, 1);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StatementComponent" componentName=""
                 parentClasses="public Component" constructorParams="int OutputIndex "
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
         edBkgCol="0" labelText="in" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7d26e18983d8e3e5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="190 0 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="is" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="17ae89b946a8eb99" memberName="outputLabel"
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
