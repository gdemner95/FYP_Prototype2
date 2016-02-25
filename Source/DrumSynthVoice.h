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
    DrumSynthVoice()
    :   level(0.0),
    tailOff(0.0), /*drumSound (nullptr)*/
    currentDrumBuffer (nullptr)
    {
    };
    
    bool canPlaySound(SynthesiserSound* sound) override {
        
        return dynamic_cast<DrumSound*>(sound) != nullptr;
    };
    
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
    {
        
        jassert (dynamic_cast<DrumSound*> (sound) != nullptr);
        DrumSound* drumSound = static_cast<DrumSound*> (sound);
        
        currentDrumBuffer = drumSound->getBuffer(0, velocity);
        
        //        velocity *= 127;
        //
        //        drum.velocities[5].samples[random] = ;
        
        positionInBuffer = 0;
        level = 0.15 * velocity;
        //        vel = velocity;
        tailOff = 0.0;
    }
    
    void pitchWheelMoved (int newPitchWheelValue) override {}
    void controllerMoved (int controllerNumber, int newControllerValue) override {}
    
    void stopNote(float velocity, bool allowTailOff) override{
        clearCurrentNote();
        currentDrumBuffer = nullptr;
        
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
        if (currentDrumBuffer == nullptr)
            return;
        //        const DrumSound* tempSound = drumSound.getVelRange(vel)->getNextSample();
        const AudioSampleBuffer& currentSound = *currentDrumBuffer;
        
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
                    currentDrumBuffer = nullptr;
                    break;
                }
                
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    currentDrumBuffer = nullptr;
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
                    const float sampleValue = currentSound.getSample (i % currentSound.getNumChannels(), positionInBuffer);
                    outputBuffer.setSample (i, startSample, sampleValue);
                }
                
                startSample++;
                positionInBuffer++;
            }
            
        }
    }
private:
    double level, tailOff;
    //    int random;
    //    int timbre;
    //    float vel;
    //    Drum drum;
    DrumSound* drumSound;
    AudioSampleBuffer* currentDrumBuffer;
    
    int positionInBuffer;
    
};



#endif  // DRUMSYNTHVOICE_H_INCLUDED
