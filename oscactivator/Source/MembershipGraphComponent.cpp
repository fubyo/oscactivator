/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Jan 2013 4:43:56pm

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
    //[/UserPreSize]

    setSize (600, 400);


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

    g.fillAll (Colours::bisque);

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
			g.drawLine( (termManager->terms[i]->a()-min)*width/difference, height-1, (termManager->terms[i]->b()-min)*width/difference, 0);
			g.drawLine( (termManager->terms[i]->b()-min)*width/difference, 0, (termManager->terms[i]->c()-min)*width/difference, 0);
			g.drawLine( (termManager->terms[i]->c()-min)*width/difference, 0, (termManager->terms[i]->d()-min)*width/difference, height-1);
		}
	} 

    //[/UserPaint]
}

void MembershipGraphComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
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
                 overlayOpacity="0.330000013" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffe4c4"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
