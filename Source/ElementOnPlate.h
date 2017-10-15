/*
  ==============================================================================

    ElementOnPlate.h
    Created: 15 Oct 2017 4:59:06pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CBCInOuts.h"

//==============================================================================
/*
*/
class ElementOnPlate    : public Component
{
public:
    ElementOnPlate(Colour colour) : colour(colour)
    {
        setPaintingIsUnclipped (true);
    }
    
    ~ElementOnPlate()
    {
    }
    
    void paint (Graphics& g) override
    {
        
        g.setColour (Colours::black);
        g.drawEllipse(0, 0, 10, 10, 1);
        g.setColour (colour);
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
        getParentComponent()->repaint();
        myDragger.dragComponent (this, e, &cbc);
        location.setX (static_cast<double> (getBounds().getX() + 5) / (getParentWidth()));
        location.setY (static_cast<double> (getBounds().getY() + 5) / (getParentHeight()));
        broadcaster.setValue(e.x * e.y);
    }
    
    void mouseUp (const MouseEvent& e) override
    {
        location.setX (static_cast<double> (getBounds().getX() + 5) / (getParentWidth()));
        location.setY (static_cast<double> (getBounds().getY() + 5) / (getParentHeight()));
        broadcaster.setValue(1);
    }
    
    LocationOnPlate& getLocation() { return location; };
    void setLocation (LocationOnPlate locationToBeSet) { location = locationToBeSet; };
    Slider& getBroadcaster() { return broadcaster; };
    
private:
    LocationOnPlate location;
    Slider broadcaster;
    CBCInOuts cbc;
    Colour colour;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ElementOnPlate)
};
