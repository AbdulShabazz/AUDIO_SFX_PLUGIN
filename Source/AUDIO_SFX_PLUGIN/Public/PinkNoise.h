#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class PinkNoise
    {
    public:
        PinkNoise();
        void GeneratePinkNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyPinkFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}