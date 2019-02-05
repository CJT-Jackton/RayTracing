//
// Texture2D.cpp
//
// Created by Jietong Chen on 2/4/2019.
//

#include "Texture2D.h"

Texture2D::Texture2D( int w, int h ) :
        Texture{ w, h },
        rawData{ w * h * 4 } {
}

float4 Texture2D::GetPixel( int x, int y ) const {
    if( x < 0 || x >= width || y < 0 || y >= height ) {
        return float4( 0, 0, 0, 0 );
    } else {
        return float4( ( float ) rawData[ 4 * ( x * width + y ) + 0 ] / 255.0f,
                       ( float ) rawData[ 4 * ( x * width + y ) + 1 ] / 255.0f,
                       ( float ) rawData[ 4 * ( x * width + y ) + 2 ] / 255.0f,
                       ( float ) rawData[ 4 * ( x * width + y ) + 3 ] /
                       255.0f );
    }
}

void Texture2D::SetPixel( int x, int y, float3 color ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        rawData[ 4 * ( x * width + y ) + 0 ] = ( BTYE ) ( color.r * 255 );
        rawData[ 4 * ( x * width + y ) + 1 ] = ( BTYE ) ( color.g * 255 );
        rawData[ 4 * ( x * width + y ) + 2 ] = ( BTYE ) ( color.b * 255 );
        rawData[ 4 * ( x * width + y ) + 3 ] = ( BTYE ) ( 1.0f * 255 );
    }
}

void Texture2D::SetPixel( int x, int y, float4 color ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        rawData[ 4 * ( x * width + y ) + 0 ] = ( BTYE ) ( color.r * 255 );
        rawData[ 4 * ( x * width + y ) + 1 ] = ( BTYE ) ( color.g * 255 );
        rawData[ 4 * ( x * width + y ) + 2 ] = ( BTYE ) ( color.b * 255 );
        rawData[ 4 * ( x * width + y ) + 3 ] = ( BTYE ) ( color.a * 255 );
    }
}

void Texture2D::LoadRawTextureData( BYTE* data ) {
    rawData = std::vector< BYTE >{ data, data + ( width * height * 4 ) };
}

BTYE* Texture2D::GetNativeTexturePtr() const {
    return &rawData[ 0 ];
}
