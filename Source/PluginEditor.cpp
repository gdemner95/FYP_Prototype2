/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SamplerGUI.h"

//==============================================================================
Fyp_samplerPrototype2AudioProcessorEditor::Fyp_samplerPrototype2AudioProcessorEditor (Fyp_samplerPrototype2AudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(kickButton);
    kickButton.addListener(this);

    
//    addAndMakeVisible (midiInputListLabel);
//    midiInputListLabel.setText ("MIDI Input:", dontSendNotification);
//    midiInputListLabel.attachToComponent (&midiInputList, true);
//    addAndMakeVisible (midiInputList);
//    midiInputList.setTextWhenNoChoicesAvailable ("No MIDI Inputs Enabled");
//    const StringArray midiInputs (MidiInput::getDevices());
//    midiInputList.addItemList (midiInputs, 1);
//    midiInputList.addListener (this);
//    for (int i = 0; i < midiInputs.size(); ++i)
//    {
//        if (deviceManager.isMidiInputEnabled (midiInputs[i]))
//        {
//            setMidiInput (i);
//            break;
//        }
//    }
//    if (midiInputList.getSelectedId() == 0)
//        setMidiInput (0);
//    
    setSize(600, 600);// Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
}

Fyp_samplerPrototype2AudioProcessorEditor::~Fyp_samplerPrototype2AudioProcessorEditor()
{
}

//==============================================================================
void Fyp_samplerPrototype2AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::slategrey);
    
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void Fyp_samplerPrototype2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    

    kickButton.setBounds (10, 10, getWidth() - 20, 20);
}
void Fyp_samplerPrototype2AudioProcessorEditor::buttonClicked(Button* button)
{
    MyAudioSource audioSource;
    
    if(button == &kickButton){
        audioSource.playFromButton(1);
    };
    
    
}