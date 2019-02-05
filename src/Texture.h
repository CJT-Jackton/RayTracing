//
// Texture.h
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <hlsl++.h>
#include <vector>

#include "Object.h"

typedef unsigned char BTYE;

class Texture : public Object {
public:

    Texture( int w, int h );

    virtual BTYE* GetNativeTexturePtr() const = 0;

public:

    const int width;
    const int height;
};

#endif // TEXTURE_H
