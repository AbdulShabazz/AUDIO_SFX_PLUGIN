#include "SimplexNoise.h"
#include "Tones.Default.Settings.h"

using namespace ToneLibrary;

template<typename T, typename U>
SimplexNoise<T,U>::SimplexNoise()
{
}

template<typename T, typename U>
void SimplexNoise<T, U>::GenerateRandomGradientTable(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
    FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef =
        Vector2DT<T>(FileInfoObjRef.DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64);
    std::iota(
        FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef.begin(),
        FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef.end(),
        0
    );
    std::shuffle(
        FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef.begin(),
        FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef.end(),
        std::mt19937_64{ std::random_device{}() }
    );
}

template<typename T, typename U>
void SimplexNoise<T, U>::GenerateRandomPermutationTable(FILEINFO_Obj<T, U>& FileInfoObjRef)
{
    FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef =
        VectorT<U>(FileInfoObjRef.DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64);
    std::iota(
        FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef.begin(),
        FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef.end(),
        0
        );
    std::shuffle(
        FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef.begin(),
        FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef.end(),
        std::mt19937_64{ std::random_device{}() }
        );
}

template<typename T, typename U>
void SimplexNoise<T,U>::ApplySimplexNoiseFilter(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    // Create a random permutation table
    GenerateRandomPermutationTable(FileInfoObjRef);

    // Create a gradient table
	GenerateRandomGradientTable(FileInfoObjRef);    
    
    // Create a 2d table
	Vector2DT<T> Vector2DTemp(FileInfoObjRef.DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64);

    // Create a 4D lookup table
	Vector4DT<T> Vector4DTemp(FileInfoObjRef.DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64);
    
    // Implement the noise generation function
	for (U i = 0; i < FileInfoObjRef.DefaultPermutatioTableSizeForSimplexNoiseFilterUInt64; i++)
	{
		Vector2DTemp[i] = Vector2DT<T>(
			FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[i].x,
			FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[i].y
			);
		Vector4DTemp[i] = Vector4DT<T>(
			FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[i].x,
			FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[i].y,
			FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[i].x,
			FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[i].y
			);
	}
    
    T x = 0, y = 0;
    
    // Skew the input space
	T s = (x + y) 0.5 * (sqrt(3.0) - 1.0);
    U i = static_cast<U>(std::floor(x + s));
    U j = static_cast<U>(std::floor(y + s));
    
    // Unskew the cell origin, back to the (x,y) space
	T t = (i + j) * (3.0 - sqrt(3.0)) / 6.0;
    T X0 = i - t;
    T Y0 = j - t;
    
    // Determine the relative coords of the point within the simplex
    T x0 = x - X0;
    T y0 = y - Y0;
    
    // Determine the simplex containing the point
    U i1 = 0, j1 = 0;
    if (x0 > y0)
    {
        i1 = 1;
        j1 = 0;
    }
    else
    {
        i1 = 0;
        j1 = 1;
    }
    
    // Offsets for the other two vertices of the simplex
    T x1 = x0 - i1 + (1.0f / 6.0f);
    T y1 = y0 - j1 + (1.0f / 6.0f);
    T x2 = x0 - 0.5f + (1.0f / 3.0f);
    T y2 = y0 - 0.5f + (1.0f / 3.0f);
    
    // Determine the gradient indices
    U ii = i & 255;
    U jj = j & 255;
    U gi0 = FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef[ii +      FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef[jj     ]] % 8;
    U gi1 = FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef[ii + i1 + FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef[jj + j1]] % 8; 
    U gi2 = FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef[ii + 1  + FileInfoObjRef.VectorPermutatioTableForSimplexNoiseUInt64TRef[jj + 1 ]] % 8;
    
    T n0, n1, n2;   
    
    // Calculate the contribution of the corner, gi0
    T t0 = 0.5f - x0 * x0 - y0 * y0;
    if (t0 < 0)
    {
        n0 = 0.0
    }
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * dot(FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[gi0], x0, y0);
    }

    // Calculate the contribution of the corner, gi1
    T t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 < 0)
    {
        n1 = 0.0
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * dot(FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[gi1], x1, y1);
    }

    // Calculate the contribution of the corner, gi2
    T t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t1 < 0)
    {
        n2 = 0.0
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * dot(FileInfoObjRef.VectorGradientTable2DForSimplexNoiseFilterFloat64TRef[gi2], x2, y2);
    }
    
    // Add contributions from each corner
    T G2 = (n0 + n1 + n2);
    
    // Return the noise value
	T t = (i + j) * G2;
}

/**
* Simplex Noise is a variant of Perlin Noise that was developed by 
* Ken Perlin in 2001. It is generally considered faster 
* and more efficient to generate than Perlin Noise. It is generated
* using a Simplex, which is a multi-dimensional generalization
* of a triangle.
* @param [ FILEINFO_Obj ] The file parameters struct
* used to retain details for the file.
* @return [ void ] --- No return value.
*/
template<typename T, typename U>
void SimplexNoise<T,U>::GenerateSimplexNoise(FILEINFO_Obj<T,U>& FileInfoObjRef)
{
    ApplySimplexNoiseFilter(FileInfoObj);
}
