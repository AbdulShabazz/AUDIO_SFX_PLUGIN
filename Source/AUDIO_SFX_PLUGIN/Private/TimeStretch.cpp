#include "TimeStretch.h"

using namespace ToneLibrary;

template<typename T, typename U>
TimeStretch<T,U>::TimeStretch()
{
}

template<typename T, typename U>
void TimeStretch<T,U>::ApplyTimeStretchFilter(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    
    // Set time-stretching ratio
	U StretchRatio = FileInfoObjRef.TimeStretchStretchRatioInNumberOfSamplesUInt64T;
	if (StretchRatio < 1)
	{
		std::cout << "error -  TimeStretch<T,U>::ApplyTimeStretchFilter - FileInfoObjRef.invalidTimeStretchStretchRatioInNumberOfSamplesUInt64TLessThan1" << std::endl;
		return
	}
	T StretchRatioTimeStep = 1 / FileInfoObjRef.TimeStretchStretchRatioInNumberOfSamplesUInt64T;
	
    // Set up audio buffers
	U NumChannels = FileInfoObjRef.TimeStretchVector3DT[0].size();;
	U NumSamples = FileInfoObjRef.TimeStretchVector3DT[0][0].size() * StretchRatio;
	Vector2DT<T>& oBuffer = FileInfoObjRef.TimeStretchVector3DT[1];
	Vector2DT<T>& oBufferTemp = FileInfoObjRef.TimeStretchVector3DT[0];
    
    // Set pitch-scaling ratio
	T PitchRatio = FileInfoObjRef.TimeStretchPitchRatioFloat64T;
    
	// Apply pitch scaling	
	for (U Channel = 0; Channel < NumChannels; Channel++)
	{
		for (U Sample = 0; Sample < NumSamples; Sample++)
		{
			oBufferTemp[Channel][SampleIndex] *= PitchRatio;
		}
	}

	// Apply time stretching
	U OutputSampleIndex = 0;  StretchRatio;
	for (U Channel = 0; Channel < NumChannels; Channel++)
	{
		U SampleIndexUInt64T = 0;
		oBuffer[Channel] = VectorT<T>(NumSamples);
		for (U Sample = 0; Sample < NumSamples - 1; Sample++)
		{
			T TimeStepFloat64T = StretchRatioTimeStep;
			for(U StepUInt64T = 0; StepUInt64T < StretchRatio; StepUInt64T++)
			{
				oBuffer[Channel][SampleIndexUInt64T] = 
					TimeStepFloat64T * oBufferTemp[Channel][Sample + 1] + 
					(1 - TimeStepFloat64T) * oBufferTemp[Channel][Sample];
				TimeStepFloat64T += StretchRatioTimeStep;
				SampleIndexUInt64T++;
			}
		}
	}
	
}

/**
* GenerateTimeStretch Tool
* @param [ TimeStretchVector3DT[0].size() ] -- Number of channels
* @param [ TimeStretchVector3DT[0][0].size() ] --- Number of precomputed samples
* @param [ TimeStretchStretchRatioInNumberOfSamplesUInt64T ] --- Time-stretch in number of samples
* @param [ TimeStretchPitchRatio ] --- Pitch-scaling ratio
* @param [ TimeStretchVector3DT[0] ] --- Input
* @returns [ TimeStretchVector3DT[1] ] --- Output
*/
template<typename T, typename U>
void TimeStretch<T,U>::GenerateTimeStretch(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    ApplyTimeStretchFilter(FileInfoObjRef);
}
