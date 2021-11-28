/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthAudioProcessor::BasicSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
m_parameters(*this, nullptr, "PARAMETERS", createParameterLayout())

#endif
{
    m_parameters.state = ValueTree("savedParams");
    synth.clearVoices();
    
    for (int i = 0; i < 8; i++)
        synth.addVoice(new SynthVoice());
    
    synth.clearSounds();
    synth.addSound(new SynthSound());
    
}
AudioProcessorValueTreeState::ParameterLayout BasicSynthAudioProcessor::createParameterLayout(){
    
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    std::vector<std::unique_ptr<RangedAudioParameter>> t_params;
    
    auto filterRange = NormalisableRange<float> (10.0f, 19000.0f);
    filterRange.setSkewForCentre(1000);
    
    auto t_atkParam = std::make_unique<AudioParameterFloat>(ATK_ID, ATK_NAME, 0.001f, 5.0f,0.1f);
    auto t_decayParam = std::make_unique<AudioParameterFloat>(DEC_ID, DEC_NAME, 0.001f, 5.0f,0.5f);
    auto t_sustainParam = std::make_unique<AudioParameterFloat>(SUS_ID, SUS_NAME, 0.001f, 1.0f,0.7f);
    auto t_releaseParam = std::make_unique<AudioParameterFloat>(REL_ID, REL_NAME, 0.001f, 5.0f,0.1f);
    
    auto t_waveType = std::make_unique<AudioParameterFloat>(WT1_ID, WT1_NAME,0,3,0);
    
    auto t_waveType2 = std::make_unique<AudioParameterFloat>(WT2_ID, WT2_NAME,0,3,0);
    
    auto t_cutoffFreq = std::make_unique<AudioParameterFloat>(CF_ID, CF_NAME,filterRange, 1000.0f);
    auto t_resonance = std::make_unique<AudioParameterFloat>(RES_ID, RES_NAME,0.0f,5.0f,1.0f);
    
    auto t_filterType = std::make_unique<AudioParameterFloat>(FT_ID, FT_NAME,0,2,0);
    
    auto t_blend = std::make_unique<AudioParameterFloat>(BL_ID, BL_NAME,0,1,0);
    
    //    juce::StringArray filterString;
    //    filterString.add("LPF");
    //    filterString.add("BPF");
    //    filterString.add("HPF");
    //    filterString.add("NOTCH");
    //
    //    auto filterTypeParam = std::make_unique<AudioParameterChoice>(FT_ID, FT_NAME, filterString, 0);
    
    t_params.push_back(std::move(t_atkParam));
    t_params.push_back(std::move(t_decayParam));
    t_params.push_back(std::move(t_sustainParam));
    t_params.push_back(std::move(t_releaseParam));
    t_params.push_back(std::move(t_waveType));
    t_params.push_back(std::move(t_cutoffFreq));
    t_params.push_back(std::move(t_resonance));
    t_params.push_back(std::move(t_filterType));
    t_params.push_back(std::move(t_waveType2));
    t_params.push_back(std::move(t_blend));
    
    
    return { t_params.begin(), t_params.end() };
}

BasicSynthAudioProcessor::~BasicSynthAudioProcessor()
{
}

//==============================================================================
const String BasicSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String BasicSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void BasicSynthAudioProcessor::updateFilterParams()
{
    int menuChoice = *m_parameters.getRawParameterValue(FT_ID);
    float coff = *m_parameters.getRawParameterValue(CF_ID);
    float reso = *m_parameters.getRawParameterValue(RES_ID);
    
    if (menuChoice == 0)
        svf.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    else if (menuChoice == 1)
        svf.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
    else if (menuChoice == 2)
        svf.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
    else
        svf.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    
    svf.state->setCutOffFrequency(lastSR, coff, reso);
}

//==============================================================================
void BasicSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    t_atkTime = *m_parameters.getRawParameterValue(ATK_ID);
    t_decayTime = *m_parameters.getRawParameterValue(DEC_ID);
    t_releaseTime = *m_parameters.getRawParameterValue(REL_ID);
    t_sustainLevel = *m_parameters.getRawParameterValue(SUS_ID);
    
    ignoreUnused(samplesPerBlock);
    lastSR = sampleRate;
    synth.setCurrentPlaybackSampleRate(lastSR);
    dsp::ProcessSpec spec;
    spec.numChannels = getMainBusNumOutputChannels();
    spec.sampleRate = lastSR;
    spec.maximumBlockSize = samplesPerBlock;
    
    svf.reset();
    updateFilterParams();
    svf.prepare(spec);
}

void BasicSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    for(int i = 0; i <synth.getNumVoices(); i++)
    {
        if((synthvox = dynamic_cast<SynthVoice*>(synth.getVoice(i))))
        {
            synthvox->setADSRsampleRate(lastSR);
        synthvox->getADSR(m_parameters.getRawParameterValue(ATK_ID)->load(),m_parameters.getRawParameterValue(DEC_ID)->load(),m_parameters.getRawParameterValue(SUS_ID)->load(),m_parameters.getRawParameterValue(REL_ID)->load());
        synthvox->getWT(m_parameters.getRawParameterValue(WT1_ID)->load(),m_parameters.getRawParameterValue(WT2_ID)->load());
            synthvox->getBlend(m_parameters.getRawParameterValue(BL_ID)->load());
        }
    }
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
       
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
   
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    dsp::AudioBlock<float> ablock (buffer);
    updateFilterParams();
    svf.process(dsp::ProcessContextReplacing<float> (ablock));

}

//==============================================================================
bool BasicSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BasicSynthAudioProcessor::createEditor()
{
    return new BasicSynthAudioProcessorEditor (*this);
}

//==============================================================================
void BasicSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    std::unique_ptr <XmlElement> xml (m_parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void BasicSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr <XmlElement> t_parameters(getXmlFromBinary(data, sizeInBytes));
       
    if (t_parameters != nullptr) {
        if (t_parameters -> hasTagName(m_parameters.state.getType())) m_parameters.state = ValueTree::fromXml(*t_parameters);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicSynthAudioProcessor();
}
