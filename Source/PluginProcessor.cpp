/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PlateReverb2AudioProcessor::PlateReverb2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
}

PlateReverb2AudioProcessor::~PlateReverb2AudioProcessor()
{
}

//==============================================================================
const String PlateReverb2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PlateReverb2AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PlateReverb2AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double PlateReverb2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PlateReverb2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int PlateReverb2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PlateReverb2AudioProcessor::setCurrentProgram (int index)
{
}

const String PlateReverb2AudioProcessor::getProgramName (int index)
{
    return {};
}

void PlateReverb2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

/*
 ==============================================================================
    Calculate Eigenfrequencies and Modes
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculateAndSortOmegaMatrix()
{
    std::vector<float> tempEigenFrequencies;
    std::vector<int> tempHorizontalModes;
    std::vector<int> tempVerticalModes;
    
    double val = 0.0;
    double m1 = 1.0;
    double m2 = 1.0;

    /*
     ==============================================================================
        Calculate Stable Eigenfrequencies
     ==============================================================================
    */
    
    while (val < fs * 2)
    {
        val = (pow ((m1 / Lx), 2) + pow ((m2 / Ly), 2)) * pow (kSq, 0.5) * pow (double_Pi, 2);
        
        if (val < fs * 2)
        {
            tempEigenFrequencies.push_back (val);
            tempHorizontalModes.push_back (m1);
            tempVerticalModes.push_back (m2);
            ++m2;
            
        } else {
            m2 = 1;
            ++m1;
            
            val = (pow ((m1 / Lx), 2) + pow ((m2 / Ly), 2)) * pow (kSq, 0.5) * pow (double_Pi, 2);
            
            if (val > fs * 2) //if (m1,1) > fs * 2, break out of the loop
            {
                break;
            }
        }
    }
    
    /*
     ==============================================================================
        Sort Vectors according to Eigenfrequencies
     ==============================================================================
    */
    
    int i = 0;
    while (i != tempEigenFrequencies.size())
    {
        if (tempEigenFrequencies[i] < tempEigenFrequencies[i-1])
        {
            int index (0);
            while (tempEigenFrequencies[i] > tempEigenFrequencies[index])
            {
                ++index;
            }
            tempEigenFrequencies.insert (tempEigenFrequencies.begin()+index, tempEigenFrequencies[i]);
            tempHorizontalModes.insert (tempHorizontalModes.begin()+index, tempHorizontalModes[i]);
            tempVerticalModes.insert (tempVerticalModes.begin()+index, tempVerticalModes[i]);
            tempEigenFrequencies.erase (tempEigenFrequencies.begin() + i + 1);
            tempHorizontalModes.erase (tempHorizontalModes.begin() + i + 1);
            tempVerticalModes.erase (tempVerticalModes.begin() + i + 1);
        }
        ++i;
    }
    
    sortedOmegaMatrix.setEigenFrequencies (tempEigenFrequencies);
    sortedOmegaMatrix.setHorizontalModes (tempHorizontalModes);
    sortedOmegaMatrix.setVerticalModes (tempVerticalModes);
    
}


/*
 ==============================================================================
    Delete Eigenfrequencies that are Close Together
 ==============================================================================
*/

void PlateReverb2AudioProcessor::deleteCents ()
{
    omegaPositionsPrev = omegaPositions;
    omegaPositions.clear();
    
    const std::vector<float>& eigenFrequenciesPre (sortedOmegaMatrix.getEigenFrequencies());
    const std::vector<int>& horizontalModesPre (sortedOmegaMatrix.getHorizontalModes());
    const std::vector<int>& verticalModesPre (sortedOmegaMatrix.getVerticalModes());

    vectorLength = eigenFrequenciesPre.size();
    
    eigenFrequencies.clear();
    horizontalModes.clear();
    verticalModes.clear();
    
    double omegaPrev = 0;
    double ncent = pow (pow (2.0, 1.0 / 12.0), (C / 100.0)) * (eigenFrequenciesPre[0] / (2.0 * double_Pi)) - eigenFrequenciesPre[0] / (2.0 * double_Pi);
    
    for (int n = 0; n < vectorLength; ++n)
    {
        //if (current eigenfrequency - saved eigenfrequency) < ncent, don't include eigenfrequency
        if (eigenFrequenciesPre[n] / (2.0*double_Pi) - omegaPrev / (2.0*double_Pi) >= ncent)
        {
            eigenFrequencies.push_back (eigenFrequenciesPre[n]);
            horizontalModes.push_back (horizontalModesPre[n]);
            verticalModes.push_back (verticalModesPre[n]);
            omegaPrev = eigenFrequenciesPre[n]; //otherwise set next saved eigenfrequency
            
            omegaPositions.push_back(n);
            
            // and calculate next ncent
            ncent = pow (pow (2, 1.0 / 12.0), (C / 100.0)) * (eigenFrequenciesPre[n] / (2.0 * double_Pi)) - eigenFrequenciesPre[n] / (2.0 * double_Pi);
        }
    }
    
    vectorLength = eigenFrequencies.size();
}

