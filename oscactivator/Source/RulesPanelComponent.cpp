/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Mar 2013 5:33:20pm

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

#include "RulesPanelComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
RulesPanelComponent::RulesPanelComponent ()
    : groupComponent (0),
      outputsListBox (0),
      inputsListBox (0),
      label (0),
      label2 (0),
      addExampleButton (0),
      updateRulesButton (0),
      examplesNumberLabel (0),
      clearExamplesButton (0),
      deleteRulesButton (0),
      applyToggleButton (0),
      rulesListBox (0)
{
    addAndMakeVisible (groupComponent = new GroupComponent (L"new group",
                                                            L"Example demonstration"));

    addAndMakeVisible (outputsListBox = new ListBox());
    outputsListBox->setName (L"new component");

    addAndMakeVisible (inputsListBox = new ListBox());
    inputsListBox->setName (L"new component");

    addAndMakeVisible (label = new Label (L"new label",
                                          L"Relevant inputs"));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"Relevant outputs"));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (addExampleButton = new TextButton (String::empty));
    addExampleButton->setButtonText (L"Add example");
    addExampleButton->addListener (this);

    addAndMakeVisible (updateRulesButton = new TextButton (L"new button"));
    updateRulesButton->setButtonText (L"Update rules");
    updateRulesButton->addListener (this);

    addAndMakeVisible (examplesNumberLabel = new Label (L"new label",
                                                        L"# examples in the queue"));
    examplesNumberLabel->setFont (Font (15.0000f, Font::plain));
    examplesNumberLabel->setJustificationType (Justification::centredLeft);
    examplesNumberLabel->setEditable (false, false, false);
    examplesNumberLabel->setColour (TextEditor::textColourId, Colours::black);
    examplesNumberLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (clearExamplesButton = new TextButton (String::empty));
    clearExamplesButton->setButtonText (L"Clear examples");
    clearExamplesButton->addListener (this);

    addAndMakeVisible (deleteRulesButton = new TextButton (L"new button"));
    deleteRulesButton->setButtonText (L"Delete all rules");
    deleteRulesButton->addListener (this);

    addAndMakeVisible (applyToggleButton = new ToggleButton (L"new toggle button"));
    applyToggleButton->setButtonText (L"Apply rules to outputs");
    applyToggleButton->addListener (this);

    addAndMakeVisible (rulesListBox = new ListBox());
    rulesListBox->setName (L"new component");


    //[UserPreSize]
	inputsListBox->setModel(new MultipleSelectionListBoxModel(false));
	outputsListBox->setModel(new MultipleSelectionListBoxModel(true));

	outputsListBox->setColour(outputsListBox->backgroundColourId, Colours::lightgrey);
	inputsListBox->setColour(outputsListBox->backgroundColourId, Colours::lightgrey);

	outputsListBox->setMultipleSelectionEnabled(true);
	inputsListBox->setMultipleSelectionEnabled(true);

	Pool::Instance()->reg("OutputsList", outputsListBox);
	Pool::Instance()->reg("InputsList", inputsListBox);
	Pool::Instance()->reg("RulesPanelComponent", this);

	interactionOn = false;


	rulesListBox->setModel(new RulesListBoxModel());
	rulesListBox->setColour(rulesListBox->backgroundColourId, Colours::lightgrey);
	rulesListBox->setRowHeight(80);
    //[/UserPreSize]

    setSize (609, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

RulesPanelComponent::~RulesPanelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponent);
    deleteAndZero (outputsListBox);
    deleteAndZero (inputsListBox);
    deleteAndZero (label);
    deleteAndZero (label2);
    deleteAndZero (addExampleButton);
    deleteAndZero (updateRulesButton);
    deleteAndZero (examplesNumberLabel);
    deleteAndZero (clearExamplesButton);
    deleteAndZero (deleteRulesButton);
    deleteAndZero (applyToggleButton);
    deleteAndZero (rulesListBox);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RulesPanelComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RulesPanelComponent::resized()
{
    groupComponent->setBounds (8, 8, 592, 224);
    outputsListBox->setBounds (184, 56, 152, 160);
    inputsListBox->setBounds (24, 56, 152, 160);
    label->setBounds (19, 32, 150, 24);
    label2->setBounds (179, 32, 150, 24);
    addExampleButton->setBounds (344, 56, 112, 24);
    updateRulesButton->setBounds (344, 192, 246, 24);
    examplesNumberLabel->setBounds (344, 80, 150, 24);
    clearExamplesButton->setBounds (464, 56, 128, 24);
    deleteRulesButton->setBounds (440, 240, 150, 24);
    applyToggleButton->setBounds (13, 240, 152, 24);
    rulesListBox->setBounds (16, 272, 576, 320);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void RulesPanelComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == addExampleButton)
    {
        //[UserButtonCode_addExampleButton] -- add your button handler code here..
		addExample();
        //[/UserButtonCode_addExampleButton]
    }
    else if (buttonThatWasClicked == updateRulesButton)
    {
        //[UserButtonCode_updateRulesButton] -- add your button handler code here..
		updateRules();
        //[/UserButtonCode_updateRulesButton]
    }
    else if (buttonThatWasClicked == clearExamplesButton)
    {
        //[UserButtonCode_clearExamplesButton] -- add your button handler code here..
		clearExamples();
        //[/UserButtonCode_clearExamplesButton]
    }
    else if (buttonThatWasClicked == deleteRulesButton)
    {
        //[UserButtonCode_deleteRulesButton] -- add your button handler code here..
		ruleGenerator.deleteAllRules();

		rulesListBox->updateContent();
        //[/UserButtonCode_deleteRulesButton]
    }
    else if (buttonThatWasClicked == applyToggleButton)
    {
        //[UserButtonCode_applyToggleButton] -- add your button handler code here..
		if (applyToggleButton->getToggleState())
			interactionOn = true;
		else
			interactionOn = false;
        //[/UserButtonCode_applyToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool RulesPanelComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void RulesPanelComponent::changeListenerCallback (ChangeBroadcaster* source)
{

}

void RulesPanelComponent::addExample()
{
	InputsPanelComponent* ipc = (InputsPanelComponent*)Pool::Instance()->getObject("InputsPanelComponent");
	OutputsPanelComponent* opc = (OutputsPanelComponent*)Pool::Instance()->getObject("OutputsPanelComponent");

	if (ipc && opc)
	{
		Example example;

		Array<ValueRelevance> inputs;
		for (int i=0; i<inputsListBox->getModel()->getNumRows(); i++)
		{
			ValueRelevance vr;
			vr.value = *ipc->inputs[i]->pValue;
			vr.relevance=inputsListBox->isRowSelected(i);

			inputs.add(vr);
		}

		Array<ValueRelevance> outputs;
		for (int i=0; i<outputsListBox->getModel()->getNumRows(); i++)
		{
			ValueRelevance vr;
			vr.value = *opc->outputs[i]->pValue;
			vr.relevance=outputsListBox->isRowSelected(i);

			outputs.add(vr);
		}

		example.setExample(inputs, outputs);
		ruleGenerator.addExample(example);

		examplesNumberLabel->setText(String(ruleGenerator.getNumberOfQueuedExamples()) + String("  examples in the queue"), true);
	}
}

void RulesPanelComponent::updateRules()
{
	ruleGenerator.updateRulebase();
	examplesNumberLabel->setText(String(ruleGenerator.getNumberOfQueuedExamples()) + String("  examples in the queue"), true);

	rulesListBox->updateContent();
}

void RulesPanelComponent::clearExamples()
{
	ruleGenerator.clearExamples();
	examplesNumberLabel->setText(String(ruleGenerator.getNumberOfQueuedExamples()) + String("  examples in the queue"), true);
}

void RulesPanelComponent::inputRemoved(int index)
{
	ruleGenerator.removeInput(index);
	updateRules();
}

void RulesPanelComponent::outputRemoved(int index)
{
	ruleGenerator.removeOutput(index);
	updateRules();
}

int RulesPanelComponent::getRuleIndex(Component* ruleComponent)
{
	for (int i=0; i<=ruleGenerator.rules.size(); i++)
	{
		Component* rowComponent = rulesListBox->getComponentForRowNumber(i);

		if (rowComponent == ruleComponent)
			return i;
	}

	return -1;
}

void RulesPanelComponent::updateRuleList()
{
	rulesListBox->updateContent();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RulesPanelComponent" componentName=""
                 parentClasses="public Component, public ChangeListener, public TextEditor::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="609"
                 initialHeight="600">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="5260aed5ae0568f8" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 8 592 224" title="Example demonstration"/>
  <GENERICCOMPONENT name="new component" id="9e399de4bf88af70" memberName="outputsListBox"
                    virtualName="" explicitFocusOrder="0" pos="184 56 152 160" class="ListBox"
                    params=""/>
  <GENERICCOMPONENT name="new component" id="709cfb2d467cfc8f" memberName="inputsListBox"
                    virtualName="" explicitFocusOrder="0" pos="24 56 152 160" class="ListBox"
                    params=""/>
  <LABEL name="new label" id="d2899fa8af7b8cdd" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="19 32 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Relevant inputs" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="960b78f59105bbee" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="179 32 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Relevant outputs" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="ebb2f16bef857239" memberName="addExampleButton" virtualName=""
              explicitFocusOrder="0" pos="344 56 112 24" buttonText="Add example"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="2d2a32888233453b" memberName="updateRulesButton"
              virtualName="" explicitFocusOrder="0" pos="344 192 246 24" buttonText="Update rules"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="bb5bc327d75e93b2" memberName="examplesNumberLabel"
         virtualName="" explicitFocusOrder="0" pos="344 80 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="# examples in the queue" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="4d4810bd2145df80" memberName="clearExamplesButton"
              virtualName="" explicitFocusOrder="0" pos="464 56 128 24" buttonText="Clear examples"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="3d50325343f48754" memberName="deleteRulesButton"
              virtualName="" explicitFocusOrder="0" pos="440 240 150 24" buttonText="Delete all rules"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TOGGLEBUTTON name="new toggle button" id="bb824fb6bd365ee7" memberName="applyToggleButton"
                virtualName="" explicitFocusOrder="0" pos="13 240 152 24" buttonText="Apply rules to outputs"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <GENERICCOMPONENT name="new component" id="a850b194e41969d7" memberName="rulesListBox"
                    virtualName="" explicitFocusOrder="0" pos="16 272 576 320" class="ListBox"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
