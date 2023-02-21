#include "WhitePerlinNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
WhitePerlinNoise<T,U>::WhitePerlinNoise()
{
}

template<typename T, typename U>
void WhitePerlinNoise<T,U>::ApplyWhitePerlinNoiseFilter(FILEINFO_Obj<T,U>& FileInfoObj)
{
    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Set the range of the noise signal
    std::uniform_real_distribution<T> dis(-1.0f, 1.0f);

    // Init a vec array of gradients
    Vector2DT<T> Gradients2DFloat64(2, VectorT<T>(FileInfoObj.PerlinNoiseNumGradientsFloat64));

    // Generate a set of random gradients
    for(U j = 0; j < FileInfoObj.PerlinNoiseNumGradientsFloat64; j++)
    {
        Gradients2DFloat64[0][j] = dis(gen);
        Gradients2DFloat64[1][j] = dis(gen);
    }

    // Generate noise data
    VectorT<T> NoiseMap1DFloat64(
        FileInfoObj.PerlinNoiseWidthUInt64 * 
        FileInfoObj.PerlinNoiseHeightUInt64
        );
    U hUint64 = FileInfoObj.PerlinNoiseHeightUInt64;
    U wUint64 = FileInfoObj.PerlinNoiseWidthUInt64;
    for (U i = 0; i < hUint64; i++)
    {
        for (U j = 0; j < wUint64; j++)
        {
            // Calculate the indices of the four gradients that enclose the point
            U i0 = static_cast<U>(i / 2);
            U j0 = static_cast<U>(j / 2);
            U i1 = i0 + 1;
            U j1 = j0 + 1;

            // Calculate the weight for each gradient
            T wi = i / 2.0f - i0;
            T wj = j / 2.0f - j0;

            // Interpolate the values at the four (4) gradients
            T n0 = DotProductFloat64(
                Gradients2DFloat64[i0 + wUint64 + j0], { wi, wj }
                );
            T n1 = DotProductFloat64(
                Gradients2DFloat64[i1 + wUint64 + j0], { wi, wj }
                );
            T n2 = DotProductFloat64(
                Gradients2DFloat64[i0 + wUint64 + j1], { wi, wj }
                );
            T n3 = DotProductFloat64(
                Gradients2DFloat64[i1 + wUint64 + j1], { wi, wj }
                );

            // Interpolate between the four values to get the final noise value for the point
            T NoiseValueFloat64 = BilinearInterpolationT<T>(n0, n1, n2, n3, wi, wj);

            // Store the NoiseValueFloat64 in the noise map
            NoiseMap1DFloat64[i + wUint64 * j] = NoiseValueFloat64;
        }
        FileInfoObj.NoiseBufferFloat64 = NoiseMap1DFloat64;
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
template<typename T, typename U>
void WhitePerlinNoise<T,U>::GenerateWhitePerlinNoise(FILEINFO_Obj<T,U>& FileInfoObj)
{
    ApplyWhitePerlinNoiseFilter(FileInfoObj);
}