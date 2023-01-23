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
#include <vector>
#include <unordered_map>

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

//UE_FLOAT64 operator"" _dB(UE_FLOAT64 iFloat64)
//{
//    return iFloat64;
//}
//
//UE_FLOAT64 operator"" _hz(UE_FLOAT64 iFloat64)
//{
//    return iFloat64;
//}
//
//UE_FLOAT64 operator"" _khz(UE_FLOAT64 iFloat64)
//{
//    return iFloat64 * 1e3;
//}
//
//UE_FLOAT64 operator"" _mhz(UE_FLOAT64 iFloat64)
//{
//    return iFloat64 * 1e6;
//}
//
//UE_FLOAT64 operator"" _ghz(UE_FLOAT64 iFloat64)
//{
//    return iFloat64 * 1e9;
//}

// INT64
//UE_UINT64 operator"" _dB(UE_UINT64 iUInt64)
//{
//    return iUInt64;
//}
//
//UE_UINT64 operator"" _hz(UE_UINT64 iUInt64)
//{
//    return iUInt64;
//}
//
//UE_UINT64 operator"" _khz(UE_UINT64 iUInt64)
//{
//    return iUInt64 * 1e3;
//}
//
//UE_UINT64 operator"" _mhz(UE_UINT64 iUInt64)
//{
//    return iUInt64 * 1e6;
//}
//
//UE_UINT64 operator"" _ghz(UE_UINT64 iUInt64)
//{
//    return iUInt64 * 1e9;
//}

template <typename T, typename U>
struct SETTINGS_OBJ
{
    T DefaultSampleRateFloat64 = 192.0_khz;
    U TableSizeUInt16 = 256;
    T AmplitudeFloat64 = 1.0f;
};

template <typename T>
using VectorT = std::vector<T>;

using VectorFloat64Ref = std::vector<UE_FLOAT64>&;

template <typename T>
using Vector2DT = std::vector<std::vector<T>>;

template <typename T>
using Vector3DT = std::vector<std::vector<std::vector<T>>>;

template <typename T>
using Vector4DT = std::vector<std::vector<std::vector<std::vector<T>>>>;

template <typename U>
using Vector4DU = std::vector<std::vector<std::vector<std::vector<U>>>>;

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

template <typename T>
struct ConvolutionReverbFIRObj
{
    Vector2DT<T> PlateFiniteImpulseResponseFIRVector2DT; // PLATE
    Vector2DT<T> SpringFiniteImpulseResponseFIRVector2DT; // SPRING
    Vector2DT<T> ConvolutionFiniteImpulseResponseFIRVector2DT; // CONVOLUTION
    struct ALGORITHMIC
    {
        struct SMALL_ROOM
        {
            Vector2DT<T> WoodenRoomFiniteImpulseResponseFIRVector2DT; // WOODEN
            Vector2DT<T> GlassRoomFiniteImpulseResponseFIRVector2DT; // GLASS
            struct METAL
            {
                Vector2DT<T> TitaniumRoomFiniteImpulseResponseFIRVector2DT; // TITANIUM
                Vector2DT<T> IronRoomFiniteImpulseResponseFIRVector2DT; // IRON
                Vector2DT<T> LeadRoomFiniteImpulseResponseFIRVector2DT; // LEAD
                Vector2DT<T> GoldRoomFiniteImpulseResponseFIRVector2DT; // GOLD
                Vector2DT<T> SteelRoomFiniteImpulseResponseFIRVector2DT; // STEEL
                Vector2DT<T> AluminumRoomFiniteImpulseResponseFIRVector2DT; // ALUMINUM
            } MetalObj;
            Vector2DT<T> RubberRoomFiniteImpulseResponseFIRVector2DT; // RUBBER
            Vector2DT<T> CeramicRoomFiniteImpulseResponseFIRVector2DT; // CERAMIC
            Vector2DT<T> PlasticRoomFiniteImpulseResponseFIRVector2DT; // PLASTIC
            Vector2DT<T> CottonRoomFiniteImpulseResponseFIRVector2DT; // COTTON
        } SmallRoomObj;
        Vector2DT<T> MediumHallFiniteImpulseResponseFIRVector2DT; // MEDIUM HALL
        Vector2DT<T> ConcertHallFiniteImpulseResponseFIRVector2DT; //CONCERT HALL
        Vector2DT<T> CathedralFiniteImpulseResponseFIRVector2DT; // CATHEDRAL
        Vector2DT<T> ConcertStadiumFiniteImpulseResponseFIRVector2DT; // STADIUM
    } AlgorithmicObj;
};

