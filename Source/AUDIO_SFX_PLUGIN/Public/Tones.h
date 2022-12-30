#pragma once

class BlackNoise;
class BlueNoise;
class GreyNoise;
class PinkNoise;
class PurpleNoise;
class WhiteNoise;
class WhitePerlinNoise;

class Tone : public 
    BlackNoise, 
    BlueNoise,
    GreyNoise,
    PinkNoise,
    PurpleNoise,
    WhiteNoise,
    WhitePerlinNoise
{

public:

    Tone();

    struct NOISE_OBJ
    {
        BlackNoise Black;
        BlueNoise Blue;
        GreyNoise Grey;
        PinkNoise Pink;
        PurpleNoise Purple;
        WhiteNoise White;
        WhitePerlinNoise Perlin;
    } NoiseObj;

    struct RANDOM_TONE_OBJ {

    } RandomToneGenerateObj;
};