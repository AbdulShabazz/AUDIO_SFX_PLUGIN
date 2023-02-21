#pragma once

template<typename T, typename U>
struct FILEINFO_Obj;

namespace ToneLibrary
{
    template<typename T, typename U>
    class TimeStretch
    {
    public:
        TimeStretch();
        void GenerateTimeStretch(FILEINFO_Obj<T,U>& FileInfoObj);
    protected:
        void ApplyTimeStretchFilter(FILEINFO_Obj<T,U>& FileInfoObj);
    };
}

