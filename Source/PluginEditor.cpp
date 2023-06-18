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
   

    // Initialize Knobs position and layout values - - - - - - - - 
    knobWidth = 100;
    knobHeight = 100;

    currentKnobYPos = ((getHeight() / 2) - (knobHeight / 2));
    driveKnobXPos = ((getWidth() / 5) * 1) - (knobWidth / 2);
    rangeKnobXPos = ((getWidth() / 5) * 2) - (knobWidth / 2);
    mixKnobXPos = ((getWidth() / 5) * 3) - (knobWidth / 2);
    volumeKnobXPos = ((getWidth() / 5) * 4) - (knobWidth / 2);

    InitializeAll();

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1400, 900);


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
    g.setFont (75.0f);
    
    const int titleWidth = 700;
    g.drawFittedText("FRACTAL DISTORTION", getWidth() / 2 - (titleWidth / 2), getHeight() / 2 - 200, titleWidth, 100, juce::Justification::centred, 1);

    g.setFont(15.0f);
    g.drawText("Drive", driveKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Range", rangeKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Mix", mixKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("X-Fractal", volumeKnobXPos, getHeight() / 2 + 5, knobWidth, knobHeight, juce::Justification::centred, false);

    g.drawText("X_Min", driveKnobXPos, getHeight() / 2 + 155, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("X_Max", rangeKnobXPos, getHeight() / 2 + 155, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Y_Min", mixKnobXPos, getHeight() / 2 + 155, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Y_Max", volumeKnobXPos, getHeight() / 2 + 155, knobWidth, knobHeight, juce::Justification::centred, false);

    g.drawText("Crystal", driveKnobXPos, getHeight() / 2 + 310, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Multiplier", rangeKnobXPos, getHeight() / 2 + 310, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Power", mixKnobXPos, getHeight() / 2 + 310, knobWidth, knobHeight, juce::Justification::centred, false);
    g.drawText("Complexity", volumeKnobXPos, getHeight() / 2 + 310, knobWidth, knobHeight, juce::Justification::centred, false);
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

    X_Min.get()->setBounds(driveKnobXPos, currentKnobYPos + 150, knobWidth, knobHeight);
    X_Max.get()->setBounds(rangeKnobXPos, currentKnobYPos + 150, knobWidth, knobHeight);
    Y_Min.get()->setBounds(mixKnobXPos, currentKnobYPos + 150, knobWidth, knobHeight);
    Y_Max.get()->setBounds(volumeKnobXPos, currentKnobYPos + 150, knobWidth, knobHeight);

    Knob_Crystallize.get()->setBounds(driveKnobXPos, currentKnobYPos + 300, knobWidth, knobHeight);
    Knob_Multiplier.get()->setBounds(rangeKnobXPos, currentKnobYPos + 300, knobWidth, knobHeight);
    Knob_Power.get()->setBounds(mixKnobXPos, currentKnobYPos + 300, knobWidth, knobHeight);
    Knob_Complexity.get()->setBounds(volumeKnobXPos, currentKnobYPos + 300, knobWidth, knobHeight);
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

void XDistortionAudioProcessorEditor::InitializeAll()
{
    InitializeSliders_Drive();
    InitializeSliders_Fractal();
    InitializeSliders_Crystal();
}

void XDistortionAudioProcessorEditor::InitializeSliders_Drive()
{
    // Initialize Sliders - Drive  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
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

    // Initialize Slider Attachments - - - - - - - - 
    Attachment_Drive = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Drive", *Knob_Drive.get());
    Attachment_Range = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Range", *Knob_Range.get());
    Attachment_Mix = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Mix", *Knob_Mix.get());
    Attachment_Volume = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "XFractal", *Knob_Volume.get());
}

void XDistortionAudioProcessorEditor::InitializeSliders_Fractal()
{
    // Initialize Sliders - Fractal  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    X_Min = std::make_unique<juce::Slider>("X_Min");
    X_Max = std::make_unique<juce::Slider>("X_Max");
    Y_Min = std::make_unique<juce::Slider>("Y_Min");
    Y_Max = std::make_unique<juce::Slider>("Y_Max");

    addAndMakeVisible(X_Min.get());
    addAndMakeVisible(X_Max.get());
    addAndMakeVisible(Y_Min.get());
    addAndMakeVisible(Y_Max.get());

    X_Min.get()->setSliderStyle(juce::Slider::Rotary);
    X_Max.get()->setSliderStyle(juce::Slider::Rotary);
    Y_Min.get()->setSliderStyle(juce::Slider::Rotary);
    Y_Max.get()->setSliderStyle(juce::Slider::Rotary);

    X_Min.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    X_Max.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Y_Min.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Y_Max.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

    // Initialize Slider Attachments - - - - - - - - 
    Attachment_X_Min = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "X_Min", *X_Min.get());
    Attachment_X_Max = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "X_Max", *X_Max.get());
    Attachment_Y_Min = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Y_Min", *Y_Min.get());
    Attachment_Y_Max = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Y_Max", *Y_Max.get());
}

void XDistortionAudioProcessorEditor::InitializeSliders_Crystal()
{
    // Initialize Sliders - Fractal  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    Knob_Crystallize = std::make_unique<juce::Slider>("Crystal");
    Knob_Multiplier = std::make_unique<juce::Slider>("Multiplier");
    Knob_Power = std::make_unique<juce::Slider>("Power");
    Knob_Complexity = std::make_unique<juce::Slider>("Complexity");

    addAndMakeVisible(Knob_Crystallize.get());
    addAndMakeVisible(Knob_Multiplier.get());
    addAndMakeVisible(Knob_Power.get());
    addAndMakeVisible(Knob_Complexity.get());

    Knob_Crystallize.get()->setSliderStyle(juce::Slider::Rotary);
    Knob_Multiplier.get()->setSliderStyle(juce::Slider::Rotary);
    Knob_Power.get()->setSliderStyle(juce::Slider::Rotary);
    Knob_Complexity.get()->setSliderStyle(juce::Slider::Rotary);

    Knob_Crystallize.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Knob_Multiplier.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Knob_Power.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    Knob_Complexity.get()->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);

    // Initialize Slider Attachments - - - - - - - - 
    Attachment_Crystallize = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Crystal", *Knob_Crystallize.get());
    Attachment_Multiplier = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Multiplier", *Knob_Multiplier.get());
    Attachment_Power = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Power", *Knob_Power.get());
    Attachment_Complexity = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.GetValueTreeState(), "Complexity", *Knob_Complexity.get());
}
