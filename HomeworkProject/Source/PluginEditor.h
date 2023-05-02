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
class HomeworkProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
//                                                public juce::ComboBox::Listener,
//                                                public juce::Slider::Listener
{
public:
    HomeworkProjectAudioProcessorEditor (HomeworkProjectAudioProcessor&);
    ~HomeworkProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
//    virtual void comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged) override;
//    virtual void sliderValueChanged(juce::Slider* slider) override;

private:
    
    //set look and feel
    juce::LookAndFeel_V4 lookAndFeel4;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HomeworkProjectAudioProcessor& audioProcessor;
    
    //create knobs
    juce::Slider wetDrySlider;
    juce::Slider modFreqSlider;
    
    //create drop down menu
    juce::ComboBox modWaveSelector;

    
   
    
    //create component labels
    juce::Label wetDryLabel;
    juce::Label modFreqLabel;
    juce::Label modSelectLabel;
    
    juce::Label title;
    
   
    public:
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> mixSliderAttatchment;
    
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> freqSliderAttatchment;

    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> choiceAttatchment;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeworkProjectAudioProcessorEditor)
};
