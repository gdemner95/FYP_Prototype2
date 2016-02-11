/*
  ==============================================================================

    DrumSynthSound.cpp
    Created: 29 Jan 2016 2:19:29pm
    Author:  George Demner

  ==============================================================================
*/

#include "DrumSynthSound.h"

DrumSound::DrumSound (File file, int n, int c)
:   note (n), channel (c)
{
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReader> drumReader[8];
    
//    file = ("/Users/GeorgeDemner/Desktop/Hats Closed Shaft Close Mic 6_6.wav");
    
    formatManager.registerBasicFormats();
    
    drumReader[0] = formatManager.createReaderFor(file);
    
    buffer[0].velocities[5].samples[0].setSize(drumReader[0]->numChannels, drumReader[0]->lengthInSamples);
    drumReader[0]->read(&buffer[0].velocities[5].samples[0],
                     0,
                     drumReader[0]->lengthInSamples,
                     0,
                     true,
                     true);
    printf("NumChannels %d\n", drumReader[0]->numChannels);
    printf("Length In Samples %lld\n", drumReader[0]->lengthInSamples);
        printf("");
        printf("");
        printf("");
}

bool DrumSound::appliesToNote (int midiNoteNumber)
{
    return note == midiNoteNumber;
}

bool DrumSound::appliesToChannel (int midiChannel)
{
    return channel == 0 || channel == midiChannel;
}

