#include "AudioEqualization.h"

using namespace ToneLibrary;

AudioEqualization::AudioEqualization()
{
}

void AudioEqualization::ApplyAudioEqualizationFilter(FILEINFO_Obj& FileInfoObj)
{
    // struct for storing audio sample data
    // READ audio, bps, bitrate, sample rate, number of channels
    // Perform an FFT (Cooley-Tukey or Bluestein) to convert from time domain to frequency domain

}

void AudioEqualization::GenerateAudioEqualization(FILEINFO_Obj& FileInfoObj)
{
    ApplyAudioEqualizationFilter(FileInfoObj);
}
