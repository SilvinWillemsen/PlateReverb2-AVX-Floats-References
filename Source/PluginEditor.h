/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PlateArea.h"
#include "KnobsArea.h"


//==============================================================================
/**
*/
class PlateReverb2AudioProcessorEditor  : public AudioProcessorEditor,
                                          private Slider::Listener,
                                          private Button::Listener
{
public:
    PlateReverb2AudioProcessorEditor (PlateReverb2AudioProcessor&);
    ~PlateReverb2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void setRedButtonOpacity(float value) {knobsArea.getRedButton().setOpacity(value);};
    
private:
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button* button) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PlateReverb2AudioProcessor& processor;
    PlateArea plateArea;
    KnobsArea knobsArea;
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlateReverb2AudioProcessorEditor)
};

