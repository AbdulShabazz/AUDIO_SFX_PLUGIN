#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
    class PurpleNoise
    {
    public:
        PurpleNoise();
        void GeneratePurpleNoise(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyPurpleFilter(FILEINFO_Obj& FileInfoObj);

    };
}
