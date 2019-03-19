//
// ProceduralTexture.h
//
// Base class of procedural texture.
//
// Created by Jietong Chen on 2019/3/18.
//

#ifndef PROCEDURALTEXTURE_H
#define PROCEDURALTEXTURE_H

#include "Texture.h"

namespace RayTracer {
    /**
     * Base class of procedural texture.
     */
    class ProceduralTexture : public Texture {
    public:
        /**
         * Create a procedural texture.
         */
        ProceduralTexture();

        /**
         * Get the pointer to the texture native data.
         *
         * @return null pointer
         */
        BYTE* GetNativeTexturePtr() const override;

    public:
        /** the main color of the procedural texture */
        float4 mainColor;

        /** the secondary color of the procedural texture */
        float4 secondaryColor;

    }; // ProceduralTexture
} // RayTracer

#endif // PROCEDURALTEXTURE_H
