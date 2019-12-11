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
class M_ADSR    : public Component
{
public:
    M_ADSR(BasicSynthAudioProcessor&);
    ~M_ADSR();

    void paint (Graphics&) override;
    void resized() override;
    

private:
    BasicSynthAudioProcessor& processor;
    
    Slider m_AtkSlider;
    Slider m_DecaySlider;
    Slider m_SustainSlider;
    Slider m_ReleaseSlider;

    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> m_AtkValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> m_DecValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> m_SusValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> m_RelValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (M_ADSR)
};
