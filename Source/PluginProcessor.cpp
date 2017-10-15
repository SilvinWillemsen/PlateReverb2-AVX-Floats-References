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
    The Quicksort Algorithm will be used to sort the eigenfrequencies
 ==============================================================================
*/

void quickSort(std::vector<float>& eigenFrequencies, std::vector<int>& horizontalModes, std::vector<int>& verticalModes, int left, int right) {
    int i = left, j = right;
    float tempEigenFrequency;
    int tempHorizontalMode;
    int tempVerticalMode;
    float pivot = eigenFrequencies[(left + right) / 2];
    
    while (i <= j)
    {
        while (eigenFrequencies[i] < pivot)
            i++;
        while (eigenFrequencies[j] > pivot)
            j--;
        if (i <= j)
        {
            tempEigenFrequency = eigenFrequencies[i];
            eigenFrequencies[i] = eigenFrequencies[j];
            eigenFrequencies[j] = tempEigenFrequency;
            
            tempHorizontalMode = horizontalModes[i];
            horizontalModes[i] = horizontalModes[j];
            horizontalModes[j] = tempHorizontalMode;
            
            tempVerticalMode = verticalModes[i];
            verticalModes[i] = verticalModes[j];
            verticalModes[j] = tempVerticalMode;
            i++;
            j--;
        }
    };
    
    //recursion
    if (left < j)
        quickSort(eigenFrequencies, horizontalModes, verticalModes, left, j);
    if (i < right)
        quickSort(eigenFrequencies, horizontalModes, verticalModes, i, right);
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
    
    //initialise loopvariables
    double omega = 0.0;
    double m1 = 1.0;
    double m2 = 1.0;

    /*
     ==============================================================================
        Calculate Stable Eigenfrequencies
     ==============================================================================
    */
    
    while (omega < fs * 2) //while the eigenfrequency satisfies the stability condition 'eigenfrequency < 2fs'...
    {
        omega = (pow ((m1 / Lx), 2) + pow ((m2 / Ly), 2)) * pow (kSq, 0.5) * pow (double_Pi, 2);
        
        if (omega < fs * 2) //if the newly calculated eigenfreuqency still satisfies the stability condition, add it to the vector
        {
            tempEigenFrequencies.push_back (omega); //eigenfrequency value
            tempHorizontalModes.push_back (m1);     //corresponding horizontal mode
            tempVerticalModes.push_back (m2);       //corresponding vertical mode
            ++m2;                                   //increment the vertical mode
            
        } else {
            m2 = 1;                                 //reset the vertical mode
            ++m1;                                   //and increment the horizontal mode
            
            omega = (pow ((m1 / Lx), 2) + pow ((m2 / Ly), 2)) * pow (kSq, 0.5) * pow (double_Pi, 2);
            
            if (omega > fs * 2) //if (m1,1) > 2fs, break out of the loop
            {
                break;
            }
        }
    }
    
    //(quick)sort vectors according to eigenfrequency values
    quickSort(tempEigenFrequencies, tempHorizontalModes, tempVerticalModes, 0, static_cast<int> (tempEigenFrequencies.size() - 1));
    
    vectorLength = tempEigenFrequencies.size();
    
    //move the (sorted) temporary values in the sortedOmegaMatrix variable
    sortedOmegaMatrix.setEigenFrequencies (std::move (tempEigenFrequencies));
    sortedOmegaMatrix.setHorizontalModes (std::move (tempHorizontalModes));
    sortedOmegaMatrix.setVerticalModes (std::move (tempVerticalModes));
    
}

/*
 ==============================================================================
    Delete Eigenfrequencies that are close together
 ==============================================================================
*/

