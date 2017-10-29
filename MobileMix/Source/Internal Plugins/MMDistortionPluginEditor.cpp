/*
  ==============================================================================

    MMDistortionPluginEditor.cpp
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MMDistortionPluginEditor.h"

MMDistortionPluginEditor::MMDistortionPluginEditor(MMDistortionPlugin& processor) :
    MobileMixPluginInstanceEditor(processor)
{
    gainSliderAttachment = createSliderAttachment(processor.paramDistortion->paramID, gainSlider);
    addAndMakeVisible(gainSlider);
}

MMDistortionPluginEditor::~MMDistortionPluginEditor()
{

}

void MMDistortionPluginEditor::resized()
{
    gainSlider.setBounds(10, 10, getWidth() / 10, getHeight() - 20);
}
