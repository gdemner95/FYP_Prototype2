/*
 ==============================================================================
 
 DrumSynthSound.cpp
 Created: 29 Jan 2016 2:19:29pm
 Author:  George Demner
 
 ==============================================================================
 */
#include "JuceHeader.h"
#include "DrumSynthSound.h"
#include "Strings.h"
//DrumSound::DrumSound (int n, int c, int f, int v, int s)
//: note (n), channel(c)
//{
//    File localDir = File::getSpecialLocation (File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile ("Resources");
////    char charBuffer[128] = { 0 };
//    
////    for (int i = 0; i < 6; i++){
////        sprintf(charBuffer, "%s%s%s", fileName[0], velocityIndex[5], stringEnd[0]);
////        printf("%s\n", charBuffer);
//        File tempFile = localDir.getChildFile("Bass Drum In 6_1.wav");
//        AudioFormatManager formatManager;
//        ScopedPointer<AudioFormatReader> drumReader;
//        formatManager.registerFormat (new WavAudioFormat(), true);
//        
//        drumReader = formatManager.createReaderFor(tempFile);
//
//        buffer.velocities[0].samples[0].setSize(drumReader->numChannels, drumReader->lengthInSamples);
//        drumReader->read(&buffer.velocities[5].samples[0],
//                         0,
//                         drumReader->lengthInSamples,
//                         0,
//                         true,
//                         true);
////    };
//
//}
//bool DrumSound::appliesToNote (int midiNoteNumber)
//{
//    return note == midiNoteNumber;
//}
//
//bool DrumSound::appliesToChannel (int midiChannel)
//{
//    return channel == 0 || channel == midiChannel;
//}
//
//AudioSampleBuffer* DrumSound::getBufferForVelocity (float velocity)
//{
//    // get the array of buffers for this velocity band
//    // this will be the array of random variations
//    // choose one of these and return a pointer to it..
//    jassertfalse;
//    return nullptr;
//}
//

DrumSound::DrumSound (int n, int c)
:   note (n), channel (c)
{
    File localDir = File::getSpecialLocation (File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile ("Resources");
    
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReader> drumReader[8];
    
    formatManager.registerFormat (new WavAudioFormat(), true);
    char charBuffer[128] = { 0 };
    
    for (int v = 5; v < 6; v++)
    {
        for (int s = 0; s < 6; s++)
        {
            sprintf(charBuffer, "%s%s%s", fileName[0], velocityIndex[v], stringEnd[s]);

            File tempFile = localDir.getChildFile(charBuffer);

            drumReader[s] = formatManager.createReaderFor(tempFile);
            
            printf("inside constructor: %d%d%d\n", 0, v, s);
            buffer.velocities[v].samples[s].setSize(drumReader[s]->numChannels, drumReader[s]->lengthInSamples);
            drumReader[s]->read(&buffer.velocities[v].samples[s],
                                0,
                                drumReader[s]->lengthInSamples,
                                0,
                                true,
                                true);
            
            printf("sounds added: %s to %d_%d_%d \n", charBuffer, 0 ,v ,s);
        }
    }


}

bool DrumSound::appliesToNote (int midiNoteNumber)
{
    return note == midiNoteNumber;
}

bool DrumSound::appliesToChannel (int midiChannel)
{
    return channel == 0 || channel == midiChannel;
}
AudioSampleBuffer* DrumSound::getBufferForVelocity (float velocity)
{
    AudioSampleBuffer* tempBuffer = buffer.getVelRange(velocity)->getNextSample();
    return tempBuffer;
    // get the array of buffers for this velocity band
    // this will be the array of random variations
    // choose one of these and return a pointer to it..
    jassertfalse;
}
