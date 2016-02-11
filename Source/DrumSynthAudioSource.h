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

//class DrumSynthAudioSource : AudioSource
//{
//public:
//    DrumSynthAudioSource(/*MidiKeyboardState& keyState*/)/*: keyboardState(keyState)*/
//    {
//        for(int i = 0; i < 32; i++){
//            synth.addVoice(new DrumSynthVoice());
//            std::cout << "voices added\n";
//        }
//        File file("/Users/GeorgeDemner/Desktop/Hats Closed Shaft Close Mic 6_6.wav");
//        synth.addSound(new DrumSound(file, 60, 0));
//        std::cout << "sounds added\n";
//        
//        defaultMidiIn = midiInput->getDefaultDeviceIndex();
//        std::cout << "DrumSynthAudioSource - Constructed\n";
//    };
//    
//    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
//    {
//        std::cout << "DrumSynthAudioSource - prepareToPlay\n";
//        synth.setCurrentPlaybackSampleRate(sampleRate);
//        midiCollector.reset(sampleRate);
//        }
//        void releaseResources() override
//        {
//            std::cout << "DrumSynthAudioSource - releaseResources\n";
//        }
//        
//        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
//        {
//            std::cout << "DrumSynthAudioSource - getnextAudioBlock\n";
//            //                    deviceManager.handleIncomingMidiMessageInt(midiInput, const midiCollector);
//            bufferToFill.clearActiveBufferRegion();
//            MidiBuffer incomingMidi;
//            //        midiIterator.getNextEvent(incomingMidi, bufferToFill.startSample);
//            midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
//            //            keyboardState.processNextMidiBuffer (incomingMidi, bufferToFill.startSample,
//            //                                                 bufferToFill.numSamples, true); // [4]
//            synth.renderNextBlock (*bufferToFill.buffer, incomingMidi,
//                                   bufferToFill.startSample, bufferToFill.numSamples); // [5]
//        }
//        
//        
//    private:
//        Synthesiser synth;
//        };
//        
//        

#endif  // DRUMSYNTHAUDIOSOURCE_H_INCLUDED
