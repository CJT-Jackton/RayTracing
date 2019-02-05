//
// RenderBuffer.cpp
//
// Created by Jietong Chen on 2/2/2019.
//

#include "RenderBuffer.h"

BYTE* RenderBuffer::GetNativeRenderBufferPtr() const {
    return buffer[ 0 ];
}
