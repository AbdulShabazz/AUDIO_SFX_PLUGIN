#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class BlueNoise
    {
    public:
        BlueNoise();
        void GenerateBlueNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyBlueFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}