#pragma once

#include <vector>
#include <complex>
#include <cmath>
#include <random>
#include <array>
#include <algorithm>
#include <string>
#include <iostream>
#include <assert.h>
#include <type_traits>

using UE_UINT16 = unsigned int;
using UE_UINT64 = unsigned long long int;
using UE_FLOAT16 = float;
using UE_FLOAT32 = double;
using UE_FLOAT64 = long double;
using UE_FLOAT64PTR = long double*;
using UE_FLOAT64REF = long double&;

const UE_FLOAT16 UE_FLOAT16_PI = 3.1415926535897932f;
const UE_FLOAT32 UE_FLOAT32_PI = 3.14159265358979323846f;
const UE_FLOAT64 UE_FLOAT64_PI = 3.141592653589793238462643383279502884197169399f;

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
    UE_FLOAT64 DefaultSampleRateFloat64 = 192.0_khz;
    UE_UINT16 TableSizeUInt16 = 256;
    UE_FLOAT64 AmplitudeFloat64 = 1.0f;
} TonesSettingsObj;

template <typename T>
using VectorT = std::vector<T>;

using VectorFloat64Ref = std::vector<UE_FLOAT64>&;

template <typename T>
using Vector2DT = std::vector<std::vector<T>>;

template <typename T>
using Vector3DT = std::vector<std::vector<std::vector<T>>>;

template <typename T>
using Vector4DT = std::vector<std::vector<std::vector<std::vector<T>>>>;

template <typename T>
using ComplexVectorT = std::vector<std::complex<T>>;

template <typename T>
using ComplexVector2DT = std::vector<std::vector<std::complex<T>>>;

template <typename T>
using ComplexVector3DT = std::vector<std::vector<std::vector<std::complex<T>>>>;

template <typename T>
using ComplexVector4DT = std::vector<std::vector<std::vector<std::vector<std::complex<T>>>>>;

template <typename T>
using ComplexNumberT = std::complex<T>;

using ComplexFloat64T = ComplexNumberT<UE_FLOAT64>;
using ComplexVectorFloat64T = ComplexVectorT<UE_FLOAT64>;
using ComplexVector2DFloat64T = ComplexVector2DT<UE_FLOAT64>;
using ComplexVector3DFloat64T = ComplexVector3DT<UE_FLOAT64>;

template <typename T, typename U>
struct FILEINFO_Obj
{
    // TemporaryAudioPlaybackFileVector4DTRef[AudioFile][UndoBuffer][AudioChannel][Stream]
    Vector4DT<T>& TemporaryAudioPlaybackFileVector4DTRef;
    // TemporaryAudioFileComplexVector4DTRef[AudioFile][UndoBuffer][AudioChannel][Stream]
    ComplexVector4DT<T>& TemporaryAudioFileComplexVector4DTRef;
    // TemporaryAudioPlaybackFileVector4DTRef[Stream]
    VectorT<T>& TemporaryAudioPlaybackFileVectorTRef;
    // TemporaryAudioFileComplexVectorTRef[Stream]
    ComplexVectorT<T>& TemporaryAudioFileComplexVectorTRef;
    VectorT<T>& NoiseBufferVectorTRef;
    T NumOctavesFloat64 = 7.25f;
    U OptionalSeedValueUInt16;
    U PerlinNoiseWidthUInt64;
    U PerlinNoiseHeightUInt64;
    T PerlinNoiseNumGradientsFloat64;
    T BlackNoisePersistenceValueFloat64;
    U AudioFormatUInt64;
    T AudioBitRateFloat64;
    /**
    * Audio sample rate of desired Dolby audio channels. Default: 192.0_khz
    */
    T AudioSampleRateFloat64 = 192.0_khz;
    /**
    * Number of desired dolby audio channels. Default: 2
    */
    U AudioNumberOfDolbyChannelsUInt64 = 2;
    /**
    * Audio bits per sample. Default: 64
    */
    U AudioBitsPerSampleUInt64 = 64;
    enum class EditingModeENUM
    {
        BuildAudio = 1,
        Playback
    };
    EditingModeENUM EditingModeEnum = EditingModeENUM::BuildAudio;
    enum class EqualizationAlgorithmENUM
    {
        CooleyTukey = 1,
        Blustein,
        Radix2
    };
    EqualizationAlgorithmENUM AudioEqualizationAlgorithmEnum = EqualizationAlgorithmENUM::CooleyTukey;
    /**
    * Length, or desired, in BYTES of the file.
    */
    U LengthUInt64;
    /**  The fractal noise dynamic range,from 0 to this value. Default is 32.
    */
    T FractalNoiseRangeParameterFloat64 = 32;
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
    * @param [ T 2, 3, 4, 8, or 16 ] --- valid params. Default is 4.
    */
    T FractalNoiseSquaresSmoothnessFactorFloat64 = 4; 
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

template <typename T> 
T DotProductT(
    const std::vector<T>& a, 
    const std::vector<T>& b
    )
{
    return a[0] * b[0] + a[1] * b[1];
}

template <typename T>
T BilinearInterpolationT(
    const UE_UINT64 n0, 
    const UE_UINT64 n1, 
    const UE_UINT64 n2, 
    const UE_UINT64 n3, 
    const T wx, 
    const T wy
    )
{
    T wx_offset = (1 - wx);
    T wy_offset = (1 - wy);
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

template <typename T>
/**
* USAGE: ComplexNumberToPairT<UE_FLOAT64> C = ComplexNumberToPairT<UE_FLOAT64>(3.0f,4.0f);
* C.first; // 5.0
* C.second; // 0.9272952180016122
* @param [ real ] --- The real component
* @param [ imag ] ---  The imaginary component
* @return [ std::pair<T, T> ] --- A pair value
*/
std::pair<T, T> ComplexNumberToPairT( const T real, const T imag )
{
    T magnitude = std::sqrt(real * real + imag * imag);
    T phase = std::atan2(imag, real);
    return std::make_pair<T>(magnitude, phase);
}

template <typename T>
class BuildPrecision
{
public: 
    // forbid an rvalue constructor //
    explicit BuildPrecision(
        T tl = 0, // Lower
        T tu = 8, // Upper
        T ts = 8  // Set
        ) : tlShort(tl), tuShort(tu), tsShort(ts)
    {
        
    };
    virtual std::string FloatPrecision(T ts)
    {
        std::vector<std::string> lvalT = std::vector<std::string>{
            "float", "UE_FLOAT16", "UE_FLOAT32", "UE_FLOAT64"
        };

        std::string ResultStdString = "UE_FLOAT64";
        return ResultStdString;
    };
    std::string IntPrecision(T ts)
    {
        std::vector<std::string> lvalT = std::vector<std::string>{
            "char", "short", "int", "long", "long long"
        };

        std::string ResultStdString = "UE_FLOAT64";
        return ResultStdString;
    };
    virtual std::string UnsignedIntPrecision(T ts)
    {
        std::string ResultStdString = "unsigned " + IntPrecision(ts);
        return ResultStdString;
    };
protected:
    T tlShort; // Lower
    T tuShort; // Upper
    T tsShort; // Set
};

template <short T>
class PlaybackPrecision : public BuildPrecision<short>
{
public:
    // forbid an rvalue constructor //
    explicit PlaybackPrecision(
        short tl = 0, // Lower
        short tu = 8, // Upper
        short ts = 8  // Set
        )
    {
        tlShort = tl;
        tuShort = tu;
        tsShort = ts;
    };
};