void PlateReverb2AudioProcessor::deleteCents()
{
    //retrieve the sorted eigenfrequency matrix
    const std::vector<float>& sortedEigenFrequencies (sortedOmegaMatrix.getEigenFrequencies());
    const std::vector<int>& sortedHorizontalModes (sortedOmegaMatrix.getHorizontalModes());
    const std::vector<int>& sortedVerticalModes (sortedOmegaMatrix.getVerticalModes());
    
    //clearing vectors is needed if this function is used after initialisation
    eigenFrequencies.clear();
    horizontalModes.clear();
    verticalModes.clear();
    
    double omegaPrev = 0;
    
    //calculate difference between two eigenfrequencies according to parameter C (cents)
    double diff = pow (pow (2.0, 1.0 / 12.0), (C / 100.0)) * (sortedEigenFrequencies[0] / (2.0 * double_Pi))
                   - sortedEigenFrequencies[0] / (2.0 * double_Pi);
    
    for (int n = 0; n < vectorLength; ++n)
    {
        //if (current eigenfrequency - saved eigenfrequency) > diff, include eigenfrequency
        if (sortedEigenFrequencies[n] / (2.0 * double_Pi) - omegaPrev / (2.0 * double_Pi) >= diff)
        {
            eigenFrequencies.push_back (sortedEigenFrequencies[n]);
            horizontalModes.push_back (sortedHorizontalModes[n]);
            verticalModes.push_back (sortedVerticalModes[n]);
            omegaPrev = sortedEigenFrequencies[n]; //set the next saved eigenfrequency

            // and calculate next diff
            diff = pow (pow (2, 1.0 / 12.0), (C / 100.0)) * (sortedEigenFrequencies[n] / (2.0 * double_Pi))
                    - sortedEigenFrequencies[n] / (2.0 * double_Pi);
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
    //retrieve input and (left and right) output positions
    const double& inputX = positions.getInput().getX();
    const double& inputY = positions.getInput().getY();
    const double& outputLX = positions.getOutputL().getX();
    const double& outputLY = positions.getOutputL().getY();
    const double& outputRX = positions.getOutputR().getX();
    const double& outputRY = positions.getOutputR().getY();
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiIn[m] = sin (horizontalModes[m] * double_Pi * inputX) * sin (verticalModes[m] * double_Pi * inputY);
        phiOutL[m] = sin (horizontalModes[m] * double_Pi * outputLX) * sin (verticalModes[m] * double_Pi * outputLY);
        phiOutR[m] = sin (horizontalModes[m] * double_Pi * outputRX) * sin (verticalModes[m] * double_Pi * outputRY);
        
    }

}

/*
 ==============================================================================
    Calculate the Coefficients for the Update Equation
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculateCoefficients()
{
    //calculate loss coefficient and coefficients A and C
    const double lossCoef = 12.0 * (log (10.0) / decay);
    const double coefA = 1.0 / pow (k, 2) + lossCoef / (rho * h * k);
    const double coefC = lossCoef / (rho * h * k) - 1.0 / pow (k, 2);
    
    double coefB;
    double coefIn;
    
    //if there are no unstable eigenfrequencies, insert an unused index to make the unstableEigenFrequencies vector non-zero
    if (unstableEigenFrequencies.size() == 0)
    {
        unstableEigenFrequencies = { static_cast<int>(vectorLength + AVXZeros + 1) };
    }
    
    int i = 0;
    for (int m = 0; m < vectorLength; ++m)
    {
        if (m == unstableEigenFrequencies[i])
        {
            coefIndA[m] = 0;
            coefBdA[m] = 0;
            coefCdA[m] = 0;
            ++i;
        } else {
            coefB = 2.0 / pow (k, 2) - pow (eigenFrequencies[m], 2);
            coefIn = phiIn[m] / (rho * h);
            coefIndA[m] = static_cast<float> (coefIn / coefA);
            coefBdA[m] = static_cast<float> (coefB / coefA);
            coefCdA[m] = static_cast<float> (coefC / coefA);
        }
    }
    
}

/*
 ==============================================================================
    Converting Regular Variables to AVX-Compatible Variables
 ==============================================================================
*/

void PlateReverb2AudioProcessor::AVXAll(){

    //initialise AVX vectors
    AVXZeros = ((AVX - (vectorLength % AVX)) % AVX);    //calculate how many zeros are needed for zeropadding
    AVXVectorLength = (vectorLength + AVXZeros) / AVX;
    __phiOutL = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __phiOutR = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __coefBdA = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __coefCdA = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __coefIndA = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    
    float* phiOutLPtr = (float*)&__phiOutL[0];
    float* phiOutRPtr = (float*)&__phiOutR[0];
    float* coefBdAPtr = (float*)&__coefBdA[0];
    float* coefCdAPtr = (float*)&__coefCdA[0];
    float* coefIndAPtr = (float*)&__coefIndA[0];
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiOutLPtr[m] = phiOutL[m];
        phiOutRPtr[m] = phiOutR[m];
        coefBdAPtr[m] = coefBdA[m];
        coefCdAPtr[m] = coefCdA[m];
        coefIndAPtr[m] = coefIndA[m];
    }
}


/*
 ==============================================================================
    Activated when the Plate is Stretched
 ==============================================================================
*/

