/*
 ==============================================================================
 
 This file was auto-generated by the Introjucer!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DrumSynthAudioSource.h"
#include "DrumSynthSound.h"
#include "DrumSynthVoice.h"
#include "Strings.h"

//==============================================================================
Fyp_samplerPrototype2AudioProcessor::Fyp_samplerPrototype2AudioProcessor(/*DrumSynthAudioSource& kickAudioSource*/)/* : kickAudioSource(keyboardState)*/
{
    for(int i = 0; i < 32; i++){
        synth.addVoice(new DrumSynthVoice());
        std::cout << "voices added\n";
    }
//    File localDir = File::getSpecialLocation (File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile ("Resources");
//    char *localDirPath[128];
//    sprintf(*localDirPath, "%c", localDir);
//    char charBuffer[128] = { 0 };
//    sprintf(charBuffer, "%s%s%s", fileName[0], velocityIndex[5], stringEnd[0]);
    
    File file("/Users/GeorgeDemner/Documents/UWE/Year 3/Final Year Project/FYP_SamplerPrototype2/Builds/MacOSX/Bass Drum In 6_1.wav");
    synth.addSound(new DrumSound(file, 48, 0));
        std::cout << "sounds added\n";

    /*
    
    // Initialise synthesiser variables here
    char charBuffer[128] = { 0 };
    for(int a = 0; a < 7; a++){
        for (int x = 5; x < 6; x++){
            for (int i = 0; i < 6; i++){
                sprintf(charBuffer, "%s%s%s", fileName[a], velocityIndex[x], stringEnd[i]);
                buffer[a].velocities[x].samples[i].openResource(charBuffer);
                buffer[a].velocities[x].samples[i].reset();
                printf("Buffer - %d Velocity - %d Sample - %d %s\n", a, x, i, charBuffer);
            }
        }
    }
    
    for(int b = 0; b < 8; b++){
        for(int a = 0; a < 5; a++){
            for (int x = 5; x < 6; x++){
                for (int i = 0; i < 6; i++){
                    sprintf(charBuffer, "%s%s%s%s", fileName[b+7], cymbalMics[a], velocityIndex[x], stringEnd[i]);
                    cymbals[b].mics[a].velocities[x].samples[i].openResource(charBuffer);
                    cymbals[b].mics[a].velocities[x].samples[i].reset();
                    printf("Cymbal - %d Mics - %d Velocity - %d Sample - %d %s\n", b, a, x, i, charBuffer);
                }
            }
        }
    }
    
    */
    
}

Fyp_samplerPrototype2AudioProcessor::~Fyp_samplerPrototype2AudioProcessor()
{
}

//==============================================================================
const String Fyp_samplerPrototype2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

const String Fyp_samplerPrototype2AudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String Fyp_samplerPrototype2AudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool Fyp_samplerPrototype2AudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool Fyp_samplerPrototype2AudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool Fyp_samplerPrototype2AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Fyp_samplerPrototype2AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Fyp_samplerPrototype2AudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double Fyp_samplerPrototype2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Fyp_samplerPrototype2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Fyp_samplerPrototype2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Fyp_samplerPrototype2AudioProcessor::setCurrentProgram (int index)
{
}

const String Fyp_samplerPrototype2AudioProcessor::getProgramName (int index)
{
    return String();
}

void Fyp_samplerPrototype2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Fyp_samplerPrototype2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Fyp_samplerPrototype2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void Fyp_samplerPrototype2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    const int numSamples = buffer.getNumSamples();
    
    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    
    //    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    //    {
    //        float* channelData = buffer.getWritePointer (channel);
    //
    //        // ..do something to the data...
    //    }
    
    
}

//==============================================================================
bool Fyp_samplerPrototype2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Fyp_samplerPrototype2AudioProcessor::createEditor()
{
    return new Fyp_samplerPrototype2AudioProcessorEditor (*this);
}

//==============================================================================
void Fyp_samplerPrototype2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Fyp_samplerPrototype2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Fyp_samplerPrototype2AudioProcessor();
}
