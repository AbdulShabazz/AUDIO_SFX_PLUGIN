#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class AudioMix
    {
    public:
        AudioMix();
        void GenerateAudioMix(FILEINFO_Obj<T, U>&);
        void ResetAudioMixResult(FILEINFO_Obj<T, U>&);
    };
}

