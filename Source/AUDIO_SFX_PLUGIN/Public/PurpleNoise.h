#pragma once

class PurpleNoise
{
public:
    PurpleNoise();
    void GeneratePurpleNoise(float* noise, int length);
protected:
    void ApplyPurpleFilter(float* noise, int length);

};