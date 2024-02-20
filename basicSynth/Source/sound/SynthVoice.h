/*
  ==============================================================================

    SynthVoice.h
    Created: 19 Nov 2019 2:26:45pm
    Author:  Leonardo Foletto

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "PolyBLEPOscillator.h"


class SynthVoice : public juce::SynthesiserVoice {
public:
    
    bool canPlaySound (juce::SynthesiserSound* sound) {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void setADSRsampleRate(double sr) {
        m_env1.setSampleRate(sr);
        
    }
    
    void getADSR(float atk, float decay, float sustain, float release) {
        env1_params.attack =  atk;
        env1_params.decay =  decay;
        env1_params.sustain = sustain;
        env1_params.release =  release;

    }

    double setOsc(int i) {
        return v_osc[i].getNextSample();
    }
    
    double oscNextSample() {
        auto bl = m_blend.load();
        auto freq = frequency.load();
        for (int i = 0; i < 3; i++)
        {
            v_osc[i].setFreq(freq);
        }
        v_osc[0].setWF(wt[0]);
        v_osc[1].setWF(wt[1]);
        auto sub_lev = 0.5;
        return setOsc(0) * (1 - bl) + setOsc(1) * bl + setOsc(2) * sub_lev;
    }
    
    void getWT(float wt1, float wt2) {
        wt[0] = wt1;
        wt[1] = wt2;
        wt[2] = 0;
    }
    
    void getBlend(float blend) {
           m_blend.store(blend);
       }

    void getPitchBend(int pw) {
        float pb = (pw * 2 / 16383) - 1;
        m_pitchBend.store(pb);
    }
    
    void startNote(int midinotenumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPos) {
        m_env1.noteOn();
        amplitude.store(velocity);
        frequency.store(juce::MidiMessage::getMidiNoteInHertz(midinotenumber));
    }
    
    void stopNote(float velocity, bool allowTailOff) {
        m_env1.noteOff();
        
        if (velocity == 0)
           clearCurrentNote();
    }
    
    void pitchWheelMoved (int newPitchWheelValue) {

        getPitchBend(newPitchWheelValue);
        
        auto oldF = frequency.load();
        auto pB = m_pitchBend.load();
        
        frequency.store(oldF  * std::pow(2, pB * 2 / 12 ));
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue) { 
    }
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
        m_env1.setParameters(env1_params);
        for (int sam = 0; sam < numSamples; ++sam) {
            auto amp = amplitude.load();
            for (int chan = 0; chan < outputBuffer.getNumChannels(); ++chan) {
                outputBuffer.addSample(chan, startSample, m_env1.getNextSample() * oscNextSample() * amp);
            }   
            ++startSample;
        }   
    }

private:
    
    std::atomic<double> amplitude;
    std::atomic<double> frequency;
    std::atomic<double> m_blend;
    std::atomic<double> m_pitchBend;
    static_assert(std::atomic<double>::is_always_lock_free);
    
    PolyBLEPOscillator m_osc;
    
    juce::ADSR m_env1;
    juce::ADSR::Parameters env1_params;

    std::vector <PolyBLEPOscillator> v_osc {m_osc, m_osc, m_osc};
    std::vector <int> wt {0,0,0};

    
    
};
