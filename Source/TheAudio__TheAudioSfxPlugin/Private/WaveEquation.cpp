#include "WaveEquation.h"

using namespace ToneLibrary;

template<typename T, typename U>
WaveEquation<T, U>::WaveEquation(
	T WaveSpeedInMetersPerSecondFloat64T, 
	T WaveLengthInMetersFloat64T, 
	T StartTimeInSecondsFloat64T
	)
	: WaveSpeedInMetersPerSecondPrivateFloat64T(WaveSpeedInMetersPerSecondFloat64T),
	  WaveLengthInMetersPrivateFloat64T(WaveLengthInMetersFloat64T),
	  StartTimeInSecondsPrivateFloat64T(StartTimeInSecondsFloat64T)
{

}

template<typename T, typename U>
void WaveEquation<T, U>::SendWaveEquationParameters(FILEINFO_Obj<T, U>& FileInfo_ObjRef)
{
	WaveSpeedInMetersPerSecondPrivateFloat64T = 
		FileInfo_ObjRef.WaveEquationWaveSpeedInMetersPerSecondFloat64T || 
		WaveSpeedInMetersPerSecondPrivateFloat64T;
	WaveLengthInMetersPrivateFloat64T = 
		FileInfo_ObjRef.WaveEquationWaveLengthInMetersFloat64T || 
		WaveLengthInMetersPrivateFloat64T;
	StartTimeInSecondsPrivateFloat64T = 
		FileInfo_ObjRef.WaveEquationStartTimeInSecondsFloat64T || 
		StartTimeInSecondsPrivateFloat64T;
	FileInfo_ObjRef.WaveEquationResultFloat64TRef = 
		std::sin(
			WaveSpeedInMetersPerSecondPrivateFloat64T * 
			FileInfo_ObjRef.WaveEquationCurrentTimeInSecondsFloat64T /
			WaveLengthInMetersPrivateFloat64T * 
			FileInfo_ObjRef.WaveEquationCurrentPositionInMetersFloat64T
			)
}

template<typename T, typename U>
void WaveEquation<T, U>::GenerateWaveEquation(FILEINFO_Obj<T, U>& FileInfo_ObjRef)
{

}