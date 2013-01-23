/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  23 Jan 2013 5:58:35pm

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

#include "MembershipGraphComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MembershipGraphComponent::MembershipGraphComponent ()
{

    //[UserPreSize]
	termManager=0;
	selectionIndex=-1;
    //[/UserPreSize]

    setSize (592, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MembershipGraphComponent::~MembershipGraphComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MembershipGraphComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffe0e0e0));

    //[UserPaint] Add your own custom painting code here..
	double width = 592;
	double height = 200;

	g.setColour(Colours::black);
	if (termManager)
	{	double min = termManager->getMin();
		double max = termManager->getMax();
		double difference = max-min;
		for (int i=0; i<termManager->terms.size(); i++)
		{
			if (i==selectionIndex)
				g.setColour(Colours::blue);
			else
				g.setColour(Colours::black);

			g.drawLine( (termManager->terms[i]->a()-min)*width/difference, height-1, (termManager->terms[i]->b()-min)*width/difference, 0);
			g.drawLine( (termManager->terms[i]->b()-min)*width/difference, 0, (termManager->terms[i]->c()-min)*width/difference, 0);
			g.drawLine( (termManager->terms[i]->c()-min)*width/difference, 0, (termManager->terms[i]->d()-min)*width/difference, height-1);
		}

		for (int i=0; i<termManager->terms.size(); i++)
		{
			float x=0,y=0;
			termManager->terms[i]->centroid(x,y);
			x = (x-min)*width/difference;
			y = height-(y)*height/difference;

			if (i==selectionIndex)
				g.setColour(Colours::blue);
			else
				g.setColour(Colours::black);

			g.drawEllipse(x, y, 5, 5, 2);
			g.drawText(String(termManager->terms[i]->name().c_str()), x, y, 100, 20, juce::Justification::left,true);
		}

	}

    //[/UserPaint]
}

void MembershipGraphComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MembershipGraphComponent::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	double width = 592;
	double height = 200;
	double min = termManager->getMin();
	double max = termManager->getMax();
	double difference = max-min;

	selectionIndex = -1;

	if (termManager)
	{
		for (int i=0; i<termManager->terms.size(); i++)
		{
			float x=0,y=0;
			termManager->terms[i]->centroid(x,y);
			x = (x-min)*width/difference;
			y = height-(y)*height/difference;

			if (e.getMouseDownX()>x-5 && e.getMouseDownX()<x+5 && e.getMouseDownY()>y-5 && e.getMouseDownY()<y+5 )
			{
				selectionIndex = i;
			}
		}

		repaint();
	}
    //[/UserCode_mouseDown]
}

bool MembershipGraphComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
	if (key == juce::KeyPress::deleteKey && termManager && selectionIndex!=-1)
	{
		termManager->removeTerm(selectionIndex);
		repaint();
	}

    return true;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MembershipGraphComponent::setTermManager(TermManager* pTermManager)
{
	termManager = pTermManager;
	repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MembershipGraphComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="592"
                 initialHeight="200">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffe0e0e0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
