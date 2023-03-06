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
    setSize (417, 419);
    
    bgImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    
    slider1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider1.setBounds(50, 50, 200, 200);
    slider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0,0);
    slider1.setLookAndFeel(&largeKnobLNF);
    addAndMakeVisible(slider1);
    
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider2.setBounds(300, 300, 100, 100);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0,0);
    slider2.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(slider2);
    
    effectSelector.addListener(this);
    effectSelector.addItem("None",1);
    effectSelector.addItem("Gain",2);
    effectSelector.setBounds(300, 50, 150, 50);
    addAndMakeVisible(effectSelector);
    
    
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
    if (comboBoxThatHasChanged == &effectSelector){
        audioProcessor.setEffect(effectSelector.getSelectedId());
    }
}