/*
 ==============================================================================
    Calculate the In- and Output coefficients (Phi)
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculatePhi()
{
    const double& inputX = positions.getInput().getX();
    const double& inputY = positions.getInput().getY();
    const double& outputLX = positions.getOutputL().getX();
    const double& outputLY = positions.getOutputL().getY();
    const double& outputRX = positions.getOutputR().getX();
    const double& outputRY = positions.getOutputR().getY();
    
    phiIn.clear();
    phiOutL.clear();
    phiOutR.clear();
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiIn.push_back (sin (horizontalModes[m] * double_Pi * inputX) * sin (verticalModes[m] * double_Pi * inputY));
        phiOutL.push_back (sin (horizontalModes[m] * double_Pi * outputLX) * sin (verticalModes[m] * double_Pi * outputLY));
        phiOutR.push_back (sin (horizontalModes[m] * double_Pi * outputRX) * sin (verticalModes[m] * double_Pi * outputRY));
        
    }

}

/*
 ==============================================================================
 Calculate the Coefficients for the Update Equation
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculateCoefficients()
{
    double cm = 12.0 * (log (10.0) / decay);
    
    double factorA;
    double factorB;
    double factorC;
    double factorIn;
    
    factorBdA.clear();
    factorCdA.clear();
    factorIndA.clear();
    
    factorA = 1.0 / pow (k, 2) + cm / (rho * h * k);
    factorC = cm / (rho * h * k) - 1.0 / pow (k, 2);
    
    for (int m = 0; m < vectorLength; ++m)
    {
        factorB = 2.0/ pow (k, 2) - pow (eigenFrequencies[m], 2);
        factorIn = phiIn[m] / (rho * h);
        factorIndA.push_back (static_cast<float> (factorIn / factorA));
        factorBdA.push_back (static_cast<float> (factorB / factorA));
        factorCdA.push_back (static_cast<float> (factorC / factorA));
    }

    
    for (int m = 0; m < unstableModes.size(); ++m)
    {
        factorBdA[unstableModes[m]] = 0;
        factorIndA[unstableModes[m]] = 0;
        
    }
    
}


/*
 ==============================================================================
    Converting Regular Variables to AVX-Compatible Variables
 ==============================================================================
*/

void PlateReverb2AudioProcessor::AVXAll(){
    
    for (int m = 0; m < AVXZeros; ++m)
    {
        phiOutL.push_back(0);
        phiOutR.push_back(0);
        factorBdA.push_back(0);
        factorCdA.push_back(0);
        factorIndA.push_back(0);
    }
    
    AVXVectorLength = (vectorLength + AVXZeros) / AVX;
    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    __phiOutL = __zeroVector;
    __phiOutR = __zeroVector;
    __factorBdA = __zeroVector;
    __factorCdA = __zeroVector;
    __factorIndA = __zeroVector;
    
    int n = 0;
    for (int m = 0; m < vectorLength + AVXZeros; m = m + AVX)
    {
        AVXPhiOutL (m, n);
        AVXPhiOutR (m, n);
        AVXFactorBdA (m, n);
        AVXFactorCdA (m, n);
        AVXFactorIndA (m, n);
        ++n;
    }
}

inline void PlateReverb2AudioProcessor::AVXPhiOutL (int m, int n)
{
    __phiOutL[n] = _mm256_setr_ps (phiOutL[m], phiOutL[m+1], phiOutL[m+2], phiOutL[m+3],
                                   phiOutL[m+4], phiOutL[m+5], phiOutL[m+6], phiOutL[m+7]);
}

