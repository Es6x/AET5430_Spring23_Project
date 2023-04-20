/*
  ==============================================================================

    MyOscillator.h
    Created: 19 Apr 2023 12:43:11am
    Author:  Evan Kramer

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class MyOscillator : public juce::dsp::Oscillator<float> {

public:

    void prepareToPlay(juce::dsp::ProcessSpec spec);

    juce::AudioBuffer<float> processBlock ();
    
    void setModWaveSelection(int wave);
    
    
    
    int choice = 1;

private:
    juce::dsp::Gain<float> gainDSP;

    double fs;
    int numSamples;
    int numChannels;
};
