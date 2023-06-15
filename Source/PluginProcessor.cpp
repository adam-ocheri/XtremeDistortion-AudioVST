/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Fractalizer.h"

//==============================================================================
XDistortionAudioProcessor::XDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Get All Sliders States
    ValueTreeState = std::make_unique<juce::AudioProcessorValueTreeState>(*this, nullptr);

    // - - - - Drive Parameters
    ValueTreeState.get()->createAndAddParameter("Drive", "Drive", "Drive", juce::NormalisableRange<float>(0.1f, 1.0f, 0.000001f), 1.0f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Range", "Range", "Range", juce::NormalisableRange<float>(0.1f, 3000.0f, 0.000001f), 1.0f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Mix", "Mix", "Mix", juce::NormalisableRange<float>(0.0f, 1.0f, 0.000001f), 1.0f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("XFractal", "XFractal", "XFractal", juce::NormalisableRange<float>(0.000001f, 1.0f, 0.000001f), 1.0f, nullptr, nullptr);

    ValueTreeState.get()->state = juce::ValueTree("Drive");
    ValueTreeState.get()->state = juce::ValueTree("Range");
    ValueTreeState.get()->state = juce::ValueTree("Mix");
    ValueTreeState.get()->state = juce::ValueTree("XFractal");

    // - - - - Fractal Parameters
    ValueTreeState.get()->createAndAddParameter("X_Min", "X_Min", "X_Min", juce::NormalisableRange<float>(-2.5f, 1.5f, 0.000001f), -2.5f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("X_Max", "X_Max", "X_Max", juce::NormalisableRange<float>(1.5f, 3.0f, 0.000001f), 1.5f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Y_Min", "Y_Min", "Y_Min", juce::NormalisableRange<float>(-2.0f, 2.0f, 0.000001f), -2.0f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Y_Max", "Y_Max", "Y_Max", juce::NormalisableRange<float>(0.000001f, 3.0f, 0.000001f), 2.0f, nullptr, nullptr);

    ValueTreeState.get()->state = juce::ValueTree("X_Min");
    ValueTreeState.get()->state = juce::ValueTree("X_Max");
    ValueTreeState.get()->state = juce::ValueTree("Y_Min");
    ValueTreeState.get()->state = juce::ValueTree("Y_Max");

    // - - - - Crystal Parameters
    ValueTreeState.get()->createAndAddParameter("Crystal", "Crystal", "Crystal", juce::NormalisableRange<float>(0.f, 1.f, 0.000001f), 1.f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Multiplier", "Multiplier", "Multiplier", juce::NormalisableRange<float>(1.f, 300.0f, 0.000001f), 1.f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Power", "Power", "Power", juce::NormalisableRange<float>(1.0f, 42.0f, 0.000001f), 1.0f, nullptr, nullptr);
    ValueTreeState.get()->createAndAddParameter("Complexity", "Complexity", "Complexity", juce::NormalisableRange<float>(10.0f, 200.0f, 1.0f), 100.f, nullptr, nullptr);

    ValueTreeState.get()->state = juce::ValueTree("Crystal");
    ValueTreeState.get()->state = juce::ValueTree("Multiplier");
    ValueTreeState.get()->state = juce::ValueTree("Power");
    ValueTreeState.get()->state = juce::ValueTree("Complexity");
}

XDistortionAudioProcessor::~XDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String XDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool XDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool XDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool XDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double XDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int XDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int XDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String XDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void XDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void XDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void XDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool XDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void XDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    // Pi value
    const float PI = std::atanf(1.0f) * 4;

    // - - Drive params
    float drive = *ValueTreeState.get()->getRawParameterValue("Drive");
    float range = *ValueTreeState.get()->getRawParameterValue("Range");
    float mix = *ValueTreeState.get()->getRawParameterValue("Mix");
    float volume = *ValueTreeState.get()->getRawParameterValue("XFractal");

    // - - Fractal params
    float x_min = *ValueTreeState.get()->getRawParameterValue("X_Min");
    float x_max = *ValueTreeState.get()->getRawParameterValue("X_Max");
    float y_min = *ValueTreeState.get()->getRawParameterValue("Y_Min");
    float y_max = *ValueTreeState.get()->getRawParameterValue("Y_Max");

    // - - Crystal params
    float crystal = *ValueTreeState.get()->getRawParameterValue("Crystal");
    float cMultiplier = *ValueTreeState.get()->getRawParameterValue("Multiplier");
    float cPower = *ValueTreeState.get()->getRawParameterValue("Power");
    float cComplexity = *ValueTreeState.get()->getRawParameterValue("Complexity");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    Fractalizer* Fractal = new Fractalizer(3, buffer.getNumSamples(), x_min, x_max, y_min, y_max, cComplexity);
    Fractal->Fractalize();


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        
        float fractal = 0.0f; 
        float complex = 0.00001f;

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //calculate fractal
            //complex = (complex + complex) * (complex + complex);
            complex += 0.00001f;

            float crystallizedSignal = (((cPower) / pow((PI * 2), cPower)) * atan(*channelData * (cMultiplier / (PI * 2)))) * crystal;
            fractal += sin(Fractal->Fractals[channel + 1][sample] * complex - (crystallizedSignal)) * volume;

            // Process Audio manipulation
            float cleanSignal = *channelData;
            *channelData = (*channelData * drive * (range + ((fractal * fractal) * ((PI * 2) * fractal))));                         //* (range + (fractal * fractal));                                                            // Overdrive the sample
            float distortedSignal = (2.0f / PI) * atan(*channelData );                                                  // Clip the sample within the +1 to -1 range
            
            *channelData = (((distortedSignal * mix) + (cleanSignal * (1.0f - mix))) - (crystallizedSignal * mix) / 2.0f) * 1;//volume                 // Interpolate Dry/Wet value (get the avg. of the two signals)

            channelData++;
        }
    }
}

//==============================================================================
bool XDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* XDistortionAudioProcessor::createEditor()
{
    return new XDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void XDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::MemoryOutputStream stream(destData, false);
    ValueTreeState.get()->state.writeToStream(stream);
}

void XDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    juce::ValueTree valueTree = juce::ValueTree::readFromData(data, sizeInBytes);

    if (valueTree.isValid())
    {
        ValueTreeState.get()->state = valueTree;
    }
}

juce::AudioProcessorValueTreeState& XDistortionAudioProcessor::GetValueTreeState()
{
    return *ValueTreeState.get();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XDistortionAudioProcessor();
}
