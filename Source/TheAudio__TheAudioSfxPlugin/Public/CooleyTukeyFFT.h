#pragma once

#include "Tones.Default.Settings.h"

namespace ToneLibrary
{
    // Set Float(T) and Unsigned Int (U) resolution 
    template<typename T, typename U>
    class CooleyTukeyFFT
    {
    public:
        CooleyTukeyFFT();
        void GenerateCooleyTukeyFFT(FILEINFO_Obj<T, U>& FileInfoObj);
    private:
        void ApplyCooleyTukeyFFTFilterT(
            FILEINFO_Obj<T, U>& FileInfoObj,
            ComplexVector4DT<T>&
        );
        void CooleyTukeyFFTi(
            FILEINFO_Obj<T, U>& FileInfoObj,
            VectorT<T>&
        );
    };
}

