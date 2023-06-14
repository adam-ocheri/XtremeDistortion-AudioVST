/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class XDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XDistortionAudioProcessorEditor (XDistortionAudioProcessor&);
    ~XDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    std::unique_ptr<juce::Slider> Knob_Drive;
    std::unique_ptr<juce::Slider> Knob_Range;
    std::unique_ptr<juce::Slider> Knob_Mix;
    std::unique_ptr<juce::Slider> Knob_Volume;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Drive;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Range;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Mix;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Volume;

    // Layout attributes
    int knobWidth;
    int knobHeight;

    int currentKnobYPos;
    int driveKnobXPos;
    int rangeKnobXPos;
    int mixKnobXPos;
    int volumeKnobXPos;

    void refreshLayout();
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    XDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XDistortionAudioProcessorEditor)
};