void PlateReverb2AudioProcessor::plateStretching()
{
    unstableEigenFrequencies.clear();
    
    const double lossCoef = 12.0 * (log (10.0) / decay);
    const double coefA = 1.0 / pow(k, 2) + lossCoef / (rho * h * k);
    const double coefC = lossCoef / (rho * h * k) - 1.0 / pow (k, 2);
    
    double coefB;
    double coefIn;
    double omega = 0.0;
    
    float* coefBdAPtr = (float*)&__coefBdA[0];
    float* coefCdAPtr = (float*)&__coefCdA[0];
    float* coefIndAPtr = (float*)&__coefIndA[0];
    
    for (int m = 0; m < vectorLength; ++m)
    {
        omega = (pow ((horizontalModes[m] / Lx), 2) + pow ((verticalModes[m] / Ly), 2)) * pow (kSq, 0.5) * pow(double_Pi, 2); //calculate eigenfrequency
        if (omega < fs * 2) //if the eigenfrequency is stable, calculate coefBdA normally
        {
            eigenFrequencies[m] = omega;
            coefB = 2.0 / pow(k, 2) - pow (omega, 2);
            coefIn = phiIn[m] / (rho * h);
            
            coefBdA[m] = (static_cast<float> (coefB / coefA));
            coefCdA[m] = static_cast<float> (coefC / coefA);
            coefIndA[m] = static_cast<float> (coefIn / coefA);
            
            //insert directly into AVX variables
            coefBdAPtr[m] = coefBdA[m];
            coefCdAPtr[m] = coefCdA[m];
            coefIndAPtr[m] = coefIndA[m];

        } else { //save the index of the unstable eigenfrequency
            eigenFrequencies[m] = 0;
            
            coefBdA[m] = 0;
            coefBdAPtr[m] = 0;
            
            coefCdA[m] = 0;
            coefCdAPtr[m] = 0;
            
            coefIndA[m] = 0;
            coefIndAPtr[m] = 0;
            unstableEigenFrequencies.push_back(m);
        }
        
    }
    
    /*
     ==============================================================================
        Make sure unstable modes have zero influence on the update equation
     ==============================================================================
    */
    
    float* qPrevPtr = (float*)&__qPrev[0];
    float* qNowPtr = (float*)&__qNow[0];
    
    for (int m = 0; m < unstableEigenFrequencies.size(); ++m)
    {
        qPrevPtr[unstableEigenFrequencies[m]] = 0;
        qNowPtr[unstableEigenFrequencies[m]] = 0;
    }

}


void PlateReverb2AudioProcessor::decayChange()
{
    //calculate loss coefficient and coefficients A and C
    const double lossCoef = 12.0 * (log (10.0) / decay);
    const double coefA = 1.0 / pow (k, 2) + lossCoef / (rho * h * k);
    const double coefC = lossCoef / (rho * h * k) - 1.0 / pow (k, 2);
    
    double coefB;
    double coefIn;
    
    //if there are no unstable eigenfrequencies, insert an unused index to make the unstableEigenFrequencies vector non-zero
    if (unstableEigenFrequencies.size() == 0)
    {
        unstableEigenFrequencies = { static_cast<int>(vectorLength + AVXZeros + 1) };
    }
    
    float* coefBdAPtr = (float*)&__coefBdA[0];
    float* coefCdAPtr = (float*)&__coefCdA[0];
    float* coefIndAPtr = (float*)&__coefIndA[0];
    
    int i = 0;
    for (int m = 0; m < vectorLength; ++m)
    {
        if (m == unstableEigenFrequencies[i])
        {
            coefBdA[m] = 0;
            coefCdA[m] = 0;
            coefIndA[m] = 0;
            
            coefBdAPtr[m] = 0;
            coefCdAPtr[m] = 0;
            coefIndAPtr[m] = 0;
            
            ++i;
        } else {
            coefB = 2.0 / pow (k, 2) - pow (eigenFrequencies[m], 2);
            coefIn = phiIn[m] / (rho * h);
            
            coefIndA[m] = static_cast<float> (coefIn / coefA);
            coefBdA[m] = static_cast<float> (coefB / coefA);
            coefCdA[m] = static_cast<float> (coefC / coefA);
            
            coefIndAPtr[m] = coefIndA[m];
            coefBdAPtr[m] = coefBdA[m];
            coefCdAPtr[m] = coefCdA[m];
        }
    }
    
}

/*
 ==============================================================================
    Activated when the Flanging of the left output is recalculated
 ==============================================================================
*/

