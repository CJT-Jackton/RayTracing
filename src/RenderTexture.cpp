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

//    float4 color = float4( colori.r / 255.0f, colori.g / 255.0f,
//                           colori.b / 255.0f, colori.a / 255.0f );
    float4 color = float4( colori ) / float4( 255.0f );

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

//        float4 c = float4( GammaCorrection( ACESFilm( color.rgb ), 2.2f ),
//                           1.0f );
//        float4 c = float4( ACESFilm( GammaCorrection( color.rgb, 2.2f ) ),
//                           1.0f );
//        float4 c = float4( GammaCorrection( color.rgb, 2.2f ), 1.0f );
        float4 c = float4( ACESFilm( color.rgb ), 1.0f );
        c *= 256.0f;

        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();

        int r = ( c.r == 256.0f ) ? 255 : int( c.r );
        int g = ( c.g == 256.0f ) ? 255 : int( c.g );
        int b = ( c.b == 256.0f ) ? 255 : int( c.b );
        int a = ( c.a == 256.0f ) ? 255 : int( c.a );

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
