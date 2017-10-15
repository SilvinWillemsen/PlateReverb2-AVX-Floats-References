/*
  ==============================================================================

    FlangeCurve.h
    Created: 29 Sep 2017 11:58:07am
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FlangeCurve    : public Component
{
public:
    FlangeCurve()
    {
    }

    ~FlangeCurve()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour (Colours::white);
        g.setOpacity (0.5);
        const float detail (1000.0);
        
        if (activeL) //if the left microphone is moving, draw its path according to the UI controls
        {
            Path wavePathL;
            wavePathL.startNewSubPath (getWidth() * (radiusLX * sin (phaseLX) + 0.5), getHeight() * (radiusLY * sin (phaseLY) + 0.5));
            for (float t = 0; t <= detail; ++t)
            {
                wavePathL.lineTo (getWidth() * (radiusLX * sin (speedLX * 2 * double_Pi * t / detail + + phaseLX) + 0.5),
                                  getHeight() * (radiusLY * sin (speedLY * 2 * double_Pi * t / detail + phaseLY) + 0.5));
            }
            g.setColour (Colours::black);
            g.setOpacity(0.5);
            g.strokePath (wavePathL, PathStrokeType (5.0f));
            g.setColour (Colours::white);
            g.setOpacity(0.8);
            g.strokePath (wavePathL, PathStrokeType (4.5f));
        }
        
        if (activeR) //if the left microphone is moving, draw its path according to the UI controls
        {
            Path wavePathR;
            wavePathR.startNewSubPath (getWidth() * (radiusRX * sin (phaseRX) + 0.5), getHeight() * (radiusRY * sin (phaseRY) + 0.5));
            for (float t = 0; t <= detail; ++t)
            {
                wavePathR.lineTo (getWidth() * (radiusRX * sin (speedRX * 2 * double_Pi * t / detail + phaseRX) + 0.5),
                                  getHeight() * (radiusRY * sin (speedRY * 2 * double_Pi * t / detail + phaseRY) + 0.5));
                
            }
            g.setColour (Colours::black);
            g.setOpacity(0.5);
            g.strokePath (wavePathR, PathStrokeType (5.0f));
            g.setColour (Colours::red);
            g.setOpacity(0.5);
            g.strokePath (wavePathR, PathStrokeType (4.5f));
        }
    }

    void resized() override
    {
    }
    
    void setActiveL (bool active) { activeL = active; };
    void setActiveR (bool active) { activeR = active; };
    
    void setRadiusLX (float radius) { radiusLX = radius; };
    void setRadiusLY (float radius) { radiusLY = radius; };
    void setSpeedLX (float speed) { speedLX = speed; };
    void setSpeedLY (float speed) { speedLY = speed; };
    void setPhaseLX (float phase) { phaseLX = phase; };
    void setPhaseLY (float phase) { phaseLY = phase; };
    
    void setRadiusRX (float radius) { radiusRX = radius; };
    void setRadiusRY (float radius) { radiusRY = radius; };
    void setSpeedRX (float speed) { speedRX = speed; };
    void setSpeedRY (float speed) { speedRY = speed; };
    void setPhaseRX (float phase) { phaseRX = phase; };
    void setPhaseRY (float phase) { phaseRY = phase; };
    
    bool getActiveL() { return activeL; };
    bool getActiveR() { return activeR; };
    
    float getRadiusLX() { return radiusLX; };
    float getRadiusLY() { return radiusLY; };
    float getSpeedLX() { return speedLX; };
    float getSpeedLY() { return speedLY; };
    float getPhaseLX() { return phaseLX; };
    float getPhaseLY() { return phaseLY; };
    
    float getRadiusRX() { return radiusRX; };
    float getRadiusRY() { return radiusRY; };
    float getSpeedRX() { return speedRX; };
    float getSpeedRY() { return speedRY; };
    float getPhaseRX() { return phaseRX; };
    float getPhaseRY() { return phaseRY; };

private:
    
    bool activeL = false;
    bool activeR = false;
    
    float radiusLX = 0.4;
    float radiusLY = 0.4;
    float speedLX = 2;
    float speedLY = 3;
    float phaseLX = 0;
    float phaseLY = 0.5 * float_Pi;

    float radiusRX = 0.4;
    float radiusRY = 0.4;
    float speedRX = 1;
    float speedRY = 1;
    float phaseRX = 0;
    float phaseRY = 0.5 * float_Pi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangeCurve)
};
