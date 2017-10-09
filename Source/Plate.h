/*
  ==============================================================================

    Plate.h
    Created: 26 Sep 2017 1:10:56pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CBC.h"
#include "Input.h"
#include "OutputL.h"
#include "OutputR.h"
#include "ElementOnPlate.h"
#include "PlateResizer.h"
#include "FlangeCurve.h"

#include <sstream>
#include <iomanip>

//==============================================================================
/*
*/
class Plate    : public Component
{
public:
    Plate()
    {
        PlatePositions positions;
        input.setInputLocation (positions.getInput());
        outputL.setOutputLLocation (positions.getOutputL());
        outputR.setOutputRLocation (positions.getOutputR());
        addAndMakeVisible (flangeCurve);
        addAndMakeVisible (input);
        addAndMakeVisible (outputL);
        addAndMakeVisible (outputR);
        
        plateResizer.setParent(this);
        addChildComponent (plateResizer);
        addAndMakeVisible (plateResizer);
    }

    ~Plate()
    {
    }

    void paint (Graphics& g) override
    {

        ColourGradient leftEdge (Colours::black, 0, 0, Colours::lightgrey, 5, 0, false);
        g.setGradientFill (leftEdge);
        g.fillRect (0, 5, 5, getHeight() - 10);
        
        ColourGradient rightEdge (Colours::black, getWidth(), 0, Colours::lightgrey, getWidth() - 5, 0, false);
        g.setGradientFill (rightEdge);
        g.fillRect (getWidth() - 5, 5, getWidth(), getHeight() - 10);
        
        ColourGradient bottomEdge (Colours::black, 0, getHeight(), Colours::lightgrey, 0, getHeight() - 5, false);
        g.setGradientFill (bottomEdge);
        g.fillRect (5, getHeight() - 5, getWidth() - 10, getHeight());
        
        ColourGradient topEdge (Colours::black, 0, 0, Colours::lightgrey, 0, 5, false);
        g.setGradientFill (topEdge);
        g.fillRect (5, 0, getWidth()-10, 5);
        
        double gradientVar = sin (1.0 / 4.0 * double_Pi) * 5;
        
        ColourGradient topLeft (Colours::lightgrey, 5, 5, Colours::black, 5 - gradientVar, 5 - gradientVar, true);
        g.setGradientFill (topLeft);
        g.fillRect (0, 0, 5, 5);
        
        ColourGradient topRight (Colours::lightgrey, getWidth()-5, 5, Colours::black, getWidth()-5+gradientVar, 5-gradientVar, true);
        g.setGradientFill (topRight);
        g.fillRect (getWidth()-5, 0, getWidth(), 5);

        ColourGradient bottomRight (Colours::lightgrey, getWidth() - 5, getHeight() - 5,
                                    Colours::black, getWidth() - 5 + gradientVar, getHeight() - 5 + gradientVar, true);
        g.setGradientFill (bottomRight);
        g.fillRect (getWidth() - 5, getHeight() - 5, getWidth(), getHeight());
        
        ColourGradient bottomLeft (Colours::lightgrey, 5, getHeight() - 5,
                                   Colours::black, 5 - gradientVar, getHeight() - 5 + gradientVar, true);
        g.setGradientFill(bottomLeft);
        g.fillRect (0, getHeight() - 5,
                    5, getHeight());
        
        ColourGradient colourGradient (Colours::white, widthControl.getValue() * 100, 0,
                                       Colours::darkgrey, widthControl.getValue() * 100, 400, true);
        g.setGradientFill (colourGradient);
        
        g.fillRect (plateBounds);
        
        std::ostringstream widthString;
        std::ostringstream heightString;
        
        if (getLocalBounds().getWidth() < 200.0)
        {
            (widthString << std::setprecision (2) << getWidth() / 200.0);
        } else {
            (widthString << std::setprecision (3) << getWidth() / 200.0);
        }
        
        if (getLocalBounds().getHeight() < 200.0)
        {
            (heightString << std::setprecision (2) << getHeight() / 200.0);
        } else {
            (heightString << std::setprecision (3) << getHeight() / 200.0);
        }
            
        String currentSizeAsString = widthString.str() + " x " + heightString.str() + " m";

        g.setColour (Colours::white);
        Font helv;
        helv.setTypefaceName("Helvetica");
        g.setFont(helv);
        g.drawText(currentSizeAsString, getWidth() - 120, getHeight() - 35, 100, 20, Justification::bottomRight);
    }
    
    void resized() override
    {
        widthControl.setValue(getWidth() / 200.0);
        heightControl.setValue(getHeight() / 200.0);
        plateBounds.setBounds(getX() - 5, getY() - 5, getWidth() - 10, getHeight() - 10);
        plateResizer.setBounds(getWidth() - 10, getHeight() - 10, 10, 10);
        input.setBounds(input.getInputLocation().getX() * getWidth() - 5, input.getInputLocation().getY() * getHeight() - 5, 10, 10);
        outputL.setBounds(outputL.getOutputLLocation().getX() * getWidth() - 5, outputL.getOutputLLocation().getY() * getHeight() - 5, 10, 10);
        outputR.setBounds(outputR.getOutputRLocation().getX() * getWidth() - 5, outputR.getOutputRLocation().getY() * getHeight() - 5, 10, 10);
        flangeCurve.setBounds(plateBounds);
    }

    Slider* getWidthControl() {return &widthControl;};
    Slider* getHeightControl() {return &heightControl;};
            
    Input* getInput() {return &input;};
    OutputL* getOutputL() {return &outputL;};
    OutputR* getOutputR() {return &outputR;};
    FlangeCurve* getFlangeCurve() {return &flangeCurve;};
        
private:
    Slider widthControl;
    Slider heightControl;
    Input input;
    OutputL outputL;
    OutputR outputR;
    PlateResizer plateResizer;
    FlangeCurve flangeCurve;
    CBC cbc;
    Rectangle<int> plateBounds;
            
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Plate)
};
