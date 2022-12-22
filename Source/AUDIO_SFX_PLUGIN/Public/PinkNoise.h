#pragma once

class PinkNoise
{
public:
    PinkNoise();
    void GeneratePinkNoise(float* noise, int length);
protected:
    void ApplyPinkFilter(float* noise, int length);
};