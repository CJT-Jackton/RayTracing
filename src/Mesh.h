//
// Mesh.h
//
// Mesh class contain an array of primitive.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef MESH_H
#define MESH_H

#include "pch.h"

namespace RayTracing {
    /**
     * Mesh class contain an array of primitive.
     */
    class Mesh : public Object {
    public:
        /**
         * Create a empty Mesh.
         */
        Mesh();

        /**
         * Add a primitive to the mesh.
         *
         * @param primitive the primitive
         */
        void AddPrimitive( std::unique_ptr< Primitive > primitive );

        /**
         * Get the array of primitive.
         *
         * @return the array of primitive
         */
        const std::vector< std::unique_ptr< Primitive > >&
        GetPrimitives() const;

    public:
        /** the primitive of the mesh */
        std::vector< std::unique_ptr< Primitive > > primitives;

        /** the renderer this mesh belong */
        Renderer* renderer;
    };
} // RayTracing

#endif // MESH_H
