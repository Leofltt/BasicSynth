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
    
    void getADSR(float* atk, float* decay, float* sustain, float* release)
    {
        m_env1.setAttack(*atk);
        m_env1.setDecay(*decay);
        m_env1.setSustain(*sustain);
        m_env1.setRelease(*release);
        
    }
    
    double setADSR()
    {
        return m_env1.adsr(setWT(), m_env1.trigger);
    }

    double setWT()
    {
        if(t_wt == 0)
            return m_osc1.sinewave(frequency);
        if(t_wt == 1)
            return m_osc1.saw(frequency);
        if(t_wt == 2)
            return m_osc1.square(frequency);
        else
            return m_osc1.sinewave(frequency);
    }
    
    void getWT(float* wt)
    {
        t_wt = *wt;
    }
    
    void startNote(int midinotenumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPos)
    {
        m_env1.trigger = 1;
        amplitude = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midinotenumber);
    }
    
    void stopNote(float velocity, bool allowTailOff)
    {
        m_env1.trigger = 0;
        
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
        
        
        for (int sam = 0; sam < numSamples; ++sam)
        {
           
            
            for (int chan = 0; chan < outputBuffer.getNumChannels(); ++chan)
            {
                outputBuffer.addSample(chan, startSample, setADSR() * amplitude);
            }
            
            ++startSample;
        }
        
    }

private:
    
    double amplitude;
    double frequency;
    maxiOsc m_osc1;
    maxiEnv m_env1;
    float t_wt;

    
};
