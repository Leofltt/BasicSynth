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
    
    m_OscValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment> (processor.m_parameters, WT_ID, m_OscMenu);
    
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
    
    g.setColour(Colours::darkseagreen);
    g.drawRoundedRectangle(area, 20.0f, 1.0f);
    
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    m_OscMenu.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    
}
