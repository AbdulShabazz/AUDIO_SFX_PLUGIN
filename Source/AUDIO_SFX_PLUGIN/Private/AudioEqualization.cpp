#include "AudioEqualization.h"

using namespace ToneLibrary;

AudioEqualization::AudioEqualization()
{
}

void AudioEqualization::NormalizeAudio(ComplexVectorFloat64& NoiseBufferComplexFloat64)
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
* used to retain details about the file.
* @return [ void ] --- No return value.
*/
void AudioEqualization::CooleyTukeyFFT(
    FILEINFO_Obj& FileInfoObj, 
    ComplexVectorFloat64& NoiseBufferComplexFloat64
    )
{
    UE_UINT64 nUInt64 = FileInfoObj.LengthUInt64;

    if (!NoiseBufferComplexFloat64.empty() && NoiseBufferComplexFloat64.size() < 2)
    {
        return;
    }
    else 
    if (!NoiseBufferComplexFloat64.empty())
    {
        nUInt64 = NoiseBufferComplexFloat64.size();
    }
    else // NoiseBufferComplexFloat64.empty()
    {
        NoiseBufferComplexFloat64 = ComplexVectorFloat64(nUInt64);
    }

    UE_UINT64 nHalfRangeUInt64 = UE_UINT64( nUInt64 / 2);

    ComplexVectorFloat64 EvenComplexVectorFloat64 = ComplexVectorFloat64(nHalfRangeUInt64);
    ComplexVectorFloat64 OddComplexVectorFloat64 = ComplexVectorFloat64(nHalfRangeUInt64);

    if(!NoiseBufferComplexFloat64.empty())
    {
        for (UE_UINT64 iUInt64 = 0; iUInt64 < nHalfRangeUInt64; iUInt64++)
        {
            EvenComplexVectorFloat64[iUInt64] = NoiseBufferComplexFloat64[iUInt64 * 2];
            OddComplexVectorFloat64[iUInt64] = NoiseBufferComplexFloat64[iUInt64 * 2 + 1];
        }
    }
    else
    {
        for (UE_UINT64 iUInt64 = 0; iUInt64 < nHalfRangeUInt64; iUInt64++)
        {
            EvenComplexVectorFloat64[iUInt64].real(FileInfoObj.NoiseBufferFloat64[iUInt64 * 2]);
            OddComplexVectorFloat64[iUInt64].real(FileInfoObj.NoiseBufferFloat64[iUInt64 * 2 + 1]);
        }
    }

    CooleyTukeyFFT(FileInfoObj, EvenComplexVectorFloat64);
    CooleyTukeyFFT(FileInfoObj, OddComplexVectorFloat64);

    for (UE_UINT64 kUInt64 = 0; kUInt64 < nHalfRangeUInt64; kUInt64++)
    {
        std::complex<UE_FLOAT64> tComplexFloat64 = 
            std::polar<UE_FLOAT64>(1.0f, -2.0f * M_PI * kUInt64 / nUInt64) * 
                OddComplexVectorFloat64[kUInt64];
        NoiseBufferComplexFloat64[kUInt64] = EvenComplexVectorFloat64[kUInt64] + tComplexFloat64;
        NoiseBufferComplexFloat64[kUInt64 + UE_UINT64( nHalfRangeUInt64)] = EvenComplexVectorFloat64[kUInt64] - tComplexFloat64;
    }

    bool AtHighestScopeLevelBool = EvenComplexVectorFloat64.size() == UE_UINT64(FileInfoObj.LengthUInt64 / 2);
    if (AtHighestScopeLevelBool)
    {
        NormalizeAudio(NoiseBufferComplexFloat64);
    }
}

/**
* The BluesteinFFT, simlar to Radix-2, and Cooley-Tukey Fast Fourier Transform (FFT), 
* is an efficient algorithm for computing the Discrete Fourier Transform (DFT), 
* with a time complexity of only O(N Log N). One of the benefits of the BluesteinFFT,
* is that it can be used to compute the DFT on sequences of arbitrary length.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to retain details about the file.
* @return [ void ] --- No return value.
*/
void AudioEqualization::BluesteinFFT(
    FILEINFO_Obj& FileInfoObj,
    ComplexVectorFloat64& NoiseBufferComplexFloat64
    )
{
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
void AudioEqualization::Radix2FFT(
    FILEINFO_Obj& FileInfoObj,
    ComplexVectorFloat64& NoiseBufferComplexFloat64
    )
{
}

void AudioEqualization::ApplyAudioEqualizationFilter(FILEINFO_Obj& FileInfoObj)
{
    // struct for storing audio sample data
    // READ audio, bps, bitrate, sample rate, number of channels
    // Ensure target file has matching bitrate, and number of channels as the primary
    // Perform an FFT (Cooley-Tukey or Bluestein etc.) to convert from time domain to frequency domain
    // Normalize
    // Perform an iFFT (Cooley-Tukey or Bluestein etc.) to convert from frequency domain to time domain
}

void AudioEqualization::GenerateAudioEqualization(FILEINFO_Obj& FileInfoObj)
{
    ApplyAudioEqualizationFilter(FileInfoObj);
}
