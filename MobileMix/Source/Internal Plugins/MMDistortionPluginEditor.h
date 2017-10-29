/*
  ==============================================================================

    MMDistortionPluginEditor.h
    Created: 15 Sep 2017 11:01:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "MMDistortionPlugin.h"
#include "../Core/MobileMixPluginInstanceEditor.h"

class MMDistortionPluginEditor :
    public MobileMixPluginInstanceEditor
{
public:
    MMDistortionPluginEditor(MMDistortionPlugin& processor);
    ~MMDistortionPluginEditor();

protected:
    void resized() override;

private:
    MMSliderAttachment gainSliderAttachment;

    MMParameterSlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MMDistortionPluginEditor)
};
