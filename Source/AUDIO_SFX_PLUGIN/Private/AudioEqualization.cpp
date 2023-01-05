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
                std::cout << "Error - AudioEqualization<T>::ApplyAudioEqualizationFilterT : invalid FileInfoObjRef.AudioEqualizationAlgorithmEnum" << std::endl;
            }
            iCooleyTukeyFFT.GenerateCooleyTukeyFFT(FileInfoObjRef);
            NormalizeComplexAudioT(FileInfoObjRef);
            iCooleyTukeyFFT.GenerateCooleyTukeyFFT(FileInfoObjRef);
            NormalizeAudioForPlaybackT(FileInfoObjRef);
            break;
    }
}

template <typename T, typename U>
void AudioEqualization<T, U>::GenerateAudioEqualization(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    ApplyAudioEqualizationFilterT(FileInfoObjRef);
}
