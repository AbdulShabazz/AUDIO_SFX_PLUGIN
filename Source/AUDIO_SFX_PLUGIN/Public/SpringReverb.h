#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class SpringReverb
    {
    public:
        SpringReverb();
        void GenerateSpringReverb(FILEINFO_Obj<T, U>&);
    };
}


