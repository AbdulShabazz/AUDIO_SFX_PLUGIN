#include "WhitePerlinNoise.h"
#include "Tones.Default.Settings.h"

WhitePerlinNoise::WhitePerlinNoise()
{
}

void WhitePerlinNoise::ApplyWhitePerlinNoiseFilter(FILEINFO_Obj& FileInfoObj)
{
    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Set the range of the noise signal
    std::uniform_real_distribution<const UE_FLOAT64> dis(-1.0f, 1.0f);

    // Init a vec array of gradients
    std::vector<std::vector<UE_UINT64>> Gradients2DUFloat64(2, std::vector<UE_UINT64>(FileInfoObj.PerlinNoiseNumGradientsFloat64));

    // Generate a set of random gradients
    for(UE_UINT64 j = 0; j < FileInfoObj.PerlinNoiseNumGradientsFloat64; j++)
    {
        Gradients2DUFloat64[0][j] = dis(gen);
        Gradients2DUFloat64[1][j] = dis(gen);
    }

    // Generate noise data
    std::vector<UE_FLOAT64> noise(
        FileInfoObj.PerlinNoiseWidthUInt64 * FileInfoObj.PerlinNoiseHeightUInt64
        );
    UE_UINT64 hUint64 = FileInfoObj.PerlinNoiseHeightUInt64;
    UE_UINT64 wUint64 = FileInfoObj.PerlinNoiseWidthUInt64;
    for (UE_UINT64 i = 0; i < hUint64; i++)
    {
        for (UE_UINT64 j = 0; j < wUint64; j++)
        {
            // Calculate the indices of the four gradients that enclose the point
            UE_UINT64 i0 = i / 2;
            UE_UINT64 j0 = j / 2;
            UE_UINT64 i1 = i0 + 1;
            UE_UINT64 j1 = j0 + 1;

            // Calculate the weight for each gradient
            UE_FLOAT64 wi = i / 2.0f - i0;
            UE_FLOAT64 wj = j / 2.0f - j0;

            // Interpolate the values at the four (4) gradients
            UE_UINT64 n0 = DotProductUint64(
                { Gradients2DUFloat64[i0][j0], Gradients2DUFloat64[i1][j0] }, 
                { Gradients2DUFloat64[i0][j1], Gradients2DUFloat64[i1][j1] }
                );
            UE_UINT64 n1 = DotProductUint64(
                { Gradients2DUFloat64[i0][j0], Gradients2DUFloat64[i1][j0] },
                { Gradients2DUFloat64[i0][j1], Gradients2DUFloat64[i1][j1] }
                );
            UE_UINT64 n2 = DotProductUint64(
                { Gradients2DUFloat64[i0][j0], Gradients2DUFloat64[i1][j0] },
                { Gradients2DUFloat64[i0][j1], Gradients2DUFloat64[i1][j1] }
                );
            UE_UINT64 n3 = DotProductUint64(
                { Gradients2DUFloat64[i0][j0], Gradients2DUFloat64[i1][j0] },
                { Gradients2DUFloat64[i0][j1], Gradients2DUFloat64[i1][j1] }
                );

            // Interpolate between the four values to get the final noise value for the point
            UE_FLOAT64 NoiseValueFloat64 = BilinearInterpolationT<UE_UINT64, UE_FLOAT64>(n0, n1, n2, n3, wi, wj);

            // Store the NoiseValueFloat64 in the noise map
            noise[i + wUint64 * j] = NoiseValueFloat64;
        }
    }
}

/**
* White Perlin Noise is a type of gradient noise that is generated
* by interpolating bilinearly between a set of randomly generated gradients.
* It was developed by Ken Perlin in the 1980s as a more natural-sounding
* alternative to white noise.
* @param [ FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
void WhitePerlinNoise::GenerateWhitePerlinNoise(FILEINFO_Obj& FileInfoObj)
{
    ApplyWhitePerlinNoiseFilter(FileInfoObj);
}