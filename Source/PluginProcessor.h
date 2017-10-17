/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <immintrin.h>

struct OmegaMatrix
{
    
public:
    OmegaMatrix() : eigenFrequencies (0), horizontalModes (0), verticalModes (0) {}
    OmegaMatrix (std::vector<float> eigenFrequencies, std::vector<int> horizontalModes, std::vector<int> verticalModes)
    : eigenFrequencies (eigenFrequencies), horizontalModes (horizontalModes), verticalModes (verticalModes) {};
    
    ~OmegaMatrix() {};
    
    void setEigenFrequencies(std::vector<float> eigenFrequenciesToBeSet) {eigenFrequencies = eigenFrequenciesToBeSet;};
    void setHorizontalModes(std::vector<int> horizontalModesToBeSet) {horizontalModes = horizontalModesToBeSet;};
    void setVerticalModes(std::vector<int> verticalModesToBeSet) {verticalModes = verticalModesToBeSet;};

    std::vector<float>& getEigenFrequencies() {return eigenFrequencies;};
    std::vector<int>& getHorizontalModes() {return horizontalModes;};
    std::vector<int>& getVerticalModes() {return verticalModes;};
    
private:
    std::vector<float> eigenFrequencies;
    std::vector<int> horizontalModes;
    std::vector<int> verticalModes;
};

struct __OmegaMatrix
{
    
public:
    __OmegaMatrix() : __eigenFrequencies (0), __horizontalModes (0), __verticalModes (0) {}
    __OmegaMatrix (std::vector<__m256> __eigenFrequencies, std::vector<__m256i> __horizontalModes, std::vector<__m256i> __verticalModes)
    : __eigenFrequencies (__eigenFrequencies), __horizontalModes (__horizontalModes), __verticalModes (__verticalModes) {};
    
    ~__OmegaMatrix() {};
    
    std::vector<__m256> getEigenFrequencies() {return __eigenFrequencies;};
    std::vector<__m256i> getHorizontalModes() {return __horizontalModes;};
    std::vector<__m256i> getVerticalModes() {return __verticalModes;};
    
private:
    std::vector<__m256> __eigenFrequencies;
    std::vector<__m256i> __horizontalModes;
    std::vector<__m256i> __verticalModes;
};

class LocationOnPlate
{
    
public:
    
    LocationOnPlate() : x (0.0), y (0.0) {};
    LocationOnPlate (double v, double w) : x (v), y (w) {};
    
    ~LocationOnPlate() {};
    
    double getX() { return x; }
    double getY() { return y; }
    void setX (double v) { x = v; }
    void setY (double w) { y = w; }
    void setLocation (double v, double w) { x = v; y = w; };
    
    
private:
    double x,y;
    
};

struct PlatePositions
{
    
public:
    PlatePositions():input (0.4,0.415), outputL (0.1, 0.45), outputR (0.84, 0.45) {};
    
    ~PlatePositions() {};
    
    LocationOnPlate& getInput() { return input; };
    LocationOnPlate& getOutputL() { return outputL; };
    LocationOnPlate& getOutputR() { return outputR; };
    
    void setInput(LocationOnPlate& inputToBeSet) { input = inputToBeSet; };
    void setOutputL(LocationOnPlate& outputToBeSet) { outputL = outputToBeSet; };
    void setOutputR(LocationOnPlate& outputToBeSet) { outputR = outputToBeSet; };
    
private:
    LocationOnPlate input, outputL, outputR;
    
};

