#include "BluesteinFFT.h"

using namespace ToneLibrary;


template <typename T, typename U>
BluesteinFFT<T, U>::BluesteinFFT()
{

}

template <typename T, typename U>
void BluesteinFFT<T, U>::ApplyBluesteinTransform(
	FILEINFO_Obj<T, U>& FileInfoObjRef
	)
{
	FileInfoObjRef.BluesteinAudioFileComplexVector2DT;
	U nSizeUInt64 = 1;
	while (nSizeUInt64 < 2 * FileInfoObjRef.BlueSteinNumSamplesUInt64)
	{
		nSizeUInt64 *= 2;
	}
	for(ComplexVectorT<T>& nAudioChannelComplexVectorT : FileInfoObjRef.BluesteinAudioFileComplexVector2DT)
	{
		ComplexVectorT<T> ExtendedSamplesComplexVectorT(nSizeUInt64);
		for (const T& nSampleComplexNumberT : nAudioChannelComplexVectorT)
		{
			ExtendedSamplesComplexVectorT[nSampleIndexUInt64] = nSampleComplexNumberT;
		}
		for (U nSampleIndexUInt64 = FileInfoObjRef.BlueSteinNumSamplesUInt64; nSampleIndexUInt64 < nSizeUInt64; nSampleIndexUInt64++)
		{
			ExtendedSamplesComplexVectorT[nSampleIndexUInt64] = ComplexVectorT<T>(0.0f,0.0f);
		}
		ComplexVectorT<T> PowersOfOmegaComplexVectorT(nSizeUInt64);
		PowersOfOmegaComplexVectorT[0] = ComplexVectorT<T>(1.0f, 0.0f);
		for (U nSampleIndexUInt64 = 1; nSampleIndexUInt64 < nSizeUInt64; nSampleIndexUInt64++)
		{
			PowersOfOmegaComplexVectorT[nSampleIndexUInt64] = 
				PowersOfOmegaComplexVectorT[nSampleIndexUInt64 - 1] * 
				(nSampleIndexUInt64 % 2 == 0 ?
					ForwardTwiddleFactorComplexVectorT[nSampleIndexUInt64 / 2] :
					InverseTwiddleFactorComplexVectorT[nSampleIndexUInt64 / 2]
					);
		}
		ComplexVectorT<T> OmegaNComplexVectorT = FileInfoObjRef.BluesteinInverseFlag ? 
			ComplexNumberT<T>(cos(UE_FLOAT64_PI / nSizeUInt64), -sin(UE_FLOAT64_PI / nSizeUInt64)) : 
			ComplexNumberT<T>(cos(UE_FLOAT64_PI / nSizeUInt64),  sin(UE_FLOAT64_PI / nSizeUInt64)) ;
		for (U nBlockSizeUInt64 = 1; nBlockSizeUInt64 < nSizeUInt64; nBlockSizeUInt64 *= 2)
		{
			for (U nBlockStartUInt64 = 0; nBlockStartUInt64 < nSizeUInt64; nBlockStartUInt64 += 2 * nBlockSizeUInt64)
			{
				ComplexNumberT<T> OmegaNComplexNumberT = ComplexNumberT<T>(1.0f, 0.0f);
				for (U nIndexUInt64 = 0; nIndexUInt64 < nBlockSizeUInt64; nIndexUInt64++)
				{
					ComplexNumberT<T> tComplexT = OmegaNComplexNumberT * ExtendedSamplesComplexVectorT[nBlockStartUInt64 + nBlockSizeUInt64 + nIndexUInt64];
					ComplexNumberT<T> uComplexT = ExtendedSamplesComplexVectorT[nBlockStartUInt64 + nIndexUInt64];
					ExtendedSamplesComplexVectorT[nBlockStartUInt64 + nIndexUInt64] = uComplexT + tComplexT;
					ExtendedSamplesComplexVectorT[nBlockStartUInt64 + nBlockSizeUInt64 + nIndexUInt64] = uComplexT - tComplexT;
					OmegaNComplexNumberT *= OmegaNComplexVectorT[nBlockSizeUInt64 + nSampleIndexUInt64];
				}
			}
			OmegaNComplexVectorT *= OmegaNComplexVectorT;
		}
		if (FileInfoObjRef.BluesteinInverseFlag)
		{
			for (U nSampleIndexUInt64 = 0; nSampleIndexUInt64 < nSizeUInt64; nSampleIndexUInt64++)
			{
				ExtendedSamplesComplexVectorT[nSampleIndexUInt64] /= nSizeUInt64;
			}
		}
		for (U nSampleIndexUInt64 = 0; nSampleIndexUInt64 < nAudioChannelComplexVectorT.size(); nSampleIndexUInt64++)
		{
			nChannelComplexVectorT[nSampleIndexUInt64] = ComplexNumberT<T>(0.0f, 0.0f);
			for (U kSampleIndexUInt64 = 0; kSampleIndexUInt64 < FileInfoObjRef.BlueSteinNumSamplesUInt64; kSampleIndexUInt64++)
			{
				nChannelComplexVectorT[nSampleIndexUInt64] += 
					ExtendedSamplesComplexVectorT[kSampleIndexUInt64] * 
					PowersOfOmegaComplexVectorT[((nSampleIndexUInt64 * kSampleIndexUInt64) % nSizeUInt64 + nSizeUInt64) % nSizeUInt64];
			}
		}
	}
}

