/*
  ==============================================================================

    Filter.cpp
    Created: 2 Dec 2019 8:36:01pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#include "FilterUI.h"


//==============================================================================
Filter::Filter(BasicSynthAudioProcessor& p) : processor(p)
{
    setSize(200, 200);
    
    m_filterMenu.addItem("Low Pass", 1);
    m_filterMenu.addItem("High Pass", 2);
    m_filterMenu.addItem("Band Pass", 3);
    m_filterMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&m_filterMenu);
    m_ftValue = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processor.m_parameters, FT_ID, m_filterMenu);
    
    cf.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cf.setRange(10.0f, 19000.0f);
    cf.setSkewFactorFromMidPoint(1000);
    cf.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
    cf.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&cf);
    m_CutoffValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, CF_ID, cf);
    
    res.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    res.setPopupDisplayEnabled(true, true, this);
    res.setRange(0, 5);
    res.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
    addAndMakeVisible(&res);
    m_ResonanceValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.m_parameters, RES_ID, res);
    
}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{
    juce::Rectangle<int> title (0,10,getWidth(), 20);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter",title, juce::Justification::centredTop);
    
    juce::Rectangle<float> area (25,25,150,150);
    
    g.setColour(juce::Colours::orange);
    g.drawRoundedRectangle(area, 20.0f, 1.0f);
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    m_filterMenu.setBounds(area.removeFromTop(20));
    cf.setBounds(30, 100, 70, 70);
    res.setBounds(100, 100, 70, 70);
    
    
}
