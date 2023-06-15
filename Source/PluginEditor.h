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

    // Drive Parametes  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    std::unique_ptr<juce::Slider> Knob_Drive;
    std::unique_ptr<juce::Slider> Knob_Range;
    std::unique_ptr<juce::Slider> Knob_Mix;
    std::unique_ptr<juce::Slider> Knob_Volume;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Drive;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Range;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Mix;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Volume;

    // Drive Parametes Layout attributes - - - - - - - - - - -  
    int knobWidth;
    int knobHeight;

    int currentKnobYPos;
    int driveKnobXPos;
    int rangeKnobXPos;
    int mixKnobXPos;
    int volumeKnobXPos;

    // Fractal Parametes  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    std::unique_ptr<juce::Slider> X_Min;
    std::unique_ptr<juce::Slider> X_Max;
    std::unique_ptr<juce::Slider> Y_Min;
    std::unique_ptr<juce::Slider> Y_Max;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_X_Min;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_X_Max;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Y_Min;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Y_Max;

    // Crystal Parametes  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    std::unique_ptr<juce::Slider> Knob_Crystallize;
    std::unique_ptr<juce::Slider> Knob_Multiplier;
    std::unique_ptr<juce::Slider> Knob_Power;
    std::unique_ptr<juce::Slider> Knob_Complexity;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Crystallize;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Multiplier;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Power;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> Attachment_Complexity;

    void refreshLayout();
    void InitializeAll();
    void InitializeSliders_Drive();
    void InitializeSliders_Fractal();
    void InitializeSliders_Crystal();
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    XDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XDistortionAudioProcessorEditor)
};
