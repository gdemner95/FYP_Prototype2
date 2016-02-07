/*
 ==============================================================================
 
 This file was auto-generated by the Introjucer!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DrumSynthAudioSource.h"

//==============================================================================
Fyp_samplerPrototype2AudioProcessor::Fyp_samplerPrototype2AudioProcessor()
{
    
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
    
    kickAudioSource.prepareToPlay(samplesPerBlock, sampleRate);
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
    
    const int numSamples = buffer.getNumSamples();
    
    // Pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    
    MidiBuffer processMidi;
    int time;
    MidiMessage m;
    
    for(MidiBuffer::Iterator i (midiMessages);i.getNextEvent(m,time);)
    {
        if(m.isNoteOn())
        {
            std::cout << "note on\n";
            
            AudioSourceChannelInfo info;
            info.buffer = &buffer;
            info.startSample = 0;
            info.numSamples = buffer.getNumSamples();
            kickAudioSource.prepareToPlay(numSamples, getSampleRate());
            kickAudioSource.getNextAudioBlock(info);
        }
        else if (m.isNoteOff()){}
        else if(m.isAftertouch()){}
        
        processMidi.addEvent(m, time);
    }
    midiMessages.swapWith(processMidi);
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
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
