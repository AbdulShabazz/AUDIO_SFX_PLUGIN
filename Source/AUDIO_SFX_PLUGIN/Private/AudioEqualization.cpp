#include "AudioEqualization.h"

using namespace ToneLibrary;

template <typename T, typename U>
AudioEqualization<T, U>::AudioEqualization()
{
}

template <typename T, typename U>
void AudioEqualization<T, U>::NormalizeAudioForPlaybackT(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
    FileInfoObjRef.TemporaryAudioPlaybackFileVector4DTRef;
}

template <typename T, typename U>
void AudioEqualization<T, U>::NormalizeComplexAudioT(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
    std::transform(
        FileInfoObjRef.TemporaryAudioFileComplexVectorTRef.begin(),
        FileInfoObjRef.TemporaryAudioFileComplexVectorTRef.end(),
        FileInfoObjRef.TemporaryAudioFileComplexVectorTRef,
        [](ComplexT<T> x)
        {
            return static_cast<T>(x / FileInfoObjRef.TemporaryAudioFileComplexVectorTRef.size());
        }
        );
}

template <typename T, typename U>
void AudioEqualization<T, U>::ApplyAudioEqualizationFilterT(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    // struct for storing audio sample data
    // READ audio stream, BitsPerSample (bps), bitrate, sample rate, number of channels
    // Ensure target file has matching bitrate, and number of channels as the primary
    // Convert vector sequence to complex numbers
    // Perform an FFT (Cooley-Tukey or Bluestein etc.) to convert from time domain to frequency domain
    // Normalize (complex form)
    // Normalize (for playback)
    // Perform an FFT (Cooley-Tukey or Bluestein etc.) of the modified data

    switch (FileInfoObjRef.AudioEqualizationAlgorithmEnum)
    {
        bool ProperCallBool = false;
        case FILEINFO_Obj::AudioEqualizationENUM::Blustein:
            iBluesteinFFT.GenerateBluesteinFFT(FileInfoObjRef);
            NormalizeComplexAudioT(FileInfoObjRef);
            iBluesteinFFT.GenerateBluesteinFFT(FileInfoObjRef);
            NormalizeAudioForPlaybackT(FileInfoObjRef);
            break;
        case FILEINFO_Obj::AudioEqualizationENUM::Radix2:
            iRadix2FFT.GenerateRadix2FFT(FileInfoObjRef);
            NormalizeComplexAudioT(FileInfoObjRef);
            iRadix2FFT.GenerateRadix2FFT(FileInfoObjRef);
            NormalizeAudioForPlaybackT(FileInfoObjRef);
            break;
        case FILEINFO_Obj::AudioEqualizationENUM::CooleyTukey:
            ProperCallBool = true;
        default:
            if(!ProperCallBool)
            {
                std::cout << "Error - AudioEqualization<T>::ApplyAudioEqualizationFilterT : FileInfoObjRef.InvalidAudioEqualizationAlgorithmEnum" << std::endl;
            }
            iCooleyTukeyFFT.GenerateCooleyTukeyFFT(FileInfoObjRef);
            NormalizeComplexAudioT(FileInfoObjRef);
            iCooleyTukeyFFT.GenerateCooleyTukeyFFT(FileInfoObjRef);
            NormalizeAudioForPlaybackT(FileInfoObjRef);
            break;
    }
}

/**
* GenerateAudioEqualization Tool
* @param [ AudioEqualizationVector3DTRef[0] ] --- Input signal
* @param [ AudioEqualizationSampleRateFloat64T ] --- Sample rate of the audio file [44.1_khz | 48_khz | 96_khz | 192_khz]
* @param [ AudioEqualizationVector3DTRef[0].size() ] --- Number of channels in the audio signal
* @param [ AudioEqualizationLowCutOffFrequencyInHertzFloat64 ] --- low band cut off frequency in hertz [OPTION 1]
* @param [ AudioEqualizationHighCutOffFrequencyInHertzFloat64 ] --- high band cut off frequency in hertz [OPTION 1]
* @param [ AudioEqualizationLowGainMultiplierBetween0And10Float64T ] --- low frequency gain multiplier [0,10] [OPTION 1]
* @param [ AudioEqualizationHighGainMultiplierBetween0And10Float64T ] --- high frequency gain multiplier [0,10] [OPTION 1]
* @param [ AudioEqualizationVectorMultibandFlag ] --- Enables multiband equalization [OPTION 2]
* @param [ AudioEqualizationAlgorithmEnum ] --- Algorithm to use for the Fast Fourier Transform FFT during multi-band equalization [OPTION 2]
* @param [ AudioEqualizationFrequenciesInHertzWithMidbandGainMultipliersBetween0And10VectorTFloat64 ] --- Vector array of multi band target frequencies in hertz and their gain multipliers [OPTION 2]
* @returns [ AudioEqualizationVector3DTRef[1] ] --- Output signal
*/
template <typename T, typename U>
void AudioEqualization<T, U>::GenerateAudioEqualization(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    if(FileInfoObjRef.AudioEqualizationVectorMultibandFlag)
    {
        ApplyAudioEqualizationFilterT(FileInfoObjRef);
    }
    else
    {
        // Audio parameters
		T const nSampleRateFloat64T = FileInfoObjRef.AudioEqualizationSampleRateFloat64T;
		U const nNumberOfChannelsUInt64T = FileInfoObjRef.AudioEqualizationVector3DTRef[0].size();

		// Equalization parameters
		T const nLowCutOffFrequencyInHertzFloat64T = FileInfoObjRef.AudioEqualizationLowCutOffFrequencyInHertzFloat64T;
		T const nHighCutOffFrequencyInHertzFloat64T = FileInfoObjRef.AudioEqualizationHighCutOffFrequencyInHertzFloat64T;
		T const nLowGainMultiplierBetween0And10Float64T = FileInfoObjRef.AudioEqualizationLowGainMultiplierBetween0And10Float64T;
		T const nHighGainMultiplierBetween0And10Float64T = FileInfoObjRef.AudioEqualizationHighGainMultiplierBetween0And10Float64T;
        
        // Loop through channels
		for (U nChannelUInt64T = 0; nChannelUInt64T < nNumberOfChannelsUInt64T; nChannelUInt64T++)
		{
			// Loop through samples
			for (U nSampleUInt64T = 0; nSampleUInt64T < FileInfoObjRef.AudioEqualizationVector3DTRef[0][nChannelUInt64T].size(); nSampleUInt64T++)
			{
				// Get sample
				T const nSampleFloat64T = FileInfoObjRef.AudioEqualizationVector3DTRef[0][nChannelUInt64T][nSampleUInt64T];

				// Get frequency
				T const nFrequencyFloat64T = static_cast<T>(nSampleUInt64T * nSampleRateFloat64T / FileInfoObjRef.AudioEqualizationVector3DTRef[0][nChannelUInt64T].size());

				// Apply equalization
				T nEqualizedSampleFloat64T = nSampleFloat64T;
				if (nFrequencyFloat64T < nLowCutOffFrequencyInHertzFloat64T)
				{
					nEqualizedSampleFloat64T = nSampleFloat64T * nLowGainMultiplierBetween0And10Float64T;
				}
				else if (nFrequencyFloat64T > nHighCutOffFrequencyInHertzFloat64T)
				{
					nEqualizedSampleFloat64T = nSampleFloat64T * nHighGainMultiplierBetween0And10Float64T;
				}
                
				// Store equalized sample
				FileInfoObjRef.AudioEqualizationVector3DTRef[1][nChannelUInt64T][nSampleUInt64T] = nEqualizedSampleFloat64T;
			}
		}
    }
}
