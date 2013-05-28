/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  15 Feb 2013 6:19:51pm

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
#include "RulesPanelComponent.h"
//[/MiscUserDefs]

//==============================================================================
OutputsPanelComponent::OutputsPanelComponent ()
    : groupComponent (0),
      outputsListBox (0),
      addButton (0),
      removeButton (0),
      membershipGraph (0),
      label (0),
      termEditor (0),
      label2 (0),
      setButton (0),
      minEditor (0),
      maxEditor (0),
      outputComponent (0),
      valueSlider (0)
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
    addAndMakeVisible (valueSlider = new Slider (L"new slider"));
    valueSlider->setRange (0, 1, 0);
    valueSlider->setSliderStyle (Slider::LinearHorizontal);
    valueSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    valueSlider->addListener (this);


    //[UserPreSize]
	outputsListBox->setMultipleSelectionEnabled(false);
	outputsListBox->setModel(this);
	outputsListBox->setColour(outputsListBox->backgroundColourId, Colours::lightgrey);

	outputComponent->addChangeListener(this);
	outputComponent->setVisible(false);

	Pool::Instance()->reg("OutputsPanelComponent", this);


	minEditor->addListener(this);
	maxEditor->addListener(this);

	membershipGraph->addChangeListener(this);
    //[/UserPreSize]

    setSize (609, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

OutputsPanelComponent::~OutputsPanelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	for (int i=0; i<outputs.size(); i++)
	{
		delete [] outputs[i]->buffer;
		delete [] outputs[i]->pValue;
		delete outputs[i]->socket;
		delete outputs[i]->termManager;
	}
    //[/Destructor_pre]

    deleteAndZero (groupComponent);
    deleteAndZero (outputsListBox);
    deleteAndZero (addButton);
    deleteAndZero (removeButton);
    deleteAndZero (membershipGraph);
    deleteAndZero (label);
    deleteAndZero (termEditor);
    deleteAndZero (label2);
    deleteAndZero (setButton);
    deleteAndZero (minEditor);
    deleteAndZero (maxEditor);
    deleteAndZero (outputComponent);
    deleteAndZero (valueSlider);


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
    membershipGraph->setBounds (8, 259, 592, 200);
    label->setBounds (8, 222, 120, 24);
    termEditor->setBounds (368, 221, 136, 24);
    label2->setBounds (344, 222, 24, 24);
    setButton->setBounds (512, 221, 86, 24);
    minEditor->setBounds (14, 463, 150, 24);
    maxEditor->setBounds (447, 464, 150, 24);
    outputComponent->setBounds (184, 32, 400, 168);
    valueSlider->setBounds (104, 222, 240, 24);
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
		Output* newOutput = new Output();
		newOutput->prepareSocket();

		outputs.add(newOutput);

		outputsListBox->updateContent();

		ListBox* outputsRelevanceListBox = (ListBox*)Pool::Instance()->getObject("OutputsList");
		if (outputsRelevanceListBox)
			outputsRelevanceListBox->updateContent();

		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (rpc)
			rpc->ruleGenerator.updateRulesDueToAddingNewIO();
        //[/UserButtonCode_addButton]
    }
    else if (buttonThatWasClicked == removeButton)
    {
        //[UserButtonCode_removeButton] -- add your button handler code here..
		int selectedrow=outputsListBox->getSelectedRow();

		if (selectedrow!=-1 && selectedrow < (int)outputs.size())
		{
			delete[] outputs[selectedrow]->pValue;
			delete outputs[selectedrow]->termManager;
			delete[] outputs[selectedrow]->buffer;
			delete outputs[selectedrow]->socket;

			membershipGraph->setTermManager(0);

			outputs.remove(selectedrow);

			if (selectedrow<outputs.size())
			{
				outputComponent->setOutputInfo(OutputInfo(outputs[selectedrow]));

				minEditor->setText(String(outputs[selectedrow]->termManager->getMin()));
				maxEditor->setText(String(outputs[selectedrow]->termManager->getMax()));
			}
			else
			{
				outputComponent->setVisible(false);

				minEditor->setText(String());
				maxEditor->setText(String());
			}

			outputsListBox->updateContent();

			ListBox* outputsRelevanceListBox = (ListBox*)Pool::Instance()->getObject("OutputsList");
			if (outputsRelevanceListBox)
				outputsRelevanceListBox->updateContent();

			RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
			if (rpc)
				rpc->outputRemoved(selectedrow);
		}
        //[/UserButtonCode_removeButton]
    }
    else if (buttonThatWasClicked == setButton)
    {
        //[UserButtonCode_setButton] -- add your button handler code here..
		if (outputsListBox->getSelectedRow()!=-1)
		{
			double currentValue=*outputs[outputsListBox->getSelectedRow()]->pValue;

			if (abs(valueSlider->getValue()-*outputs[outputsListBox->getSelectedRow()]->pValue)>0.00001)
				currentValue = valueSlider->getValue();

			outputs[outputsListBox->getSelectedRow()]->termManager->addTerm(termEditor->getText(), currentValue);
			membershipGraph->setTermManager(outputs[outputsListBox->getSelectedRow()]->termManager);

			minEditor->setText(String(outputs[outputsListBox->getSelectedRow()]->termManager->getMin()), false);
			maxEditor->setText(String(outputs[outputsListBox->getSelectedRow()]->termManager->getMax()), false);
		}
        //[/UserButtonCode_setButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void OutputsPanelComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == valueSlider)
    {
        //[UserSliderCode_valueSlider] -- add your slider handling code here..
		int selectedRow = outputsListBox->getSelectedRow();
		if (selectedRow!=-1)
		{
			RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
			if (!rpc->interactionOn)
			{
				double value = valueSlider->getValue();
				*outputs[selectedRow]->pValue = value;

				osc::OutboundPacketStream p(outputs[selectedRow]->buffer, 128);

				if (!outputs[selectedRow]->sendStateChanges)
				{
					osc::OutboundPacketStream p(outputs[selectedRow]->buffer, 128);

					p << osc::BeginMessage( outputs[selectedRow]->oscaddress.toUTF8() )
						<< (float)value
					<< osc::EndMessage;

					outputs[selectedRow]->socket->Send( p.Data(), p.Size() );
				}
				else
				{
					int termIndex = outputs[selectedRow]->termManager->getIndex(*outputs[selectedRow]->pValue);
					double memberShip = outputs[selectedRow]->termManager->terms[termIndex]->membership(*outputs[selectedRow]->pValue);

					if (memberShip==1.0 && termIndex!=outputs[selectedRow]->lastState)
					{
						outputs[selectedRow]->lastState = termIndex;

						osc::OutboundPacketStream p(outputs[selectedRow]->buffer, 128);

						p << osc::BeginMessage( outputs[selectedRow]->oscaddress.toUTF8() )
							<< (float)termIndex
						<< osc::EndMessage;

						outputs[selectedRow]->socket->Send( p.Data(), p.Size() );
					}
				}
			}
		}
        //[/UserSliderCode_valueSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

bool OutputsPanelComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
	membershipGraph->keyPressed(key);
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OutputsPanelComponent::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
		g.fillAll(Colours::lightblue);
	else
		g.fillAll(Colours::lightgrey);

	g.setColour(Colours::black);
	g.drawText(outputs[rowNumber]->name, 0, 0, width, height, juce::Justification::centredLeft, false);
}

void OutputsPanelComponent::selectedRowsChanged (int lastRowSelected)
{
	if (lastRowSelected!=-1)
	{
		outputComponent->setOutputInfo(OutputInfo(outputs[lastRowSelected]));
		outputComponent->setVisible(true);

		minEditor->setText(String(outputs[lastRowSelected]->termManager->getMin()));
		maxEditor->setText(String(outputs[lastRowSelected]->termManager->getMax()));

		RulesPanelComponent* rpc = (RulesPanelComponent*)Pool::Instance()->getObject("RulesPanelComponent");
		if (!rpc->interactionOn)
		{
			valueSlider->setRange(minEditor->getText().getDoubleValue(), maxEditor->getText().getDoubleValue());
			valueSlider->setValue(*outputs[lastRowSelected]->pValue);
		}

		membershipGraph->setTermManager(outputs[lastRowSelected]->termManager); 
	}

	//updateCurrentValue();
}

void OutputsPanelComponent::changeListenerCallback (ChangeBroadcaster* source)
{
	if (source==outputComponent)
	{
		OutputInfo output = outputComponent->getOutputInfo();
		int selectedRow=outputsListBox->getSelectedRow();

		if (selectedRow!=-1)
		{
			outputs[selectedRow]->name = output.name;
			outputs[selectedRow]->oscaddress = output.oscaddress;
			outputs[selectedRow]->port = output.port;
			outputs[selectedRow]->host = output.host;
			outputs[selectedRow]->sendStateChanges = output.sendStateChanges;

			outputs[selectedRow]->prepareSocket();

			outputsListBox->updateContent();
			outputsListBox->repaintRow(selectedRow);
		}
	}
	else if (source == membershipGraph)
	{
		termEditor->setText(membershipGraph->termManager->terms[membershipGraph->selectionIndex]->name());
	}
}

void OutputsPanelComponent::updateCurrentValue()
{
	int selectedRow=outputsListBox->getSelectedRow();
	if (selectedRow!=-1)
	{
		valueSlider->setValue(*outputs[selectedRow]->pValue);
	}
	else
		valueSlider->setValue(0);
}

void OutputsPanelComponent::textEditorReturnKeyPressed (TextEditor &editor)
{
	int selectedRow=outputsListBox->getSelectedRow();

	if (selectedRow!=-1)
	{
		if (&editor == minEditor)
		{
			valueSlider->setRange(minEditor->getText().getDoubleValue(), maxEditor->getText().getDoubleValue());
			outputs[selectedRow]->termManager->setMin(editor.getText().getDoubleValue());
			membershipGraph->repaint();
			valueSlider->repaint();
		}
		else if (&editor == maxEditor)
		{
			valueSlider->setRange(minEditor->getText().getDoubleValue(), maxEditor->getText().getDoubleValue());
			outputs[selectedRow]->termManager->setMax(editor.getText().getDoubleValue());
			membershipGraph->repaint();
			valueSlider->repaint();
		}
	}
}

void OutputsPanelComponent::sendOuputValues()
{
	for (int i=0; i<outputs.size(); i++)
	{
		if (!outputs[i]->sendStateChanges)
		{
			osc::OutboundPacketStream p(outputs[i]->buffer, 128);

			p << osc::BeginMessage( outputs[i]->oscaddress.toUTF8() )
				<< (float)*outputs[i]->pValue
			<< osc::EndMessage;

			outputs[i]->socket->Send( p.Data(), p.Size() );
		}
		else
		{
			int termIndex = outputs[i]->termManager->getIndex(*outputs[i]->pValue);
			double memberShip = outputs[i]->termManager->terms[termIndex]->membership(*outputs[i]->pValue);

			if (memberShip==1.0 && termIndex!=outputs[i]->lastState)
			{
				outputs[i]->lastState = termIndex;

				osc::OutboundPacketStream p(outputs[i]->buffer, 128);

				p << osc::BeginMessage( outputs[i]->oscaddress.toUTF8() )
					<< (float)termIndex
				<< osc::EndMessage;

				outputs[i]->socket->Send( p.Data(), p.Size() );
			}
		}
	}
}

void OutputsPanelComponent::executeSetExample()
{
	buttonClicked(setButton);
}

void OutputsPanelComponent::updateContent()
{
	outputsListBox->updateContent();
}

void OutputsPanelComponent::clearOutputs()
{
	for (int i=0; i<outputs.size(); i++)
	{
		delete [] outputs[i]->buffer;
		delete [] outputs[i]->pValue;
		delete outputs[i]->socket;
		delete outputs[i]->termManager;
	}

	outputs.clear();
}

void OutputsPanelComponent::sliderSetEnabled(bool enabler)
{
	valueSlider->setEnabled(enabler);
}

void OutputsPanelComponent::disconnectTermManagerFromMembershipGraphComponent()
{
	outputsListBox->deselectAllRows();
	membershipGraph->termManager = 0;
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
             explicitFocusOrder="0" pos="8 259 592 200" sourceFile="MembershipGraphComponent.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="d65c34a4a966a503" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 222 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Current value&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="76a41ecfc22e8bd1" memberName="termEditor"
              virtualName="" explicitFocusOrder="0" pos="368 221 136 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="a9860cbed91414aa" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="344 222 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="is" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="c4309cd0fddcd2aa" memberName="setButton"
              virtualName="" explicitFocusOrder="0" pos="512 221 86 24" buttonText="Set"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="new text editor" id="7527e80cac92e6bf" memberName="minEditor"
              virtualName="" explicitFocusOrder="0" pos="14 463 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="e86da1c8d0ae8716" memberName="maxEditor"
              virtualName="" explicitFocusOrder="0" pos="447 464 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <JUCERCOMP name="" id="669420e8ddc78026" memberName="outputComponent" virtualName=""
             explicitFocusOrder="0" pos="184 32 400 168" sourceFile="OutputComponent.cpp"
             constructorParams=""/>
  <SLIDER name="new slider" id="a54bff35f1acf7bc" memberName="valueSlider"
          virtualName="" explicitFocusOrder="0" pos="104 222 240 24" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
