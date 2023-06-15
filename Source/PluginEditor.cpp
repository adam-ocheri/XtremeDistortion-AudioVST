/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XDistortionAudioProcessorEditor::XDistortionAudioProcessorEditor (XDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Initialize Sliders
    Knob_Drive = std::make_unique<juce::Slider>("Drive");
    Knob_Range = std::make_unique<juce::Slider>("Range");
    Knob_Mix = std::make_unique<juce::Slider>("Mix");
    Knob_Volume = std::make_unique<juce::Slider>("XFractal");

    addAndMakeVisible(Knob_Drive.get());
    addAndMakeVisible(Knob_Range.get());
    addAndMakeVisible(Knob_Mix.get());
    addAndMakeVisible(Knob_Volume.get());

    Knob_Drive.get()->setSliderStyle(juce::Slider::Rotary);
    Knob_Range.get()->setSliderStyle(juce::Slider::Rotary);
    Knob_Mix.get()->setSliderStyle(juce::Slider::Rotary);
    Knob_Volume.get()->setSliderStyle(juce::Slider::Rotary);

    Knob_Drive.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Knob_Range.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Knob_Mix.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Knob_Volume.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

    // Initialize Slider Attachments
    Attachment_Drive = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Drive", *Knob_Drive.get());
    Attachment_Range = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Range", *Knob_Range.get());
    Attachment_Mix = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Mix", *Knob_Mix.get());
    Attachment_Volume = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "XFractal", *Knob_Volume.get());

    // Initialize Knobs position and layout values
    knobWidth = 100;
    knobHeight = 100;

    currentKnobYPos = ((getHeight() / 2) - (knobHeight / 2));
    driveKnobXPos = ((getWidth() / 5) * 1) - (knobWidth / 2);
    rangeKnobXPos = ((getWidth() / 5) * 2) - (knobWidth / 2);
    mixKnobXPos = ((getWidth() / 5) * 3) - (knobWidth / 2);
    volumeKnobXPos = ((getWidth() / 5) * 4) - (knobWidth / 2);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);


}

XDistortionAudioProcessorEditor::~XDistortionAudioProcessorEditor()
{
}

//==============================================================================
void XDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.drawText("Drive", driveKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Range", rangeKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Mix", mixKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("X-Fractal", volumeKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
}

void XDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    refreshLayout();

    Knob_Drive.get()->setBounds(driveKnobXPos, currentKnobYPos, knobWidth, knobHeight);
    Knob_Range.get()->setBounds(rangeKnobXPos, currentKnobYPos, knobWidth, knobHeight);
    Knob_Mix.get()->setBounds(mixKnobXPos, currentKnobYPos, knobWidth, knobHeight);
    Knob_Volume.get()->setBounds(volumeKnobXPos, currentKnobYPos, knobWidth, knobHeight);
}

void XDistortionAudioProcessorEditor::refreshLayout()
{
    knobWidth = 100;
    knobHeight = 100;

    currentKnobYPos = ((getHeight() / 2) - (knobHeight / 2));
    driveKnobXPos = ((getWidth() / 5) * 1) - (knobWidth / 2);
    rangeKnobXPos = ((getWidth() / 5) * 2) - (knobWidth / 2);
    mixKnobXPos = ((getWidth() / 5) * 3) - (knobWidth / 2);
    volumeKnobXPos = ((getWidth() / 5) * 4) - (knobWidth / 2);
}
