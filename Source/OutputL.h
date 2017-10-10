/*
 ==============================================================================
 
 OutputL.h
 Created: 27 Sep 2017 3:07:09pm
 Author:  Silvin Willemsen
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class OutputL    : public Component
{
public:
    OutputL()
    {
        setPaintingIsUnclipped(true);
    }
    
    ~OutputL()
    {
    }
    
    void paint (Graphics& g) override
    {
        g.setColour (Colours::black);
        g.drawEllipse(0, 0, 10, 10, 1);
        g.setColour (Colours::white);
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
        outputLLocation.setX (static_cast<double> (getBounds().getX() + 5) / (getParentWidth()));
        outputLLocation.setY (static_cast<double> (getBounds().getY() + 5) / (getParentHeight()));
        broadcaster.setValue(e.x * e.y);
    }
    
    void mouseUp (const MouseEvent& e) override
    {
        outputLLocation.setX (static_cast<double> (getBounds().getX() + 5) / (getParentWidth()));
        outputLLocation.setY (static_cast<double> (getBounds().getY() + 5) / (getParentHeight()));
        broadcaster.setValue(1);
    }
    
    LocationOnPlate& getOutputLLocation() { return outputLLocation; };
    void setOutputLLocation (LocationOnPlate outputLLocationToBeSet) { outputLLocation = outputLLocationToBeSet; };
    Slider& getBroadcaster() { return broadcaster; };
    
private:
    LocationOnPlate outputLLocation;
    Slider broadcaster;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputL)
};