enum class ConvolutionReverbEnumFLAGS
{
    ConvolutionReverbPlateEnumFlag = 1,
    ConvolutionReverbSpringEnumFlag,
    ConvolutionReverbConvoluteEnumFlag,
    ConvolutionReverbWoodenEnumFlag,
    ConvolutionReverbGlassEnumFlag,
    ConvolutionReverbTitaniumEnumFlag,
    ConvolutionReverbIronEnumFlag,
    ConvolutionReverbLeadEnumFlag,
    ConvolutionReverbGoldEnumFlag,
    ConvolutionReverbSteelEnumFlag,
    ConvolutionReverbAluminumEnumFlag,
    ConvolutionReverbRubberEnumFlag,
    ConvolutionReverbCeramicEnumFlag,
    ConvolutionReverbPlasticEnumFlag,
    ConvolutionReverbCottonEnumFlag,
    ConvolutionReverbMediumHallEnumFlag,
    ConvolutionReverbConcertHallEnumFlag,
    ConvolutionReverbCathedralEnumFlag,
    ConvolutionReverbConcertStadiumEnumFlag
};

// Populate 
template <typename T>
std::unordered_map<enum class ConvolutionReverbEnumFLAGS, Vector2DT<T>>& PopulateConvolutionReverbHashTableT()
{
    ConvolutionReverbHashTableT<ConvolutionReverbEnumFLAGS, Vector2DT<T>> ConvolutionReverbHashTableT;
    
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbPlateEnumFlag] = 
        ConvolutionReverbFIRObj<T>::PlateFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbSpringEnumFlag] =
        ConvolutionReverbFIRObj<T>::SpringFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbConvoluteEnumFlag] = 
        ConvolutionReverbFIRObj<T>::ConvolutionFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbWoodenEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::WoodenRoomFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbGlassEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::GlassRoomFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbTitaniumEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::MetalObj::TitaniumRoomFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbIronEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::MetalObj::IronRoomFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbLeadEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::MetalObj::LeadRoomFiniteImpulseResponseFIRVector2DT;
    ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbGoldEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::MetalObj::GoldRoomFiniteImpulseResponse;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbSteelEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::MetalObj::SteelRoomFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbAluminumEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::MetalObj::AluminumRoomFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbRubberEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::RubberRoomFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbCeramicEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::CeramicRoomFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbPlasticEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::PlasticRoomFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbCottonEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::SmallRoomObj::CottonRoomFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbMediumHallEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::MediumHallFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbConcertHallEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::ConcertHallFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbCathedralEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::CathedralFiniteImpulseResponseFIRVector2DT;
	ConvolutionReverbHashTableT[ConvolutionReverbEnumFLAGS::ConvolutionReverbConcertStadiumEnumFlag] = 
        ConvolutionReverbFIRObj<T>::AlgorithmicObj::ConcertStadiumFiniteImpulseResponseFIRVector2DT;
	return ConvolutionReverbHashTableT;
}

// Convolution Reverb FIR library lookup table (by flag)
template <typename T>
std::unordered_map<enum class ConvolutionReverbEnumFLAGS, Vector2DT<T>>& ConvolutionReverbLibraryEnumHashTableT = PopulateConvolutionReverbHashTableT();

template<typename U>
struct PhoneStruct
{
    U nIndexUInt64T;
    std::string LetterStdStr;
};

