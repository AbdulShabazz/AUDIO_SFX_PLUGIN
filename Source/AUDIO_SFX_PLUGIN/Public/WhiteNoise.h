#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class WhiteNoise
    {
    public:
        WhiteNoise();
        void GenerateWhiteNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}
