#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class FractalNoise
    {
    protected:
        void ApplyDiamondNoiseArrayShape(FILEINFO_Obj& FileInfoObj);
        void ApplyTriangularNoiseArrayShape(FILEINFO_Obj& FileInfoObj);
        void ApplyCircularNoiseArrayShape(FILEINFO_Obj& FileInfoObj);
        void ApplyRectangularNoiseArrayShape(FILEINFO_Obj& FileInfoObj);
        void ApplySquareNoiseArrayShape(FILEINFO_Obj& FileInfoObj);
        void ApplyFractalNoiseFilter(FILEINFO_Obj& FileInfoObj);
    public:
        FractalNoise();
        void GenerateFractalNoise(FILEINFO_Obj& FileInfoObj);
    };

}
