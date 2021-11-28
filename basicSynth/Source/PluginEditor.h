/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OscillatorUI.h"
#include "ADSRUI.h"
#include "FilterUI.h"

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
    
    OscillatorUI m_OscGUI;
    M_ADSR m_adsrGUI;
    Filter m_filterGUI;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthAudioProcessorEditor)
};
