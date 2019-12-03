/*
  ==============================================================================

    Oscillator.h
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
class Oscillator    : public Component,
                      private ComboBox::Listener
{
public:
    Oscillator(BasicSynthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;

private:
    ComboBox m_OscMenu;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> m_OscValue;
    
    BasicSynthAudioProcessor& processor;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
