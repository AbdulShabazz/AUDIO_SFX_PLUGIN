#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class SimplexNoise
    {
    public:
        SimplexNoise();
        void GenerateSimplexNoise(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplySimplexNoiseFilter(FILEINFO_Obj& FileInfoObj);
    };
}

