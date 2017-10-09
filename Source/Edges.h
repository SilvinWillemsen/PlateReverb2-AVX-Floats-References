/*
  ==============================================================================

    Edges.h
    Created: 27 Sep 2017 7:07:15pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Edges    : public Component
{
public:
    Edges()
    {
        //setPaintingIsUnclipped(true);

        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~Edges()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */


    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Edges)
};
