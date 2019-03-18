//
// Texture.h
//
// Base class for texture handling.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "pch.h"

namespace RayTracer {
    /**
     * Base class for texture handling.
     */
    class Texture : public Object {
    public:
        /**
         * Filtering mode for textures.
         */
        enum FilterMode{
            Point,
            Bilinear
        };

        /**
         * Wrap mode for textures.
         */
        enum TextureWrapMode{
            Repeat,
            Clamp
        };

        /**
         * Create a Texture with given size.
         *
         * @param w the width
         * @param h the height
         */
        Texture( int w, int h );

        /**
         * Get the pointer to the texture native data.
         *
         * @return the pointer to the texture native data
         */
        virtual BYTE* GetNativeTexturePtr() const = 0;

        /**
         * Sample the texture at given location.
         *
         * @param texture the texture to sample
         * @param location the sample location
         *
         * @return the color of the texture
         */
        static float4 Sample( Texture* texture, float2 location );

    public:
        /** width of the texture in pixels */
        const int width;

        /** height of the texture in pixels */
        const int height;

        /** filtering mode of the texture */
        FilterMode filterMode;

        /** texture coordinate wrapping mode */
        TextureWrapMode wrapMode;

    }; // Texture
} // RayTracer

#endif // TEXTURE_H
