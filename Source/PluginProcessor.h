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

    std::vector<float> getEigenFrequencies() {return eigenFrequencies;};
    std::vector<int> getHorizontalModes() {return horizontalModes;};
    std::vector<int> getVerticalModes() {return verticalModes;};
    
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

//struct PhiMatrix
//{
//    
//public:
//    PhiMatrix() : phiIn (0),phiOutL (0),phiOutR (0) {};
//    PhiMatrix (std::vector<double> phiIn, std::vector<float> phiOutL, std::vector<float> phiOutR)
//    : phiIn (phiIn),phiOutL (phiOutL),phiOutR (phiOutR) {};
//    
//    ~PhiMatrix() {};
//    
//    std::vector<double> getPhiIn() {return phiIn;};
//    std::vector<float> getPhiOutL() {return phiOutL;};
//    std::vector<float> getPhiOutR() {return phiOutR;};
//    
//private:
//    std::vector<double> phiIn;
//    std::vector<float> phiOutL, phiOutR;
//};

class LocationOnPlate
{
    
public:
    
    LocationOnPlate() : x (0.0), y (0.0) {};
    LocationOnPlate (double v, double w) : x (v), y (w) {};
    
    ~LocationOnPlate() {};
    
    double getX() {return x;}
    double getY() {return y;}
    void setX (double v) {x = v;}
    void setY (double w) {y = w;}
    void setLocation (double v, double w) {x = v; y = w;};
    
    
private:
    double x,y;
    
};

struct PlatePositions
{
    
public:
    PlatePositions():input (0.4,0.415), outputL (0.1, 0.45), outputR (0.84, 0.45) {};
    
    ~PlatePositions() {};
    
    LocationOnPlate getInput() {return input;};
    LocationOnPlate getOutputL() {return outputL;};
    LocationOnPlate getOutputR() {return outputR;};
    void setInput(LocationOnPlate inputToBeSet) {input = inputToBeSet;};
    void setOutputL(LocationOnPlate outputToBeSet) {outputL = outputToBeSet;};
    void setOutputR(LocationOnPlate outputToBeSet) {outputR = outputToBeSet;};
    
private:
    LocationOnPlate input, outputL, outputR;
    
};

//struct PlateStretchReturn
//{
//    
//public:
//    PlateStretchReturn()
//    {
//        __factorBdA = {_mm256_setzero_pd()};
//        AVXVectorLength = 0;
//        AVXcompatibility = 0;
//    }
//    PlateStretchReturn (std::vector<__m256> __factorBdA, unsigned long AVXVectorLength, int AVXcompatibility)
//    : __factorBdA (__factorBdA), AVXVectorLength (AVXVectorLength), AVXcompatibility (AVXcompatibility) {};
//    
//    ~PlateStretchReturn() {};
//    
//    std::vector<__m256> getFactorBdA() {return __factorBdA;};
//    unsigned long getAVXVectorLength() {return AVXVectorLength;};
//    int getAVX() {return AVXcompatibility;};
//    
//private:
//    std::vector<__m256> __factorBdA;
//    unsigned long AVXVectorLength;
//    int AVXcompatibility;
//    
//};

//struct Coefficients
//{
//    
//public:
//    Coefficients() : factorBdA (0),factorCdA (0),factorIndA (0) {};
//    Coefficients (std::vector<float> factorBdA, std::vector<float> factorCdA, std::vector<float> factorIndA)
//    : factorBdA (factorBdA), factorCdA (factorCdA), factorIndA (factorIndA) {};
//    
//    std::vector<float> getFactorBdA() {return factorBdA;};
//    std::vector<float> getFactorCdA() {return factorCdA;};
//    std::vector<float> getFactorIndA() {return factorIndA;};
//    
//private:
//    std::vector<float> factorBdA, factorCdA, factorIndA;
//};

//struct UsableVariables
//{
//    
//public:
//    UsableVariables()
//    {
//        eigenFrequencies = {0.0};
//        horizontalModes = {0};
//        verticalModes = {0};
//        phiOutL = {0.0};
//        phiOutR = {0.0};
//        factorBdA = {0.0};
//        factorCdA = {0.0};
//        factorIndA = {0.0};
//    }

