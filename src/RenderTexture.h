//
// RenderTexture.h
//
// Texture that can be rendered to. RenderTexture is the target texture
// property of a Camera, this will camera render into a texture.
//
// Currently only support RGBA32 format.
//
// Created by Jietong Chen on 2/2/2019.
//

#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include "pch.h"

namespace RayTracer {
    /**
     * Texture that can be rendered to.
     */
    class RenderTexture : public Texture {
    public:
        /**
         * Create a RenderTexture with given size.
         *
         * @param w the width
         * @param h the height
         */
        RenderTexture( int w, int h );

        /**
         * Read the color buffer.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         *
         * @return the color
         */
        float4 ReadColorBuffer( int x, int y ) const;

        /**
         * Read the depth buffer.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         *
         * @return the depth
         */
        float ReadDepthBuffer( int x, int y ) const;

        /**
         * Read the stencil buffer.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         *
         * @return the stencil value
         */
        int ReadStencilBuffer( int x, int y ) const;

        /**
         * Write the color buffer at given position.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         * @param color the color
         */
        void WriteColorBuffer( int x, int y, float4 color );

        /**
         * Write the depth/stencil buffer at given position.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         * @param depth the depth
         * @param stencil the stencil
         */
        void WriteDepthBuffer( int x, int y, float depth, int stencil );

        /**
         * Get the pointer to the texture native data.
         *
         * @return the pointer to the color buffer native data
         */
        BYTE* GetNativeTexturePtr() const override;

    protected:
        float3 ACESFilm( float3 x );

    public:
        /** color buffer */
        RenderBuffer colorBuffer;

        /** depth/stencil buffer */
        RenderBuffer depthBuffer;

    }; // RenderTexture
} // RayTracer

#endif // RENDERTEXTURE_H
