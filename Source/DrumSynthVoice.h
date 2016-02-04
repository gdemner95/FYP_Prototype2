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
    DrumSynthVoice() : level(0.0), tailOff(0.0){    };
    
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
        
        if(tailOff > 0.0){
            while(--numSamples >= 0){
                
                const AudioSampleBuffer& currentSound = drumSound->getBuffer();
                
                
                for(int i = outputBuffer.getNumChannels(); i >= 0; i--){
                    const float* currentSample = currentSound.getReadPointer(i, positionInBuffer);
                    float* currentOutput = outputBuffer.getWritePointer(i, startSample);
                    *currentOutput += *currentSample * tailOff;
                }
                
                startSample++;
                positionInBuffer++;
                tailOff *= 0.99;
                
                if(tailOff <= 0.005){
                    clearCurrentNote();
                    break;
                }
                
            }
        }
        
        
        
        
        ///etc blah blah...
    }
private:
    double level, tailOff;
    
    DrumSound* drumSound;
    int positionInBuffer;
    
};



#endif  // DRUMSYNTHVOICE_H_INCLUDED
