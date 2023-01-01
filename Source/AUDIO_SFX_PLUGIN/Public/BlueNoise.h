#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class BlueNoise
    {
    public:
        BlueNoise();
        void GenerateBlueNoise(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyBlueFilter(FILEINFO_Obj& FileInfoObj);
    };
}