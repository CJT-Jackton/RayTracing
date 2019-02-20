//
// RenderBuffer.cpp
//
// The implementation of RenderBuffer.
//
// Created by Jietong Chen on 2/2/2019.
//

#include "pch.h"

using RayTracer::RenderBuffer;
using RayTracer::BYTE;

/**
 * Create a render buffer.
 *
 * @param size the size of the buffer
 */
RenderBuffer::RenderBuffer( int size ) :
        buffer( ( unsigned int ) size, 0 ) {
}

/**
 * Create a render buffer with specified fill value.
 *
 * @param size the size of the buffer
 * @param fillValue the fill value
 */
RenderBuffer::RenderBuffer( int size, BYTE fillValue ) :
        buffer( ( unsigned int ) size, fillValue ) {
}

/**
 * Get the pointer to the buffer.
 *
 * @return the pointer to the buffer
 */
BYTE* RenderBuffer::GetNativeRenderBufferPtr() {
    return buffer.data();
}

/**
 * Get the pointer to the buffer.
 *
 * @return the pointer to the buffer
 */
BYTE* RenderBuffer::GetNativeRenderBufferPtr() const {
    return const_cast<BYTE*>(buffer.data());
}
