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
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
    }

    ~FlangeCurve()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour (Colours::white);
        g.setOpacity (0.5);
        const float detail (1000.0);
        
        if (getActiveL() == true)
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
        
        if (activeR == true)
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
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    inline void setActiveL (bool active) {activeL = active;};
    inline void setActiveR (bool active) {activeR = active;};
    
    inline void setRadiusLX (float radius) {radiusLX = radius;};
    inline void setRadiusLY (float radius) {radiusLY = radius;};
    inline void setSpeedLX (float speed) {speedLX = speed;};
    inline void setSpeedLY (float speed) {speedLY = speed;};
    inline void setPhaseLX (float phase) {phaseLX = phase;};
    inline void setPhaseLY (float phase) {phaseLY = phase;};
    
    inline void setRadiusRX (float radius) {radiusRX = radius;};
    inline void setRadiusRY (float radius) {radiusRY = radius;};
    inline void setSpeedRX (float speed) {speedRX = speed;};
    inline void setSpeedRY (float speed) {speedRY = speed;};
    inline void setPhaseRX (float phase) {phaseRX = phase;};
    inline void setPhaseRY (float phase) {phaseRY = phase;};
    
    inline bool getActiveL() {return activeL;};
    inline bool getActiveR() {return activeR;};
    
    inline float getRadiusLX() {return radiusLX;};
    inline float getRadiusLY() {return radiusLY;};
    inline float getSpeedLX() {return speedLX;};
    inline float getSpeedLY() {return speedLY;};
    inline float getPhaseLX() {return phaseLX;};
    inline float getPhaseLY() {return phaseLY;};
    
    inline float getRadiusRX() {return radiusRX;};
    inline float getRadiusRY() {return radiusRY;};
    inline float getSpeedRX() {return speedRX;};
    inline float getSpeedRY() {return speedRY;};
    inline float getPhaseRX() {return phaseRX;};
    inline float getPhaseRY() {return phaseRY;};
    

    
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
