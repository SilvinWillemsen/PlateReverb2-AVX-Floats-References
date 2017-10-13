/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PlateReverb2AudioProcessorEditor::PlateReverb2AudioProcessorEditor (PlateReverb2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (800, 440);
    
    //Add listeners to UI controls
    knobsArea.getVolumeControl().addListener (this);
    knobsArea.getDecayControl().addListener (this);
    knobsArea.getCentsControl().addListener (this);
    
    plateArea.getWidthControl().setValue (2);
    plateArea.getHeightControl().setValue (1);
    plateArea.getWidthControl().addListener (this);
    plateArea.getHeightControl().addListener (this);

    knobsArea.getFlangeButtonL().addListener (this);
    knobsArea.getFlangeButtonR().addListener (this);

    knobsArea.getRadiusLX().addListener (this);
    knobsArea.getRadiusLY().addListener (this);
    knobsArea.getRadiusRX().addListener (this);
    knobsArea.getRadiusRY().addListener (this);
    
    knobsArea.getSpeedLX().addListener (this);
    knobsArea.getSpeedLY().addListener (this);
    knobsArea.getSpeedRX().addListener (this);
    knobsArea.getSpeedRY().addListener (this);
    
    knobsArea.getPhaseLX().addListener (this);
    knobsArea.getPhaseLY().addListener (this);
    knobsArea.getPhaseRX().addListener (this);
    knobsArea.getPhaseRY().addListener (this);
    
    knobsArea.getRecalculateL().addListener (this);
    knobsArea.getRecalculateR().addListener (this);
    
    plateArea.getPlate().getInput().getBroadcaster().addListener (this);
    plateArea.getPlate().getOutputL().getBroadcaster().addListener (this);
    plateArea.getPlate().getOutputR().getBroadcaster().addListener (this);
    
    //Make the two sections of the plugin visible
    addAndMakeVisible (&plateArea);
    addAndMakeVisible(&knobsArea);

    
}

PlateReverb2AudioProcessorEditor::~PlateReverb2AudioProcessorEditor()
{
}

//==============================================================================
void PlateReverb2AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
}

void PlateReverb2AudioProcessorEditor::resized()
{
    auto fullArea (getLocalBounds());

    knobsArea.setBounds (fullArea.removeFromRight (170.0f).reduced (5.0f));
    plateArea.setBounds (10, 10, 620, 420);

}

void PlateReverb2AudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &knobsArea.getFlangeButtonL())
    {
        if (plateArea.getPlate().getFlangeCurve().getActiveL() == true)
        {
            knobsArea.getFlangeButtonL().setColour(TextButton::buttonColourId, Colours::red);
            plateArea.getPlate().getOutputL().setVisible (true);
            plateArea.getPlate().getFlangeCurve().setActiveL (false);
            plateArea.getPlate().repaint();
            
            processor.flangingL = false;
            
        } else {
            knobsArea.getFlangeButtonL().setColour(TextButton::buttonColourId, Colours::green);
            plateArea.getPlate().getOutputL().setVisible (false);
            plateArea.getPlate().getFlangeCurve().setActiveL (true);
            plateArea.getPlate().repaint();
            
            processor.flangingL = true;
        }
        
    }
    
    if (button == &knobsArea.getFlangeButtonR())
    {
        if (plateArea.getPlate().getFlangeCurve().getActiveR() == true)
        {
            knobsArea.getFlangeButtonR().setColour(TextButton::buttonColourId, Colours::red);
            plateArea.getPlate().getOutputR().setVisible (true);
            plateArea.getPlate().getFlangeCurve().setActiveR (false);
            plateArea.getPlate().repaint();
            processor.flangingR = false;
            
        } else {
            knobsArea.getFlangeButtonR().setColour(TextButton::buttonColourId, Colours::green);
            plateArea.getPlate().getOutputR().setVisible (false);
            plateArea.getPlate().getFlangeCurve().setActiveR (true);
            plateArea.getPlate().repaint();
            processor.flangingR = true;
        }
        
    }
    
    if (button == &knobsArea.getRecalculateL())
    {
        processor.recalculateLFlag = true;
    }
    
    if (button == &knobsArea.getRecalculateR())
    {
        processor.recalculateRFlag = true;
    }
    
}