template <typename T, typename U>
struct FILEINFO_Obj
{
    std::vector<std::string>& nlp_ipa_WordVectorStdStrBuffRef;
    Vector4DU<U>& nlp_ipa_PhonesVector2DUInt64TBuffRef;
    bool TimeStretchPreservePitchFlag;
    T TimeStretchPitchRatioFloat64T;
    U TimeStretchStretchRatioInNumberOfSamplesUInt64T;
    Vector3DT<T> TimeStretchVector3DT;
	ComplexVector3DT<T> TimeStretcComplexVector3DT;
    T AudioEqualizationSampleRateFloat64T;
    T AudioEqualizationLowCutOffFrequencyInHertzFloat64T;
    T AudioEqualizationHighCutOffFrequencyInHertzFloat64T;
    T AudioEqualizationLowGainMultiplierBetween0And10Float64T;
    T AudioEqualizationHighGainMultiplierBetween0And10Float64T;
    ComplexVector3DT<T> AudioEqualizationComplexVector3DTRef;
	Vector3DT<T> AudioEqualizationVector3DTRef;
    T SpringReverbDelayInSamplesFloat64T;
    T SpringReverbDecayInSecondsFloat64T;
    T SpringReverbDampingFactorBetween0And1Float64T;
    T SpringReverbSampleRateInHertzFloat64T;
    T PlateReverbDampingFloat64T;
    T PlateReverbDrynessFloat64T;
	T PlateReverbWetnessFloat64T;
    Vector3DT<T> PlateReverb3DVectorTRef;
    // Convolution Reverb Method
    ConvolutionReverbEnumFLAGS ConvolutionReverbMethodEnumFlag;
    // ConvolutionReverb Impulse Response (FIR/IIR) library
    ConvolutionReverbFIRObj<T> ConvolutionReverbImpulseResponseTObj;
    // Contains the AudioMix result at AudioMixMixedAudioResultVector3DTRef[0],
    // and the original source file at AudioMixMixedAudioResultVector3DTRef[1]. 
    // Add FIR / IIR targets to the buffer as needed.
    Vector3DT<T> ConvolutionReverbAudioResultVector3DTRef;
    // Contains the AudioMix result at AudioMixMixedAudioResultVector3DTRef[0]. Add files to the buffer as needed.
    Vector3DT<T> AudioMixMixedAudioResultVector3DTRef;
    Vector2DT<T> BluesteinAudioFileComplexVector2DT;
    // Use to designate the inverse Bluestein Transform
    bool BluesteinInverseFlag;
    U BlueSteinNumSamplesUInt64;
    Vector2DT<T> AudioSummationSummedAudioVector2DTRef;
	Vector2DT<T> AudioSummationFileAVector2DTRef;
	Vector2DT<T> AudioSummationFileBVector2DTRef;
    bool AudioSummationNormalizeFlag;
    T KarplusStrongDelayLineSynthesisFrequencyInHertzFloat64T;
	U KarplusStrongDelayLineSynthesisDelayInNumberOfSamplesUInt64T;
	VectorT<T> KarplusStrongDelayLineSynthesisRingBufferUInt64T;
    U KarplusStrongDelayLineSynthesisDefaultRingBufferSizePrivateUint64;
    U KarplusStrongDelayLineSynthesisReadIndexUInt64T;
	U KarplusStrongDelayLineSynthesisWriteIndexUInt64T;
    T WaveEquationCurrentTimeInSecondsFloat64T;
    T WaveEquationWaveSpeedInMetersPerSecondFloat64T;
    T WaveEquationWaveLengthInMetersFloat64T;
    T WaveEquationStartTimeInSecondsFloat64T;
    T WaveEquationResultFloat64TRef;
    // VectorGradientTable2DForSimplexNoiseFilterFloat64TRef
    Vector2DT<T> VectorGradientTable2DForSimplexNoiseFilterFloat64TRef;
    // DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64 = 1024
    U DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64 = 1024;
    // VectorPermutatioTableForSimplexNoiseUInt64T
    VectorT<U> VectorPermutatioTableForSimplexNoiseUInt64TRef;
    // TemporaryAudioPlaybackFileVector4DTRef[AudioFile][UndoBuffer][AudioChannel][Stream]
    Vector4DT<T> TemporaryAudioPlaybackFileVector4DTRef;
    // TemporaryAudioFileComplexVector4DTRef[AudioFile][UndoBuffer][AudioChannel][Stream]
    ComplexVector4DT<T> TemporaryAudioFileComplexVector4DTRef;
    // TemporaryAudioPlaybackFileVector4DTRef[Stream]
    VectorT<T> TemporaryAudioPlaybackFileVectorTRef;
    // TemporaryAudioFileComplexVectorTRef[Stream]
    ComplexVectorT<T> TemporaryAudioFileComplexVectorTRef;
    VectorT<T> NoiseBufferVectorTRef;
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
    const UE_UINT64& n0, 
    const UE_UINT64& n1, 
    const UE_UINT64& n2, 
    const UE_UINT64& n3, 
    const T& wx, 
    const T& wy
    )
{
    T wx_offset = (1 - wx);
    T wy_offset = (1 - wy);
    return n0 * wx_offset * wy_offset +
        n1 * wx * wy_offset +
        n2 * wx_offset * wy +
        n3 * wx * wy ;
}

