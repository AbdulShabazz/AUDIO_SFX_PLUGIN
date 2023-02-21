#include "BlueNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
BlueNoise<T,U>::BlueNoise()
{
}

template<typename T, typename U>
void BlueNoise<T,U>::ApplyBlueFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Generate noise sample buffer
    UniformRealDistributionFloat64 dis(0.0f,1.0f);

    // Generate noise sample buffer
    UE_UINT64 iUInt64 = 0;
    for (UE_FLOAT64REF SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        UE_UINT64 amplitude = std::pow(FileInfoObj.BlackNoisePersistenceValueFloat64, iUInt64++);
        SampleIdxFloat64Ref += dis(gen) + amplitude;
    }
}

/**
* Blue Noise is a type of noise with a power spectrum that follows a
* power law, with the power falling off at high frequencies. It is often
* used because of its more balanced distribution of energy compared
* to White Noise, which has equal energy at all frequencies.
* @param [ FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void BlueNoise<T,U>::GenerateBlueNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    ApplyBlueFilter(FileInfoObj);
}
