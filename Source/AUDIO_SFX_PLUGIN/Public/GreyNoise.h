#pragma once

struct FILEINFO_Obj;

class GreyNoise
{
public:
    GreyNoise();
    void GenerateGreyNoise(FILEINFO_Obj& FileInfoObj);
protected:
    void ApplyGreyFilter(FILEINFO_Obj& FileInfoObj);
};