/*
  ==============================================================================

    PlateResizer.h
    Created: 26 Sep 2017 4:14:01pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CBC.h"
#include "ElementOnPlate.h"
//==============================================================================
/*
*/
class PlateResizer    : public ResizableCornerComponent
{
public:
    PlateResizer() : ResizableCornerComponent(this, &cbc)
    {
        
    }
    
    PlateResizer(Component* parComp) : ResizableCornerComponent(parComp, &cbc)
    {
        
    }
    
    ~PlateResizer()
    {
    }
    
    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
         draws some placeholder text to get you started.
         
         You should replace everything in this method with your own
         drawing code..
         */
        //ColourGradient cornerGradient(Colours::darkgrey, 5, 5, Colours::lightgrey, 10, 10, true);
        //g.setGradientFill(cornerGradient);
        g.setColour(Colours::white);
        g.fillRect (getLocalBounds());   // draw an outline around the component
        
        Path arrows;
        arrows.addTriangle (2, 2, getWidth()-3, 2, 2, getHeight()-3);
        arrows.addTriangle (getWidth()-2, 3, getWidth()-2, getHeight()-2, 3, getHeight()-2);
        g.setColour(Colours::black);
        g.fillPath (arrows);
    }
    
    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        
    }

private:
    CBC cbc;
    Component* parComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlateResizer)
};
