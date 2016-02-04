/*
  ==============================================================================

    DrumSynthAudioSource.h
    Created: 1 Feb 2016 2:18:51pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef DRUMSYNTHAUDIOSOURCE_H_INCLUDED
#define DRUMSYNTHAUDIOSOURCE_H_INCLUDED

#include "JuceHeader.h"
#include "DrumSynthVoice.h"
#include "DrumSynthSound.h"

class DrumSynthAudioSource : AudioSource
{
public:
    DrumSynthAudioSource()
    {
        for(int i = 0; i < 32; i++){
            synth.addVoice(new DrumSynthVoice());
            
        }
        File file("/Users/GeorgeDemner/Desktop/Hats Closed Shaft Close Mic 6_6.wav");
        synth.addSound(new DrumSound(file, 60, 0));
    
//        int defaultMidiIn = midiIn.getDefaultDeviceIndex();
        std::cout << "DrumSynthAudioSource - Constructed";
        
    };
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        std::cout << "DrumSynthAudioSource - prepareToPlay";
        synth.setCurrentPlaybackSampleRate (sampleRate);
        midiCollector.reset(sampleRate);
    }
    void releaseResources() override
    {
        std::cout << "DrumSynthAudioSource - releaseResources";

    }
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        std::cout << "DrumSynthAudioSource - getnextAudioBlock";

        bufferToFill.clearActiveBufferRegion();
        MidiBuffer incomingMidi;
        midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
        keyboardState.processNextMidiBuffer (incomingMidi, bufferToFill.startSample,
                                             bufferToFill.numSamples, true); // [4]
        synth.renderNextBlock (*bufferToFill.buffer, incomingMidi,
                               bufferToFill.startSample, bufferToFill.numSamples); // [5]
    }
    
    MidiMessageCollector* getMidiCollector(){
        std::cout << "DrumSynthAudioSource - getMidiCollector";

        return &midiCollector;
    }
    
    void setMidiInput (int index)
    {
        std::cout << "DrumSynthAudioSource - setMidiInput";

        const StringArray list (MidiInput::getDevices());
        deviceManager.removeMidiInputCallback (list[MidiInput::getDefaultDeviceIndex()], getMidiCollector());
        const String newInput (list[MidiInput::getDefaultDeviceIndex()]);
        if (! deviceManager.isMidiInputEnabled (newInput))
            deviceManager.setMidiInputEnabled (newInput, true);
        deviceManager.addMidiInputCallback (newInput, getMidiCollector());
//        midiInputList.setSelectedId (index + 1, dontSendNotification);
//        lastInputIndex = index;
    }
    
private:
    MidiKeyboardState keyboardState;
    MidiMessageCollector midiCollector;
    AudioDeviceManager deviceManager;
    
//    MidiInput midiIn;
    Synthesiser synth;
};



#endif  // DRUMSYNTHAUDIOSOURCE_H_INCLUDED
