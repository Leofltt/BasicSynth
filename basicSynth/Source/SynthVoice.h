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
        if(wt[i] == 0)
            return v_osc[i].sinewave(frequency.load());
        if(wt[i] == 1)
            return v_osc[i].saw(frequency.load());
        if(wt[i] == 2)
            return v_osc[i].square(frequency.load());
        else
            return v_osc[i].sinewave(frequency.load());
    }
    
    double setOscillators()
    {
        return setWT(0) * (1 - m_blend.load()) + setWT(1) * m_blend.load();
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
        if (pw >= 8192)
            m_pitchBend.store(float(pw - 8192) / (16383 - 8192));
        
        else
            m_pitchBend.store(float(8192 - pw) / -8192);
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
        
        frequency.store(oldF  * std::pow(2, m_pitchBend.load() * 2 * 100 / 1200 ));
    }
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        m_env1.setParameters(env1_params);
        
        for (int sam = 0; sam < numSamples; ++sam)
        {
           
            
            for (int chan = 0; chan < outputBuffer.getNumChannels(); ++chan)
            {
                outputBuffer.addSample(chan, startSample, m_env1.getNextSample() * setOscillators() * amplitude.load());
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
