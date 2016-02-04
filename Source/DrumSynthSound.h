/*
  ==============================================================================

    DrumSynthSound.h
    Created: 29 Jan 2016 2:19:29pm
    Author:  George Demner

  ==============================================================================
*/

#ifndef DRUMSYNTHSOUND_H_INCLUDED
#define DRUMSYNTHSOUND_H_INCLUDED

#include "JuceHeader.h"

class DrumSound : public SynthesiserSound
{
public:
    DrumSound (File file, int note, int channel);
    
    bool appliesToNote (int midiNoteNumber);
    bool appliesToChannel (int midiChannel);

    const AudioSampleBuffer& getBuffer() { return buffer; }
    
private:
    int note;
    int channel;
    AudioSampleBuffer buffer;
};



#endif  // DRUMSYNTHSOUND_H_INCLUDED