void PlateReverb2AudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    processor.gain = knobsArea.getVolumeControl().getValue();
    processor.Lx = plateArea.getWidthControl().getValue();
    processor.Ly = plateArea.getHeightControl().getValue();
    processor.decay = knobsArea.getDecayControl().getValue();
    processor.C = knobsArea.getCentsControl().getValue();
    
    if (slider == &plateArea.getWidthControl())
    {
        processor.stretchFlag = true;
    }
    
    if (slider == &plateArea.getHeightControl())
    {
        processor.stretchFlag = true;
    }
    
    if (slider == &knobsArea.getDecayControl())
    {
        processor.decayFlag = true;
    }
    
    if (slider == &knobsArea.getCentsControl())
    {
        processor.centsFlag = true;
    }
    
    if (slider == &knobsArea.getRadiusLX())
    {
        plateArea.getPlate().getFlangeCurve().setRadiusLX (slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.radiusLX = slider->getValue();
    }
    
    if (slider == &knobsArea.getRadiusLY())
    {
        plateArea.getPlate().getFlangeCurve().setRadiusLY(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.radiusLY = slider->getValue();
    }
    
    if (slider == &knobsArea.getRadiusRX())
    {
        plateArea.getPlate().getFlangeCurve().setRadiusRX(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.radiusRX = slider->getValue();
    }
    
    if (slider == &knobsArea.getRadiusRY())
    {
        plateArea.getPlate().getFlangeCurve().setRadiusRY(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.radiusRY = slider->getValue();
    }
    
    if (slider == &knobsArea.getSpeedLX())
    {
        plateArea.getPlate().getFlangeCurve().setSpeedLX(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.speedLX = slider->getValue();
    }
    
    if (slider == &knobsArea.getSpeedLY())
    {
        plateArea.getPlate().getFlangeCurve().setSpeedLY(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.speedLY = slider->getValue();
    }
    
    if (slider == &knobsArea.getSpeedRX())
    {
        plateArea.getPlate().getFlangeCurve().setSpeedRX(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.speedRX = slider->getValue();
    }
    if (slider == &knobsArea.getSpeedRY())
    {
        plateArea.getPlate().getFlangeCurve().setSpeedRY(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.speedRY = slider->getValue();
    }
    
    if (slider == &knobsArea.getPhaseLX())
    {
        plateArea.getPlate().getFlangeCurve().setPhaseLX(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.phaseLX = slider->getValue();
    }
    
    if (slider == &knobsArea.getPhaseLY())
    {
        plateArea.getPlate().getFlangeCurve().setPhaseLY(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.phaseLY = slider->getValue();
    }
    
    if (slider == &knobsArea.getPhaseRX())
    {
        plateArea.getPlate().getFlangeCurve().setPhaseRX(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.phaseRX = slider->getValue();
    }
    
    if (slider == &knobsArea.getPhaseRY())
    {
        plateArea.getPlate().getFlangeCurve().setPhaseRY(slider->getValue());
        plateArea.getPlate().getFlangeCurve().repaint();
        processor.phaseRY = slider->getValue();
    }
    
    if (slider == &plateArea.getPlate().getInput().getBroadcaster())
    {
        processor.positions.setInput(plateArea.getPlate().getInput().getInputLocation());
        processor.inputChange = true;
    }
    
    if (slider == &plateArea.getPlate().getOutputL().getBroadcaster())
    {
        processor.positions.setOutputL(plateArea.getPlate().getOutputL().getOutputLLocation());
        processor.outputLChange = true;
    }
    
    if (slider == &plateArea.getPlate().getOutputR().getBroadcaster())
    { 
        processor.positions.setOutputR(plateArea.getPlate().getOutputR().getOutputRLocation());
        processor.outputRChange = true;
    }
    
}

