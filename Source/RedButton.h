/*
  ==============================================================================

    RedButton.h
    Created: 4 Oct 2017 11:10:47am
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class RedButton    : public Component
{
public:
    RedButton()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~RedButton()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */
        g.setColour (Colours::red);
        g.setOpacity(opacity);
        g.fillRect (getLocalBounds());

    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

    void setOpacity(float value) {opacity = value;};
    
private:
    float opacity = 0.0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedButton)
};
