#include "FractalNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

FractalNoise::FractalNoise()
{
}

void FractalNoise::ApplyDiamondNoiseArrayShape(FILEINFO_Obj& FileInfoObj)
{
}

void FractalNoise::ApplyTriangularNoiseArrayShape(FILEINFO_Obj& FileInfoObj)
{
}

void FractalNoise::ApplyCircularNoiseArrayShape(FILEINFO_Obj& FileInfoObj)
{
}

void FractalNoise::ApplyRectangularNoiseArrayShape(FILEINFO_Obj& FileInfoObj)
{
}

void FractalNoise::ApplySquareNoiseArrayShape(FILEINFO_Obj& FileInfoObj)
{
    // Find the byte quota to determine the allotment of elements
    const short NumBytesPerElementShortInt = 4;
    const UE_UINT64 NumberOfTotalElementsUInt64 = (FileInfoObj.LengthUInt64 / NumBytesPerElementShortInt) + 1; // int coerce
    UE_UINT64 NumberOfSquareElementsUInt64 = (UE_UINT64)ceil(sqrt(NumberOfTotalElementsUInt64));

    // Init SquareNoiseShapeElementsFloat64[NumberOfSquareElementsUInt64][NumberOfSquareElementsUInt64]
    std::vector<std::vector<UE_FLOAT64>> SquareNoiseShapeElementsFloat64(NumberOfSquareElementsUInt64, std::vector<UE_FLOAT64>(NumberOfSquareElementsUInt64));

    // Seed the random number generator
    std::random_device rd;

    // Set the range of the noise signal
    std::mt19937_64 gen(rd());

    // Set the range of the noise signal
    UniformRealDistributionFloat64 dis(0.0f, 1.0f);

    // Initialize the corner values
    UE_UINT64 LastValUInt64 = NumberOfSquareElementsUInt64 - 1;
    SquareNoiseShapeElementsFloat64[0            ][0            ] = dis(gen) * FileInfoObj.FractalNoiseRangeParameterFloat64;
    SquareNoiseShapeElementsFloat64[0            ][LastValUInt64] = dis(gen) * FileInfoObj.FractalNoiseRangeParameterFloat64;
    SquareNoiseShapeElementsFloat64[LastValUInt64][0            ] = dis(gen) * FileInfoObj.FractalNoiseRangeParameterFloat64;
    SquareNoiseShapeElementsFloat64[LastValUInt64][LastValUInt64] = dis(gen) * FileInfoObj.FractalNoiseRangeParameterFloat64;

    // Initialize the modpoints
    for (UE_UINT64 SideLengthUInt64 = LastValUInt64; SideLengthUInt64 >= 2; SideLengthUInt64 /= 2)
    {
        UE_UINT64 HalfLengthUInt64 = LastValUInt64 / 2;

        // Generate the new values
        for (UE_UINT64 xUInt64 = 0; xUInt64 < LastValUInt64; xUInt64 += HalfLengthUInt64)
        {
            for (UE_UINT64 yUint64 = 0; yUint64 < LastValUInt64; yUint64 += HalfLengthUInt64)
            {
                // Get the corner values
                UE_FLOAT64 aUInt64 = SquareNoiseShapeElementsFloat64[xUInt64                   ][yUint64                   ];
                UE_FLOAT64 bUInt64 = SquareNoiseShapeElementsFloat64[xUInt64 + HalfLengthUInt64][yUint64                   ];
                UE_FLOAT64 cUInt64 = SquareNoiseShapeElementsFloat64[xUInt64                   ][yUint64 + HalfLengthUInt64];
                UE_FLOAT64 dUInt64 = SquareNoiseShapeElementsFloat64[xUInt64 + HalfLengthUInt64][yUint64 + HalfLengthUInt64];

                // Calculate the midpoint values
                SquareNoiseShapeElementsFloat64[xUInt64 + HalfLengthUInt64][yUint64 + HalfLengthUInt64] =
                    (aUInt64 + bUInt64 + cUInt64 + dUInt64) / FileInfoObj.FractalNoiseSquaresSmoothnessFactorFloat64 +
                    dis(gen) * FileInfoObj.FractalNoiseRangeParameterFloat64 -
                    FileInfoObj.FractalNoiseRangeParameterFloat64 / 2;
            }
        }
    }

    // Write-back
    UE_UINT64 zUInt64 = 0;
    for (const std::vector<UE_FLOAT64>& xUInt64 : SquareNoiseShapeElementsFloat64)
    {
        for (const UE_FLOAT64& yUInt64 : xUInt64)
        {
            FileInfoObj.NoiseBufferFloat64[zUInt64++] = yUInt64;
        }
    }
}

void FractalNoise::ApplyFractalNoiseFilter(FILEINFO_Obj& FileInfoObj)
{
    // Choose the desired noise array 
    switch (FileInfoObj.FractalNoiseArrayShapeSettingEnum)
    {
        // Initialize the noise array
        // iterate over the noise array, dividing it into smaller and smaller squares with each iteration
        // Add a random offset to the midpoint value to create morex variation in the noise pattern
        // Repeat, until the desired level of detail is reached 
        case FileInfoObj.FractalNoiseArrayShapeENUM::Square:
            ApplySquareNoiseArrayShape(FileInfoObj);
            break;
        case FileInfoObj.FractalNoiseArrayShapeENUM::Rectangular:
            ApplyRectangularNoiseArrayShape(FileInfoObj);
            break;
        case FileInfoObj.FractalNoiseArrayShapeENUM::Circular:
            ApplyCircularNoiseArrayShape(FileInfoObj);
            break;
        case FileInfoObj.FractalNoiseArrayShapeENUM::Diamond:
            ApplyDiamondNoiseArrayShape(FileInfoObj);
            break;
        default:
            std::cout << 
            "Error - FractalNoise::ApplyFractalNoiseFilter: Invalid FractalNoiseArrayShapeENUM" 
            << std::endl;
            ApplySquareNoiseArrayShape(FileInfoObj);
            break;
    }
}

/**
* Fractal Noise is a type of noise that is generated by adding 
* together multiple octaves of noise, each with a different 
* frequency and amplitude. It is used to create realistic
* patterns and textures, having a more natural organic appearance
* than regular noise.
* @param [ FileInfoObj ] --- The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
void FractalNoise::GenerateFractalNoise(FILEINFO_Obj& FileInfoObj)
{
    ApplyFractalNoiseFilter(FileInfoObj);
}
