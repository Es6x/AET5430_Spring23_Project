/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HomeworkProjectAudioProcessorEditor::HomeworkProjectAudioProcessorEditor (HomeworkProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);
    

    
    //customize wet/dry % knob
    wetDrySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    wetDrySlider.setBounds(5, 205, 175, 175);
    wetDrySlider.setRange(0, 100, 1);
    wetDrySlider.setValue(50);
    wetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,30);
    wetDrySlider.setLookAndFeel(&lookAndFeel4);
    wetDrySlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan.darker(0.2));
    wetDrySlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::grey);
    wetDrySlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    wetDrySlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(wetDrySlider);
    
    //attatch wet/dry label
    wetDryLabel.setText("Wet Mix %", juce::dontSendNotification);
    wetDryLabel.attachToComponent(&wetDrySlider, false);
    wetDryLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetDryLabel);
    
    //customize modulation frequency knob
    modFreqSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    modFreqSlider.setBounds(220, 205, 175, 175);
    modFreqSlider.setRange(1, 1000, 1);
    modFreqSlider.setValue(500);
    modFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,30);
    modFreqSlider.setLookAndFeel(&lookAndFeel4);
    modFreqSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan.darker(0.2));
    modFreqSlider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::grey);
    modFreqSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    modFreqSlider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(modFreqSlider);
    
    //attatch modulation frequency label
    modFreqLabel.setText("Modulation Frequency (Hz)", juce::dontSendNotification);
    modFreqLabel.attachToComponent(&modFreqSlider, false);
    modFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modFreqLabel);
    
    //customize dropdown menu
    modWaveSelector.addItem("Sine",1);
    modWaveSelector.addItem("Sawtooth",2);
    modWaveSelector.addItem("Square",3);
    modWaveSelector.addItem("Triangle",4);

    modWaveSelector.setBounds(135, 110, 130, 30);
    modWaveSelector.setJustificationType(juce::Justification::centred);
    modWaveSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::grey.darker(0.2));
    modWaveSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::cyan.darker(0.6));
    modWaveSelector.setSelectedId(1);
    addAndMakeVisible(modWaveSelector);
    
    //attatch dropdown label
    modSelectLabel.setText("Modulation Wave Type", juce::dontSendNotification);
    modSelectLabel.attachToComponent(&modWaveSelector, false);
    modSelectLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modSelectLabel);
    
    //customize plugin title
    title.setText("Evan's Ring Modulator", juce::dontSendNotification);
    title.setBounds(0, 10, 400, 35);
    title.setFont (juce::Font (35.0f, juce::Font::bold));
    title.setColour(juce::Label::ColourIds::textColourId, juce::Colours::cyan.darker(0.2));
    title.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(title);
    
    //attatch parameters to plugin components
    mixSliderAttatchment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "mixValue", wetDrySlider) );
    freqSliderAttatchment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state, "freqValue", modFreqSlider) );
    choiceAttatchment.emplace_back(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.state, "waveChoice", modWaveSelector));
    
}

HomeworkProjectAudioProcessorEditor::~HomeworkProjectAudioProcessorEditor()
{
}

//==============================================================================
void HomeworkProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black.brighter(0.1));
}

void HomeworkProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
