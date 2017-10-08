/*
  ==============================================================================

    MobileMixPluginFormat.cpp
    Created: 25 Sep 2017 12:34:59am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginFormat.h"

#include "../Internal Plugins/MMPlugins.h"

MobileMixPluginFormat::MobileMixPluginFormat(AudioProcessorValueTreeState& _state) :
    state(_state)
{
    gainDesc = MMGainPlugin(state).getPluginDescription();
    compressorDesc = MMCompressorPlugin(state).getPluginDescription();
    reverbDesc = MMReverbPlugin(state).getPluginDescription();
    distortionDesc = MMDistortionPlugin(state).getPluginDescription();
    eqDesc = MMEQPlugin(state).getPluginDescription();
}

void MobileMixPluginFormat::getAllPluginsInExpectedParameterOrder(OwnedArray<PluginDescription>& array)
{
    array.add(new PluginDescription(gainDesc));
    array.add(new PluginDescription(compressorDesc));
    array.add(new PluginDescription(reverbDesc));
    array.add(new PluginDescription(distortionDesc));
    array.add(new PluginDescription(eqDesc));
}

void MobileMixPluginFormat::createPluginInstance(const PluginDescription& desc,
                                                 double initialSampleRate,
                                                 int initialBufferSize,
                                                 void* userData,
                                                 void (*callback)(void*, AudioPluginInstance*, const String&))
{
    if (desc.isDuplicateOf(gainDesc))
        callback(userData, new MMGainPlugin(state), String());
    else if (desc.isDuplicateOf(compressorDesc))
        callback(userData, new MMCompressorPlugin(state), String());
    else if (desc.isDuplicateOf(reverbDesc))
        callback(userData, new MMReverbPlugin(state), String());
    else if (desc.isDuplicateOf(distortionDesc))
        callback(userData, new MMDistortionPlugin(state), String());
    else if (desc.isDuplicateOf(eqDesc))
        callback(userData, new MMEQPlugin(state), String());
}