void PlateReverb2AudioProcessor::setFlangingL()
{
    double outputLX = 0.0;
    double outputLY = 0.0;
    
    // calculate all left output positions over one second using parameters from the UI
    int n;
    for (int t = 0; t <= detail; ++t)
    {
        float* phiOutLFlangePtr = (float*)&__phiOutLFlange[t][0];
        outputLX = radiusLX * sin (speedLX * 2 * double_Pi * t / detail + phaseLX) + 0.5;
        outputLY = radiusLY * sin (speedLY * 2 * double_Pi * t / detail + phaseLY) + 0.5;
        
        n = 0;
        for (int m = 0; m < vectorLength; ++m)
        {
            phiOutLFlangePtr[m] = static_cast<float> (sin (horizontalModes[m] * double_Pi * outputLX)
                                                      * sin (verticalModes[m] * double_Pi * outputLY));
        }

    }
}

/*
 ==============================================================================
    Activated when the Flanging of the right output is recalculated
 ==============================================================================
*/


void PlateReverb2AudioProcessor::setFlangingR()
{
    double outputRX = 0.0;
    double outputRY = 0.0;
    
    // calculate all right output positions over one second using parameters from the UI
    int n;
    for (int t = 0; t <= detail; ++t)
    {
        float* phiOutRFlangePtr = (float*)&__phiOutRFlange[t][0];
        outputRX = radiusRX * sin (speedRX * 2 * double_Pi * t / detail + phaseRX) + 0.5;
        outputRY = radiusRY * sin (speedRY * 2 * double_Pi * t / detail + phaseRY) + 0.5;
        
        n = 0;
        for (int m = 0; m < vectorLength; ++m)
        {
            phiOutRFlangePtr[m] = static_cast<float> (sin (horizontalModes[m] * double_Pi * outputRX)
                                                      * sin (verticalModes[m] * double_Pi * outputRY));
        }
        
    }
}

/*
 ==============================================================================
    Activated when the Input Location has changed
 ==============================================================================
*/


void PlateReverb2AudioProcessor::calculateCoefIndA()
{
    //retrieve input locations
    const double& inputX = positions.getInput().getX();
    const double& inputY = positions.getInput().getY();

    //calculate loss coefficient and coefficient A
    const double lossCoef = 12.0 * (log (10.0) / decay);
    const double coefA = 1.0 / pow (k, 2) + lossCoef / (rho * h * k);
    
    double phiIn;

    //if there are no unstable eigenfrequencies, insert an unused index to make the unstableEigenFrequencies vector non-zero
    if (unstableEigenFrequencies.size() == 0)
    {
        unstableEigenFrequencies = { static_cast<int>(vectorLength + AVXZeros + 1) };
    }
    
    int i = 0;
    float* coefIndAPtr = (float*)&__coefIndA[0];
    
    for (int m = 0; m < vectorLength; ++m)
    {
        if (m == unstableEigenFrequencies[i])
        {
            coefIndA[m] = 0;
            ++i;
        } else {
            phiIn = (sin (horizontalModes[m] * double_Pi * inputX) * sin (verticalModes[m] * double_Pi * inputY));
            coefIndA[m] = static_cast<float> ((phiIn / (rho * h)) / coefA);
            coefIndAPtr[m] = coefIndA[m];

        }
        
    }

}

/*
 ==============================================================================
    Activated when the Left Output Location has changed
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculatePhiOutL()
{
    const double& outputLX = positions.getOutputL().getX();
    const double& outputLY = positions.getOutputL().getY();

    float* phiOutLPtr = (float*)&__phiOutL[0];
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiOutL[m] = sin (horizontalModes[m] * double_Pi * outputLX) * sin (verticalModes[m] * double_Pi * outputLY);
        phiOutLPtr[m] = phiOutL[m];
    }
    
}

/*
 ==============================================================================
    Activated when the Right Output Location has changed
 ==============================================================================
*/

void PlateReverb2AudioProcessor::calculatePhiOutR()
{
    const double& outputRX = positions.getOutputR().getX();
    const double& outputRY = positions.getOutputR().getY();
    
    float* phiOutRPtr = (float*)&__phiOutR[0];
    
    for (int m = 0; m < vectorLength; ++m)
    {
        phiOutR[m] = sin (horizontalModes[m] * double_Pi * outputRX) * sin (verticalModes[m] * double_Pi * outputRY);
        phiOutRPtr[m] = phiOutR[m];
    }

}

void PlateReverb2AudioProcessor::createNewQVectors()
{
    __qPrev = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __qNow = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    
}


