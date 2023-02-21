#include "PinkNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
PinkNoise<T,U>::PinkNoise()
{

}

// Apply 1/f^2 high-pass filter to shape noise spectrum
template<typename T, typename U>
void PinkNoise<T,U>::ApplyPinkFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    // Generate noise sample buffer
    UE_UINT64 iUInt64 = 0;
    for (UE_FLOAT64REF SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxFloat64Ref /= std::sqrt(iUInt64 * iUInt64 + 1);
    }
}

/**
* Pink Noise is a type of noise that has a frequency
* spectrum that is inversely proportional to the frequency
* of the signal. This means that the power spectral density
* (a measure of the energy of a signal at different frequencies)
* of Pink Noise decreases by 3 dB per octave as the frequency increases.
* @param [ FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void PinkNoise<T,U>::GeneratePinkNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    WhiteNoise<T,U> WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(FileInfoObj);
    ApplyPinkFilter(FileInfoObj);
}

