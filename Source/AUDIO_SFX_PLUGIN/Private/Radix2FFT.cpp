#include "Radix2FFT.h"

using namespace ToneLibrary;

template <typename T, typename U>
Radix2FFT<T, U>::Radix2FFT()
{

}

/**
* The Radix-2 Fast Fourier Transform (FFT) is the most performant algorithm
* for computing the Discrete Fourier Transform (DFT) approximation on an input sequence -
* even outperforming Cooley-Tukey! If performance is a priority there are few current algorithms
* can beat Radix-2.
* @param [ FILEINFO_Obj& FileInfoObj ] --- The file parameters struct
* used to retain details about the file.
* @return [ void ] --- No return value.
*/
template <typename T, typename U>
void Radix2FFT<T, U>::GenerateRadix2FFT(
    FILEINFO_Obj<T, U>& FileInfoObjRef
    )
{
}

template <typename T, typename U>
void Radix2FFT<T, U>::ApplyRadix2FFTFilter(
    FILEINFO_Obj<T, U>& FileInfoObjRef
    )
{

}
