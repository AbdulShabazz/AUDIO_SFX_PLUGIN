#include "ConvolutionReverb.h"

using namespace ToneLibrary;

template<typename T, typename U>
ConvolutionReverb<T, U>::ConvolutionReverb()
{

}

/**
* GenerateConvolutionReverb Tool
* @param [ ConvolutionReverbSampleRateInHertzFloat64T ] --- Sample rate [44.1_khz, 48_khz, 96_khz, 192_khz]
* @param [ ConvolutionReverbAudioResultVector3DTRef[0].size() ] --- Number of audio channels
* @param [ ConvolutionReverbAudioResultVector3DTRef[0] ] --- Input signal
* @returns [ ConvolutionReverbAudioResultVector3DTRef[1] ] --- Output signal
*/
template<typename T, typename U>
void ConvolutionReverb<T, U>::GenerateConvolutionReverb(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
	// Audio parameters and constraints (verify)
	const T SampleRateInHertzFloat64T = FileInfoObjRef.ConvolutionReverbSampleRateInHertzFloat64T; // eg 44.1_khz;
	const U NumberOfAudioChannelsUInt64T = FileInfoObjRef.ConvolutionReverbAudioResultVector3DTRef[0].size();

	// Buffers for Audio Data
	FileInfoObjRef.ConvolutionReverbAudioResultVectorTRef[0];

	// Impulse response reverb data
	Vector2DT<T>& ConvolutionTargetFIRVector2DTREF;

	if (FileInfoObjRef.ConvolutionReverbMethodEnumFlag in ConvolutionReverbLibraryEnumHashTableT)
	{
		ConvolutionTargetFIRVector2DTREF = ConvolutionReverbLibraryEnumHashTableT[FileInfoObjRef.ConvolutionReverbMethodEnumFlag]
	}
	else // FileInfoObjRef.ConvolutionReverbMethodNoneSelectedEnumFlag
	{		
		std::cout << "Error - ConvolutionReverb::GenerateConvolutionReverb FileInfoObjRef.ConvolutionReverbMethodNoneSelectedEnumFlag. " << std::endl;
		return;
	}

	// Convolve the input data with the impulse response 
	// Loop through the channels
	for (
			U nChannelUInt64T = 0; 
			nChannelUInt64T < NumberOfAudioChannelsUInt64T; 
			NumberOfAudioChannelsUInt64T++
		)
	{
		//  Clear the output buffer
		FileInfoObjRef.ConvolutionReverbAudioResultVector3DTRef[1][nChannelUInt64T] = VectorT<T>(0);

		// Process each sample from the input buffer
		for (
				U nSampleIndexUInt64T = 0; 
				nSampleIndexUInt64T < FileInfoObjRef.ConvolutionReverbAudioResultVector3DTRef[0][nChannelUInt64T].size();
				nSampleIndexUInt64T++
			)
		{
			T nSampleFloat64T = 0;

			// Convolve the input sample with the impulse response
			for (
					U nFIRIndexUInt64T = 0; 
					nFIRIndexUInt64T < ConvolutionTargetFIRVector2DTREF[nChannelUInt64T].size();
					nFIRIndexUInt64T++
				)
			{
				U nIdxUint64T = nSampleIndexUInt64T - nFIRIndexUInt64T;
				if (nIdxUint64T >= 0)
				{
					nSampleFloat64T +=
						FileInfoObjRef.ConvolutionReverbAudioResultVector3DTRef[0][nChannelUInt64T][nSampleIndexUInt64T] *
						FileInfoObjRef.ConvolutionTargetFIRVector2DTREF[nChannelUInt64T][nFIRIndexUInt64T];
				}
			}
			FileInfoObjRef.ConvolutionReverbAudioResultVector3DTRef[1][nChannelUInt64T].push_back(nSampleFloat64T);
		}
	}
}