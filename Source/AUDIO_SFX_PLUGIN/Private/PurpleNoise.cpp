#include "PurpleNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

PurpleNoise::PurpleNoise()
{
}

void PurpleNoise::ApplyPurpleFilter(float* noise, int length)
{
    for (int i = 0; i < length; i++)
    {
        noise[i] /= std::sqrt(i);
    }
}

// Apply 1/f high-pass filter to shape noise spectrum
void PurpleNoise::GeneratePurpleNoise(float* noise, int length)
{
    WhiteNoise WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(noise, length);
    ApplyPurpleFilter(noise, length);
}
