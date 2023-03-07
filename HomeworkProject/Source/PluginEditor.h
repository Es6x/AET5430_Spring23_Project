/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class HomeworkProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                public juce::ComboBox::Listener,
                                                public juce::Slider::Listener
{
public:
    HomeworkProjectAudioProcessorEditor (HomeworkProjectAudioProcessor&);
    ~HomeworkProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    virtual void comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged) override;
    virtual void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HomeworkProjectAudioProcessor& audioProcessor;
    
    //create knobs
    juce::Slider wetDrySlider;
    juce::Slider modFreqSlider;
    
    //set look and feel
    juce::LookAndFeel_V4 lookAndFeel4;
    
    //create component labels
    juce::Label wetDryLabel;
    juce::Label modFreqLabel;
    juce::Label modSelectLabel;
    
    juce::Label title;
    
    //create drop down menu
    juce::ComboBox modWaveSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeworkProjectAudioProcessorEditor)
};
