#pragma once

#include "Tones.Default.Settings.h"
#include "CooleyTukeyFFT.h"
#include "BluesteinFFT.h"
#include "Radix2FFT.h"

namespace ToneLibrary 
{
    template<typename T, typename U>
    class AudioEqualization
    {
    public:
        AudioEqualization();
        void GenerateAudioEqualization(FILEINFO_Obj<T,U>&);
        void ApplyAudioEqualizationFilterT(FILEINFO_Obj<T, U>& );
    protected:
        void NormalizeComplexAudioT(FILEINFO_Obj<T, U>&);
        void NormalizeAudioForPlaybackT(FILEINFO_Obj<T, U>&);

        CooleyTukeyFFT<T, U> iCooleyTukeyFFT;
        BluesteinFFT<T, U> iBluesteinFFT;
        Radix2FFT<T, U> iRadix2FFT;
    };
}

