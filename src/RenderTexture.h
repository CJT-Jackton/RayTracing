//
// RenderTexture.h
//
// Created by Jietong Chen on 2/2/2019.
//

#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include "Texture.h"
#include "RenderBuffer.h"

class RenderTexture : public Texture {
public:
    RenderTexture( int w, int h );

    void WriteColorBuffer( int x, int y, int4 color );

    void WriteDepthBuffer( int x, int y, float depth, int stencil );

    int4 ReadColorBuffer( int x, int y ) const;

    float ReadDepthBuffer( int x, int y ) const;

    int ReadStencilBuffer( int x, int y ) const;

    BTYE* GetNativeTexturePtr() const override;

public:
    RenderBuffer colorBuffer;
    RenderBuffer depthBuffer;

}; // RenderTexture

#endif // RENDERTEXTURE_H
