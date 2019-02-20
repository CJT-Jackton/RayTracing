//
// RenderBuffer.h
//
// The color or depth buffer of a RenderTexture. A RenderTexture can contain
// multiple RenderBuffers.
//
// Created by Jietong Chen on 2/2/2019.
//

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "pch.h"

namespace RayTracer {
    /**
     * The color or depth buffer of a RenderTexture.
     */
    struct RenderBuffer {
        /**
         * Create a render buffer.
         *
         * @param size the size of the buffer
         */
        RenderBuffer( int size );

        /**
         * Create a render buffer with specified fill value.
         *
         * @param size the size of the buffer
         * @param fillValue the fill value
         */
        RenderBuffer( int size, BYTE fillValue );

        /**
         * Get the pointer to the buffer.
         *
         * @return the pointer to the buffer
         */
        BYTE* GetNativeRenderBufferPtr();

        /**
         * Get the pointer to the buffer.
         *
         * @return the pointer to the buffer
         */
        BYTE* GetNativeRenderBufferPtr() const;

        /** the buffer */
        std::vector< BYTE > buffer;

    }; // RenderBuffer
} // RayTracer

#endif // RENDERBUFFER_H