//==============================================================================
void PlateReverb2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //Initialise the Eigenfrequency Matrix (Omega, Horizontal Modes and Vertical Modes)
    calculateAndSortOmegaMatrix();
    deleteCents();

    //Initialise the In- and Output Coefficients
    phiIn = std::vector<double> (vectorLength, 0.0);
    phiOutL = std::vector<float> (vectorLength, 0.0);
    phiOutR = std::vector<float> (vectorLength, 0.0);
    calculatePhi();
    
    //Initialise the other Coefficients needed for the update equation
    coefBdA = std::vector<float> (vectorLength, 0.0);
    coefCdA = std::vector<float> (vectorLength, 0.0);
    coefIndA = std::vector<float> (vectorLength, 0.0);
    calculateCoefficients();
    
    //Convert all that is calculated above to AVX-Compatible variables (/vectors)
    AVXAll();

    //Initialise Matrices that will be used for Moving/Flanging Outputs
    __phiOutLFlange = std::vector<std::vector<__m256>> (detail + 1, std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps()));
    __phiOutRFlange = std::vector<std::vector<__m256>> (detail + 1, std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps()));
    setFlangingL();
    setFlangingR();
    
    __phiOutLFlangeUse = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __phiOutRFlangeUse = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    
    //Initialise other vectors
    __qNow = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __qPrev = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __qNext = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());
    __resultL = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());;
    __resultR = std::vector<__m256> (AVXVectorLength, _mm256_setzero_ps());;

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
    
    /*
     ==============================================================================
        Check for UI Flags and act accordingly
     ==============================================================================
    */
    
    if (recalculateLFlag)
    {
        setFlangingL();
        recalculateLFlag = false;
    }
    
    if (recalculateRFlag)
    {
        setFlangingR();
        recalculateRFlag = false;
    }
    
    if (inputChange)
    {
        calculateCoefIndA();
        inputChange = false;
    }
    
    if (outputLChange)
    {
        calculatePhiOutL();
        outputLChange = false;
    }
    
    if (outputRChange)
    {
        calculatePhiOutR();
        outputRChange = false;
    }
    
    if (decayFlag)
    {
        decayChange();
        decayFlag = false;
    }

    if (stretchFlag)
    {
        plateStretching();
        stretchFlag = false;
    }
    
    int posUseL;
    int posUseR;

    float outputSumL;
    float outputSumR;
    
    for (int channel = 0; channel < totalNumOutputChannels; ++channel) //for all channels do...
    {
        float* outputData = buffer.getWritePointer (channel);
        for (int i = 0; i < numSamples; ++i) //for all samples in the buffer do...
        {
            outputSumL = 0.0;
            outputSumR = 0.0;
            
            if (flangingL) //if the left microphone is moving do...
            {
                posUseL = (static_cast<int> (pos / (2 * fs / __phiOutLFlange.size())) % static_cast<int> (__phiOutLFlange.size()));
                
            }
            
            if (flangingR)
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
                if (flangingL)
                {
                    __phiOutLFlangeUse = __phiOutLFlange[posUseL];
                }
                
                if (flangingR)
                {
                    __phiOutRFlangeUse = __phiOutRFlange[posUseR];
                }
    
                
                //for all modes do...
                for (int m = 0; m < AVXVectorLength; ++m)
                {
                    //The update equation
                    __qNext[m] = _mm256_add_ps (_mm256_add_ps (_mm256_mul_ps (__coefBdA[m], __qNow[m]),
                                                               _mm256_mul_ps (__coefCdA[m], __qPrev[m])),
                                                _mm256_mul_ps (__coefIndA[m], __inputUse));
                    if (flangingL)
                    {
                        __resultL[m] = _mm256_mul_ps (__qNext[m], __phiOutLFlangeUse[m]);
                    } else {
                        __resultL[m] = _mm256_mul_ps (__qNext[m], __phiOutL[m]);
                    }
                    
                    if (flangingR)
                    {
                        __resultR[m] = _mm256_mul_ps (__qNext[m], __phiOutRFlangeUse[m]);
                    } else {
                        __resultR[m] = _mm256_mul_ps (__qNext[m], __phiOutR[m]);
                    }
                    
                    resultL = (float*)&__resultL[m];
                    resultR = (float*)&__resultR[m];
                    
                    for (int n = 0; n < AVX; ++n)
                    {
                        outputSumL = outputSumL + resultL[n];
                        outputSumR = outputSumR + resultR[n];
                    }
                
                    __qPrev[m] = __qNow[m];
                    __qNow[m] = __qNext[m];
                    inputUse = inputData[i] / 2;
                }
                
                ++pos;
                
                outputData[i] = (outputSumL * 1500.0) * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0;
                outputChannel2.push_back ((outputSumR * 1500.0) * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0);
                
                //if the output becomes too loud
                if (std::abs (outputSumL * 1500.0 * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0) > 4.0
                    || std::abs (outputSumR * 1500.0 * gain + (inputData[i] / 2) * (100.0 - gain) / 100.0) > 4.0){
                    std::cout<<"Whoops!"<<std::endl;

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
