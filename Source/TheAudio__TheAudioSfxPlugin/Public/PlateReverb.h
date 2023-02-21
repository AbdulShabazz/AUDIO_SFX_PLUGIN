#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class PlateReverb
    {
	public:
        PlateReverb();
		void GeneratePlateReverb(FILEINFO_Obj<T, U>&);
	protected:
		void ApplyPlateReverbFilter(FILEINFO_Obj<T, U>&);
    };
}

