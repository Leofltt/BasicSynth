/*
  ==============================================================================

    Filter.h
    Created: 2 Dec 2019 8:36:01pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Filter    : public juce::Component
{
public:
    Filter(BasicSynthAudioProcessor&);
    ~Filter();

    void paint (juce::Graphics&) override;
    void resized() override;
    

private:
    BasicSynthAudioProcessor& processor;
    
    
    juce::Slider cf;
    juce::Slider res;
    juce::ComboBox m_filterMenu;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_CutoffValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_ResonanceValue;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_ftValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
