//
// PerlinNoise.h
//
// The Perlin noise texture in 2D. This is the improved version of Perlin
// noise written by Perlin himself (https://cs.nyu.edu/~perlin/noise/).
// COPYRIGHT 2002 KEN PERLIN.
//
// Created by Jietong Chen on 2019/3/18.
//

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "pch.h"

namespace RayTracer {
    /**
     * The Perlin noise texture in 2D. This is the improved version of Perlin
     * noise written by Perlin himself (https://cs.nyu.edu/~perlin/noise/).
     * COPYRIGHT 2002 KEN PERLIN.
     */
    class PerlinNoise : public ProceduralTexture {
    public:
        /**
         * Create a Perlin noise texture.
         */
        PerlinNoise();

        /**
         * Get the color of Perlin noise at given location.
         *
         * @param location the location
         *
         * @return the color
         */
        float4 GetColor( float2 location ) const;

        /**
         * Get the pointer to the texture native data.
         *
         * @return null pointer
         */
        BYTE* GetNativeTexturePtr() const override;

    private:
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
        double noise( double x, double y, double z ) const;

        /**
         * Interpolant function 6t^5 -15t^4 + 10t^3. Further detail in the
         * paper https://mrl.nyu.edu/~perlin/paper445.pdf.
         *
         * @param t the value
         *
         * @return 6t^5 -15t^4 + 10t^3
         */
        double fade( double t ) const;

        /**
         * Linear interpolation.
         *
         * @param t the weight
         * @param a the first value
         * @param b the second value
         *
         * @return t*b + (1-t)*a
         */
        double lerp( double t, double a, double b ) const;

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
        double grad( int hash, double x, double y, double z ) const;

    private:
        /** the permutations */
        std::vector< int > p;

    }; // PerlinNoise
} // RayTracer

#endif // PERLINNOISE_H
