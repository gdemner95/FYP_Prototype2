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



struct VelRange
{
    const int randomNumbers[10] = {
        2,
        4,
        3,
        5,
        3,
        1,
        3,
        4,
        2,
        1,
    };

    AudioSampleBuffer* getNextSample(){
        int chosen = randomNumbers[rand() % 10];
        return &samples[0];
    };
    AudioSampleBuffer samples[6];
};

struct Drum
{
    VelRange* getVelRange(int velocity){
        if (velocity >= 0 & velocity < 21){
            //play lowest velocity for passed timbre
            return &velocities[0];
        }
        else if (velocity >= 21 & velocity < 40){
            return &velocities[1];
        }
        else if (velocity >= 41 & velocity < 60){
            return &velocities[2];
        }
        else if (velocity >= 61 & velocity < 80){
            return &velocities[3];
        }
        else if (velocity >= 81 & velocity < 90){
            return &velocities[4];
        }
        else
        {
            //play highest velocity for passed timbre
            return &velocities[5];
        }
    }
    
    VelRange velocities[6];
};
struct CymbalMics
{
    Drum mics[8];
};

class DrumSound : public SynthesiserSound
{
public:
    DrumSound (File file, int note, int channel);
    
    bool appliesToNote (int midiNoteNumber);
    bool appliesToChannel (int midiChannel);
    
    AudioSampleBuffer* getBuffer(int timbre, float velocity){
        velocity *= 127;
        return buffer[0].getVelRange(127)->getNextSample();
    }
private:
    int note;
    int channel;
//    AudioSampleBuffer buffer;
    Drum buffer[8];
    
};
#endif  // DRUMSYNTHSOUND_H_INCLUDED
