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
    m_OscMenu.addListener(this);
    
    m_OscValue = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.m_parameters, WT_ID, m_OscMenu);
    
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    m_OscMenu.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    
}
