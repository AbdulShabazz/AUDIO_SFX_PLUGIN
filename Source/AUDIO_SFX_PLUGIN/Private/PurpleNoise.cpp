#include "PurpleNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

PurpleNoise::PurpleNoise()
{
}

void PurpleNoise::ApplyPurpleFilter(FILEINFO_Obj& FileInfoObj)
{
    UE_UINT64 iUInt64 = 0;
    for (UE_FLOAT64REF SampleIdxFloat64Ref : FileInfoObj.NoiseBufferFloat64)
    {
        SampleIdxFloat64Ref /= std::sqrt(iUInt64++ + 1);
    }
}

// Apply 1/f high-pass filter to shape noise spectrum
void PurpleNoise::GeneratePurpleNoise(FILEINFO_Obj& FileInfoObj)
{
    WhiteNoise WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(FileInfoObj);
    ApplyPurpleFilter(FileInfoObj);
}
