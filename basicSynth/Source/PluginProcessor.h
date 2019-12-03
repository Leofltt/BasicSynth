/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#define ATK_ID "atk_time"
#define ATK_NAME "Atk Time"
#define DEC_ID "dec_time"
#define DEC_NAME "Decay Time"
#define SUS_ID "sustain"
#define SUS_NAME "Sustain Level"
#define REL_ID "rel_time"
#define REL_NAME "Release Time"
#define WT_ID "wavetype"
#define WT_NAME "Waveform Type"
#define CF_ID "cutoff_freq"
#define CF_NAME "Cutoff Frequency"
#define RES_ID "resonance"
#define RES_NAME "Resonance"
#define FT_ID "filter_type"
#define FT_NAME "Filter Type"

//==============================================================================
/**
*/
class BasicSynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BasicSynthAudioProcessor();
    ~BasicSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float t_atkTime;
    float t_decayTime;
    float t_sustainLevel;
    float t_releaseTime;
    
    AudioProcessorValueTreeState m_parameters;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
private:
    
    Synthesiser synth;
    SynthVoice* synthvox;
    
    double lastSR;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthAudioProcessor)
};
