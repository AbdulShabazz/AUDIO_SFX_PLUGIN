#include "GreyNoise.h"
#include "Tones.Default.Settings.h"

GreyNoise::GreyNoise()
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
void GreyNoise::GenerateGreyNoise(FILEINFO_Obj& FileInfoObj)
{
    ApplyGreyFilter(FileInfoObj);
}

void GreyNoise::ApplyGreyFilter(FILEINFO_Obj& FileInfoObj)
{
    UE_FLOAT64 mUInt64 = 1ull << 31;
    constexpr double powerInt64 = -1.0;

    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Generate noise sample buffer
    std::uniform_real_distribution<UE_FLOAT64> dis(
        -TonesSettingsObj.AmplitudeFloat64, 
         TonesSettingsObj.AmplitudeFloat64
        );

    // Generate noise sample buffer
    for (UE_FLOAT64REF SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxFloat64Ref = std::sqrt(std::pow(dis(gen) / static_cast<double>(mUInt64), powerInt64));
    }
}
