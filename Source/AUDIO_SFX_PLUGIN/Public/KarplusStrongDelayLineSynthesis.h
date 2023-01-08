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
		U DelayInNumberOfSamplesPrivateUInt64T;
		U ReadIndexPrivateUIntt64T;
		U WriteIndexPrivateUInt64T;
		U DefaultRingBufferSizePrivateUInt64;
		VectorT<T> RingBufferPrivateVectorT;
	};
}