template <typename T, typename U>
void BluesteinFFT<T, U>::ApplyBluesteinFFTFilter(
    FILEINFO_Obj<T, U>& FileInfoObjRef
	)
{
    U nSizeUInt64T = 0;
    while(nSizeUInt64T < nSFileInfoObjRef.BlueSteinNumSamplesUInt64 * 2)
		nSizeUInt64T *= 2;
	ForwardTwiddleFactorComplexVectorT.resize(nSizeUInt64T);
	InverseTwiddleFactorComplexVectorT.resize(nSizeUInt64T);
	for (U nSampleIndexUInt64 = 0; nSampleIndexUInt64 < nSizeUInt64T; nSampleIndexUInt64++)
	{
		ForwardTwiddleFactorComplexVectorT[nSampleIndexUInt64] = ComplexT<T>(
			cos(2 * PI * nSampleIndexUInt64 / nSizeUInt64T),
		   -sin(2 * PI * nSampleIndexUInt64 / nSizeUInt64T)
			);
		InverseTwiddleFactorComplexVectorT[nSampleIndexUInt64] = ComplexT<T>(
			cos(2 * PI * nSampleIndexUInt64 / nSizeUInt64T),
			sin(2 * PI * nSampleIndexUInt64 / nSizeUInt64T)
			);
	}
	for (U nSampleIndexUInt64 = FileInfoObjRef.BlueSteinNumSamplesUInt64; nSampleIndexUInt64 < nSizeUInt64T; nSampleIndexUInt64++)
	{
		ForwardTwiddleFactorComplexVectorT[nSampleIndexUInt64] = InverseTwiddleFactorComplexVectorT[nSampleIndexUInt64] = ComplexT<T>(0, 0);
	}
}

/**
* The BluesteinFFT Chirp-Z Fast Fourier Transform (FFT) -- simlar to Radix-2, and Cooley-Tukey,
* is an efficient algorithm for computing the Discrete Fourier Transform (DFT) approximation to the FFT.
* With a time complexity of only O(N Log N), one of the benefits of the BluesteinFFT,
* is that it can be used to compute the DFT on sequences of arbitrary length.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to retain details about the file.
* @return [ void ] --- No return value.
*/
template <typename T, typename U>
void BluesteinFFT<T, U>::InitializeBluesteinFFT(
    FILEINFO_Obj<T, U>& FileInfoObjRef
    )
{
	ApplyBluesteinFFTFilter(FileInfoObjRef);
}