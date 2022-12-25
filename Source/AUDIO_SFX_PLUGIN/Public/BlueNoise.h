#pragma once

struct FILEINFO_Obj;

class BlueNoise
{
public:
    BlueNoise();
    void GenerateBlueNoise(FILEINFO_Obj& FileInfoObj);
protected:
    void ApplyBlueFilter(FILEINFO_Obj& FileInfoObj);
};