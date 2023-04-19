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

    void setModWaveSelection(int wave);
    
    int choice = 0;

private:
    
    float mix = 50;
};
