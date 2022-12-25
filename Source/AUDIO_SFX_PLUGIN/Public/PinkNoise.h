#pragma once

struct FILEINFO_Obj;

class PinkNoise
{
public:
    PinkNoise();
    void GeneratePinkNoise(FILEINFO_Obj& FileInfoObj);
protected:
    void ApplyPinkFilter(FILEINFO_Obj& FileInfoObj);
};