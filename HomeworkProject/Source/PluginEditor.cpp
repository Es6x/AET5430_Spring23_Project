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
    setSize (415, 415);
    
    bgImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    
    slider1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider1.setBounds(10, 200, 200, 200);
    slider1.setRange(0, 100, 1);
    slider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,30);
    slider1.setLookAndFeel(&lookAndFeel4);
    slider1.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan);
    slider1.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(slider1);
    
    wetDryLabel.setText("Wet Mix %", juce::dontSendNotification);
    wetDryLabel.attachToComponent(&slider1, false);
    wetDryLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetDryLabel);
    
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider2.setBounds(210, 200, 200, 200);
    slider2.setRange(10, 500, 1);
    slider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,30);
    slider2.setLookAndFeel(&lookAndFeel4);
    slider2.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::cyan);
    slider2.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(slider2);
    
    modFreqLabel.setText("Modulation Frequency (Hz)", juce::dontSendNotification);
    modFreqLabel.attachToComponent(&slider2, false);
    modFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modFreqLabel);
    
    modWaveSelector.addListener(this);
    modWaveSelector.addItem("Sine",1);
    modWaveSelector.addItem("Triangle",2);
    modWaveSelector.addItem("Square",3);
    modWaveSelector.setBounds(140, 120, 130, 30);
    modWaveSelector.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modWaveSelector);
    
    modSelectLabel.setText("Modulation Wave Type", juce::dontSendNotification);
    modSelectLabel.attachToComponent(&modWaveSelector, false);
    modSelectLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modSelectLabel);
    
    title.setText("Evan's Ring Modulator", juce::dontSendNotification);
    title.setBounds(0, 10, 415, 35);
    title.setFont (juce::Font (35.0f, juce::Font::bold));
    title.setColour(juce::Label::ColourIds::textColourId, juce::Colours::cyan);
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
    g.drawImageAt(bgImage,0,0);
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
