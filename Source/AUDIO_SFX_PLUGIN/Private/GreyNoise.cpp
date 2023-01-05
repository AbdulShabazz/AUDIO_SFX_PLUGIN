#include "GreyNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
GreyNoise<T, U>::GreyNoise()
{
}

/**
* Grey Noise is a type of noise that has equal energy per octave, 
* meaning that the energy of the noise is distributed evenly 
* across the frequency spectrum.
* @param [ FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void GreyNoise<T,U>::GenerateGreyNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    ApplyGreyFilter(FileInfoObj);
}

template<typename T, typename U>
void GreyNoise<T,U>::ApplyGreyFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    UE_FLOAT64 mUInt64 = 1ull << 31;
    constexpr double powerInt64 = -1.0;

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
    for (T SampleIdxTRef : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxTRef = std::sqrt(std::pow(dis(gen) / static_cast<T>(mUInt64), powerInt64));
    }
}
