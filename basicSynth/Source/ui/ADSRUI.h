/*
  ==============================================================================

    ADSR.h
    Created: 2 Dec 2019 4:54:21pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class M_ADSR    : public juce::Component
{
public:
    M_ADSR(BasicSynthAudioProcessor&);
    ~M_ADSR();

    void paint (juce::Graphics&) override;
    void resized() override;
    

private:
    BasicSynthAudioProcessor& processor;
    
    juce::Slider m_AtkSlider;
    juce::Slider m_DecaySlider;
    juce::Slider m_SustainSlider;
    juce::Slider m_ReleaseSlider;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> m_AtkValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> m_DecValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> m_SusValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> m_RelValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M_ADSR)
};
