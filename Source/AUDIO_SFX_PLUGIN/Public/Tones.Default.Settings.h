#pragma once

#include <cmath>
#include <random>

struct SETTINGS_OBJ
{
    double SampleRateInt64 = 44100;
    int TableSizeInt16 = 256;
    int AmplitudeInt16 = 0.8;
} TonesSettingsObj;

struct FILEINFO_Obj
{
    float* NoiseBufferInt32;
    int LengthInt16;

};