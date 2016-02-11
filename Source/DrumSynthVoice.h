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

class DrumSynthVoice : public SynthesiserVoice
{
public:
    DrumSynthVoice() : level(0.0), tailOff(0.0), drumSound (nullptr) {    };
    
    bool canPlaySound(SynthesiserSound* sound){
        
        return dynamic_cast<DrumSound*>(sound) != nullptr;
    };
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        jassert (dynamic_cast<DrumSound*> (sound) != nullptr);
        
        drumSound = static_cast<DrumSound*> (sound);
        positionInBuffer = 0;
        level = 0.15 * velocity;
        tailOff = 0.0;
    }
    
    
    void pitchWheelMoved (int newPitchWheelValue) override {}
    void controllerMoved (int controllerNumber, int newControllerValue) override {}
    
    
    void stopNote(float velocity, bool allowTailOff) override{
        clearCurrentNote();
        drumSound = nullptr;
        
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
    
    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
    {
        if (drumSound == nullptr)
            return;
        
        const AudioSampleBuffer& currentSound = *drumSound->getBuffer(0,5);
        
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
                    drumSound = nullptr;
                    break;
                }
                
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    drumSound = nullptr;
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
//                    printf("Output channels: %d\n", i);
//                    printf("Number Of Channels: %d\n", currentSound.getNumChannels());
//                    printf("Pos in buffer: %d\n", positionInBuffer);
                    const float sampleValue = currentSound.getSample (i % currentSound.getNumChannels(), positionInBuffer);
//                    printf("startSample: %d", startSample);
//                    printf("sample Value: %f", sampleValue);

                    outputBuffer.setSample (i, startSample, sampleValue);
                }
                
                startSample++;
                positionInBuffer++;
            }
        
        }
    }
    private:
        double level, tailOff;
        
        DrumSound* drumSound;
        int positionInBuffer;
        
    };
    
    
    
#endif  // DRUMSYNTHVOICE_H_INCLUDED
