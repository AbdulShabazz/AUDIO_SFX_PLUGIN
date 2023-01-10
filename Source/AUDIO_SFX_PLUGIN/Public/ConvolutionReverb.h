#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class ConvolutionReverb
    {
    public:
        ConvolutionReverb();
        void GenerateConvolutionReverb(FILEINFO_Obj<T, U>&);
    };
}

