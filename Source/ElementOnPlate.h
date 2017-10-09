/*
  ==============================================================================

    ElementOnPlate.h
    Created: 30 Sep 2017 2:53:17pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ElementOnPlate    : public Component
{
public:
    ElementOnPlate()
    {
        parComp = this;
    }

    ~ElementOnPlate()
    {
    }
    
        void paint (Graphics& g) override
    {
    }

    void resized() override
    {
    }

    void setParComp (Component* component) {parComp = component;};
    Component* getParComp() {return parComp;};
    
private:
    Component* parComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ElementOnPlate)
};
