//
// Texture2D.h
//
// Created by Jietong Chen on 2/4/2019.
//


#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Texture.h"

typedef unsigned char BYTE;

class Texture2D : public Texture {
public:
    Texture2D( int w, int h );

    float4 GetPixel( int x, int y ) const;

    void SetPixel( int x, int y, float3 color );

    void SetPixel( int x, int y, float4 color );

    void LoadRawTextureData( BYTE* data );

    BTYE* GetNativeTexturePtr() const override;

private:
    std::vector< BYTE > rawData;
};

#endif // TEXTURE2D_H
