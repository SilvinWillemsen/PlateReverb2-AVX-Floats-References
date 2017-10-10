/*
 ==============================================================================
 
 OutputR.h
 Created: 28 Sep 2017 11:02:29am
 Author:  Silvin Willemsen
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class OutputR    : public Component
{
public:
    OutputR()
    {
        setPaintingIsUnclipped(true);
    }
    
    ~OutputR()
    {
    }
    
    void paint (Graphics& g) override
    {
        g.setColour (Colours::black);
        g.drawEllipse(0, 0, 10, 10, 1);
        
        g.setColour (Colours::red);
        
        g.fillEllipse(0.5, 0.5, 9, 9);
    }
    
    void resized() override
    {
    }
    
    ComponentDragger myDragger;
    void mouseDown (const MouseEvent& e) override
    {
        myDragger.startDraggingComponent (this, e);
        broadcaster.setValue(0);
        
    }
    
    void mouseDrag (const MouseEvent& e) override
    {
        getParentComponent() -> repaint();
        CBC cbc (getParentWidth(), getParentHeight());
        myDragger.dragComponent (this, e, &cbc);
        outputRLocation.setX (static_cast<double> (getBounds().getX() + 5) / (getParentWidth()));
        outputRLocation.setY (static_cast<double> (getBounds().getY() + 5) / (getParentHeight()));
        broadcaster.setValue(e.x * e.y);
    }
    
    void mouseUp (const MouseEvent& e) override
    {
        outputRLocation.setX (static_cast<double> (getBounds().getX() + 5) / (getParentWidth()));
        outputRLocation.setY (static_cast<double> (getBounds().getY() + 5) / (getParentHeight()));
        broadcaster.setValue(1);
    }
    
    LocationOnPlate& getOutputRLocation() { return outputRLocation; };
    void setOutputRLocation (LocationOnPlate outputRLocationToBeSet) { outputRLocation = outputRLocationToBeSet; };
    Slider& getBroadcaster() { return broadcaster; };
    
private:
    LocationOnPlate outputRLocation;
    Slider broadcaster;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputR)
};