inline void PlateReverb2AudioProcessor::AVXPhiOutR (int m, int n)
{
    __phiOutR[n] = _mm256_setr_ps (phiOutR[m], phiOutR[m+1], phiOutR[m+2], phiOutR[m+3],
                                   phiOutR[m+4], phiOutR[m+5], phiOutR[m+6], phiOutR[m+7]);}

inline void PlateReverb2AudioProcessor::AVXFactorBdA (int m, int n)
{
    __factorBdA[n] = _mm256_setr_ps (factorBdA[m], factorBdA[m+1], factorBdA[m+2], factorBdA[m+3],
                                     factorBdA[m+4], factorBdA[m+5], factorBdA[m+6], factorBdA[m+7]);
}

inline void PlateReverb2AudioProcessor::AVXFactorCdA (int m, int n)
{
    __factorCdA[n] = _mm256_setr_ps (factorCdA[m], factorCdA[m+1], factorCdA[m+2], factorCdA[m+3],
                                     factorCdA[m+4], factorCdA[m+5], factorCdA[m+6], factorCdA[m+7]);
}

inline void PlateReverb2AudioProcessor::AVXFactorIndA (int m, int n)
{
    __factorIndA[n] = _mm256_setr_ps (factorIndA[m], factorIndA[m+1], factorIndA[m+2], factorIndA[m+3],
                                      factorIndA[m+4], factorIndA[m+5], factorIndA[m+6], factorIndA[m+7]);
}

inline void PlateReverb2AudioProcessor::AVXQPrev (std::vector<float> qPrev, int m, int n)
{
    __qPrev[n] = _mm256_setr_ps (qPrev[m], qPrev[m+1], qPrev[m+2], qPrev[m+3],
                                 qPrev[m+4], qPrev[m+5], qPrev[m+6], qPrev[m+7]);
}

inline void PlateReverb2AudioProcessor::AVXQNow (std::vector<float> qNow, int m, int n)
{
    __qNow[n] = _mm256_setr_ps (qNow[m], qNow[m+1], qNow[m+2], qNow[m+3],
                                qNow[m+4], qNow[m+5], qNow[m+6], qNow[m+7]);
}


/*
 ==============================================================================
    Activated when the Plate is Stretched
 ==============================================================================
*/

void PlateReverb2AudioProcessor::plateStretching()
{
    double cm = 12.0 * (log (10.0) / decay);
    double factorB;
    double factorA = 1.0 / pow(k, 2) + cm / (rho * h * k);
    double factorIn;
    
    double val = 0.0;

    factorIndA.clear();
    unstableModes.clear();
    
    calculatePhi();
    
    
    for (int m = 0; m < vectorLength; ++m)
    {
        factorIn = phiIn[m] / (rho * h);
        factorIndA.push_back (static_cast<float> (factorIn / factorA));
        
        val = (pow ((horizontalModes[m] / Lx), 2) + pow ((verticalModes[m] / Ly), 2)) * pow (kSq, 0.5) * pow(double_Pi, 2); //calculate eigenfrequency
        if (val < fs * 2)
        {
            factorB = 2.0 / pow(k, 2) - pow (val,2);
            factorBdA[m] = (static_cast<float> (factorB / factorA));
            
        } else {
            factorBdA[m] = 0;
            unstableModes.push_back(m);
        }
        
    }
    
    std::vector<float> qPrev;
    std::vector<float> qNow;
    
    for (int m = 0; m < AVXVectorLength; ++m)
    {
        float* qPrevPtr = (float*)&__qPrev[m];
        float* qNowPtr = (float*)&__qNow[m];
    
        for (int n = 0; n < AVX; ++n){
            qPrev.push_back (qPrevPtr[n]);
            qNow.push_back (qNowPtr[n]);
        }
    }
    
    /*
     ==============================================================================
        Make sure unstable modes have zero influence on the update equation
     ==============================================================================
    */
    
    for (int m = 0; m < unstableModes.size(); ++m)
    {
        qNow[unstableModes[m]] = 0;
        qPrev[unstableModes[m]] = 0;
        factorIndA[unstableModes[m]] = 0;
        //phiOutL[unstableModes[m]] = 0;
        //phiOutR[unstableModes[m]] = 0;
    }
    
    for (int m = 0; m < AVXZeros; ++m)
    {
        factorIndA.push_back(0);
    }
    
    int n = 0;
    for (int m = 0; m < vectorLength + AVXZeros; m = m + AVX)
    {
        AVXQNow(qNow, m, n);
        AVXQPrev(qPrev, m, n);
        AVXFactorIndA(m, n);
        AVXFactorBdA(m, n);
        //AVXPhiOutL(m, n);
        //AVXPhiOutR(m, n);
        ++n;
    }

}

