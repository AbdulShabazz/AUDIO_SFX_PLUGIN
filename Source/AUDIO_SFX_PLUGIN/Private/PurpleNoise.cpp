#include "PurpleNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

PurpleNoise::PurpleNoise()
{
}

void PurpleNoise::ApplyPurpleFilter(FILEINFO_Obj& FileInfoObj)
{
    int I = FileInfoObj.LengthInt16;
    for (int i = 0; i < I; i++)
    {
        FileInfoObj.NoiseBufferInt32[i] /= std::sqrt(i);
    }
}

// Apply 1/f high-pass filter to shape noise spectrum
void PurpleNoise::GeneratePurpleNoise(FILEINFO_Obj& FileInfoObj)
{
    WhiteNoise WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(FileInfoObj);
    ApplyPurpleFilter(FileInfoObj);
}
