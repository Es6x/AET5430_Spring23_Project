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
    

    
    
    slider1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider1.setBounds(5, 205, 175, 175);
    slider1.setRange(0, 100, 1);
    slider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,30);
    slider1.setLookAndFeel(&lookAndFeel4);
    slider1.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan.darker(0.2));
    slider1.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::grey);
    slider1.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    slider1.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(slider1);
    
    wetDryLabel.setText("Wet Mix %", juce::dontSendNotification);
    wetDryLabel.attachToComponent(&slider1, false);
    wetDryLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetDryLabel);
    
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider2.setBounds(220, 205, 175, 175);
    slider2.setRange(10, 500, 1);
    slider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,30);
    slider2.setLookAndFeel(&lookAndFeel4);
    slider2.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan.darker(0.2));
    slider2.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::grey);
    slider2.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    slider2.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(slider2);
    
    modFreqLabel.setText("Modulation Frequency (Hz)", juce::dontSendNotification);
    modFreqLabel.attachToComponent(&slider2, false);
    modFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modFreqLabel);
    
    modWaveSelector.addListener(this);
    modWaveSelector.addItem("Sine",1);
    modWaveSelector.addItem("Square",2);
    modWaveSelector.addItem("Triangle",3);
    modWaveSelector.setBounds(135, 110, 130, 30);
    modWaveSelector.setJustificationType(juce::Justification::centred);
    modWaveSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::grey.darker(0.2));
    modWaveSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::cyan.darker(0.6));
    modWaveSelector.setSelectedId(1);
    addAndMakeVisible(modWaveSelector);
    
    modSelectLabel.setText("Modulation Wave Type", juce::dontSendNotification);
    modSelectLabel.attachToComponent(&modWaveSelector, false);
    modSelectLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modSelectLabel);
    
    title.setText("Evan's Ring Modulator", juce::dontSendNotification);
    title.setBounds(0, 10, 400, 35);
    title.setFont (juce::Font (35.0f, juce::Font::bold));
    title.setColour(juce::Label::ColourIds::textColourId, juce::Colours::cyan.darker(0.2));
    title.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(title);
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


void HomeworkProjectAudioProcessorEditor::comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged){
    if (comboBoxThatHasChanged == &modWaveSelector){
        audioProcessor.setEffect(modWaveSelector.getSelectedId());
    }
}
