#include "BluesteinFFT.h"

using namespace ToneLibrary;


template <typename T, typename U>
BluesteinFFT<T, U>::BluesteinFFT()
{

}

/**
* The BluesteinFFT Fast Fourier Transform (FFT) -- simlar to Radix-2, and Cooley-Tukey,
* is an efficient algorithm for computing the Discrete Fourier Transform (DFT) approximation to the FFT.
* With a time complexity of only O(N Log N), one of the benefits of the BluesteinFFT,
* is that it can be used to compute the DFT on sequences of arbitrary length.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to retain details about the file.
* @return [ void ] --- No return value.
*/
template <typename T, typename U>
void BluesteinFFT<T, U>::GenerateBluesteinFFT(
    FILEINFO_Obj<T, U>& FileInfoObjRef
    )
{

}

template <typename T, typename U>
void BluesteinFFT<T, U>::ApplyBluesteinFFTFilter(
    FILEINFO_Obj<T, U>& FileInfoObjRef
)
{

}