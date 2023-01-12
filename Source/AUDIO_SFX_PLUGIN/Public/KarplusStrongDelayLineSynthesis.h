#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
	template<typename T, typename U>
	class KarplusStrongDelayLineSynthesis
	{
	public:
		KarplusStrongDelayLineSynthesis(
			T FrequencyInHertzFloat64T,
			U DelayFloat64T,
			U ReadIndexFloat64T,
			U WriteIndexFloat64T, 
			U DefaultRingBufferSizePrivateUInt64
		);
		void SendKarplusStrongDelayLineSynthesisParameters(FILEINFO_Obj<T, U>&);
		void GenerateKarplusStrongDelayLineSynthesis(FILEINFO_Obj<T, U>&);
	private:
		T FrequencyInHertzPrivateFloat64T;
		U DelayInNumberOfSamplesPrivateUInt64T = 1;
		U ReadIndexPrivateUIntt64T = 0;
		U WriteIndexPrivateUInt64T = 0;
		U DefaultRingBufferSizePrivateUInt64 = 1024;
		VectorT<T> RingBufferPrivateVectorT;
	};
}

