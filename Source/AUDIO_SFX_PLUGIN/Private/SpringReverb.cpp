#include "SpringReverb.h"

using namespace ToneLibrary;

template<typename T, typename U>
SpringReverb<T, U>::SpringReverb()
{
	
}

/**
* GenerateSpringReverb Tool
* @param [ SpringReverbDelayInSamplesFloat64T ] --- Delay in samples
* @param [ SpringReverbDecayInSecondsFloat64T ] --- Decay in seconds
* @param [ SpringReverbDampingFactorBetween0And1Float64T ] --- Damping factor, between [0,1]
* @param [ SpringReverbSampleRateInHertzFloat64T ] --- Sample rate [44.1_khz, 48_khz, 96_khz, 192_khz]
* @param [ SpringReverbVector3DRef[0] ] --- Input signal
* @returns [ SpringReverbVector3DRef[1] ] --- Output signal
*/
template<typename T, typename U>
void SpringReverb<T, U>::GenerateSpringReverb(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
	// Reverb params
	const T DelayInSamplesFloat64T = FileInfoObjRef.SpringReverbDelayInSamplesFloat64T;
	const T DecayInSecondsFloat64T = FileInfoObjRef.SpringReverbDecayInSecondsFloat64T;
	const T DampingFactorFloat64T = FileInfoObjRef.SpringReverbDampingFactorBetween0And1Float64T;
	
	// Audio Parameters (verify)
	const T SampleRateFloat64T = FileInfoObjRef.SpringReverbSampleRateInHertzFloat64T;
	const U NumChannelsUInt64T = FileInfoObjRef.SpringReverbVector3DRef[0].size();

	// Buffers for audio data
	FileInfoObjRef.SpringReverbVector3DRef[0]; // Input signal
	FileInfoObjRef.SpringReverbVector3DRef[1]; // Output signal
	
	// Process each channel
	for (U nChannelIndexUInt64T = 0; nChannelIndexUInt64T < SpringReverbVector3DRef[0].size(); nChannelIndexUInt64T++)
	{
		// Process each sample
		for (U nSampleIndexUInt64T = 0; nSampleIndexUInt64T < SpringReverbVector3DRef[0][nChannelIndexUInt64T].size(); nSampleIndexUInt64T++)
		{
			// Get input sample
			const T InputSampleFloat64T = SpringReverbVector3DRef[0][nChannelIndexUInt64T][nSampleIndexUInt64T];

			// Calculate the decay factor
			const T DecayFactorFloat64T = pow(DampingFactorFloat64T, nSampleIndexUInt64T / (SampleRateFloat64T * DecayInSecondsFloat64T));

			// Calculate the delay index
			U DelayIndexUInt64T = nSampleIndexUInt64T - DelayInSamplesFloat64T;
			
			// Calculate the delay sample value
			T DelaySampleFloat64T = DelayIndexUInt64T < 0 ? 0 : SpringReverbVector3DRef[0][nChannelIndexUInt64T][DelayIndexUInt64T];
			
			// Returm the resultant output sample value
			SpringReverbVector3DRef[1][nChannelIndexUInt64T][nSampleIndexUInt64T] = InputSampleFloat64T + (DecayFactorFloat64T * DelaySampleFloat64T);
		}
	}
}
