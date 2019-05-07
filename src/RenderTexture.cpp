//
// RenderTexture.cpp
//
// The implementation of RenderTexture.
//
// Created by Jietong Chen on 2/2/2019.
//

#include "pch.h"

using RayTracer::RenderTexture;
using RayTracer::BYTE;
using RayTracer::floatBYTE;

std::mutex write_mutex;

/**
 * Create a RenderTexture with given size.
 *
 * @param w the width
 * @param h the height
 */
RenderTexture::RenderTexture( int w, int h ) :
        Texture{ w, h },
        colorBuffer{ w * h * 16, 0 },
        depthBuffer{ w * h * 4, 0 } {
}

/**
 * Read the color buffer.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 *
 * @return the color
 */
float4 RenderTexture::ReadColorBuffer( int x, int y ) const {
    float4 color = float4( 0.0f );

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();
        floatBYTE c{};

        // red channel
        c.byte[ 0 ] = colorBufferData[ 16 * ( y * width + x ) + 0 ];
        c.byte[ 1 ] = colorBufferData[ 16 * ( y * width + x ) + 1 ];
        c.byte[ 2 ] = colorBufferData[ 16 * ( y * width + x ) + 2 ];
        c.byte[ 3 ] = colorBufferData[ 16 * ( y * width + x ) + 3 ];
        float red = c.f;

        // green channel
        c.byte[ 0 ] = colorBufferData[ 16 * ( y * width + x ) + 4 ];
        c.byte[ 1 ] = colorBufferData[ 16 * ( y * width + x ) + 5 ];
        c.byte[ 2 ] = colorBufferData[ 16 * ( y * width + x ) + 6 ];
        c.byte[ 3 ] = colorBufferData[ 16 * ( y * width + x ) + 7 ];
        float green = c.f;

        // blue channel
        c.byte[ 0 ] = colorBufferData[ 16 * ( y * width + x ) + 8 ];
        c.byte[ 1 ] = colorBufferData[ 16 * ( y * width + x ) + 9 ];
        c.byte[ 2 ] = colorBufferData[ 16 * ( y * width + x ) + 10 ];
        c.byte[ 3 ] = colorBufferData[ 16 * ( y * width + x ) + 11 ];
        float blue = c.f;

        // alpha channel
        c.byte[ 0 ] = colorBufferData[ 16 * ( y * width + x ) + 12 ];
        c.byte[ 1 ] = colorBufferData[ 16 * ( y * width + x ) + 13 ];
        c.byte[ 2 ] = colorBufferData[ 16 * ( y * width + x ) + 14 ];
        c.byte[ 3 ] = colorBufferData[ 16 * ( y * width + x ) + 15 ];
        float alpha = c.f;

        color = float4( red, green, blue, alpha );
    }

    return color;
}

/**
 * Read the depth buffer.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 *
 * @return the depth
 */
float RenderTexture::ReadDepthBuffer( int x, int y ) const {
    float depth = 0.0f;

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* depthBufferData = depthBuffer.GetNativeRenderBufferPtr();

        floatBYTE d{};
        d.byte[ 0 ] = depthBufferData[ 4 * ( y * width + x ) + 0 ];
        d.byte[ 1 ] = depthBufferData[ 4 * ( y * width + x ) + 1 ];
        d.byte[ 2 ] = depthBufferData[ 4 * ( y * width + x ) + 2 ];

        depth = d.f;
    }

    return depth;
}

/**
 * Read the stencil buffer.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 *
 * @return the stencil value
 */
int RenderTexture::ReadStencilBuffer( int x, int y ) const {
    int stencil = 0;

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* depthBufferData = depthBuffer.GetNativeRenderBufferPtr();

        stencil = depthBufferData[ 4 * ( y * width + x ) + 3 ];
    }

    return stencil;
}

/**
 * Write the color buffer at given position.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param color the color
 */
void RenderTexture::WriteColorBuffer( int x, int y, float4 color ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();
        floatBYTE c{};

        //float3 xc = ACESFilm( color.rgb );
        //color = float4( xc.r, xc.g, xc.b, 1.0f );

        // red channel
        c.f = color.r;
        colorBufferData[ 16 * ( y * width + x ) + 0 ] = c.byte[ 0 ];
        colorBufferData[ 16 * ( y * width + x ) + 1 ] = c.byte[ 1 ];
        colorBufferData[ 16 * ( y * width + x ) + 2 ] = c.byte[ 2 ];
        colorBufferData[ 16 * ( y * width + x ) + 3 ] = c.byte[ 3 ];

        // green channel
        c.f = color.g;
        colorBufferData[ 16 * ( y * width + x ) + 4 ] = c.byte[ 0 ];
        colorBufferData[ 16 * ( y * width + x ) + 5 ] = c.byte[ 1 ];
        colorBufferData[ 16 * ( y * width + x ) + 6 ] = c.byte[ 2 ];
        colorBufferData[ 16 * ( y * width + x ) + 7 ] = c.byte[ 3 ];

        // blue channel
        c.f = color.b;
        colorBufferData[ 16 * ( y * width + x ) + 8 ] = c.byte[ 0 ];
        colorBufferData[ 16 * ( y * width + x ) + 9 ] = c.byte[ 1 ];
        colorBufferData[ 16 * ( y * width + x ) + 10 ] = c.byte[ 2 ];
        colorBufferData[ 16 * ( y * width + x ) + 11 ] = c.byte[ 3 ];

        // alpha channel
        c.f = color.a;
        colorBufferData[ 16 * ( y * width + x ) + 12 ] = c.byte[ 0 ];
        colorBufferData[ 16 * ( y * width + x ) + 13 ] = c.byte[ 1 ];
        colorBufferData[ 16 * ( y * width + x ) + 14 ] = c.byte[ 2 ];
        colorBufferData[ 16 * ( y * width + x ) + 15 ] = c.byte[ 3 ];
    }
}

/**
 * Write the depth/stencil buffer at given position.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param depth the depth
 * @param stencil the stencil
 */
void RenderTexture::WriteDepthBuffer( int x, int y, float depth,
                                      int stencil ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
//#if MULTI_THREAD
//        std::lock_guard< std::mutex > lock_guard{ write_mutex };
//#endif
        BYTE* depthBufferData = depthBuffer.GetNativeRenderBufferPtr();

        floatBYTE d{ depth };

        depthBufferData[ 4 * ( y * width + x ) + 0 ] = d.byte[ 0 ];
        depthBufferData[ 4 * ( y * width + x ) + 1 ] = d.byte[ 1 ];
        depthBufferData[ 4 * ( y * width + x ) + 2 ] = d.byte[ 2 ];
        depthBufferData[ 4 * ( y * width + x ) + 3 ] = d.byte[ 3 ];
        //depthBufferData[ 4 * ( y * width + x ) + 3 ] = ( BYTE ) stencil;
    }
}

/**
 * Get the pointer to the texture native data.
 *
 * @return the pointer to the color buffer native data
 */
BYTE* RenderTexture::GetNativeTexturePtr() const {
    return colorBuffer.GetNativeRenderBufferPtr();
}

float3 RenderTexture::ACESFilm( float3 x ) {
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return saturate( ( x * ( a * x + b ) ) / ( x * ( c * x + d ) + e ) );
}

float3 RenderTexture::GammaCorrection( float3 color, float gamma ) {
    float power = 1.0f / gamma;

    float r = pow( ( float ) color.r, power );
    float g = pow( ( float ) color.g, power );
    float b = pow( ( float ) color.b, power );

    return float3( r, g, b );
}
