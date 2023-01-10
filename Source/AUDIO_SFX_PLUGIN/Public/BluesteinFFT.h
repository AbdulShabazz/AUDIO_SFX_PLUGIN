#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    template <typename T,typename U>
    class BluesteinFFT
    {
    public:
        BluesteinFFT();
        void InitializeBluesteinFFT(
            FILEINFO_Obj<T, U>& FileInfoObjRef
            );
        void ApplyBluesteinTransform(
            FILEINFO_Obj<T, U>& FileInfoObjRef
            );
    private:
        void ApplyBluesteinFFTFilter(
            FILEINFO_Obj<T, U>& FileInfoObjRef
            );
		ComplexVectorT<T> ForwardTwiddleFactorComplexVectorT;
		ComplexVectorT<T> InverseTwiddleFactorComplexVectorT;
    };
}

