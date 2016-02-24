/*
 ==============================================================================
 
 DrumSynthSound.cpp
 Created: 29 Jan 2016 2:19:29pm
 Author:  George Demner
 
 ==============================================================================
 */

#include "DrumSynthSound.h"
#include "Strings.h"
DrumSound::DrumSound (int n, int c, int f)
: note (n), channel(c)
{
    File localDir = File::getSpecialLocation (File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile ("Resources");
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReader> drumReader;
    formatManager.registerFormat (new WavAudioFormat(), true);
    File tempFile = localDir.getChildFile("Bass Drum In 6_1.wav");
    
    drumReader = formatManager.createReaderFor(tempFile);
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

