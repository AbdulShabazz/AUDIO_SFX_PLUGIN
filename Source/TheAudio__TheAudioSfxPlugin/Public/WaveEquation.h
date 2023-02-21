#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
	template<typename T, typename U>
	class WaveEquation
	{
	public:
		explicit WaveEquation(T, T, T);
		void SendWaveEquationParameters(FILEINFO_Obj<T, U>&);
		void GenerateWaveEquation(FILEINFO_Obj<T, U>&);
	private:
		T WaveSpeedInMetersPerSecondPrivateFloat64T;
		T WaveLengthInMetersPrivateFloat64T;
		T StartTimeInSecondsPrivateFloat64T;
	};
}

