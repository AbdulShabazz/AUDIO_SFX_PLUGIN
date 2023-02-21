#include "Radix2FFT.h"

using namespace ToneLibrary;

template <typename T, typename U>
Radix2FFT<T, U>::Radix2FFT()
{

}

template <typename T, typename U>
void Radix2FFT<T, U>::ApplyRadix2FFTFilter(
    FILEINFO_Obj<T, U>& FileInfoObjRef
    )
{
    U nUInt64 = NoiseBufferComplexVectorTRef.size();

    if (NoiseBufferComplexVectorTRef.size() < 2)
    {
        return;
    }

    U nQuarterRangeUInt64 = static_cast<U>(nUInt64 / 4);

    ComplexVectorT<T> EvenComplexVectorT = ComplexVectorT<T>(nQuarterRangeUInt64);
    ComplexVectorT<T> OddComplexVectorT = ComplexVectorT<T>(nQuarterRangeUInt64);
    ComplexVectorT<T> EvenComplexVectorTModulo4 = ComplexVectorT<T>(nQuarterRangeUInt64);
    ComplexVectorT<T> OddComplexVectorTModulo4 = ComplexVectorT<T>(nQuarterRangeUInt64);

    for (U iUInt64 = 0; iUInt64 < nQuarterRangeUInt64; iUInt64++)
    {
        EvenComplexVectorT[iUInt64] = NoiseBufferComplexVectorTRef[iUInt64 * 2];
        OddComplexVectorT[iUInt64] = NoiseBufferComplexVectorTRef[iUInt64 * 2 + 1];
        EvenComplexVectorTModulo4[iUInt64] = NoiseBufferComplexVectorTRef[iUInt64 * 2 + 2];
        OddComplexVectorTModulo4[iUInt64] = NoiseBufferComplexVectorTRef[iUInt64 * 2 + 3];
    }

    Radix2FFT(FileInfoObj, EvenComplexVectorT);
    Radix2FFT(FileInfoObj, OddComplexVectorT);
    Radix2FFT(FileInfoObj, EvenComplexVectorTModulo4);
    Radix2FFT(FileInfoObj, OddComplexVectorTModulo4);

    ComplexNumberT<T>
        wComplexNumberT = ComplexNumberT<T>(1.0f),
        wnComplexNumberT = ComplexNumberT<T>(
            std::cos(2 * static_cast<T>(UE_FLOAT64_PI) / nUInt64),
            std::sin(2 * static_cast<T>(UE_FLOAT64_PI) / nUInt64)
            );

    for (U kUInt64 = 0; kUInt64 < nQuarterRangeUInt64; kUInt64++)
    {
        /*ComplexNumberT<T> tComplexNumberT = wComplexNumberT + OddComplexVectorT[kUInt64];
        FileInfoObj.TemporaryAudioFileComplexVectorTRef[kUInt64] = EvenComplexVectorT[kUInt64] + tComplexNumberT;
        FileInfoObj.TemporaryAudioFileComplexVectorTRef[kUInt64 + nQuarterRangeUInt64] = EvenComplexVectorT[kUInt64] - tComplexNumberT;
        wComplexNumberT *= wnComplexNumberT;*/
    }
}

/**
* The Radix-2 Fast Fourier Transform (FFT) is the most performant algorithm
* for computing the Discrete Fourier Transform (DFT) approximation on an input sequence -
* even outperforming Cooley-Tukey! If performance is a priority there are few current algorithms
* can beat Radix-2.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to retain details about the file.
* @return [ void ] --- No return value.
*/
template <typename T, typename U>
void Radix2FFT<T, U>::GenerateRadix2FFT(
    FILEINFO_Obj<T, U>& FileInfoObjRef
    )
{
    ApplyRadix2FFTFilter(FileInfoObjRef);
}
