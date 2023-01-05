#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class SimplexNoise
    {
    public:
        SimplexNoise();
        void GenerateSimplexNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplySimplexNoiseFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}

