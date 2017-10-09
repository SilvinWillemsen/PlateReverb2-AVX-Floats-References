/*
  ==============================================================================

    PlateArea.h
    Created: 26 Sep 2017 1:10:45pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Plate.h"

//==============================================================================
/*
*/
class PlateArea    : public Component

{
public:
    PlateArea()
    {
        setPaintingIsUnclipped (true);
        addAndMakeVisible (plate);
    }

    ~PlateArea()
    {
    }

    void paint (Graphics& g) override
    {
        ColourGradient backgroundGradient = ColourGradient(Colours::black, getWidth() / 2, getHeight() / 2,
                                                           Colours::darkgrey, getWidth(), getHeight(), true);
        g.setGradientFill(backgroundGradient);
        g.fillRect (getLocalBounds());
    }

    void resized() override
    {
        plate.setBounds (10, 10, 400, 200);
    }
    
    Plate* getPlate() {return &plate;};
    Slider* getWidthControl() {return plate.getWidthControl();};
    Slider* getHeightControl() {return plate.getHeightControl();};

private:
    Plate plate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlateArea)
};
