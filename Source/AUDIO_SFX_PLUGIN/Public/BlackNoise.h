#pragma once

struct FILEINFO_Obj;

class BlackNoise
{
public:
    BlackNoise();
    void GenerateBlackNoise(FILEINFO_Obj& FileInfoObj);
protected:
    void ApplyBlackFilter(FILEINFO_Obj& FileInfoObj);
};