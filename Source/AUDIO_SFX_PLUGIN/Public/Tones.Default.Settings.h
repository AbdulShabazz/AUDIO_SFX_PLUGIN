#pragma once

#include <vector>
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
T DotProductT(
    const std::vector<T>& a, 
    const std::vector<T>& b
    )
{
    return a[0] * b[0] + a[1] * b[1];
}

template<typename U>
U BilinearInterpolationT(
    const UE_UINT64 n0, 
    const UE_UINT64 n1, 
    const UE_UINT64 n2, 
    const UE_UINT64 n3, 
    const U wx, 
    const U wy
    )
{
    U wx_offset = (1 - wx);
    U wy_offset = (1 - wy);
    return n0 * wx_offset * wy_offset +
        n1 * wx * wy_offset +
        n2 * wx_offset * wy +
        n3 * wx * wy ;
}

UE_FLOAT64 DotProductFloat64(
    const std::vector<UE_FLOAT64>& a, 
    const std::vector<UE_FLOAT64>& b
    )
{
    return  DotProductT<UE_FLOAT64>(a, b);
}
using UniformRealDistributionFloat64 = std::uniform_real_distribution<UE_FLOAT64>;