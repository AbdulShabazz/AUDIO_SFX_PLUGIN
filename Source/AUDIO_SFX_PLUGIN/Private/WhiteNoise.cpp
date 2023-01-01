#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

WhiteNoise::WhiteNoise()
{
}
/**
* White Noise is a type of noise that is characterized
* by a flat frequency spectrum. It is a random, broadband
* sound that contains equal energy per frequency and is
* perceived as a constant, hissing sound. It is called
* White Noise because it is analogous to white light,
* which contains all frequencies of the visible spectrum.
* @param [ FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
void WhiteNoise::GenerateWhiteNoise(FILEINFO_Obj& FileInfoObj)
{
    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Generate noise sample buffer
    UniformRealDistributionFloat64 dis(
        -TonesSettingsObj.AmplitudeFloat64, 
         TonesSettingsObj.AmplitudeFloat64
        );

    // Generate noise sample buffer
    for (UE_FLOAT64REF SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxFloat64Ref = dis(gen);
    }
}