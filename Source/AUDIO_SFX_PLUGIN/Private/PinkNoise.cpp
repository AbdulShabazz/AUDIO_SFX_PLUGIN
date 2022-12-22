#include "PinkNoise.h"
#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

PinkNoise::PinkNoise()
{
}

// Apply 1/f^2 high-pass filter to shape noise spectrum
void PinkNoise::ApplyPinkFilter(float* noise, int length)
{
    for (int i = 0; i < length; i++)
    {
        noise[i] /= std::sqrt(i*i);
    }
}

void PinkNoise::GeneratePinkNoise(float* noise, int length)
{
    WhiteNoise WhiteNoiseObj;
    WhiteNoiseObj.GenerateWhiteNoise(noise, length);
    ApplyPinkFilter(noise, length);
}

