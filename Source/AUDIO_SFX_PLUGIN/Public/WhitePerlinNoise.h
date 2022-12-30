#pragma once

struct FILEINFO_Obj;

class WhitePerlinNoise
{

public:

    WhitePerlinNoise();
    void GenerateWhitePerlinNoise(FILEINFO_Obj& FileInfoObj);

protected:

    void ApplyWhitePerlinNoiseFilter(FILEINFO_Obj& FileInfoObj);
};