//UE_FLOAT64 DotProductFloat64(
//    const std::vector<UE_FLOAT64>& a, 
//    const std::vector<UE_FLOAT64>& b
//    )
//{
//    return  DotProductT<UE_FLOAT64>(a, b);
//}

using UniformRealDistributionFloat64 = std::uniform_real_distribution<UE_FLOAT64>;

template <typename T>
/**
* USAGE: ComplexNumberToPolarPairT<UE_FLOAT64> C = ComplexNumberToPolarPairT<UE_FLOAT64>(3.0f,4.0f);
* C.first; // 5.0
* C.second; // 0.9272952180016122
* @param [ real ] --- The magnitude component
* @param [ imag ] ---  The phase component
* @return [ std::pair<T, T> ] --- A polar pair value
*/
std::pair<T, T> ComplexNumberToPolarPairT( const T& real, const T& imag )
{
    T magnitude = std::sqrt(real * real + imag * imag);
    T phase = std::atan2(imag, real);
    return std::make_pair<T>(magnitude, phase);
}

template <typename T>
/**
* USAGE: PolarPairProductT<UE_FLOAT64> C = PolarPairProductT<UE_FLOAT64>(A,B);
* C.first; // 5.0
* C.second; // 0.9272952180016122
* @param [ real ] --- The magnitude component
* @param [ imag ] ---  The phase component
* @return [ std::pair<T, T> ] --- A polar pair value
*/
std::pair<T, T> PolarPairProductT(const std::pair<T, T>& rval, const std::pair<T, T>& lval)
{
    T magnitude = rval.first * lval.first;
    T phase = rval.second + lval.second;
    return std::make_pair<T>(magnitude, phase);
}

template <typename T>
class IDEBuildPrecision
{
public: 
    // forbid an rvalue constructor //
    explicit IDEBuildPrecision(
        T tl = 0, // Lower
        T tu = 8, // Upper
        T ts = 8  // Set
        ) : tlShort(tl), tuShort(tu), tsShort(ts)
    {
        
    };
    virtual std::string FloatPrecision(T& ts)
    {
        std::vector<std::string> lvalT = std::vector<std::string>{
            "float", "UE_FLOAT16", "UE_FLOAT32", "UE_FLOAT64"
        };

        std::string ResultStdString = "UE_FLOAT64";
        return ResultStdString;
    };
    std::string IntPrecision(T& ts)
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
class IDEPlaybackPrecision : public IDEBuildPrecision<short>
{
public:
    // forbid any rvalue constructor //
    explicit IDEPlaybackPrecision(
        short& tl = 0, // Lower
        short& tu = 8, // Upper
        short& ts = 8  // Set
        )
    {
        tlShort = tl;
        tuShort = tu;
        tsShort = ts;
    };
};