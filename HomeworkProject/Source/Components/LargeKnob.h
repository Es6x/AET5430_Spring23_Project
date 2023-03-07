/*
  ==============================================================================

    LargeKnob.h
    Created: 2 Mar 2023 12:57:35pm
    Author:  Evan Kramer

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class LargeKnob : public juce::LookAndFeel_V4{
    
public:
    
    juce::Image knob = juce::ImageCache::getFromMemory(BinaryData::knob_large_png, BinaryData::knob_large_pngSize);
    
    
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float
                                    rotaryEndAngle, juce::Slider& slider);
    
};

