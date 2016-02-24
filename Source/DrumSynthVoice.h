/*
 ==============================================================================
 
 DrumSynthVoice.h
 Created: 1 Feb 2016 1:43:06pm
 Author:  George Demner
 
 ==============================================================================
 */

#ifndef DRUMSYNTHVOICE_H_INCLUDED
#define DRUMSYNTHVOICE_H_INCLUDED

#include "JuceHeader.h"
#include "DrumSynthSound.h"
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
    
    DrumSound* getNextSample(){
        int chosen = randomNumbers[rand() % 10];
        printf("chosen sample: %d", chosen);
        return samples[chosen];
    };
    DrumSound* samples[6];
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


class DrumSynthVoice : public SynthesiserVoice
{
public:
    DrumSynthVoice() : level(0.0), tailOff(0.0) /*drumSound (nullptr)*/ {    };
    
    bool canPlaySound(SynthesiserSound* sound) override {
        
        return dynamic_cast<DrumSound*>(sound) != nullptr;
    };
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        
        jassert (dynamic_cast<DrumSound*> (sound) != nullptr);
        velocity *= 127;
        
        for (int i = 0; i < 6; i++){
            drumSound.velocities[5].samples[i] = static_cast<DrumSound*> (sound);
        }
        
        positionInBuffer = 0;
        level = 0.15 * velocity;
//        vel = velocity;
        tailOff = 0.0;
        
        switch(midiNoteNumber){
            case 48 : timbre = 0;
        }
        
        
    }
    
    DrumSound* getSound(int timbre, float velocity){
        velocity *= 127;
        return drumSound.getVelRange(velocity)->getNextSample();
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override {}
    void controllerMoved (int controllerNumber, int newControllerValue) override {}
    
    
    void stopNote(float velocity, bool allowTailOff) override{
        clearCurrentNote();
        drumSound.velocities[5].samples[0] = nullptr;
        
        if (allowTailOff)
        {
            if (tailOff == 0.0)
                tailOff = 1.0;
        }
        else
        {
            clearCurrentNote();
        }
        
    }
    
    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        if (drumSound.velocities[5].samples[0] == nullptr)
            return;

        const AudioSampleBuffer& currentSound = drumSound.velocities[5].samples[0]->getBuffer(0,5);
        
        if(tailOff > 0.0){
            while(--numSamples >= 0){
                
                for(int i = outputBuffer.getNumChannels(); --i >= 0;)
                {
                    const float sampleValue = (currentSound.getSample (i % currentSound.getNumChannels(), positionInBuffer) * tailOff);
                    outputBuffer.setSample (i, startSample, sampleValue);
                }
                
                startSample++;
                positionInBuffer++;
                tailOff *= 0.99;
                if (positionInBuffer >= currentSound.getNumSamples())
                {
                    clearCurrentNote();
                    drumSound.velocities[0].samples[0] = nullptr;
                    break;
                }
                
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    drumSound.velocities[0].samples[0] = nullptr;
                    break;
                }
            }
            
        }
        else
        {
            while( --numSamples >= 0)
            {
                for(int i = outputBuffer.getNumChannels(); --i >= 0;)
                {
//                                        printf("Output channels: %d\n", i);
//                                        printf("Number Of Channels: %d\n", currentSound.getNumChannels());
                    //                    printf("Pos in buffer: %d\n", positionInBuffer);
                    const float sampleValue = currentSound.getSample (i % currentSound.getNumChannels(), positionInBuffer);
//                                        printf("startSample: %d\n", startSample);
//                                        printf("sample Value: %f\n", sampleValue);
                    
                    outputBuffer.setSample (i, startSample, sampleValue);
                }
                
                startSample++;
                positionInBuffer++;
            }
            
        }
    }
private:
    double level, tailOff;
    
    int timbre;
    float vel;
    Drum drumSound;
//    DrumSound* drumSoundSamples[5];
    
    int positionInBuffer;
    
};



#endif  // DRUMSYNTHVOICE_H_INCLUDED
