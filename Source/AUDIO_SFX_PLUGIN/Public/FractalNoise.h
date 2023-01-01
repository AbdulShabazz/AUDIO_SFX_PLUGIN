#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class FractalNoise
    {
    protected:
        void ApplyFractalNoiseFilter(FILEINFO_Obj& FileInfoObj);
    public:
        FractalNoise();
        void GenerateFractalNoise(FILEINFO_Obj& FileInfoObj);
    };

}
