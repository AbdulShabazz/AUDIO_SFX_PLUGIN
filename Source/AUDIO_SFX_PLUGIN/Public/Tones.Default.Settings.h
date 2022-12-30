#pragma once

#include <vector>>
#include <cmath>
#include <random>
#include <array>
#include <algorithm>
#include <string>

using UE_UINT16 = unsigned int;
using UE_UINT64 = unsigned long long int;
using UE_FLOAT64 = long double;
using UE_FLOAT64PTR = long double*;
using UE_FLOAT64REF = long double&;
using UE_VECTOR1DFLOAT64REF = std::vector<UE_FLOAT64>&;

UE_FLOAT64 operator"" _hz(UE_FLOAT64 iFloat64)
{
    return iFloat64;
}

UE_FLOAT64 operator"" _khz(UE_FLOAT64 iFloat64)
{
    return iFloat64 * 1e3;
}

UE_FLOAT64 operator"" _mhz(UE_FLOAT64 iFloat64)
{
    return iFloat64 * 1e6;
}

UE_FLOAT64 operator"" _ghz(UE_FLOAT64 iFloat64)
{
    return iFloat64 * 1e9;
}

struct SETTINGS_OBJ
{
    UE_FLOAT64 SampleRateUInt64 = 44'100.0_hz;
    UE_UINT16 TableSizeUInt16 = 256;
    UE_FLOAT64 AmplitudeFloat64 = 1.0f;
} TonesSettingsObj;

struct FILEINFO_Obj
{
    UE_VECTOR1DFLOAT64REF NoiseBufferFloat64;
    UE_FLOAT64 NumOctavesFloat64 = 7.25f;
    UE_UINT16 OptionalSeedValueUInt16;
    UE_UINT64 PerlinNoiseWidthUInt64;
    UE_UINT64 PerlinNoiseHeightUInt64;
    UE_FLOAT64 PerlinNoiseNumGradientsFloat64;
    UE_FLOAT64 BlackNoisePersistenceValueFloat64;
    UE_UINT64 LengthUInt64;
};

template<typename T> 
T DotProductT(const std::vector<T>& a, const std::vector<T>& b)
{
    return a[0] * b[0] + a[1] * b[1];
}

#define DotProductUint64 DotProductT<UE_UINT64>

template<typename A, typename B>
B BilinearInterpolationT(A n0, A n1, A n2, A n3, B wx, B wy)
{
    B wx_offset = (1 - wx);
    B wy_offset = (1 - wy);
    return n0 * wx_offset * wy_offset +
        n1 * wx * wy_offset +
        n2 * wx_offset * wy +
        n3 * wx * wy
}