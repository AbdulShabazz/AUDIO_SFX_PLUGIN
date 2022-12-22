#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

WhiteNoise::WhiteNoise()
{
}

void WhiteNoise::GenerateWhiteNoise(float* noise, int length)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis(-TonesSettingsObj.AmplitudeInt32, TonesSettingsObj.AmplitudeInt32);
    for (int i = 0; i < length; i++)
    {
        noise[i] = dis(gen);
    }
}