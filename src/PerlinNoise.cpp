//
// PerlinNoise.cpp
//
// The implementation of PerlinNoise.
//
// Created by Jietong Chen on 2019/3/18.
//

#include "pch.h"

using RayTracer::PerlinNoise;
using RayTracer::BYTE;

/**
 * Create a Perlin noise texture.
 */
PerlinNoise::PerlinNoise() {
    // initialize default color
    mainColor = float4( 1.0f );
    secondaryColor = float4( 0.0f, 0.0f, 0.0f, 1.0f );

    // initialize the permutation vector with the reference values
    // (https://cs.nyu.edu/~perlin/noise/)
    p = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
          140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148,
          247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
          57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68,
          175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111,
          229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
          102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208,
          89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109,
          198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147,
          118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
          189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70,
          221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108,
          110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251,
          34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235,
          249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204,
          176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114,
          67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 };

    // duplicate the permutation vector
    p.insert( p.end(), p.begin(), p.end() );
}

/**
 * Get the color of Perlin noise at given location.
 *
 * @param location the location
 *
 * @return the color
 */
float4 PerlinNoise::GetColor( float2 location ) const {
    double perlin = noise( location.x, location.y, 0.586 );
    // mapping the noise value to [0, 1]
    perlin = perlin * 0.5 + 0.5;

    return perlin * mainColor + ( 1 - perlin ) * secondaryColor;
}

/**
 * Sample the Perlin noise. We only need 2D texture so the z-coordinate
 * value can be arbitrarily value.
 *
 * @param x the x-coordinate
 * @param y the y-coordinate
 * @param z the z-coordinate (ignored)
 *
 * @return the noise value (-1.0, 1.0)
 */
double PerlinNoise::noise( double x, double y, double z ) const {
    int X = ( int ) floor( x ) & 255;               // FIND UNIT CUBE THAT
    int Y = ( int ) floor( y ) & 255;               // CONTAINS POINT.
    int Z = ( int ) floor( z ) & 255;

    x -= floor( x );                                // FIND RELATIVE X,Y,Z
    y -= floor( y );                                // OF POINT IN CUBE.
    z -= floor( z );

    double u = fade( x );                           // COMPUTE FADE CURVES
    double v = fade( y );                           // FOR EACH OF X,Y,Z.
    double w = fade( z );

    int A = p[ X ] + Y;
    int AA = p[ A ] + Z;
    int AB = p[ A + 1 ] + Z;  // HASH COORDINATES OF
    int B = p[ X + 1 ] + Y;
    int BA = p[ B ] + Z;
    int BB = p[ B + 1 ] + Z;  // THE 8 CUBE CORNERS,

    return lerp(
            w,
            lerp( v,
                  lerp( u,
                        grad( p[ AA ], x, y, z ),               // AND ADD
                        grad( p[ BA ], x - 1, y, z ) ),         // BLENDED
                  lerp( u,
                        grad( p[ AB ], x, y - 1, z ),           // RESULTS
                        grad( p[ BB ], x - 1, y - 1, z ) ) ),   // FROM  8
            lerp( v,
                  lerp( u,
                        grad( p[ AA + 1 ], x, y, z - 1 ),       // CORNERS
                        grad( p[ BA + 1 ], x - 1, y, z - 1 ) ), // OF CUBE
                  lerp( u,
                        grad( p[ AB + 1 ], x, y - 1, z - 1 ),
                        grad( p[ BB + 1 ], x - 1, y - 1, z - 1 ) ) ) );
}

/**
 * Interpolant function 6t^5 -15t^4 + 10t^3. Further detail in the
 * paper https://mrl.nyu.edu/~perlin/paper445.pdf.
 *
 * @param t the value
 *
 * @return 6t^5 -15t^4 + 10t^3
 */
double PerlinNoise::fade( double t ) const {
    return t * t * t * ( t * ( t * 6 - 15 ) + 10 );
}

/**
 * Linear interpolation.
 *
 * @param t the weight
 * @param a the first value
 * @param b the second value
 *
 * @return t*b + (1-t)*a
 */
double PerlinNoise::lerp( double t, double a, double b ) const {
    return a + t * ( b - a );
}

/**
 * Calculate gradient from 12 vectors defined by the directions
 * from the center of a cube to its edges. Further detail in the
 * paper https://mrl.nyu.edu/~perlin/paper445.pdf.
 *
 * @param hash the hash code
 * @param x the x-coordinate
 * @param y the y-coordinate
 * @param z the z-coordinate
 *
 * @return the gradient
 */
double PerlinNoise::grad( int hash, double x, double y, double z ) const {
    int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
    double u = h < 8 ? x : y;               // INTO 12 GRADIENT DIRECTIONS.
    double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ( ( h & 1 ) == 0 ? u : -u ) + ( ( h & 2 ) == 0 ? v : -v );
}

/**
 * Get the pointer to the texture native data.
 *
 * @return null pointer
 */
BYTE* PerlinNoise::GetNativeTexturePtr() const {
    return nullptr;
}
