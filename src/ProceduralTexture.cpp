//
// ProceduralTexture.cpp
//
// The implementation of ProceduralTexture.
//
// Created by Jietong Chen on 2019/3/18.
//

#include "pch.h"

using RayTracer::ProceduralTexture;
using RayTracer::Texture;
using RayTracer::BYTE;

/**
 * Create a procedural texture. The texture size is 1x1 (trivial).
 */
ProceduralTexture::ProceduralTexture() :
        Texture{ 1, 1 } {
}

/**
 * Get the pointer to the texture native data.
 *
 * @return null pointer
 */
BYTE* ProceduralTexture::GetNativeTexturePtr() const {
    return const_cast<BYTE*>(nullptr);
}
