#include "PlateReverb.h"

using namespace ToneLibrary;

template<typename T, typename U>
PlateReverb<T,U>::PlateReverb()
{

}

template<typename T, typename U>
void PlateReverb<T, U>::ApplyPlateReverbFilter(
	FILEINFO_Obj<T, U>& FileInfoObj_Ref
	)
{
	// Loop through the channels
	for (U nChannelUInt64 = 0; nChannelUInt64 < FileInfoObj_Ref.PlateReverb3DVectorTRef[0].size(); nChannelUInt64++)
	{
		// Loop through the samples
		for (U nSampleIdxUInt64 = 0; nSampleIdxUInt64 < FileInfoObj_Ref.PlateReverb3DVectorTRef[0][nChannelUInt64].size(); nSampleIdxUInt64++)
		{
			// Apply the plate algorithm
			
			// Get the current input sample and the previous output sample, iff available.
			T inFloat64T = FileInfoObj_Ref.PlateReverb3DVectorTRef[0][nChannelUInt64][nSampleIdxUInt64];
			T outFloat64T = nSampleIdxUInt64 > 0 ? FileInfoObj_Ref.PlateReverb3DVectorTRef[1][nChannelUInt64][nSampleIdxUInt64 - 1] : 0.0;
			
			// Calculate the Wet (processed) / Dry (unprocessed) levels
			T wetFloat64T = FileInfoObj_Ref.PlateReverbDampingFloat64T * (outFloat64TT + inFloat64T);
			T dryFloat64T = inFloat64T;

			// Mix the Wet and Dry levels
			T WetMixFloat64T = FileInfoObj_Ref.PlateReverbWetnessFloat64T * wetFloat64T;
			T DryMixFloat64T = FileInfoObj_Ref.PlateReverbDrynessFloat64T * dryFloat64T;
			T MixFloat64T = WetMixFloat64T + DryMixFloat64T;

			// Set the output sample
			FileInfoObj_Ref.PlateReverb3DVectorTRef[1][nChannelUInt64][nSampleIdxUInt64] = MixFloat64T;
		}
	}
}

/**
* Plate Reverb synthesis tool
* @param [ PlateReverbDampingFloat64T ] --- Damping level
* @param [ PlateReverbDrynessFloat64T ] --- Dryness of the reverb
* @param [ PlateReverbWetnessFloat64T ] --- Wetness of the reverb
* @param [ PlateReverb3DVectorTRef[0] ] --- Original file
* @returns [ PlateReverb3DVectorTRef[1] ] --- Returns result
*/
template<typename T, typename U>
void PlateReverb<T, U>::GeneratePlateReverb(
	FILEINFO_Obj<T, U>& FileInfoObj_Ref
	)
{
	ApplyPlateReverbFilter(FileInfoObj_Ref);
}