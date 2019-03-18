//
// Texture.cpp
//
// The implementation of Texture.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Texture;
using RayTracer::Texture2D;

/**
 * Create a Texture with given size.
 *
 * @param w the width
 * @param h the height
 */
Texture::Texture( int w, int h ) :
        width{ w },
        height{ h },
        filterMode{ FilterMode::Point },
        wrapMode{ TextureWrapMode::Repeat } {
}

/**
 * Sample the texture at given location.
 *
 * @param texture the texture to sample
 * @param location the sample location
 *
 * @return the color of the texture
 */
float4 Texture::Sample( Texture* texture, float2 location ) {
    float4 color = float4( 0.0f );

    if( Texture2D* tex2d = dynamic_cast<Texture2D*>(texture) ) {
        float u = location.x;
        float v = location.y;

        if( u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f ) {
            if( tex2d->wrapMode == TextureWrapMode::Repeat ) {
                // location = fmod( location, 1.0f );
                u = fmod( u, 1.0f );
                v = fmod( v, 1.0f );
            } else if( tex2d->wrapMode == TextureWrapMode::Clamp ) {
                // location = saturate( location );
                u = u < 0.0f ? 0.0f : u;
                u = u > 1.0f ? 1.0f : u;

                v = v < 0.0f ? 0.0f : v;
                v = v > 1.0f ? 1.0f : v;
            }
        }

        // vertical flip
        v = 1.0f - v;

        if( tex2d->filterMode == FilterMode::Point ) {
            float x = u * tex2d->width;
            float y = v * tex2d->height;

            x -= 0.5f;
            y -= 0.5f;

            color = tex2d->GetPixel( ( int ) round( x ), ( int ) round( y ) );

        } else if( tex2d->filterMode == FilterMode::Bilinear ) {
            float x = u * tex2d->width;
            float y = v * tex2d->height;

            x -= 0.5f;
            y -= 0.5f;

            int2 q11 = int2( ( int ) floor( x ), ( int ) floor( y ) );
            int2 q12 = q11 + int2( 0, 1 );
            int2 q21 = q11 + int2( 1, 0 );
            int2 q22 = q11 + int2( 1, 1 );

            float a11 = ( q22.x - x ) * ( q22.y - y );
            float a12 = ( q21.x - x ) * ( y - q21.y );
            float a21 = ( x - q12.x ) * ( q12.y - y );
            float a22 = ( x - q11.x ) * ( y - q11.y );

            color += a11 * tex2d->GetPixel( q11.x, q11.y );
            color += a12 * tex2d->GetPixel( q12.x, q12.y );
            color += a21 * tex2d->GetPixel( q21.x, q21.y );
            color += a22 * tex2d->GetPixel( q22.x, q22.y );
        }
    }

    return color;
}