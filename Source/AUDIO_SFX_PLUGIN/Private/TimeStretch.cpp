#include "TimeStretch.h"

using namespace ToneLibrary;

template<typename T, typename U>
TimeStretch<T,U>::TimeStretch()
{
}

template<typename T, typename U>
void TimeStretch<T,U>::ApplyTimeStretchFilter(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
	// TODO: Add FileInfoObjRef properties to Tones.Default.Settings.h

    // Set up audio buffers
	U NumChannels = FileInfoObjRef.NumChannels;
	U NumSamples = FileInfoObjRef.NumSamples;
	U NumSamplesPerChannel = NumSamples / NumChannels;
	T& AudioBuffer = FileInfoObjRef.AudioBuffer;
	T& AdioBufferTemp = FileInfoObjRef.AudioBufferTemp;
    
    // Set time-stretching ratio
	T StretchRatio = FileInfoObjRef.StretchRatio;
    
    // Set pitch-scaling ratio
	T PitchRatio = FileInfoObjRef.PitchRatio;
    
	// Process input audio 	
	for (U Channel = 0; Channel < NumChannels; Channel++)
	{
		for (U Sample = 0; Sample < NumSamplesPerChannel; Sample++)
		{
			U SampleIndex = Sample * NumChannels + Channel;
			oBufferTemp[SampleIndex] = oBuffer[SampleIndex];
		}
	}

	// Apply pitch scaling
	for (U Channel = 0; Channel < NumChannels; Channel++)
	{
		for (U Sample = 0; Sample < NumSamplesPerChannel; Sample++)
		{
			U SampleIndex = Sample * NumChannels + Channel;
			oBuffer[SampleIndex] = oBufferTemp[SampleIndex] * PitchRatio;
		}
	}	
	
	// Apply time-stretching filter
	U OutputSampleIndex = 0;
	for (U Channel = 0; Channel < NumChannels; Channel++)
	{
		for (U Sample = 0; Sample < NumSamplesPerChannel; Sample++)
		{
			U SampleIndex = Sample * NumChannels + Channel;
			oBuffer[OutputSampleIndex] = oBufferTemp[SampleIndex];
			OutputSampleIndex += StretchRatio;
		}
	}
}

template<typename T, typename U>
void TimeStretch<T,U>::GenerateTimeStretch(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    ApplyTimeStretchFilter(FileInfoObjRef);
}