//    UsableVariables (OmegaMatrix omegaMatrix, Coefficients coefficients, PhiMatrix phiMatrix)
//    {
//        eigenFrequencies = omegaMatrix.getEigenFrequencies();
//        horizontalModes = omegaMatrix.getHorizontalModes();
//        verticalModes = omegaMatrix.getVerticalModes();
//        
//        phiOutL = phiMatrix.getPhiOutL();
//        phiOutR = phiMatrix.getPhiOutR();
//        factorBdA = coefficients.getFactorBdA();
//        factorCdA = coefficients.getFactorCdA();
//        factorIndA = coefficients.getFactorIndA();
//    }
//    
//    ~UsableVariables() {};
//    
//    void setPhiOutL (std::vector<float> phiOutLToBeSet) {phiOutL = phiOutLToBeSet;};
//    void setPhiOutR (std::vector<float> phiOutRToBeSet) {phiOutR = phiOutRToBeSet;};
//    void setFactorIndA (std::vector<float> factorIndAToBeSet) {factorIndA = factorIndAToBeSet;};
//    
//    std::vector<float> getEigenFrequencies() {return eigenFrequencies;};
//    std::vector<int> getHorizontalModes() {return horizontalModes;};
//    std::vector<int> getVerticalModes() {return verticalModes;};
//    std::vector<float> getPhiOutL() {return phiOutL;};
//    std::vector<float> getPhiOutR() {return phiOutR;};
//    std::vector<float> getFactorBdA() {return factorBdA;};
//    std::vector<float> getFactorCdA() {return factorCdA;};
//    std::vector<float> getFactorIndA() {return factorIndA;};
//
//private:
//    std::vector<float> eigenFrequencies;
//    std::vector<int> horizontalModes;
//    std::vector<int> verticalModes;
//    std::vector<float> phiOutL;
//    std::vector<float> phiOutR;
//    std::vector<float> factorBdA;
//    std::vector<float> factorCdA;
//    std::vector<float> factorIndA;
//};

//struct FlangeMatrices
//{
//    
//public:
//    FlangeMatrices()
//    {
//        std::vector<__m256> __zeroVector (1,_mm256_setzero_ps());
//        __phiOutLFlange = {__zeroVector};
//        __phiOutRFlange = {__zeroVector};
//    }
//    
//    FlangeMatrices(std::vector<std::vector<__m256>> __phiOutLFlangeToBeSet, std::vector<std::vector<__m256>> __phiOutRFlangeToBeSet)
//    {
//        __phiOutLFlange = __phiOutLFlangeToBeSet;
//        __phiOutRFlange = __phiOutRFlangeToBeSet;
//    }
//    
//    std::vector<std::vector<__m256>>  getPhiOutLFlange() {return __phiOutLFlange;};
//    std::vector<std::vector<__m256>>  getPhiOutRFlange() {return __phiOutRFlange;};
//    
//private:
//    std::vector<std::vector<__m256>> __phiOutLFlange;
//    std::vector<std::vector<__m256>> __phiOutRFlange;
//};

