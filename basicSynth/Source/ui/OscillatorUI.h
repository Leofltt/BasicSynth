/*
  ==============================================================================

    PolyBLEPOscillator.h
    Created: 2 Dec 2019 3:41:42pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class OscillatorUI    : public juce::Component,
                      private juce::ComboBox::Listener
{
public:
    OscillatorUI(BasicSynthAudioProcessor&);
    ~OscillatorUI();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(juce::ComboBox*) override;

private:
    juce::ComboBox m_OscMenu;
    juce::ComboBox m_OscMenu2;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_Osc1Value;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_Osc2Value;
    
    juce::Slider m_BlendSlider;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> m_BlendValue;
    
    
    BasicSynthAudioProcessor& processor;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorUI)
};
