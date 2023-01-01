#pragma once

struct IFILEINFO_Obj;

namespace ToneLibrary
{
    class WhiteNoise
    {
    public:
        WhiteNoise();
        void GenerateWhiteNoise(FILEINFO_Obj& FileInfoObj);
    };
}
