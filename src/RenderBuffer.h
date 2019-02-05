//
// RenderBuffer.h
//
// Created by Jietong Chen on 2/2/2019.
//

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <vector>

typedef unsigned char BYTE;

struct RenderBuffer {
    BYTE* GetNativeRenderBufferPtr() const;

    std::vector< BYTE > buffer;
};

#endif // RENDERBUFFER_H
