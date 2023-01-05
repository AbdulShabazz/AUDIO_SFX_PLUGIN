#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class GreyNoise
    {
    public:
        GreyNoise();
        void GenerateGreyNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyGreyFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}