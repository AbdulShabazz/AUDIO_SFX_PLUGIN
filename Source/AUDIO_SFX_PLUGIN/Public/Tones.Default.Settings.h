#pragma once

#include <vector>
#include <cmath>
#include <random>
#include <array>
#include <algorithm>
#include <string>
#include <iostream>
#include <complex>

using UE_UINT16 = unsigned int;
using UE_UINT64 = unsigned long long int;
using UE_FLOAT64 = long double;
using UE_FLOAT64PTR = long double*;
using UE_FLOAT64REF = long double&;
using UE_VECTOR1DFLOAT64REF = std::vector<UE_FLOAT64>&;

const UE_FLOAT64 M_PI = 3.14159265358979323846L;

// FLOAT64
UE_FLOAT64 operator"" _dB(UE_FLOAT64 iFloat64)
{
    return iFloat64;
}

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

// INT64
UE_UINT64 operator"" _dB(UE_UINT64 iFloat64)
{
    return iFloat64;
}

UE_UINT64 operator"" _hz(UE_UINT64 iFloat64)
{
    return iFloat64;
}

UE_UINT64 operator"" _khz(UE_UINT64 iFloat64)
{
    return iFloat64 * 1e3;
}

UE_UINT64 operator"" _mhz(UE_UINT64 iFloat64)
{
    return iFloat64 * 1e6;
}

UE_UINT64 operator"" _ghz(UE_UINT64 iFloat64)
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
    UE_UINT64 AudioFormatUInt64;
    UE_FLOAT64 AudioBitRateFloat64;
    /**
    * Audio sample rate of desired Dolby audio channels. Default: 192.0_khz
    */
    UE_FLOAT64 AudioSampleRateFloat64 = 192.0_khz;
    /**
    * Number of desired dolby audio channels. Default: 2
    */
    UE_UINT64 AudioNumberOfDolbyChannelsUInt64 = 2;
    /**
    * Length, or desired, in BYTES of the file.
    */
    UE_UINT64 LengthUInt64;
    /**  The fractal noise dynamic range,from 0 to this value. Default is 32.
    */
    UE_FLOAT64 FractalNoiseRangeParameterFloat64 = 32;
    /**
    * This helps smooth out the fractal noise square pattern
    * to reduce the overall variation between adjacent values.
    * 
    * The degree of smoothing can be adjusted by changing this value
    * which serves as the divisor. For example, if you want a smoother
    * noise pattern you could use a divisor of 8 or 16 or 4. This would
    * result in a noise pattern with a lower level of detail and less variation
    * between adjacent values.
    * 
    * On the other hand, if you desire a noisier, more varied pattern, you
    * could use a smaller divisor such as 2 or 3.
    * 
    * Overall, the choice is a completely personal preference and specific to the
    * requirements of the application.
    * @param [ UE_FLOAT64 2, 3, 4, 8, or 16 ] --- valid params. Default is 4.
    */
    UE_FLOAT64 FractalNoiseSquaresSmoothnessFactorFloat64 = 4; 
    enum class FractalNoiseArrayShapeENUM 
    { 
        Square = 1, 
        Rectangular,
        Circular,
        Triangular,
        Diamond
    };
    /**
    * This setting determines the shape of the noise pattern array. The shape
    * can effect the overall appearance and characteristics of the noise.
    * The avalable patterns are Square, Rectangular, Circular, Triangular,
    * and Diamond.
    * For example, a square noise pattern will have a more evenly distributed appearance.
    * Whereas a rectangle or other irregular shape may have a more uneven, organic appearance,
    * with different levels of detail in different directions.
    * @param [ enum class FractalNoiseArrayShapeSettingEnum ] --- Used to determine the shape of the generated noise.
    */
    FractalNoiseArrayShapeENUM FractalNoiseArrayShapeSettingEnum = FractalNoiseArrayShapeENUM::Square;
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