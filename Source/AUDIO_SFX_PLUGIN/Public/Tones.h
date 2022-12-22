#pragma once

class BlackNoise;
class BlueNoise;
class GreyNoise;
class PinkNoise;
class PurpleNoise;
class WhiteNoise;

class Tone : public 
    BlackNoise, 
    BlueNoise,
    GreyNoise,
    PinkNoise,
    PurpleNoise,
    WhiteNoise
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
    } NoiseObj;
    struct RANDOM_TONE_OBJ {

    } RandomToneGenerateObj;
};