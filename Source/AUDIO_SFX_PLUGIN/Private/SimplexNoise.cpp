#include "SimplexNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

SimplexNoise::SimplexNoise()
{
}

void SimplexNoise::ApplySimplexNoiseFilter(FILEINFO_Obj& FileInfoObj)
{
    // Create a random permutation table
    // Create a gradient table
    // Create a 4D lookup table
    // Implement the noise generation function
    // Skew the input space
    // Unskew the cell origin, back to the (x,y) space
    // Determine the relative coords of th epoint within the simplex
    // Determine the simplex containing the point
    // Determine the gradient indices
    // Calculate the contribution of the corners
    // Return the noise value
}

/**
* Simplex Noise is a variant of Perlin Noise that was developed by 
* Ken Perlin in 2001. It is generally considered to be faster 
* and more efficient to generate than Perlin Noise. It is generated
* using a Simplex, which is a multi-dimensional generalization
* of a triangle.
* @param [ FILEINFO_Obj ] The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
void SimplexNoise::GenerateSimplexNoise(FILEINFO_Obj& FileInfoObj)
{
    ApplySimplexNoiseFilter(FileInfoObj);
}
