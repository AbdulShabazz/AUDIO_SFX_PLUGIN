#include "GreyNoise.h"
#include "Tones.Default.Settings.h"

GreyNoise::GreyNoise()
{
}

void GreyNoise::GenerateGreyNoise(FILEINFO_Obj& FileInfoObj)
{
    ApplyGreyFilter(FileInfoObj);
}

void GreyNoise::ApplyGreyFilter(FILEINFO_Obj& FileInfoObj)
{
    unsigned long long mUInt64 = 1ull << 31;
    constexpr double powerInt64 = -1.0;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis(
        -TonesSettingsObj.AmplitudeInt16, 
         TonesSettingsObj.AmplitudeInt16
    );

    int I = FileInfoObj.LengthInt16;
    for (size_t iUInt64 = 0; iUInt64 < I; iUInt64++)
    {
        FileInfoObj.NoiseBufferInt32[iUInt64] = std::sqrt(std::pow(dis(gen) / static_cast<double>(mUInt64), powerInt64));
    }
}
