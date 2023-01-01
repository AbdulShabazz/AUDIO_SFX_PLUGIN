#include "TimeStretch.h"

using namespace ToneLibrary;

TimeStretch::TimeStretch()
{
}

void TimeStretch::ApplyTimeStretchFilter(FILEINFO_Obj& FileInfoObj)
{
    // Set up audio buffers
    // Set time-stretching ratio
    // Set pitch-scaling ratio
    // Process input audio
}

void TimeStretch::GenerateTimeStretch(FILEINFO_Obj& FileInfoObj)
{
    ApplyTimeStretchFilter(FileInfoObj);
}
