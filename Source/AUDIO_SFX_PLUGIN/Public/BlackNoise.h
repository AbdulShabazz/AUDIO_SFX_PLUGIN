#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class BlackNoise
    {
    public:
        BlackNoise();
        void GenerateBlackNoise(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyBlackFilter(FILEINFO_Obj& FileInfoObj);
    };
}