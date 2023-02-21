#include "AudioSummation.h"

using namespace ToneLibrary;

template<typename T, typename U>
AudioSummation<T, U>::AudioSummation()
{

}

template<typename T, typename U>
void AudioSummation<T, U>::NormalizeAudio(VectorT<T>& AudioData)
{
	// Find the maximum value in the audio file
	T MaxValue = 0;
	for (U i = 0; i < AudioData.size(); i++)
	{
		if (AudioData[i] > MaxValue)
		{
			MaxValue = AudioData[i];
		}
	}
	for (U i = 0; i < AudioData.size(); i++)
	{
		AudioData[i] = AudioData[i] / MaxValue;
	}
}

template<typename T, typename U>
void AudioSummation<T, U>::GenerateAudioSummation(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
	// cache objects to local variables
	FileInfoObjRef.AudioSummationSummedAudioVector2DTRef.resize(AudioSummationFileAVector2DTRef.size())
	FileInfoObjRef.AudioSummationFileAVector2DTRef;
	FileInfoObjRef.AudioSummationFileBVector2DTRef;
	// Sum the audio files by channel
	for (U nChannelIndexUInt64 = 0; nChannelIndexUInt64 < FileInfoObjRef.AudioSummationFileAVector2DTRef.size(); nChannelIndexUInt64++)
	{
		for (U nSampleIndexUInt64 = 0; nSampleIndexUInt64 < FileInfoObjRef.AudioSummationFileAVector2DTRef[nChannelIndexUInt64].size(); nSampleIndexUInt64++)
		{
			FileInfoObjRef.AudioSummationSummedAudioVector2DTRef[nChannelIndexUInt64][nSampleIndexUInt64] =
				FileInfoObjRef.AudioSummationFileAVector2DTRef[nChannelIndexUInt64][nSampleIndexUInt64] +
				FileInfoObjRef.AudioSummationFileBVector2DTRef[nChannelIndexUInt64][nSampleIndexUInt64];
		}		
		if (FileObjRef.AudioSummationNormalizeFlag)
		{
			NormalizeAudio(FileInfoObjRef.AudioSummationSummedAudioVector2DTRef[nChannelIndexUInt64]);
		}
	}	
}