/*
 ==============================================================================
    Activated when Flanging is recalculated
 ==============================================================================
*/

void PlateReverb2AudioProcessor::setFlanging(bool left)
{
    const double detail (fs/2.0);

    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    std::vector<std::vector<__m256>> __zeroMatrix (detail + 1, __zeroVector);
    
    /*
     ==============================================================================
        Recalculate Left Output
     ==============================================================================
    */
    
    if (left == true)
    {
        std::vector<float> phiOutLFlange;
        std::vector<double> outputLX;
        std::vector<double> outputLY;
        
        for(double t = 0.0; t <= detail; ++t)
        {
            outputLX.push_back (radiusLX * sin (speedLX * 2 * double_Pi * t / detail + phaseLX) + 0.5);
            outputLY.push_back (radiusLY * sin (speedLY * 2 * double_Pi * t / detail + phaseLY) + 0.5);
        }
        
        std::vector<float> phiOutLTemp (vectorLength + AVXZeros, 0);
        std::vector<__m256> __phiOutLTemp (AVXVectorLength, _mm256_setzero_ps());
        __phiOutLFlange = __zeroMatrix;
        
        for (int t = 0; t <= detail; ++t)
        {
            for (int m = 0; m < vectorLength; ++m)
            {
                phiOutLTemp[m] = static_cast<float> (sin (horizontalModes[m] * double_Pi * outputLX[t])
                                                     * sin (verticalModes[m] * double_Pi * outputLY[t]));
            }
            
            int n = 0;
            for (int m = 0; m < vectorLength + AVXZeros; m = m + AVX)
            {
                __phiOutLTemp[n] = _mm256_setr_ps (phiOutLTemp[m], phiOutLTemp[m+1], phiOutLTemp[m+2], phiOutLTemp[m+3], phiOutLTemp[m+4],
                                                   phiOutLTemp[m+5], phiOutLTemp[m+6], phiOutLTemp[m+7]);
                ++n;
            }
            __phiOutLFlange[t] = __phiOutLTemp;
        }
        
        
    } else {
        
    /*
    ==============================================================================
        Recalculate Right Output
    ==============================================================================
    */
        
        std::vector<float> phiOutRFlange;
        std::vector<double> outputRX;
        std::vector<double> outputRY;
        
        for(double t = 0.0; t <= detail; ++t)
        {
            outputRX.push_back (radiusRX * sin (speedRX * 2 * double_Pi * t / detail + phaseRX) + 0.5);
            outputRY.push_back (radiusRY * sin (speedRY * 2 * double_Pi * t / detail + phaseRY) + 0.5);
        }
        
        std::vector<float> phiOutRTemp (vectorLength + AVXZeros, 0);
        std::vector<__m256> __phiOutRTemp (AVXVectorLength, _mm256_setzero_ps());
        __phiOutRFlange = __zeroMatrix;
        
        for (int t = 0; t <= detail; ++t)
        {
            for (int m = 0; m < vectorLength; ++m)
            {
            phiOutRTemp[m] = static_cast<float> (sin (horizontalModes[m] * double_Pi * outputRX[t])
                                                 * sin (verticalModes[m] * double_Pi * outputRY[t]));
                
            }
            
            int n = 0;
            for (int m = 0; m < vectorLength + AVXZeros; m = m + AVX)
            {
                __phiOutRTemp[n] = _mm256_setr_ps (phiOutRTemp[m], phiOutRTemp[m+1], phiOutRTemp[m+2], phiOutRTemp[m+3], phiOutRTemp[m+4],
                                                   phiOutRTemp[m+5], phiOutRTemp[m+6], phiOutRTemp[m+7]);
                ++n;
            }
            __phiOutRFlange[t] = __phiOutRTemp;
        }
        
    }

}

/*
 ==============================================================================
    Activated when the Input Location has changed
 ==============================================================================
*/


