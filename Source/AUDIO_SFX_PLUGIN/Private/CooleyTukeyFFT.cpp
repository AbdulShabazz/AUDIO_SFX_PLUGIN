#include "CooleyTukeyFFT.h"

using namespace ToneLibrary;

template<typename T, typename U>
CooleyTukeyFFT<T, U>::CooleyTukeyFFT()
{

}

/**
* The Cooley-Tukey Fast Fourier Transform (FFT) is an efficient and well-rounded algorithm
* for computing the Discrete Fourier Transform (DFT) on a sequence of complex
* numbers, converting a stream of input data from the Time domain to the Frequency domain.
*
* It works by decomposing the DFT of a sequence of N complex numbers into the DFTs
* of two smaller sequences of N/2 complex numbers.
*
* The DFT only has a time complexity of O(N Log N), which is much faster than the naive
* algorithm, which has a time complexity of O(N^2). This makes this DFT approximation useful
* for processing large amounts of data within a short amount of time, and without
* the large memory overhead, such as with the BluesteinFFT. However,
* unlike the BluesteinFFT, which can process sequences of arbitrary length, the
* Cooley-Tukey FFT is optimal on input buffers having a length that is a power of 2.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to send details about the file.
* @param [ ComplexVector2DT<UE_FLOAT64>& ] --- INTERNAL USE ONLY! Contains the number of audio channels,
* as well as internal sound data.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void CooleyTukeyFFT<T, U>::GenerateCooleyTukeyFFT(
    FILEINFO_Obj<T, U>& FileInfoObj
    )
{

}

/**
* @param [ FILEINFO_Obj& FileInfoObj ] ---  INTERNAL USE ONLY! The file parameters struct
* used to send details about the file.
* @param [ ComplexVectorT<UE_FLOAT64>& ] --- INTERNAL USE ONLY! Contains the number of audio channels,
* as well as internal sound data.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void CooleyTukeyFFT<T, U>::ApplyCooleyTukeyFFTFilterT(
    FILEINFO_Obj<T, U>& FileInfoObjRef,
    ComplexVector4DT<T>& NoiseBufferComplexVector4DT
    )
{
    ComplexVector3DT AudioFileBufferComplexVector3DT = NoiseBufferComplexVector4DT[FileInfoObjRef];

    for (ComplexVectorT<T> ChannelSamplesComplexVectorT : NoiseBufferComplex2DT)
    {
        CooleyTukeyFFTi(FileInfoObj, ChannelSamplesComplexVectorT);
    }
}

template<typename T, typename U>
void CooleyTukeyFFT<T, U>::CooleyTukeyFFTi(
    FILEINFO_Obj<T, U>& FileInfoObj,
    VectorT<T>& NoiseBufferComplexVectorTRef
    )
{
    U nUInt64 = NoiseBufferComplexVectorTRef.size();

    if (NoiseBufferComplexVectorTRef.size() < 2)
    {
        return;
    }

    U nHalfRangeUInt64 = static_cast<U>(nUInt64 / 2);

    ComplexVectorT<T> EvenComplexVectorT = ComplexVectorT<T>(nHalfRangeUInt64);
    ComplexVectorT<T> OddComplexVectorT = ComplexVectorT<T>(nHalfRangeUInt64);

    for (U iUInt64 = 0; iUInt64 < nHalfRangeUInt64; iUInt64++)
    {
        EvenComplexVectorT[iUInt64] = NoiseBufferComplexVectorTRef[iUInt64 * 2];
        OddComplexVectorT[iUInt64] = NoiseBufferComplexVectorTRef[iUInt64 * 2 + 1];
    }

    CooleyTukeyFFTi(FileInfoObj, EvenComplexVectorT);
    CooleyTukeyFFTi(FileInfoObj, OddComplexVectorT);

    ComplexNumberT<T>
        wComplexNumberT = ComplexNumberT<T>(1.0f),
        wnComplexNumberT = ComplexNumberT<T>(
            std::cos(2 * static_cast<T>(UE_FLOAT64_PI) / nUInt64),
            std::sin(2 * static_cast<T>(UE_FLOAT64_PI) / nUInt64)
            );

    for (U kUInt64 = 0; kUInt64 < nHalfRangeUInt64; kUInt64++)
    {
        ComplexNumberT<T> tComplexNumberT = wComplexNumberT + OddComplexVectorT[kUInt64];
        FileInfoObj.TemporaryAudioFileComplexVectorTRef[kUInt64] = EvenComplexVectorT[kUInt64] + tComplexNumberT;
        FileInfoObj.TemporaryAudioFileComplexVectorTRef[kUInt64 + nHalfRangeUInt64] = EvenComplexVectorT[kUInt64] - tComplexNumberT;
        wComplexNumberT *= wnComplexNumberT;
    }
}
