/*
  ==============================================================================

    MyOscillator.cpp
    Created: 19 Apr 2023 12:43:11am
    Author:  Evan Kramer

  ==============================================================================
*/

#include "MyOscillator.h"

void MyOscillator::prepareToPlay(juce::dsp::ProcessSpec spec){
    fs = spec.sampleRate;
    numSamples = spec.maximumBlockSize;
    numChannels = spec.numChannels;
    prepare(spec);
    setModWaveSelection(choice);
    setFrequency(250.f);
    
    gainDSP.prepare(spec);
    gainDSP.setGainLinear(0.001f);
}

juce::AudioBuffer<float> MyOscillator::processBlock (){
    juce::AudioBuffer<float> oscBuffer = juce::AudioBuffer<float>(numChannels, numSamples);
    juce::dsp::AudioBlock<float> audioBlock {oscBuffer};
    
    process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gainDSP.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    audioBlock.copyTo(oscBuffer);
    return oscBuffer;
}



void MyOscillator::setModWaveSelection(int wave){
    choice = wave-1;
    switch(choice){
        case 0:
            //sine wave
            initialise([](float x) {return std::sin(x); });
            break;
            
        case 1:
            //square wave
            initialise([](float x) {return x / juce::MathConstants<float>::pi;});
            break;
            
        case 2:
            //saw wave
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
            break;
            
        default:
            //jassertfalse;
            break;
    }
}
    