void PlateReverb2AudioProcessor::calculateFactorIndA()
{
    double inputX (positions.getInput().getX());
    double inputY (positions.getInput().getY());
    
    double cm = 12.0 * (log (10.0) / decay);
    
    double factorA = 1.0 / pow (k, 2) + cm / (rho * h * k);
    double phiIn;
    
    factorIndA.clear();
    for (int m = 0; m < vectorLength + AVXZeros; ++m)
    {
        factorIndA.push_back(0);
    }
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiIn = (sin (horizontalModes[m] * double_Pi * inputX) * sin (verticalModes[m] * double_Pi * inputY));
        factorIndA[m] = static_cast<float> ((phiIn / (rho * h)) / factorA);
    }
    
    for (int m = 0; m < unstableModes.size(); ++m)
    {
        factorIndA[m] = 0;
    }
    
    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    __factorIndA = __zeroVector;
    
    int n = 0;
    for (int m = 0; m < AVXVectorLength; ++m)
    {
        AVXFactorIndA(m, n);
        ++n;
    }
    
}

/*
 ==============================================================================
    Activated when the Left Output Location has changed
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculatePhiOutL()
{
    double outputLX (positions.getOutputL().getX());
    double outputLY (positions.getOutputL().getY());
        
    phiOutL.clear();
    for (int m = 0; m < vectorLength + AVXZeros; ++m)
    {
        phiOutL.push_back(0);
    }
    
    AVXVectorLength = (vectorLength + AVXZeros) / AVX;
    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    __phiOutL = __zeroVector;
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiOutL[m] = sin (horizontalModes[m] * double_Pi * outputLX) * sin (verticalModes[m] * double_Pi * outputLY);
    }
    
    int n = 0;
    for (int m = 0; m < AVXVectorLength; ++m)
    {
        AVXPhiOutL(m, n);
        ++n;
    }
    
}

/*
 ==============================================================================
    Activated when the Right Output Location has changed
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculatePhiOutR()
{
    double outputRX (positions.getOutputR().getX());
    double outputRY (positions.getOutputR().getY());
    
    phiOutR.clear();
    for (int m = 0; m < vectorLength + AVXZeros; ++m)
    {
        phiOutR.push_back(0);
    }
    
    AVXVectorLength = (vectorLength + AVXZeros) / AVX;
    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    __phiOutR = __zeroVector;
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiOutR[m] = sin (horizontalModes[m] * double_Pi * outputRX) * sin (verticalModes[m] * double_Pi * outputRY);
    }
    
    int n = 0;
    for (int m = 0; m < AVXVectorLength; ++m)
    {
        AVXPhiOutR(m, n);
        ++n;
    }

}

void PlateReverb2AudioProcessor::createNewQVectors()
{
    
    vectorLength = eigenFrequencies.size();
    AVXZeros = ((AVX - (vectorLength % AVX)) % AVX);
    AVXVectorLength = (vectorLength + AVXZeros) / AVX;

    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    
    __qPrev = __zeroVector;
    __qNow = __zeroVector;
    
}


//==============================================================================
void PlateReverb2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    calculateAndSortOmegaMatrix();
    deleteCents();
    calculatePhi();
    calculateCoefficients();
    
    vectorLength = eigenFrequencies.size();
    AVXZeros = ((AVX - (vectorLength % AVX)) % AVX);
    AVXVectorLength = (vectorLength + AVXZeros) / AVX;
    AVXAll();
    
    setFlanging (true);
    setFlanging (false);
    
    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());
    __qNow = __zeroVector;
    __qPrev = __zeroVector;

}

void PlateReverb2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PlateReverb2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void PlateReverb2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = 1;
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    std::vector<float> outputChannel2;
    const float* inputData (buffer.getReadPointer (0));
    
    //check for control flags and act accordingly
    if (recalculateLFlag == true)
    {
        setFlanging(true);
        recalculateLFlag = false;
    }
    
    if (recalculateRFlag == true)
    {
        setFlanging(false);
        recalculateRFlag = false;
    }
    
    if (inputChange == true)
    {
        calculateFactorIndA();
        inputChange = false;
    }
    
    if (outputLChange == true)
    {
        calculatePhiOutL();
        outputLChange = false;
    }
    
    if (outputRChange == true)
    {
        calculatePhiOutR();
        outputRChange = false;
    }
    
    if (decayFlag == true)
    {
        calculateCoefficients();
        AVXAll();
        decayFlag = false;
    }

    if (stretchFlag == true)
    {
        plateStretching();
        stretchFlag = false;
    }
    
    //initialise short-scope loopvariables
    std::vector<__m256> __zeroVector (AVXVectorLength, _mm256_setzero_ps());

    std::vector<__m256> __qNext (__zeroVector);
    std::vector<__m256> __resultL (__zeroVector);
    std::vector<__m256> __resultR (__zeroVector);

    int posUseL;
    int posUseR;
    
    std::vector<__m256> __phiOutLFlangeUse (__zeroVector);
    std::vector<__m256> __phiOutRFlangeUse (__zeroVector);

    float outputSumL = 0.0;
    float outputSumR = 0.0;
    
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        float* outputData = buffer.getWritePointer (channel);
        for (int i = 0; i < numSamples; ++i)
        {
            outputSumL = 0.0;
            outputSumR = 0.0;
            
            if (flangingL == true)
            {
                posUseL = (static_cast<int> (pos / (2 * fs / __phiOutLFlange.size())) % static_cast<int> (__phiOutLFlange.size()));
            }
            
            if (flangingR == true)
            {
                posUseR = (static_cast<int> (pos / (2 * fs / __phiOutRFlange.size())) % static_cast<int> (__phiOutRFlange.size()));
            }
            
            __m256 __inputUse (_mm256_setr_ps (inputUse, inputUse, inputUse, inputUse, inputUse, inputUse, inputUse, inputUse));

            /*
             ==============================================================================
                Main Loop
             ==============================================================================
            */
            
            if (channel == 0)
            {
                if (flangingL == true)
                {
                    __phiOutLFlangeUse = __phiOutLFlange[posUseL];
                }
                
                if (flangingR == true)
                {
                    __phiOutRFlangeUse = __phiOutRFlange[posUseR];
                }
    
                
                //for all available modes do...
                for (int m = 0; m < AVXVectorLength; ++m)
                {
                    
                    __qNext[m] = _mm256_add_ps (_mm256_add_ps (_mm256_mul_ps (__factorBdA[m], __qNow[m]),
                                                               _mm256_mul_ps (__factorCdA[m], __qPrev[m])),
                                                _mm256_mul_ps (__factorIndA[m], __inputUse));
                    if (flangingL == true)
                    {
                        __resultL[m] = _mm256_mul_ps (__qNext[m], __phiOutLFlangeUse[m]);
                    } else {
                        __resultL[m] = _mm256_mul_ps (__qNext[m], __phiOutL[m]);
                    }
                    
                    if (flangingR == true)
                    {
                        __resultR[m] = _mm256_mul_ps (__qNext[m], __phiOutRFlangeUse[m]);
                    } else {
                        __resultR[m] = _mm256_mul_ps (__qNext[m], __phiOutR[m]);
                    }
                    

                    float* resultL = (float*)&__resultL[m];
                    float* resultR = (float*)&__resultR[m];
                    
                    for (int n = 0; n < AVX; ++n){
                        outputSumL = outputSumL + resultL[n];
                        outputSumR = outputSumR + resultR[n];
                    }
                
                    __qPrev[m] = __qNow[m];
                    __qNow[m] = __qNext[m];
                    inputUse = inputData[i] / 2;
                    //inputUse = 1;
                }
                
                ++pos;
                
                outputData[i] = (outputSumL * 1500.0) * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0;
                outputChannel2.push_back ((outputSumR * 1500.0) * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0);
                
                //if the output becomes too loud reset QVectors
                if (std::abs (outputSumL * 1500.0 * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0) > 4.0
                    || std::abs (outputSumR * 1500.0 * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0) > 4.0){
                    std::cout<<"Whoops!"<<std::endl;
                    createNewQVectors();
                    outputSumL = 0.0;
                    outputSumR = 0.0;
                    outputChannel2[i-1] = 0;
                }
                
            } else {
                //right output channel
                outputData[i] = outputChannel2[i];
            }
            
        }
    }
}

//==============================================================================
bool PlateReverb2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PlateReverb2AudioProcessor::createEditor()
{
    return new PlateReverb2AudioProcessorEditor (*this);
}

//==============================================================================
void PlateReverb2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PlateReverb2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PlateReverb2AudioProcessor();
}
