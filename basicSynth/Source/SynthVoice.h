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
#include "maximilian.h"


class SynthVoice : public SynthesiserVoice
{
public:
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void setADSRsampleRate(double sr)
    {
        m_env1.setSampleRate(sr);
        
    }
    
    void getADSR(float* atk, float* decay, float* sustain, float* release)
    {
        env1_params.attack =  *atk;
        env1_params.decay =  *decay;
        env1_params.sustain = *sustain;
        env1_params.release =  *release;

    }

    double setWT(int i)
    {
        auto freq = frequency.load();
        
        if(wt[i] == 0)
            return v_osc[i].sinewave(freq);
        if(wt[i] == 1)
            return v_osc[i].saw(freq);
        if(wt[i] == 2)
            return v_osc[i].square(freq);
        else
            return v_osc[i].sinewave(freq);
    }
    
    double setOscillators()
    {
        auto bl = m_blend.load();
        return setWT(0) * (1 - bl) + setWT(1) * bl;
    }
    
    void getWT(float* wt1, float *wt2)
    {
        wt[0] = *wt1;
        wt[1] = *wt2;
    }
    
    void getBlend(float* blend)
       {
           m_blend.store(*blend);
       }

    void getPitchBend(int pw)
    {
        float pb = (pw * 2 / 16383) - 1;
        m_pitchBend.store(pb);
    }
    
    void startNote(int midinotenumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPos)
    {
        m_env1.noteOn();
        amplitude.store(velocity);
        frequency.store(MidiMessage::getMidiNoteInHertz(midinotenumber));
    }
    
    void stopNote(float velocity, bool allowTailOff)
    {
        m_env1.noteOff();
        
        if (velocity == 0)
           clearCurrentNote();
    }
    
    void pitchWheelMoved (int newPitchWheelValue)
    {

        getPitchBend(newPitchWheelValue);
        
        auto oldF = frequency.load();
        auto pB = m_pitchBend.load();
        
        frequency.store(oldF  * std::pow(2, pB * 2 * 100 / 1200 ));
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        m_env1.setParameters(env1_params);
        
        for (int sam = 0; sam < numSamples; ++sam)
        {
           
            auto amp = amplitude.load();
            
            for (int chan = 0; chan < outputBuffer.getNumChannels(); ++chan)
            {
                outputBuffer.addSample(chan, startSample, m_env1.getNextSample() * setOscillators() * amp);
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
    
    maxiOsc m_osc;
    
    ADSR m_env1;
    ADSR::Parameters env1_params;

    std::vector <maxiOsc> v_osc {m_osc, m_osc};
    std::vector <float> wt {0,0};

    
    
};
