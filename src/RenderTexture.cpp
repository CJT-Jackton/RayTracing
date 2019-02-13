//
// RenderTexture.cpp
//
// The implementation of RenderTexture.
//
// Created by Jietong Chen on 2/2/2019.
//

#include "pch.h"

using RayTracing::RenderTexture;
using RayTracing::BYTE;
using RayTracing::floatBYTE;

std::mutex write_mutex;

/**
 * Create a RenderTexture with given size.
 *
 * @param w the width
 * @param h the height
 */
RenderTexture::RenderTexture( int w, int h ) :
        Texture{ w, h },
        colorBuffer{ w * h * 4, 0 },
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
    int4 colori;

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();

        colori = int4( colorBufferData[ 4 * ( y * width + x ) + 0 ],
                       colorBufferData[ 4 * ( y * width + x ) + 1 ],
                       colorBufferData[ 4 * ( y * width + x ) + 2 ],
                       colorBufferData[ 4 * ( y * width + x ) + 3 ] );
    }

    float4 color = float4( colori.r / 255.0f, colori.g / 255.0f,
                           colori.b / 255.0f, colori.a / 255.0f );

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
//#if MULTI_THREAD
//        std::lock_guard< std::mutex > lock_guard{ write_mutex };
//#endif
        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();

        int r = ( color.r * 256 == 256 ) ? 255 : color.r * 256;
        int g = ( color.g * 256 == 256 ) ? 255 : color.g * 256;
        int b = ( color.b * 256 == 256 ) ? 255 : color.b * 256;
        int a = ( color.a * 256 == 256 ) ? 255 : color.a * 256;

        colorBufferData[ 4 * ( y * width + x ) + 0 ] = ( BYTE ) r;
        colorBufferData[ 4 * ( y * width + x ) + 1 ] = ( BYTE ) g;
        colorBufferData[ 4 * ( y * width + x ) + 2 ] = ( BYTE ) b;
        colorBufferData[ 4 * ( y * width + x ) + 3 ] = ( BYTE ) a;
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
