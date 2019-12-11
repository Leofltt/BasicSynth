/*
  ==============================================================================

    Oscillator.cpp
    Created: 2 Dec 2019 3:41:42pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(BasicSynthAudioProcessor& p) : processor(p)
{
    setSize(200, 200);
    
    m_OscMenu.setJustificationType(Justification::centred);
    m_OscMenu.addItem("Sine", 1);
    m_OscMenu.addItem("Saw", 2);
    m_OscMenu.addItem("Square", 3);
    addAndMakeVisible(&m_OscMenu);
    
    m_OscMenu2.setJustificationType(Justification::centred);
    m_OscMenu2.addItem("Sine", 1);
    m_OscMenu2.addItem("Saw", 2);
    m_OscMenu2.addItem("Square", 3);
    addAndMakeVisible(&m_OscMenu2);
    
    m_BlendSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    m_BlendSlider.setRange(0.0, 1.0);
    m_BlendSlider.setTextBoxStyle(Slider::NoTextBox, true, 40, 20);
    m_BlendSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&m_BlendSlider);
    
    m_Osc1Value = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (processor.m_parameters, WT1_ID, m_OscMenu);
    m_Osc2Value = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (processor.m_parameters, WT2_ID, m_OscMenu2);
    m_BlendValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.m_parameters, BL_ID, m_BlendSlider);
    
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    Rectangle<int> title (0, 10, getWidth(), 20);
    
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator",title, Justification::centredTop);
    
    Rectangle<float> area (25,25,150,150);
    
    g.setColour(Colours::red);
    g.drawRoundedRectangle(area, 20.0f, 1.0f);
    
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    m_OscMenu.setBounds(area.removeFromTop(20));
    m_OscMenu2.setBounds(area.removeFromTop(20));
    
    m_BlendSlider.setBounds(area.removeFromTop(75));
   
    

}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    
}
