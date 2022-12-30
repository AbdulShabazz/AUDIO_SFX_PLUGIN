#include "PinkNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

PinkNoise::PinkNoise()
{
}

// Apply 1/f^2 high-pass filter to shape noise spectrum
void PinkNoise::ApplyPinkFilter(FILEINFO_Obj& FileInfoObj)
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
void PinkNoise::GeneratePinkNoise(FILEINFO_Obj& FileInfoObj)
{
    WhiteNoise WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(FileInfoObj);
    ApplyPinkFilter(FileInfoObj);
}

