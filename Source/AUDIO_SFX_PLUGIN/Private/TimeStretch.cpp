#include "TimeStretch.h"

using namespace ToneLibrary;

template<typename T, typename U>
TimeStretch<T,U>::TimeStretch()
{
}

template<typename T, typename U>
void TimeStretch<T,U>::ApplyTimeStretchFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    // Set up audio buffers
    // Set time-stretching ratio
    // Set pitch-scaling ratio
    // Process input audio
}

template<typename T, typename U>
void TimeStretch<T,U>::GenerateTimeStretch(FILEINFO_Obj<T,U>& FileInfoObj)
{
    ApplyTimeStretchFilter(FileInfoObj);
}
