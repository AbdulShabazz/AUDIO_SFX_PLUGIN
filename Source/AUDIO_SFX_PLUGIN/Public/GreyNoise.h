#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class GreyNoise
    {
    public:
        GreyNoise();
        void GenerateGreyNoise(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyGreyFilter(FILEINFO_Obj& FileInfoObj);
    };
}