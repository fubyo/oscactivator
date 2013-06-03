/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  3 Jun 2013 2:17:31pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MEMBERSHIPGRAPHCOMPONENT_MEMBERSHIPGRAPHCOMPONENT_D674C028__
#define __JUCER_HEADER_MEMBERSHIPGRAPHCOMPONENT_MEMBERSHIPGRAPHCOMPONENT_D674C028__

//[Headers]     -- You can add your own extra header files here --
#include "..\JuceLibraryCode\JuceHeader.h"
#include "TermManager.h"
#include "Pool.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MembershipGraphComponent  : public Component,
                                  public ChangeBroadcaster
{
public:
    //==============================================================================
    MembershipGraphComponent ();
    ~MembershipGraphComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setTermManager(TermManager* pTermManager);
	int selectionIndex;
	TermManager* termManager;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void mouseDown (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
    bool keyPressed (const KeyPress& key);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MembershipGraphComponent (const MembershipGraphComponent&);
    const MembershipGraphComponent& operator= (const MembershipGraphComponent&);
};


#endif   // __JUCER_HEADER_MEMBERSHIPGRAPHCOMPONENT_MEMBERSHIPGRAPHCOMPONENT_D674C028__
