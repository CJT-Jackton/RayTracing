//
// Checkerboard2D.cpp
//
// The implementation of Checkerboard2D.
//
// Created by Jietong Chen on 2019/3/18.
//

#include "pch.h"

using RayTracer::Checkerboard2D;
using RayTracer::BYTE;

/**
 * Create a Checkboard2D texture.
 */
Checkerboard2D::Checkerboard2D() {
    // initialize with default color
    mainColor = float4( 0.8f, 0.8f, 0.8f, 1.0f );
    secondaryColor = float4( 0.4f, 0.4f, 0.4f, 1.0f );
}

/**
 * Get the color at given location.
 *
 * @param location the location
 *
 * @return the color of the texture
 */
float4 Checkerboard2D::GetColor( float2 location ) const {
    if( location.x < 0.5f && location.y < 0.5f ||
        location.x >= 0.5f && location.y >= 0.5f ) {
        return mainColor;
    } else {
        return secondaryColor;
    }
}

/**
 * Get the pointer to the texture native data.
 *
 * @return null pointer
 */
BYTE* Checkerboard2D::GetNativeTexturePtr() const {
    return nullptr;
}
