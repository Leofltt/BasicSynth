/*
  ==============================================================================

    Filter.h
    Created: 2 Dec 2019 8:36:01pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(BasicSynthAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;
    

private:
    BasicSynthAudioProcessor& processor;
    
    Slider cf;
    Slider res;
    ComboBox m_filterMenu;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_CutoffValue;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_ResonanceValue;

    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> m_ftValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
