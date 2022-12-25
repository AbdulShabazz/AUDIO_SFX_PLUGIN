#include "PinkNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

PinkNoise::PinkNoise()
{
}

// Apply 1/f^2 high-pass filter to shape noise spectrum
void PinkNoise::ApplyPinkFilter(FILEINFO_Obj& FileInfoObj)
{
    int I = FileInfoObj.LengthInt16;
    for (int i = 0; i < I; i++)
    {
        FileInfoObj.NoiseBufferInt32[i] /= std::sqrt(i*i);
    }
}

void PinkNoise::GeneratePinkNoise(FILEINFO_Obj& FileInfoObj)
{
    WhiteNoise WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(FileInfoObj);
    ApplyPinkFilter(FileInfoObj);
}

