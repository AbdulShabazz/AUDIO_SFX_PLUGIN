#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class AudioSummation
    {
	public:
		AudioSummation();
		void GenerateAudioSummation(FILEINFO_Obj<T, U>&);
	private:
		void NormalizeAudio(VectorT<T>& );
    };
}

