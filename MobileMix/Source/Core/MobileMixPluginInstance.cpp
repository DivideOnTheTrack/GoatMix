/*
  ==============================================================================

    MobileMixPluginInstance.cpp
    Created: 15 Sep 2017 11:04:56am
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "MobileMixPluginInstance.h"

MobileMixPluginInstance::MobileMixPluginInstance(AudioProcessor& rootProcessor,
                                                 ValueTree& parentState) :
    AudioPluginInstance(BusesProperties()
                        .withInput("Input",  AudioChannelSet::stereo())
                        .withOutput("Output", AudioChannelSet::stereo())),
    state(rootProcessor, parentState)
{
}

MobileMixPluginInstance::~MobileMixPluginInstance()
{
}

AudioProcessorValueTreeState& MobileMixPluginInstance::getParameterState()
{
    return state.state;
}

void MobileMixPluginInstance::registerParameters()
{
    paramBypass = getParameterState().createAndAddParameter(addPrefixToParameterName("Bypass"),
                                                            addPrefixToParameterName("Bypass"),
                                                            "",
                                                            NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                            0.0f,
                                                            [](float value){ return (value != 1.0f) ? NEEDS_TRANS("False") : NEEDS_TRANS("True"); },
                                                            nullptr);
}

void MobileMixPluginInstance::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID == paramBypass->paramID)
    {
        assert(newValue == 0.0f || newValue == 1.0f);
        (newValue == 1.0f) ? suspendProcessing(true) : suspendProcessing(false);
    }
}

void MobileMixPluginInstance::fillInPluginDescription(PluginDescription &description) const
{
    description.name = getName();
    description.uid = description.name.hashCode();
    description.pluginFormatName = "Internal";
    description.manufacturerName = JucePlugin_Manufacturer;
    description.version = JucePlugin_VersionString;
    description.isInstrument = false;
}

void MobileMixPluginInstance::releaseResources()
{
}

bool MobileMixPluginInstance::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return (layouts.getMainInputChannelSet() == getBusesLayout().getMainInputChannelSet()) &&
        (layouts.getMainOutputChannelSet() == getBusesLayout().getMainOutputChannelSet());
}

bool MobileMixPluginInstance::hasEditor() const
{
    return true;
}

bool MobileMixPluginInstance::acceptsMidi() const
{
    return false;
}

bool MobileMixPluginInstance::producesMidi() const
{
    return false;
}

double MobileMixPluginInstance::getTailLengthSeconds() const
{
    return 0.0;
}

int MobileMixPluginInstance::getNumPrograms()
{
    return 1; // Required by some hosts (as opposed to 0)
}

int MobileMixPluginInstance::getCurrentProgram()
{
    return 0;
}

void MobileMixPluginInstance::setCurrentProgram(int index)
{
}

const String MobileMixPluginInstance::getProgramName(int index)
{
    return {};
}

void MobileMixPluginInstance::changeProgramName(int index, const String& newName)
{
}

void MobileMixPluginInstance::getStateInformation(MemoryBlock& destData)
{
    std::unique_ptr<XmlElement> xml(getParameterState().state.createXml());
    assert(xml);
    copyXmlToBinary(*xml, destData);
}

void MobileMixPluginInstance::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    assert(xml);
    getParameterState().state = ValueTree::fromXml(*xml);
}

const String MobileMixPluginInstance::addPrefixToParameterName(StringRef name) const
{
    return getName() + ": " + name;
}

void MobileMixPluginInstance::finalizeParametersAndAddToParentState()
{
    state.finalizeParametersAndAddToParent(getName());
}
