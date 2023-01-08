#pragma once

#include"Tones.Default.Settings.h"

namespace ToneLibrary
{
    template<typename T, typename U>
    class PlateReverb
    {
	public:
        PlateReverb();
		void GeneratePlateReverb(FILEINFO_Obj<T, U>&);
		void SetSize(FILEINFO_Obj<T, U>&);
		void SetDamping(FILEINFO_Obj<T, U>&);
		void SetWetLevel(FILEINFO_Obj<T, U>&);
		void SetDryLevel(FILEINFO_Obj<T, U>&);
	protected:
		void ApplyPlateReverbFilter(FILEINFO_Obj<T, U>&);
    private:
		T& AudioBufferPrivateFloat64TRef;
		T& AudioBufferTempPrivateFloat64TRef;
		U NumChannelsPrivateUint64T;
		U NumSamplesPrivateUint64T;
		U NumSamplesPerChannelPrivateUint64T;
		U SampleRatePrivateUint64T;
		U SizePrivateUint64T;
		T WetLevelPrivateFloat64T;
		T DryLevelPrivateFloat64T;
		T DampingPrivateFloat64T;
    };
}

