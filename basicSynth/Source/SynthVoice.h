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
        env1_params.attack = 0.001 * *atk;
        env1_params.decay = 0.001 * *decay;
        env1_params.sustain = *sustain;
        env1_params.release = 0.001 * *release;

    }

    double setWT(int i)
    {
        if(wt[i] == 0)
            return v_osc[i].sinewave(frequency);
        if(wt[i] == 1)
            return v_osc[i].saw(frequency);
        if(wt[i] == 2)
            return v_osc[i].square(frequency);
        else
            return v_osc[i].sinewave(frequency);
    }
    
    double setOscillators()
    {
        return setWT(0) * (1 - m_blend) + setWT(1) * m_blend;
    }
    
    void getWT(float* wt1, float *wt2)
    {
        wt[0] = *wt1;
        wt[1] = *wt2;
    }
    
    void getBlend(float* blend)
       {
           m_blend = *blend;
       }
    
    void startNote(int midinotenumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPos)
    {
        m_env1.noteOn();
        amplitude = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midinotenumber);
    }
    
    void stopNote(float velocity, bool allowTailOff)
    {
        m_env1.noteOff();
        
        if (velocity == 0)
           clearCurrentNote();
    }
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
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
                outputBuffer.addSample(chan, startSample, m_env1.getNextSample() * setOscillators() * amplitude);
            }
            
            ++startSample;
        }
        
    }

private:
    
    double amplitude;
    double frequency;
    double m_blend;
    
    maxiOsc m_osc;
    
    ADSR m_env1;
    ADSR::Parameters env1_params;

    std::vector <maxiOsc> v_osc {m_osc, m_osc};
    std::vector <float> wt {0,0};

    
    
};
