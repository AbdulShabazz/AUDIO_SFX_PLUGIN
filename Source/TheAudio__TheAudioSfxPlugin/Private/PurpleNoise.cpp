#include "PurpleNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template <typename T, typename U>
PurpleNoise<T,U>::PurpleNoise()
{
}

template <typename T, typename U>
void PurpleNoise<T,U>::ApplyPurpleFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    U iUInt64 = 0;
    for (T& SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxFloat64Ref /= std::sqrt(iUInt64++ + 1);
    }
}

// Apply 1/f high-pass filter to shape noise spectrum
template <typename T, typename U>
void PurpleNoise<T,U>::GeneratePurpleNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    WhiteNoise<T> WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(FileInfoObj);
    ApplyPurpleFilter(FileInfoObj);
}
