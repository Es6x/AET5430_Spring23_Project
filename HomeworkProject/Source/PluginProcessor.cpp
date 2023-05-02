/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HomeworkProjectAudioProcessor::HomeworkProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "RingModParams", createParameterLayout())
#endif
{
}

HomeworkProjectAudioProcessor::~HomeworkProjectAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout HomeworkProjectAudioProcessor::createParameterLayout(){
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>( juce::ParameterID("mixValue",1) ,"Mix %", juce::NormalisableRange<float> (0.f, 100.f), 50.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>( juce::ParameterID("freqValue",1),"Modulation Frequency", juce::NormalisableRange<float> (1.f, 1000.f), 500.f));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID("waveChoice",1), "Modulation Type", juce::StringArray ("Sine","Sawtooth","Square","Triangle"), 0));
    
    return {params.begin(), params.end()};
}

//==============================================================================
const juce::String HomeworkProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HomeworkProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HomeworkProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HomeworkProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HomeworkProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HomeworkProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HomeworkProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HomeworkProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HomeworkProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void HomeworkProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HomeworkProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //prepare the modulator
    mod.prepareToPlay(sampleRate);
    //mod.setRate(500.f);
}

void HomeworkProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HomeworkProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HomeworkProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    float mixValue = *state.getRawParameterValue("mixValue");
    setWetMix(mixValue);
    
    float freqValue = *state.getRawParameterValue("freqValue");
    setModFreq(freqValue);
    
    int choice = *state.getRawParameterValue("waveChoice");
    setWaveSelection(choice);
    
    
    //loop through all channels
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        
        // loop through each sample
        for (int n = 0 ; n < buffer.getNumSamples() ; ++n){
            
            //get sample
            float x = buffer.getWritePointer(channel) [n];
            
            //modulate sample
            float w = mod.processSample(x, channel);
            
            //apply wet/dry gain
            float y = mixWet * w + mixDry * x;

           //write the new sample to the buffer
            buffer.getWritePointer(channel) [n] = y;
        }
    }
}

//==============================================================================
bool HomeworkProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HomeworkProjectAudioProcessor::createEditor()
{
    return new HomeworkProjectAudioProcessorEditor (*this);
}

//==============================================================================
void HomeworkProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
    
    auto currentState = state.copyState();
    std::unique_ptr<juce::XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HomeworkProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName(state.state.getType())){
        state.replaceState(juce::ValueTree::fromXml(*xml));
    }
    
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//update wet/dry value
void HomeworkProjectAudioProcessor::setWetMix(float mixValue){
    mixWet = mixValue / 100.f;
    mixDry = 1.f-mixWet;
}
//update modulator frequency
void HomeworkProjectAudioProcessor::setModFreq(int freqValue){
    modFreq = freqValue;
    mod.setRate(modFreq);
}

//update modulation wave type
void HomeworkProjectAudioProcessor::setWaveSelection(int choice){
    waveSelection = choice;
    mod.setModWaveSelection(waveSelection);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HomeworkProjectAudioProcessor();
}
