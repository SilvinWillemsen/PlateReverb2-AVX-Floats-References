/*
  ==============================================================================

    KnobsArea.h
    Created: 29 Sep 2017 3:40:44pm
    Author:  Silvin Willemsen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "RedButton.h"

//==============================================================================
/*
*/
class KnobsArea    : public Component
{
public:
    KnobsArea()
    {
        Font bigFont (20.0f);
        
        generalKnobsLabel.setText ("General Settings", NotificationType::dontSendNotification);
        generalKnobsLabel.setFont (bigFont);
        generalKnobsLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&generalKnobsLabel);
        
        volumeLabel.setText ("Dry/Wet", NotificationType::dontSendNotification);
        volumeLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&volumeLabel);
        
        volumeControl.setSliderStyle (Slider::RotaryVerticalDrag);
        volumeControl.setRange (0.0, 100.0, 1.0);
        volumeControl.setValue (80.0);
        volumeControl.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
        volumeControl.setPopupDisplayEnabled(true, true, this);
        volumeControl.setTextValueSuffix (" %");
        addAndMakeVisible (&volumeControl);
        
        centsLabel.setText ("Quality - Performance", NotificationType::dontSendNotification);
        centsLabel.setJustificationType (Justification::centred);
        //addAndMakeVisible (&centsLabel);
        
        centsControl.setSliderStyle (Slider::RotaryVerticalDrag);
        centsControl.setRange (1.0, 20.0, 0.01);
        centsControl.setValue (10.0);
        centsControl.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
        //centsControl.setPopupDisplayEnabled (true, this);
        //addAndMakeVisible (&centsControl);
        
        addAndMakeVisible (&redButton);
        
        decayLabel.setText ("Decay", NotificationType::dontSendNotification);
        decayLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&decayLabel);
        
        decayControl.setSliderStyle (Slider::RotaryVerticalDrag);
        decayControl.setRange (1.0, 10.0, 0.01);
        decayControl.setValue (4.0);
        decayControl.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
        decayControl.setPopupDisplayEnabled (true, true, this);
        decayControl.setTextValueSuffix (" s");
        addAndMakeVisible (&decayControl);
        
        flangingLabel.setText ("Flanging", NotificationType::dontSendNotification);
        flangingLabel.setFont (bigFont);
        flangingLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&flangingLabel);

        flangeButtonL.setButtonText("L");
        addAndMakeVisible (&flangeButtonL);
        
        flangeButtonR.setButtonText("R");
        addAndMakeVisible (&flangeButtonR);
        
        radiusLabel.setText ("Shape Radii", NotificationType::dontSendNotification);
        radiusLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&radiusLabel);
        
        radiusLXLabel.setText ("LX", NotificationType::dontSendNotification);
        radiusLXLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&radiusLXLabel);
        
        radiusLX.setSliderStyle (Slider::RotaryVerticalDrag);
        radiusLX.setRange (0.0, 0.5);
        radiusLX.setValue (0.4);
        radiusLX.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&radiusLX);
        
        radiusLYLabel.setText ("LY", NotificationType::dontSendNotification);
        radiusLYLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&radiusLYLabel);
        
        radiusLY.setSliderStyle (Slider::RotaryVerticalDrag);
        radiusLY.setRange (0.0, 0.5);
        radiusLY.setValue (0.4);
        radiusLY.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&radiusLY);

        radiusRXLabel.setText ("RX", NotificationType::dontSendNotification);
        radiusRXLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&radiusRXLabel);

        radiusRX.setSliderStyle (Slider::RotaryVerticalDrag);
        radiusRX.setRange (0.0, 0.5);
        radiusRX.setValue (0.4);
        radiusRX.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&radiusRX);
        
        radiusRYLabel.setText ("RY", NotificationType::dontSendNotification);
        radiusRYLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&radiusRYLabel);

        radiusRY.setSliderStyle (Slider::RotaryVerticalDrag);
        radiusRY.setRange (0.0, 0.5);
        radiusRY.setValue (0.4);
        radiusRY.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&radiusRY);
        
        speedLabel.setText ("Shape Speeds", NotificationType::dontSendNotification);
        speedLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&speedLabel);
        
        speedLXLabel.setText ("LX", NotificationType::dontSendNotification);
        speedLXLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&speedLXLabel);

        speedLX.setSliderStyle (Slider::RotaryVerticalDrag);
        speedLX.setRange (1, 6, 1);
        speedLX.setValue (2);
        speedLX.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&speedLX);
        
        speedLYLabel.setText ("LY", NotificationType::dontSendNotification);
        speedLYLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&speedLYLabel);
        
        speedLY.setSliderStyle (Slider::RotaryVerticalDrag);
        speedLY.setRange (1, 6, 1);
        speedLY.setValue (3);
        speedLY.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&speedLY);
        
        speedRXLabel.setText ("RX", NotificationType::dontSendNotification);
        speedRXLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&speedRXLabel);
        
        speedRX.setSliderStyle (Slider::RotaryVerticalDrag);
        speedRX.setRange (1, 6, 1);
        speedRX.setValue (1);
        speedRX.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&speedRX);
        
        speedRYLabel.setText ("RY", NotificationType::dontSendNotification);
        speedRYLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&speedRYLabel);
        
        speedRY.setSliderStyle (Slider::RotaryVerticalDrag);
        speedRY.setRange (1, 6, 1);
        speedRY.setValue (1);
        speedRY.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&speedRY);
        
        phaseLabel.setText ("Shape phases", NotificationType::dontSendNotification);
        phaseLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&phaseLabel);
        
        phaseLXLabel.setText ("LX", NotificationType::dontSendNotification);
        phaseLXLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&phaseLXLabel);
        
        phaseLX.setSliderStyle (Slider::RotaryVerticalDrag);
        phaseLX.setRange (0, 2 * float_Pi, 0.1 * float_Pi);
        phaseLX.setValue (0);
        phaseLX.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&phaseLX);
        
        phaseLYLabel.setText ("LY", NotificationType::dontSendNotification);
        phaseLYLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&phaseLYLabel);
        
        phaseLY.setSliderStyle (Slider::RotaryVerticalDrag);
        phaseLY.setRange (0, 2 * float_Pi, 0.1 * float_Pi);
        phaseLY.setValue (0.5 * float_Pi);
        phaseLY.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&phaseLY);
        
        phaseRXLabel.setText ("RX", NotificationType::dontSendNotification);
        phaseRXLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&phaseRXLabel);
        
        phaseRX.setSliderStyle (Slider::RotaryVerticalDrag);
        phaseRX.setRange (0, 2 * float_Pi, 0.1 * float_Pi);
        phaseRX.setValue (0);
        phaseRX.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&phaseRX);
        
        phaseRYLabel.setText ("RY", NotificationType::dontSendNotification);
        phaseRYLabel.setJustificationType (Justification::centred);
        addAndMakeVisible (&phaseRYLabel);
        
        phaseRY.setSliderStyle (Slider::RotaryVerticalDrag);
        phaseRY.setRange (0, 2 * float_Pi, 0.1 * float_Pi);
        phaseRY.setValue (0.5 * float_Pi);
        phaseRY.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (&phaseRY);
        
        recalculateL.setButtonText ("Recalculate L");
        addAndMakeVisible (&recalculateL);
        
        recalculateR.setButtonText ("Recalculate R");
        addAndMakeVisible (&recalculateR);

    }

    ~KnobsArea()
    {
    }

    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        float halfArea = getWidth() / 2.0;
        auto knobsAreaArea = getLocalBounds();
        knobsAreaArea.removeFromTop(10.0f);
        auto topKnobsArea = knobsAreaArea.removeFromTop(95.0f);

        generalKnobsLabel.setBounds (topKnobsArea.removeFromTop (20.0f));
        
        topKnobsArea.removeFromTop(10.0f);
        auto topLeftKnobsArea = topKnobsArea.removeFromLeft(halfArea);
        
        volumeControl.setBounds (topLeftKnobsArea.removeFromTop (45.0f).reduced (2.0f));
        volumeLabel.setBounds (topLeftKnobsArea);
        
        decayControl.setBounds (topKnobsArea.removeFromTop (45.0f).reduced (2.0f));
        decayLabel.setBounds (topKnobsArea);

        auto bottomKnobsArea = knobsAreaArea.removeFromTop(65.0f);
        redButton.setBounds (bottomKnobsArea.removeFromTop (45.0f).reduced (5.0f));
