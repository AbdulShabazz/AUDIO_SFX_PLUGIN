#pragma once

struct FILEINFO_Obj;

namespace ToneLibrary 
{
    class AudioEqualization
    {
    public:
        AudioEqualization();
        void GenerateAudioEqualization(FILEINFO_Obj& FileInfoObj);
    protected:
        void ApplyAudioEqualizationFilter(FILEINFO_Obj& FileInfoObj);
    };
}

