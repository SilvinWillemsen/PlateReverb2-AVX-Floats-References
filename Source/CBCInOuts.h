/*
  ==============================================================================

    CBCInOuts.h
    Created: 15 Oct 2017 4:36:04pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class CBCInOuts    : public ComponentBoundsConstrainer
{
public:
    CBCInOuts()
    {
        setMinimumOnscreenAmounts(1000, 1000, 1000, 1000);
    }

    ~CBCInOuts()
    {
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CBCInOuts)
};
