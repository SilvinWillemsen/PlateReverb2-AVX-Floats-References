/*
  ==============================================================================

    CBC.h
    Created: 26 Sep 2017 4:19:41pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class CBC    : public ComponentBoundsConstrainer
{
public:
    CBC()
    {
        setSizeLimits (200, 100, 600, 400);
    }
    
    CBC(int width, int height)
    {
        setMinimumOnscreenAmounts(1000, 1000, 1000, 1000);
    }

    ~CBC()
    {
    }

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CBC)
};
