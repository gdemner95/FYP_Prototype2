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
        0,
        4,
        2,
        1,
    };

    AudioSampleBuffer* getNextSample(){
        int chosen = randomNumbers[rand() % 10];
        printf("chosen sample: %d", chosen);
        return &samples[chosen];
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
    DrumSound (int note, int channel);
    virtual ~DrumSound() {}

    bool appliesToNote (int midiNoteNumber);
    bool appliesToChannel (int midiChannel);

    AudioSampleBuffer* getBufferForVelocity (float velocity);

    
    AudioSampleBuffer* getBuffer(int timbre, float velocity){
        velocity *= 127;
        return buffer.getVelRange(velocity)->getNextSample();
    }
private:
    int note;
    int channel;
    Drum buffer;
};
//class DrumSound : public SynthesiserSound
//{
//public:
//    DrumSound (int note, int channel, int f, int v, int s);
//    virtual ~DrumSound() {}
//    
//    bool appliesToNote (int midiNoteNumber);
//    bool appliesToChannel (int midiChannel);
//    
//
//    AudioSampleBuffer& getBuffer(){
//        return buffer;
//    };
//    //        velocity *= 127;
//    //        return buffer[timbre].getVelRange(velocity)->getNextSample();
//    //    }
//private:
//    int note;
//    int channel;
//    AudioSampleBuffer buffer;
//};

//DrumSound::DrumSound (int n, int c, int f)
//:   note (n), channel (c)
//{
//    File localDir = File::getSpecialLocation (File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile ("Resources");
//
//    AudioFormatManager formatManager;
//    ScopedPointer<AudioFormatReader> drumReader[8];
//
//    formatManager.registerFormat (new WavAudioFormat(), true);
//    char charBuffer[128] = { 0 };
//
//    for (int v = 5; v < 6; v++)
//    {
//        for (int s = 0; s < 6; s++)
//        {
//            sprintf(charBuffer, "%s%s%s", fileName[f], velocityIndex[v], stringEnd[s]);
//
//            File tempFile = localDir.getChildFile(charBuffer);
//
//            drumReader[s] = formatManager.createReaderFor(tempFile);
//
//            printf("inside constructor: %d%d%d\n", f, v, s);
//            buffer[f].velocities[v].samples[s].setSize(drumReader[s]->numChannels, drumReader[s]->lengthInSamples);
//            drumReader[s]->read(&buffer[f].velocities[v].samples[s],
//                                0,
//                                drumReader[s]->lengthInSamples,
//                                0,
//                                true,
//                                true);
//
//            printf("sounds added: %s to %d_%d_%d \n", charBuffer, f ,v ,s);
//        }
//    }

//    printf("NumChannels %d\n", drumReader[s]->numChannels);
//    printf("Length In Samples %lld\n", drumReader[s]->lengthInSamples);
//    printf("");
//    printf("");
//    printf("");
//}
//
//bool DrumSound::appliesToNote (int midiNoteNumber)
//{
//    return note == midiNoteNumber;
//}
//
//bool DrumSound::appliesToChannel (int midiChannel)
//{
//    return channel == 0 || channel == midiChannel;
//}


#endif  // DRUMSYNTHSOUND_H_INCLUDED
