#pragma once

#include "Tones.Default.Settings.h"

struct FILEINFO_Obj;

namespace ToneLibrary 
{
    using ComplexVectorFloat64 = std::vector<std::complex<UE_FLOAT64>>;

    class AudioEqualization
    {
    public:
        AudioEqualization();
        void GenerateAudioEqualization(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyAudioEqualizationFilter(FILEINFO_Obj& FileInfoObj);
        void CooleyTukeyFFT(
            FILEINFO_Obj& FileInfoObj,
            ComplexVectorFloat64& );
        void BluesteinFFT(
            FILEINFO_Obj& FileInfoObj,
            ComplexVectorFloat64& );
        void Radix2FFT(
            FILEINFO_Obj& FileInfoObj,
            ComplexVectorFloat64& );
        void NormalizeAudio(ComplexVectorFloat64& m);
    };
}

