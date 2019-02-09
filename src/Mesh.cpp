//
// Mesh.cpp
//
// The implementation of Mesh.
//
// Created by Jietong Chen on 2/1/2019.
//

#include "pch.h"

using RayTracing::Mesh;
using RayTracing::Object;
using RayTracing::Primitive;

/**
 * Create a empty Mesh.
 */
Mesh::Mesh() :
        Object{ "Empty-Mesh" } {
}

/**
 * Add a primitive to the mesh.
 *
 * @param primitive the primitive
 */
void Mesh::AddPrimitive( std::unique_ptr< Primitive > primitive ) {
    primitive->mesh = this;
    primitives.emplace_back( std::move( primitive ) );
}

/**
 * Get the array of primitive.
 *
 * @return the array of primitive
 */
const std::vector< std::unique_ptr< Primitive > >& Mesh::GetPrimitives() const {
    return primitives;
}
