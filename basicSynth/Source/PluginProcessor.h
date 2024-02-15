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
#define WT1_ID "wavetype osc1"
#define WT1_NAME "Waveform Type osc1"
#define WT2_ID "wavetype osc2"
#define WT2_NAME "Waveform Type osc2"
#define CF_ID "cutoff_freq"
#define CF_NAME "Cutoff Frequency"
#define RES_ID "resonance"
#define RES_NAME "Resonance"
#define FT_ID "filter_type"
#define FT_NAME "Filter Type"
#define BL_ID "osc_mix"
#define BL_NAME "Oscillator Mix"

//==============================================================================
/**
*/
class BasicSynthAudioProcessor  : public juce::AudioProcessor
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

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateFilterParams(float cf, float res);
    
    juce::AudioProcessorValueTreeState m_parameters;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
private:
    
    float t_atkTime;
    float t_decayTime;
    float t_sustainLevel;
    float t_releaseTime;
    
    juce::LinearSmoothedValue<float> smoothATK { 0.0f};
    juce::LinearSmoothedValue<float> smoothDEC { 1.0f};
    juce::LinearSmoothedValue<float> smoothSUS { 0.0f};
    juce::LinearSmoothedValue<float> smoothREL { 0.0f};
    juce::LinearSmoothedValue<float> smoothRES { 0.50f};
    juce::LinearSmoothedValue<float> smoothCF { 20000.0f};
    juce::LinearSmoothedValue<float> smoothBLEND { 0.0f};
    
    using SVF = juce::dsp::StateVariableFilter::Filter<float>;
    using Filter = juce::dsp::IIR::Filter<float>;
    
    juce::dsp::ProcessorDuplicator<SVF, juce::dsp::StateVariableFilter::Parameters<float>> svf;
    
    juce::Synthesiser synth;
    SynthVoice* synthvox;
    
    double lastSR;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicSynthAudioProcessor)
};
