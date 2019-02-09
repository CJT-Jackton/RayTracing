//
// Primitive.cpp
//
// The implementation of Primitive.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracing::Primitive;

/**
 * Copy a Primitive from another Primitive.
 *
 * @param other the primitive to copy from
 */
Primitive::Primitive( const Primitive& other ) :
        mesh{ other.mesh } {
}
