/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthAudioProcessorEditor::BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), m_OscGUI(p), m_adsrGUI(p), m_filterGUI(p)
{

    setSize (600, 300);
    
    addAndMakeVisible(&m_OscGUI);
    addAndMakeVisible(&m_adsrGUI);
    addAndMakeVisible(&m_filterGUI);
}

BasicSynthAudioProcessorEditor::~BasicSynthAudioProcessorEditor()
{
}

//==============================================================================
void BasicSynthAudioProcessorEditor::paint (Graphics& g)
{
 
    g.fillAll(Colours::black);

    
}

void BasicSynthAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    m_OscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    m_adsrGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    m_filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

}


