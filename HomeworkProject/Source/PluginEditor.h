/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/LargeKnob.h"
#include "Components/SmallKnob.h"

//==============================================================================
/**
*/
class HomeworkProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                public juce::ComboBox::Listener
{
public:
    HomeworkProjectAudioProcessorEditor (HomeworkProjectAudioProcessor&);
    ~HomeworkProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    virtual void comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HomeworkProjectAudioProcessor& audioProcessor;
    
    juce::Image bgImage;
    
    juce::Slider slider1;
    juce::Slider slider2;
    
    LargeKnob largeKnobLNF;
    SmallKnob smallKnobLNF;
    juce::LookAndFeel_V4 lookAndFeel4;
    
    juce::Label wetDryLabel;
    juce::Label modFreqLabel;
    
    
    juce::ComboBox effectSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeworkProjectAudioProcessorEditor)
};
