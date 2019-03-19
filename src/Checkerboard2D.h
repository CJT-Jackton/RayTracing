//
// Checkerboard2D.h
//
// The checkerboard texture.
//
// Created by Jietong Chen on 2019/3/18.
//

#ifndef CHECKERBOARD2D_H
#define CHECKERBOARD2D_H

#include "pch.h"

namespace RayTracer {
    /**
     * The checkerboard texture.
     */
    class Checkerboard2D : public ProceduralTexture {
    public:
        /**
         * Create a Checkboard2D texture.
         */
        Checkerboard2D();

        /**
         * Get the color at given location.
         *
         * @param location the location
         *
         * @return the color of the texture
         */
        float4 GetColor( float2 location ) const;

        /**
         * Get the pointer to the texture native data.
         *
         * @return null pointer
         */
        BYTE* GetNativeTexturePtr() const override;

    }; // Checkerboard2D
} // RayTracer

#endif // CHECKERBOARD2D_H
