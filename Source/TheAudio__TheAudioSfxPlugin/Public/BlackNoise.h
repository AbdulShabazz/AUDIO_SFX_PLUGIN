#pragma once
#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class BlackNoise
    {
    public:
        BlackNoise();
        void GenerateBlackNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyBlackFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}