/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "m_ADSR.h"
#include "Filter.h"

//==============================================================================
/**
*/
class BasicSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor&);
    ~BasicSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    
private:
    
    BasicSynthAudioProcessor& processor;
    
    Oscillator m_OscGUI;
    M_ADSR m_adsrGUI;
    Filter m_filterGUI;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthAudioProcessorEditor)
};
