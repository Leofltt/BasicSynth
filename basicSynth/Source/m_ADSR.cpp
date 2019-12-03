/*
  ==============================================================================

    ADSR.cpp
    Created: 2 Dec 2019 4:54:21pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "m_ADSR.h"

//==============================================================================
M_ADSR::M_ADSR(BasicSynthAudioProcessor& p) : processor(p)
{
    setSize(200, 200);
        m_AtkSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        m_AtkSlider.setRange(0.001, 5000); //in ms
        m_AtkSlider.setTextBoxStyle(Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_AtkSlider);
        m_AtkValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, ATK_ID,m_AtkSlider);
    
        m_DecaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        m_DecaySlider.setRange(0.001, 5000); //in ms
        m_DecaySlider.setTextBoxStyle(Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_DecaySlider);
        m_DecValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, DEC_ID,m_DecaySlider);
    
        m_SustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        m_SustainSlider.setRange(0.001, 1);
        m_SustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_SustainSlider);
        m_SusValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, SUS_ID,m_SustainSlider);
    
        m_ReleaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
        m_ReleaseSlider.setRange(0.001, 5000); //in ms
        m_ReleaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_ReleaseSlider);
        m_RelValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, REL_ID,m_ReleaseSlider);
    

}

M_ADSR::~M_ADSR()
{
}

void M_ADSR::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void M_ADSR::resized()
{
    //Rectangle<int> area = getLocalBounds().reduced(40);
    
    m_AtkSlider.setBounds(10,10,40,100);
    m_DecaySlider.setBounds(60,10,40,100);
    m_SustainSlider.setBounds(110,10,40,100);
    m_ReleaseSlider.setBounds(160,10,40,100);
 
}
