#include "WhiteNoise.h"
#include "Tones.Default.Settings.h"

WhiteNoise::WhiteNoise()
{
}

void WhiteNoise::GenerateWhiteNoise(FILEINFO_Obj& FileInfoObj)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis(-TonesSettingsObj.AmplitudeInt16, TonesSettingsObj.AmplitudeInt16);
    int I = FileInfoObj.LengthInt16;
    for (int i = 0; i < I; i++)
    {
        FileInfoObj.NoiseBufferInt32[i] = dis(gen);
    }
}