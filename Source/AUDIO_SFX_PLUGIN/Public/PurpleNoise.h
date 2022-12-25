#pragma once

struct FILEINFO_Obj;

class PurpleNoise
{
public:
    PurpleNoise();
    void GeneratePurpleNoise(FILEINFO_Obj& FileInfoObj);
protected:
    void ApplyPurpleFilter(FILEINFO_Obj& FileInfoObj);

};