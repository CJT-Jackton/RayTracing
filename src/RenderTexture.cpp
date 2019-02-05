//
// RenderTexture.cpp
//
// Created by Jietong Chen on 2/2/2019.
//

#include "RenderTexture.h"

union floatBYTE {
    float f;
    BYTE byte[4];
};

RenderTexture::RenderTexture( int w, int h ) : Texture{ w, h } {}

void RenderTexture::WriteColorBuffer( int x, int y, int4 color ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();
        colorBufferData[ 4 * ( x * width + y ) + 0 ] = color.r;
        colorBufferData[ 4 * ( x * width + y ) + 1 ] = color.g;
        colorBufferData[ 4 * ( x * width + y ) + 2 ] = color.b;
        colorBufferData[ 4 * ( x * width + y ) + 3 ] = color.a;
    }
}

void RenderTexture::WriteDepthBuffer( int x, int y, float depth,
                                      int stencil ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* depthBufferData = depthBuffer.GetNativeRenderBufferPtr();

        floatBYTE d{ depth };
//        d.f = depth;

        depthBufferData[ 4 * ( x * width + y ) + 0 ] = d.byte[ 0 ];
        depthBufferData[ 4 * ( x * width + y ) + 1 ] = d.byte[ 1 ];
        depthBufferData[ 4 * ( x * width + y ) + 2 ] = d.byte[ 2 ];

        depthBufferData[ 4 * ( x * width + y ) + 3 ] = stencil;
    }
}

int4 RenderTexture::ReadColorBuffer( int x, int y ) const {
    int4 color;

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* colorBufferData = colorBuffer.GetNativeRenderBufferPtr();

        color = int4( colorBufferData[ 4 * ( x * width + y ) + 0 ],
                      colorBufferData[ 4 * ( x * width + y ) + 1 ],
                      colorBufferData[ 4 * ( x * width + y ) + 2 ],
                      colorBufferData[ 4 * ( x * width + y ) + 3 ] );
    }

    return color;
}

float RenderTexture::ReadDepthBuffer( int x, int y ) const {
    float depth;

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* depthBufferData = depthBuffer.GetNativeRenderBufferPtr();

        floatBYTE d{};
        d.byte[ 0 ] = depthBufferData[ 4 * ( x * width + y ) + 0 ];
        d.byte[ 1 ] = depthBufferData[ 4 * ( x * width + y ) + 1 ];
        d.byte[ 2 ] = depthBufferData[ 4 * ( x * width + y ) + 2 ];

        depth = d.f;
    }

    return depth;
}

int RenderTexture::ReadStencilBuffer( int x, int y ) const {
    int stencil;

    if( x >= 0 && x < width && y >= 0 && y < height ) {
        BYTE* depthBufferData = depthBuffer.GetNativeRenderBufferPtr();

        stencil = depthBufferData[ 4 * ( x * width + y ) + 3 ];
    }

    return stencil;
}

BTYE* RenderTexture::GetNativeTexturePtr() const {
    return colorBuffer.GetNativeRenderBufferPtr();
}
