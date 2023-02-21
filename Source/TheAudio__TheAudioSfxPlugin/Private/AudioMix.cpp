#include "AudioMix.h"

using namespace ToneLibrary;

template<typename T, typename U>
AudioMix<T,U>::AudioMix()
{

}

/**
* Empty the AudioMixMixedAudioResultVector3DTRef buffer
* @param [ FileInfoObjRef ] --- The file info object that contains the file details.
* @return [ void ] --- No return value
*/
template<typename T, typename U>
void AudioMix<T, U>::ResetAudioMixResult(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
	U nMixResultChannelUInt64 = 0;
	// Loop through channels
	for (U nChannelUInt64 = 0; nChannelUInt64 < FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[nMixResultChannelUInt64].size(); nChannelUInt64++)
	{
		// Reset samples
		U nResizeToUInt64 = FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[nMixResultChannelUInt64][nChannelUInt64].size();
		FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[nMixResultChannelUInt64][nChannelUInt64] = VectorT<T>(nResizeToUInt64);
	}
}

/**
* Function to mix the audio from all channels
* @param [ FileInfoObjRef ] --- The file info object that contains the file details.
* @return [ void ] --- No return value
*/
template<typename T, typename U>
void AudioMix<T,U>::GenerateAudioMix(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
	// Loop through source files
	for(U nFileIndexUInt64 = 1; nFileIndexUInt64 < FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef.size())
	{
		// Loop through channels
		for (U nChannelUInt64 = 0; nChannelUInt64 < FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[nFileIndexUInt64].size(); nChannelUInt64++)
		{
			// Loop through samples
			for (U nSampleIndexUInt64 = 0; nSampleIndexUInt64 < FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[nFileIndexUInt64][nChannelUInt64].size(); nSampleIndexUInt64++)
			{
				FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[0][nChannelUInt64][nSampleIndexUInt64] =
					(
						FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[0][nChannelUInt64][nSampleIndexUInt64] +
						FileInfoObjRef.AudioMixMixedAudioResultVector3DTRef[nFileIndexUInt64][nChannelIndexUInt64][nSampleIndexUInt64];
					) / 2;
			}
		}
	}
}