//==============================================================================
/**
*/
class PlateReverb2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PlateReverb2AudioProcessor();
    ~PlateReverb2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /* 
     ==============================================================================
        Additional functions
     ==============================================================================
    */
    void useAVX();
    
    void calculateAndSortOmegaMatrix();
    void deleteCents();
    void calculatePhi();
    void calculateCoefficients();
    void plateStretching();
    void decayChange();
    
    void AVXAll();
    void calculatePhiOutL();
    void calculatePhiOutR();
    void calculateCoefIndA();
    
    void createNewQVectors();
    void setFlangingL();
    void setFlangingR();
    
    /*
     ==============================================================================
        Plate Variables
     ==============================================================================
    */
    
    const double fs = 44100.0;
    const double E = 2e11;
    const double v = 0.3;
    const double h = 0.0005;
    const double rho = 7850.0;
    const double k = 1.0 / fs;
    const double kSq = (E * pow (h, 2)) / (12.0 * rho * (1 - pow (v, 2)));

    /*
     ==============================================================================
        Variables Required for Loop
     ==============================================================================
    */
    
    OmegaMatrix sortedOmegaMatrix;
    PlatePositions positions;
    
    std::vector<float> eigenFrequencies;
    std::vector<int> horizontalModes;
    std::vector<int> verticalModes;
    
    std::vector<int> omegaPositions;
    std::vector<int> omegaPositionsPrev;
    
    std::vector<double> phiIn;
    std::vector<float> phiOutL;
    std::vector<float> phiOutR;
    
    std::vector<float> coefBdA;
    std::vector<float> coefCdA;
    std::vector<float> coefIndA;
    
    std::vector<__m256> __phiOutL;
    std::vector<__m256> __phiOutR;
    
    std::vector<__m256> __coefBdA;
    std::vector<__m256> __coefCdA;
    std::vector<__m256> __coefIndA;
    
    const double detail = fs / 2.0;
    std::vector<std::vector<__m256>> __phiOutLFlange;
    std::vector<std::vector<__m256>> __phiOutRFlange;
    std::vector<__m256> __phiOutLFlangeUse;
    std::vector<__m256> __phiOutRFlangeUse;
    
    std::vector<std::vector<float>> phiOutLFlange;
    std::vector<std::vector<float>> phiOutRFlange;
    std::vector<float> phiOutLFlangeUse;
    std::vector<float> phiOutRFlangeUse;

    std::vector<__m256> __qNow;
    std::vector<__m256> __qPrev;
    __m256 __resultL;
    __m256 __resultR;
    
    std::vector<float> qNext;
    std::vector<float> qNow;
    std::vector<float> qPrev;
    std::vector<float> resultL;
    std::vector<float> resultR;
    
    //initialise AVX pointers
    __m256* __coefBdAPtr = nullptr;
    __m256* __qNowPtr = nullptr;
    __m256* __coefCdAPtr = nullptr;
    __m256* __qPrevPtr = nullptr;
    __m256* __coefIndAPtr = nullptr;
    __m256* __phiOutLPtr = nullptr;
    __m256* __phiOutRPtr = nullptr;
    __m256* __phiOutLFlangePtr = nullptr;
    __m256* __phiOutRFlangePtr = nullptr;
    
    //initialise non-AVX pointers
    float* coefBdAPtr = nullptr;
    float* qNowPtr = nullptr;
    float* coefCdAPtr = nullptr;
    float* qPrevPtr = nullptr;
    float* coefIndAPtr = nullptr;
    float* phiOutLPtr = nullptr;
    float* phiOutRPtr = nullptr;
    float* phiOutLFlangePtr = nullptr;
    float* phiOutRFlangePtr = nullptr;
    float* resultLPtr = nullptr;
    float* resultRPtr = nullptr;
    
    unsigned long vectorLength = 0;
    unsigned long AVXVectorLength = 0;
    unsigned long AVXVectorLengthPrev = 0;
    
    std::vector<int> unstableEigenFrequencies;
    
    bool AVX = false;
    const int AVXSize = 8;
    int AVXZeros = 0;
    int AVXZerosPrev = 0;
    float inputUse = 0.0;
    __m256 __inputUse = _mm256_setzero_ps();
    
    /*
     ==============================================================================
        GUI Variables
     ==============================================================================
    */
    
    double gain = 1.0;
    double Lx = 2.0;
    double Ly = 1.0;
    double C = 5.0;
    double decay = 4.0;
    
    double radiusLX = 0.4;
    double radiusLY = 0.4;
    double radiusRX = 0.4;
    double radiusRY = 0.4;
    
    double speedLX = 2.0;
    double speedLY = 3.0;
    double speedRX = 1.0;
    double speedRY = 1.0;
    
    double phaseLX = 0.0;
    double phaseLY = 0.5 * double_Pi;
    double phaseRX = 0.0;
    double phaseRY = 0.5 * double_Pi;
    
    double pos = 0.0;
    
    /*
     ==============================================================================
        Flags
     ==============================================================================
    */
    
    bool recalculateLFlag = false;
    bool recalculateRFlag = false;
    
    bool decayFlag = false;
    bool centsFlag = false;
    bool stretchFlag = false;
    bool flangeFlagL = false;
    bool flangingL = false;
    bool flangingR = false;
    bool flangingL2 = false;
    bool flangingR2 = false;
    
    bool inputChange = false;
    bool outputLChange = false;
    bool outputRChange = false;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlateReverb2AudioProcessor)
};
