#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class WhitePerlinNoise
    {
    public:
        WhitePerlinNoise();
        void GenerateWhitePerlinNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyWhitePerlinNoiseFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };

}
