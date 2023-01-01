#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary
{
        class TimeStretch
    {
    public:
        TimeStretch();
        void GenerateTimeStretch(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyTimeStretchFilter(FILEINFO_Obj& FileInfoObj);
    };
}