//struct AVXVariables
//{
//    
//public:
//    AVXVariables()
//    {
//        __horizontalModes = {_mm256_setzero_si256()};
//        __verticalModes = {_mm256_setzero_si256()};
//        __phiOutL = {_mm256_setzero_pd()};
//        __phiOutR = {_mm256_setzero_pd()};
//        __factorBdA = {_mm256_setzero_pd()};
//        __factorCdA = {_mm256_setzero_pd()};
//        __factorIndA = {_mm256_setzero_pd()};
//        std::vector<__m256> __zeroVector(1,_mm256_setzero_ps());
//        __phiOutLFlange = {__zeroVector};
//        __phiOutRFlange = {__zeroVector};
//    }
//    AVXVariables (UsableVariables usableVariables)
//    {
//        std::vector<int> horizontalModes = usableVariables.getHorizontalModes();
//        std::vector<int> verticalModes = usableVariables.getVerticalModes();
//        std::vector<float> phiOutL = usableVariables.getPhiOutL();
//        std::vector<float> phiOutR = usableVariables.getPhiOutR();
//        std::vector<float> factorBdA = usableVariables.getFactorBdA();
//        std::vector<float> factorCdA = usableVariables.getFactorCdA();
//        std::vector<float> factorIndA = usableVariables.getFactorIndA();
//        
//        
//        int AVX = 8;
//        unsigned long omegaLength = phiOutL.size();
//        unsigned long AVXCompatibility = (AVX - (omegaLength % AVX)) % AVX;
//        
//        for (int m = 0; m < AVXCompatibility; ++m)
//        {
//            phiOutL.push_back(0);
//            phiOutR.push_back(0);
//            factorBdA.push_back(0);
//            factorCdA.push_back(0);
//            factorIndA.push_back(0);
//        }
//        
//        unsigned long vectorLength = (omegaLength + AVXCompatibility) / AVX;
//        std::vector<__m256> __zeroVector (vectorLength, _mm256_setzero_ps());
//        std::vector<__v8su> __zeroVectorModes (vectorLength, _mm256_setzero_si256());
//        __horizontalModes = __zeroVectorModes;
//        __verticalModes = __zeroVectorModes;
//        __phiOutL = __zeroVector;
//        __phiOutR = __zeroVector;
//        __factorBdA = __zeroVector;
//        __factorCdA = __zeroVector;
//        __factorIndA = __zeroVector;
//        
//        int n (0);
//        for (int m = 0; m < omegaLength + AVXCompatibility; m = m + AVX)
//        {
//            __phiOutL[n] = _mm256_setr_ps (phiOutL[m], phiOutL[m+1], phiOutL[m+2], phiOutL[m+3],
//                                           phiOutL[m+4], phiOutL[m+5], phiOutL[m+6], phiOutL[m+7]);
//            __phiOutR[n] = _mm256_setr_ps (phiOutR[m], phiOutR[m+1], phiOutR[m+2], phiOutR[m+3],
//                                           phiOutR[m+4], phiOutR[m+5], phiOutR[m+6], phiOutR[m+7]);
//            __factorBdA[n] = _mm256_setr_ps (factorBdA[m], factorBdA[m+1], factorBdA[m+2], factorBdA[m+3],
//                                             factorBdA[m+4], factorBdA[m+5], factorBdA[m+6], factorBdA[m+7]);
//            __factorCdA[n] = _mm256_setr_ps (factorCdA[m], factorCdA[m+1], factorCdA[m+2], factorCdA[m+3],
//                                             factorCdA[m+4], factorCdA[m+5], factorCdA[m+6], factorCdA[m+7]);
//            __factorIndA[n] = _mm256_setr_ps (factorIndA[m], factorIndA[m+1], factorIndA[m+2], factorIndA[m+3],
//                                              factorIndA[m+4], factorIndA[m+5], factorIndA[m+6], factorIndA[m+7]);
//            __horizontalModes[n] =_mm256_setr_epi32 (horizontalModes[m], horizontalModes[m+1], horizontalModes[m+2], horizontalModes[m+3],
//                                                     horizontalModes[m+4], horizontalModes[m+5], horizontalModes[m+6], horizontalModes[m+7]);
//            __verticalModes[n] =_mm256_setr_epi32 (verticalModes[m], verticalModes[m+1], verticalModes[m+2], verticalModes[m+3],
//                                                   verticalModes[m+4], verticalModes[m+5], verticalModes[m+6], verticalModes[m+7]);
//            n++;
//        }
//    }
//    
//    AVXVariables (UsableVariables usableVariables, FlangeMatrices flangeMatrices)
//    {
//        std::vector<int> horizontalModes = usableVariables.getHorizontalModes();
//        std::vector<int> verticalModes = usableVariables.getVerticalModes();
//        std::vector<float> phiOutL = usableVariables.getPhiOutL();
//        std::vector<float> phiOutR = usableVariables.getPhiOutR();
//        std::vector<float> factorBdA = usableVariables.getFactorBdA();
//        std::vector<float> factorCdA = usableVariables.getFactorCdA();
//        std::vector<float> factorIndA = usableVariables.getFactorIndA();
//        
//        
//        int AVX = 8;
//        unsigned long omegaLength = phiOutL.size();
//        unsigned long AVXCompatibility = (AVX - (omegaLength % AVX)) % AVX;
//        
//        for (int m = 0; m < AVXCompatibility; ++m)
//        {
//            phiOutL.push_back(0);
//            phiOutR.push_back(0);
//            factorBdA.push_back(0);
//            factorCdA.push_back(0);
//            factorIndA.push_back(0);
//        }
//        
//        unsigned long vectorLength = (omegaLength+AVXCompatibility) / AVX;
//        std::vector<__m256> __zeroVector(vectorLength, _mm256_setzero_ps());
//        std::vector<__v8su> __zeroVectorModes(vectorLength, _mm256_setzero_si256());
//        __horizontalModes = __zeroVectorModes;
//        __verticalModes = __zeroVectorModes;
//        __phiOutL = __zeroVector;
//        __phiOutR = __zeroVector;
//        __factorBdA = __zeroVector;
//        __factorCdA = __zeroVector;
//        __factorIndA = __zeroVector;
//        
//        int n = 0;
//        
//        for (int m = 0; m < omegaLength + AVXCompatibility; m = m + AVX)
//        {
//            __phiOutL[n] = _mm256_setr_ps (phiOutL[m], phiOutL[m+1], phiOutL[m+2], phiOutL[m+3],
//                                           phiOutL[m+4], phiOutL[m+5], phiOutL[m+6], phiOutL[m+7]);
//            __phiOutR[n] = _mm256_setr_ps (phiOutR[m], phiOutR[m+1], phiOutR[m+2], phiOutR[m+3],
//                                           phiOutR[m+4], phiOutR[m+5], phiOutR[m+6], phiOutR[m+7]);
//            __factorBdA[n] = _mm256_setr_ps (factorBdA[m], factorBdA[m+1], factorBdA[m+2], factorBdA[m+3],
//                                             factorBdA[m+4], factorBdA[m+5], factorBdA[m+6], factorBdA[m+7]);
//            __factorCdA[n] = _mm256_setr_ps (factorCdA[m], factorCdA[m+1], factorCdA[m+2], factorCdA[m+3],
//                                             factorCdA[m+4], factorCdA[m+5], factorCdA[m+6], factorCdA[m+7]);
//            __factorIndA[n] = _mm256_setr_ps (factorIndA[m], factorIndA[m+1], factorIndA[m+2], factorIndA[m+3],
//                                              factorIndA[m+4], factorIndA[m+5], factorIndA[m+6], factorIndA[m+7]);
//            __horizontalModes[n] =_mm256_setr_epi32 (horizontalModes[m], horizontalModes[m+1], horizontalModes[m+2], horizontalModes[m+3],
//                                                     horizontalModes[m+4], horizontalModes[m+5], horizontalModes[m+6], horizontalModes[m+7]);
//            __verticalModes[n] =_mm256_setr_epi32 (verticalModes[m], verticalModes[m+1], verticalModes[m+2], verticalModes[m+3],
//                                                   verticalModes[m+4], verticalModes[m+5], verticalModes[m+6], verticalModes[m+7]);
//            n++;
//        }
//        __phiOutLFlange = flangeMatrices.getPhiOutLFlange();
//        __phiOutRFlange = flangeMatrices.getPhiOutRFlange();
//    }
//    
//    void setFactorBdA(std::vector<__m256> __factorBdAToBeSet) {__factorBdA = __factorBdAToBeSet;};
//    void setPhiOutLFlange(std::vector<std::vector<__m256>> __phiOutLFlangeToBeSet) {__phiOutLFlange = __phiOutLFlangeToBeSet;};
//    void setPhiOutRFlange(std::vector<std::vector<__m256>> __phiOutRFlangeToBeSet) {__phiOutRFlange = __phiOutRFlangeToBeSet;};
//   
//    void setFactorIndA(std::vector<float> factorIndA)
//    {
//        int AVX = 8;
//        unsigned long omegaLength = factorIndA.size();
//        unsigned long AVXCompatibility = (AVX - (omegaLength % AVX)) % AVX;
//        
//        for (int m = 0; m < AVXCompatibility; ++m)
//        {
//            factorIndA.push_back(0);
//        }
//        
//        unsigned long vectorLength = (omegaLength+AVXCompatibility) / AVX;
//        std::vector<__m256> __zeroVector(vectorLength, _mm256_setzero_ps());
//        __factorIndA = __zeroVector;
//        
//        int n = 0;
//        
//        for (int m = 0; m < omegaLength + AVXCompatibility; m = m + AVX)
//        {
//            __factorIndA[n] = _mm256_setr_ps (factorIndA[m], factorIndA[m+1], factorIndA[m+2], factorIndA[m+3],
//                                              factorIndA[m+4], factorIndA[m+5], factorIndA[m+6], factorIndA[m+7]);
//            n++;
//        }
//    };
//    
//    void setPhiOutL(std::vector<float> phiOutL)
//    {
//        int AVX = 8;
//        unsigned long omegaLength = phiOutL.size();
//        unsigned long AVXCompatibility = (AVX - (omegaLength % AVX)) % AVX;
//        
//        for (int m = 0; m < AVXCompatibility; ++m)
//        {
//            phiOutL.push_back(0);
//        }
//        
//        unsigned long vectorLength = (omegaLength+AVXCompatibility) / AVX;
//        std::vector<__m256> __zeroVector(vectorLength, _mm256_setzero_ps());
//        __phiOutL = __zeroVector;
//        
//        int n = 0;
//        
//        for (int m = 0; m < omegaLength + AVXCompatibility; m = m + AVX)
//        {
//            __phiOutL[n] = _mm256_setr_ps (phiOutL[m], phiOutL[m+1], phiOutL[m+2], phiOutL[m+3],
//                                              phiOutL[m+4], phiOutL[m+5], phiOutL[m+6], phiOutL[m+7]);
//            n++;
//        }
//    };
//    
//    void setPhiOutR(std::vector<float> phiOutR)
//    {
//        int AVX = 8;
//        unsigned long omegaLength = phiOutR.size();
//        unsigned long AVXCompatibility = (AVX - (omegaLength % AVX)) % AVX;
//        
//        for (int m = 0; m < AVXCompatibility; ++m)
//        {
//            phiOutR.push_back(0);
//        }
//        
//        unsigned long vectorLength = (omegaLength+AVXCompatibility) / AVX;
//        std::vector<__m256> __zeroVector(vectorLength, _mm256_setzero_ps());
//        __phiOutR = __zeroVector;
//        
//        int n = 0;
//        
//        for (int m = 0; m < omegaLength + AVXCompatibility; m = m + AVX)
//        {
//            __phiOutR[n] = _mm256_setr_ps (phiOutR[m], phiOutR[m+1], phiOutR[m+2], phiOutR[m+3],
//                                           phiOutR[m+4], phiOutR[m+5], phiOutR[m+6], phiOutR[m+7]);
//            n++;
//        }
//    };
//
//    std::vector<__v8su> getHorizontalModes() {return __horizontalModes;};
//    std::vector<__v8su> getVerticalModes() {return __verticalModes;};
//    
//    std::vector<__m256> getPhiOutL() {return __phiOutL;};
//    std::vector<__m256> getPhiOutR() {return __phiOutR;};
//    std::vector<__m256> getFactorBdA() {return __factorBdA;};
//    std::vector<__m256> getFactorCdA() {return __factorCdA;};
//    std::vector<__m256> getFactorIndA() {return __factorIndA;};
//    
//    std::vector<std::vector<__m256>> getPhiOutLFlange() {return __phiOutLFlange;};
//    std::vector<std::vector<__m256>> getPhiOutRFlange() {return __phiOutRFlange;};
//    
//private:
//    std::vector<__v8su> __horizontalModes;
//    std::vector<__v8su> __verticalModes;
//    std::vector<__m256> __phiOutL;
//    std::vector<__m256> __phiOutR;
//    std::vector<__m256> __factorBdA;
//    std::vector<__m256> __factorCdA;
//    std::vector<__m256> __factorIndA;
//    std::vector<std::vector<__m256>> __phiOutLFlange;
//    std::vector<std::vector<__m256>> __phiOutRFlange;
//};

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
    
    void calculateAndSortOmegaMatrix();
    void deleteCents();
    void calculatePhi();
    void calculateCoefficients();
    void plateStretching();
    
    void AVXAll();
    inline void AVXPhiOutL(int m, int n);
    inline void AVXPhiOutR(int m, int n);
    inline void AVXFactorBdA(int m, int n);
    inline void AVXFactorCdA(int m, int n);
    inline void AVXFactorIndA(int m, int n);
    inline void AVXQPrev(std::vector<float> qPrev, int m, int n);
    inline void AVXQNow(std::vector<float> qNow, int m, int n);

    void calculatePhiOutL();
    void calculatePhiOutR();
    void calculateFactorIndA();
    
    void createNewQVectors();
    void setFlanging (bool left);

    
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
    
    std::vector<float> factorBdA;
    std::vector<float> factorCdA;
    std::vector<float> factorIndA;
    
    std::vector<__m256> __phiOutL;
    std::vector<__m256> __phiOutR;
    
    std::vector<__m256> __factorBdA;
    std::vector<__m256> __factorCdA;
    std::vector<__m256> __factorIndA;
    
    std::vector<std::vector<__m256>> __phiOutLFlange;
    std::vector<std::vector<__m256>> __phiOutRFlange;
    
    std::vector<__m256> __qNext;
    std::vector<__m256> __qNow;
    std::vector<__m256> __qPrev;
    std::vector<__m256> __resultL;
    std::vector<__m256> __resultR;
    
    unsigned long vectorLength = 0;
    unsigned long AVXVectorLength = 0;
    unsigned long AVXVectorLengthPrev = 0;
    
    std::vector<int> unstableModes;
    
    int AVX = 8;
    int AVXZeros = 0;
    int AVXZerosPrev = 0;
    float inputUse = 0.0;

    
    /*
     ==============================================================================
        GUI Variables
     ==============================================================================
    */
    double gain = 1.0;
    double Lx = 2.0;
    double Ly = 1.0;
    double C = 10.0;
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
    
    bool inputChange = false;
    bool outputLChange = false;
    bool outputRChange = false;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlateReverb2AudioProcessor)
};
