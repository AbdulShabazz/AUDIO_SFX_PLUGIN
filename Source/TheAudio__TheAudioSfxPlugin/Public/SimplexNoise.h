#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class SimplexNoise
    {
    public:
        SimplexNoise();
        void GenerateSimplexNoise(FILEINFO_Obj<T,U>&);
    protected:
        void ApplySimplexNoiseFilter(FILEINFO_Obj<T,U>&);
        void GenerateRandomPermutationTable(FILEINFO_Obj<T, U>&);
        void GenerateRandomGradientTable(FILEINFO_Obj<T, U>&);
    };
}

