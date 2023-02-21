#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
WhiteNoise<T,U>::WhiteNoise()
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
template<typename T, typename U>
void WhiteNoise<T,U>::GenerateWhiteNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Generate noise sample buffer
    std::uniform_real_distribution<T> dis(
        -TonesSettingsObj.AmplitudeFloat64, 
         TonesSettingsObj.AmplitudeFloat64
        );

    // Generate noise sample buffer
    for (T& SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxFloat64Ref = dis(gen);
    }
}