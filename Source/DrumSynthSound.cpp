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
    ScopedPointer<AudioFormatReader> drumReader;
    
//    file = ("/Users/GeorgeDemner/Desktop/Hats Closed Shaft Close Mic 6_6.wav");
    
    formatManager.registerBasicFormats();
    
    drumReader = formatManager.createReaderFor(file);
    
    buffer.setSize(drumReader->numChannels, drumReader->lengthInSamples);
    drumReader->read(&buffer,
                     0,
                     drumReader->lengthInSamples,
                     0,
                     true,
                     true);
}

bool DrumSound::appliesToNote (int midiNoteNumber)
{
    return note == midiNoteNumber;
}

bool DrumSound::appliesToChannel (int midiChannel)
{
    return channel == 0 || channel == midiChannel;
}
