#include "KarplusStrongDelayLineSynthesis.h"

using namespace ToneLibrary;

template<typename T, typename U>
KarplusStrongDelayLineSynthesis<T, U>::KarplusStrongDelayLineSynthesis(
	T FrequencyInHertzFloat64T,
	U DelayFloat64T = 1,
	U ReadIndexFloat64T = 0,
	U WriteIndexFloat64T = 0,
	U DefaultRingBufferSizePrivateUInt64 = 1024
	) 
	: 
	FrequencyPrivateFloat64T(FrequencyInHertzFloat64T),
	DelayPrivateFloat64T(DelayUInt64T),
	ReadIndexPrivateFloat64T(ReadIndexUInt64T),
	WriteIndexPrivateUint64T(WriteIndeUInt64T),
	DefaultRingBufferSizePrivateUint64(DefaultRingBufferSizePrivateUInt64)
{	
	
}

template<typename T, typename U>
void KarplusStrongDelayLineSynthesis<T, U>::SendKarplusStrongDelayLineSynthesisParameters(FILEINFO_Obj<T, U>& FileInfo_ObjRef)
{
	FrequencyPrivateFloat64T = FileInfo_ObjRef.KarplusStrongDelayLineSynthesisFrequencyInHertzFloat64T || FrequencyPrivateFloat64T;
	DelayPrivateUInt64T = FileInfo_ObjRef.KarplusStrongDelayLineSynthesisDelayInNumberOfSamplesUInt64T || DelayPrivateUInt64T;
	ReadIndexPrivateUInt64T = FileInfo_ObjRef.KarplusStrongDelayLineSynthesisReadIndexUInt64T || ReadIndexPrivateUInt64T;
	WriteIndexPrivateUInt64T = FileInfo_ObjRef.KarplusStrongDelayLineSynthesisWriteIndexUInt64T || WriteIndexPrivateUInt64T;
	DefaultRingBufferSizePrivateUInt64 = FileInfo_ObjRef.KarplusStrongDelayLineSynthesisDefaultRingBufferSizePrivateUInt64 || DefaultRingBufferSizePrivateUInt64;
}

// This is a Karplus-Strong delay line synthesis algorithm.
// This algorithm is used to generate a tone.
// @param [ FileInfo_ObjRef ] --- This is a reference to a FileInfo_Obj object.
// @return [ void ] --- This function does not return a value.
template<typename T, typename U>
void KarplusStrongDelayLineSynthesis<T, U>::GenerateKarplusStrongDelayLineSynthesis(FILEINFO_Obj<T, U>& FileInfo_ObjRef)
{
	// Initialize the ring buffer.
	RingBufferPrivateVectorT = VectorT<T>(DefaultRingBufferSizePrivateUInt64);
	// Create a temporary variable to hold the value of the current sample.
	T CurrentSampleFloat64T = 0.5 * (
		RingBufferPrivateVectorT[ReadIndexPrivateUInt64T] + 
		RingBufferPrivateVectorT[ReadIndexPrivateUInt64T + 
		DelayPrivateUInt64T]
		) % DefaultRingBufferSizePrivateUInt64;
	RingBufferPrivateVectorT[WriteIndexPrivateUInt64T] = CurrentSampleFloat64T;
	FileInfo_ObjRef.KarplusStrongDelayLineSynthesisCurrentSampleFloat64T = CurrentSampleFloat64T;
	
	// Increment the read and write indices.
	ReadIndexPrivateUInt64T = (ReadIndexPrivateUInt64T + 1) % DefaultRingBufferSizePrivateUInt64;
	WriteIndexPrivateUInt64T = (WriteIndexPrivateUInt64T + 1) % DefaultRingBufferSizePrivateUInt64;
}
