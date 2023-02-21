#include "BlackNoise.h"

using namespace ToneLibrary;

template<typename T, typename U>
BlackNoise<T,U>::BlackNoise()
{
}

template<typename T, typename U>
void BlackNoise<T,U>::ApplyBlackFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Set the range of the noise signal
    std::uniform_real_distribution<T> dis(-1.0f, 1.0f);

    // Generate noise sample buffer
    for (T IdxSampleT : FileInfoObj.NoiseBufferVectorTRef)
    {
        IdxSampleT = dis(gen);
    }
}

/**
* Black Noise, also known as Brownian Noise, Brown Noise or Yellow Noise, 
* is a type of noise signal that has a power spectral density  
* that decreases -6 dB per octave. This means that the power
* of the noise decreases as the frequency increases. This results 
* in a warmer or deeper sound than White Noise, which has equaL energy
* at all frequencies.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void BlackNoise<T,U>::GenerateBlackNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    ApplyBlackFilter(FileInfoObj);
}