//        centsControl.setBounds (bottomKnobsArea.removeFromTop (45.0f).reduced (2.0f));
//        centsLabel.setBounds (bottomKnobsArea);
        
        auto flangingArea (knobsAreaArea.removeFromBottom(270.0f));
        flangingLabel.setBounds (flangingArea.removeFromTop (20.0f));
        
        auto flangingButtonsArea (flangingArea.removeFromTop (30.0f));
        flangeButtonL.setBounds (flangingButtonsArea.removeFromLeft (halfArea).reduced (5.0f));
        flangeButtonL.setColour (TextButton::buttonColourId, Colours::red);
        
        flangeButtonR.setBounds (flangingButtonsArea.reduced (5.0f));
        flangeButtonR.setColour (TextButton::buttonColourId, Colours::red);

        auto radiusArea (flangingArea.removeFromTop (60.0f));
        radiusLabel.setBounds(radiusArea.removeFromTop(20.0f));
        
        auto radiusAreaLeft1 (radiusArea.removeFromLeft (halfArea / 2.0f));
        radiusLXLabel.setBounds(radiusAreaLeft1.removeFromTop (20.0f));
        radiusLX.setBounds (radiusAreaLeft1);
        
        auto radiusAreaLeft2 (radiusArea.removeFromLeft (halfArea / 2.0f));
        radiusLYLabel.setBounds(radiusAreaLeft2.removeFromTop (20.0f));
        radiusLY.setBounds (radiusAreaLeft2);
        
        auto radiusAreaRight1 (radiusArea.removeFromLeft (halfArea / 2.0f));
        radiusRXLabel.setBounds(radiusAreaRight1.removeFromTop (20.0f));
        radiusRX.setBounds (radiusAreaRight1);
        
        radiusRYLabel.setBounds(radiusArea.removeFromTop (20.0f));
        radiusRY.setBounds (radiusArea);
        
        auto speedArea (flangingArea.removeFromTop (60.0f));
        speedLabel.setBounds(speedArea.removeFromTop(20.0f));
        
        auto speedAreaLeft1 (speedArea.removeFromLeft (halfArea / 2.0f));
        speedLXLabel.setBounds(speedAreaLeft1.removeFromTop (20.0f));
        speedLX.setBounds (speedAreaLeft1);
        
        auto speedAreaLeft2 (speedArea.removeFromLeft (halfArea / 2.0f));
        speedLYLabel.setBounds(speedAreaLeft2.removeFromTop (20.0f));
        speedLY.setBounds (speedAreaLeft2);
        
        auto speedAreaRight1 (speedArea.removeFromLeft (halfArea / 2.0f));
        speedRXLabel.setBounds(speedAreaRight1.removeFromTop (20.0f));
        speedRX.setBounds (speedAreaRight1);
        
        speedRYLabel.setBounds(speedArea.removeFromTop (20.0f));
        speedRY.setBounds (speedArea);
        
        auto phaseArea (flangingArea.removeFromTop (60.0f));
        phaseLabel.setBounds(phaseArea.removeFromTop(20.0f));
        
        auto phaseAreaLeft1 (phaseArea.removeFromLeft (halfArea / 2.0f));
        phaseLXLabel.setBounds(phaseAreaLeft1.removeFromTop (20.0f));
        phaseLX.setBounds (phaseAreaLeft1);
        
        auto phaseAreaLeft2 (phaseArea.removeFromLeft (halfArea / 2.0f));
        phaseLYLabel.setBounds(phaseAreaLeft2.removeFromTop (20.0f));
        phaseLY.setBounds (phaseAreaLeft2);
        
        auto phaseAreaRight1 (phaseArea.removeFromLeft (halfArea / 2.0f));
        phaseRXLabel.setBounds(phaseAreaRight1.removeFromTop (20.0f));
        phaseRX.setBounds (phaseAreaRight1);
        
        phaseRYLabel.setBounds(phaseArea.removeFromTop (20.0f));
        phaseRY.setBounds (phaseArea);
        
        auto recalculateButtonsArea (flangingArea.removeFromTop (30.0f));
        recalculateL.setBounds (recalculateButtonsArea.removeFromLeft (halfArea).reduced (5.0f));
        recalculateL.setColour (TextButton::buttonColourId, Colours::lightsteelblue);
        
        recalculateR.setBounds (recalculateButtonsArea.reduced (5.0f));
        recalculateR.setColour (TextButton::buttonColourId, Colours::lightsteelblue);



    }

    Slider* getVolumeControl() {return &volumeControl;};
    Slider* getDecayControl() {return &decayControl;};
    Slider* getCentsControl() {return &centsControl;};
    
    TextButton* getFlangeButtonL() {return &flangeButtonL;};
    TextButton* getFlangeButtonR() {return &flangeButtonR;};
    
    Slider* getRadiusLX() {return &radiusLX;};
    Slider* getRadiusLY() {return &radiusLY;};
    Slider* getRadiusRX() {return &radiusRX;};
    Slider* getRadiusRY() {return &radiusRY;};
    
    Slider* getSpeedLX() {return &speedLX;};
    Slider* getSpeedLY() {return &speedLY;};
    Slider* getSpeedRX() {return &speedRX;};
    Slider* getSpeedRY() {return &speedRY;};
    
    Slider* getPhaseLX() {return &phaseLX;};
    Slider* getPhaseLY() {return &phaseLY;};
    Slider* getPhaseRX() {return &phaseRX;};
    Slider* getPhaseRY() {return &phaseRY;};
    
    TextButton* getRecalculateL() {return &recalculateL;};
    TextButton* getRecalculateR() {return &recalculateR;};
    
    RedButton* getRedButton() {return &redButton;};

private:
    Slider volumeControl;
    Slider decayControl;
    Slider centsControl;
    
    Label generalKnobsLabel;
    Label volumeLabel;
    Label centsLabel;
    Label decayLabel;
    Label flangingLabel;
    Label radiusLabel;
    Label radiusLXLabel;
    Label radiusLYLabel;
    Label radiusRXLabel;
    Label radiusRYLabel;
    
    Label speedLabel;
    Label speedLXLabel;
    Label speedLYLabel;
    Label speedRXLabel;
    Label speedRYLabel;
    
    Label phaseLabel;
    Label phaseLXLabel;
    Label phaseLYLabel;
    Label phaseRXLabel;
    Label phaseRYLabel;
    
    TextButton flangeButtonL;
    TextButton flangeButtonR;
    
    Slider radiusLX;
    Slider radiusLY;
    Slider radiusRX;
    Slider radiusRY;
    
    Slider speedLX;
    Slider speedLY;
    Slider speedRX;
    Slider speedRY;
    
    Slider phaseLX;
    Slider phaseLY;
    Slider phaseRX;
    Slider phaseRY;
    
    TextButton recalculateL;
    TextButton recalculateR;
    
    RedButton redButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobsArea)
};
