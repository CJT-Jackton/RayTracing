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

namespace RayTracing {
    /**
     * Base class for texture handling.
     */
    class Texture : public Object {
    public:
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

    public:
        /** width of the texture in pixels */
        const int width;

        /** height of the texture in pixels */
        const int height;

    }; // Texture
} // RayTracing

#endif // TEXTURE_H
