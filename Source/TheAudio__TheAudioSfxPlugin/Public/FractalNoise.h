#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class FractalNoise
    {
    protected:
        void ApplyDiamondNoiseArrayShape(FILEINFO_Obj<T,U>& FileInfoObj);
        void ApplyTriangularNoiseArrayShape(FILEINFO_Obj<T,U>& FileInfoObj);
        void ApplyCircularNoiseArrayShape(FILEINFO_Obj<T,U>& FileInfoObj);
        void ApplyRectangularNoiseArrayShape(FILEINFO_Obj<T,U>& FileInfoObj);
        void ApplySquareNoiseArrayShape(FILEINFO_Obj<T,U>& FileInfoObj);
        void ApplyFractalNoiseFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    public:
        FractalNoise();
        void GenerateFractalNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    };

}
