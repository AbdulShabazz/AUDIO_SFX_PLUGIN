#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class PurpleNoise
    {
    public:
        PurpleNoise();
        void GeneratePurpleNoise(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyPurpleFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}
