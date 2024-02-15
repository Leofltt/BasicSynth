/*
  ==============================================================================

    ADSR.cpp
    Created: 2 Dec 2019 4:54:21pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "ADSRUI.h"

//==============================================================================
M_ADSR::M_ADSR(BasicSynthAudioProcessor& p) : processor(p)
{
    setSize(200, 200);
        m_AtkSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        m_AtkSlider.setRange(0.001, 5); //in s
        m_AtkSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_AtkSlider);
        m_AtkValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, ATK_ID,m_AtkSlider);
    
        m_DecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        m_DecaySlider.setRange(0.001, 5); //in s
        m_DecaySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_DecaySlider);
        m_DecValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, DEC_ID,m_DecaySlider);
    
        m_SustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        m_SustainSlider.setRange(0.001, 1);
        m_SustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_SustainSlider);
        m_SusValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, SUS_ID,m_SustainSlider);
    
        m_ReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        m_ReleaseSlider.setRange(0.001, 5); //in s
        m_ReleaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
        addAndMakeVisible(&m_ReleaseSlider);
        m_RelValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, REL_ID,m_ReleaseSlider);
    

}

M_ADSR::~M_ADSR()
{
}

void M_ADSR::paint (juce::Graphics& g)
{
    juce::Rectangle<int> title (0,10,getWidth(),20);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope", title, juce::Justification::centredTop);
    g.drawText("Attack", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("Decay", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("Sustain", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("Release", 128, 150, 20, 20, juce::Justification::centredTop);
    
    juce::Rectangle<float> area (25,25,150,150);
    
    g.setColour(juce::Colours::orangered);
    g.drawRoundedRectangle(area, 20.0f, 1.0f);
}

void M_ADSR::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    m_AtkSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    m_DecaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    m_SustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    m_ReleaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
