/*
  ==============================================================================

    PolyBLEPOscillator.cpp
    Created: 2 Dec 2019 3:41:42pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorUI.h"

//==============================================================================
OscillatorUI::OscillatorUI(BasicSynthAudioProcessor& p) : processor(p) {
    setSize(200, 200);
    
    m_OscMenu.setJustificationType(juce::Justification::centred);
    m_OscMenu.addItem("Sine", 1);
    m_OscMenu.addItem("Saw", 2);
    m_OscMenu.addItem("Square", 3);
    m_OscMenu.addItem("Triangle", 4);
    m_OscMenu.addItem("Cosine", 5);
    m_OscMenu.addItem("Ramp", 6);
    m_OscMenu.addItem("PW Rect", 7);
    addAndMakeVisible(&m_OscMenu);
    
    m_OscMenu2.setJustificationType(juce::Justification::centred);
    m_OscMenu2.addItem("Sine", 1);
    m_OscMenu2.addItem("Saw", 2);
    m_OscMenu2.addItem("Square", 3);
    m_OscMenu2.addItem("Triangle", 4);
    m_OscMenu2.addItem("Cosine", 5);
    m_OscMenu2.addItem("Ramp", 6);
    m_OscMenu2.addItem("PW Rect", 7);
    addAndMakeVisible(&m_OscMenu2);
    
    m_BlendSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_BlendSlider.setRange(0.0, 1.0);
    m_BlendSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
    m_BlendSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&m_BlendSlider);
    
    m_Osc1Value = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (processor.m_parameters, WT1_ID, m_OscMenu);
    m_Osc2Value = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (processor.m_parameters, WT2_ID, m_OscMenu2);
    m_BlendValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (processor.m_parameters, BL_ID, m_BlendSlider);
}

OscillatorUI::~OscillatorUI() {
}

void OscillatorUI::paint (juce::Graphics& g) {
    juce::Rectangle<int> title (0, 10, getWidth(), 20);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("PolyBLEP Oscillator",title, juce::Justification::centredTop);
    
    juce::Rectangle<float> area (25,25,150,150);
    
    g.setColour(juce::Colours::red);
    g.drawRoundedRectangle(area, 20.0f, 1.0f);
    
}

void OscillatorUI::resized() {
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    m_OscMenu.setBounds(area.removeFromTop(20));
    m_OscMenu2.setBounds(area.removeFromTop(20));
    
    m_BlendSlider.setBounds(area.removeFromTop(75));
}

void OscillatorUI::comboBoxChanged(juce::ComboBox* box) {  
}
