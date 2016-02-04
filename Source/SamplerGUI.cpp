/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SamplerGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SamplerGUI::SamplerGUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (textButton1 = new TextButton ("Kick"));
    addAndMakeVisible (textButton1 = new TextButton ("Snare"));
    addAndMakeVisible (textButton1 = new TextButton ("Hi Hat"));

    textButton1->addListener (this);
    textButton2->addListener (this);
    textButton3->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SamplerGUI::~SamplerGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textButton1 = nullptr;
    textButton2 = nullptr;
    textButton3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SamplerGUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SamplerGUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    textButton1->setBounds (20, 20, getWidth() - 20, 20);
    textButton2->setBounds (20, 60, getWidth() - 20, 20);
    textButton3->setBounds (20, 100, getWidth() - 20, 20);

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SamplerGUI::buttonClicked (Button* button)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]
    if (button == textButton1)      TriggerButtonClicked(1);
    if (button == textButton2)      TriggerButtonClicked(2);
    if (button == textButton3)      TriggerButtonClicked(3);
    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}




//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SamplerGUI" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTBUTTON name="new button" id="e04ead43998d77af" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="89 304 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
