//
// Primitive.h
//
// The base class of primitive. Primitve is the basic mesh element in the scene.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "pch.h"

namespace RayTracing {
    /**
     * The base class of primitive.
     */
    class Primitive {
    public:
        /**
         * Default constructor.
         */
        Primitive() = default;

        /**
         * Copy a Primitive from another Primitive.
         *
         * @param other the primitive to copy from
         */
        Primitive( const Primitive& other );

        /**
         * Default deconstructor.
         */
        virtual ~Primitive() = default;

        /**
         * Assignment is forbiden.
         */
        Primitive& operator=( const Primitive& other ) = delete;

        virtual Primitive* Clone() const = 0;

        /**
         * Determine whether a ray intersect with the primitive.
         *
         * @param ray the ray
         *
         * @return the distance between the origin of the ray and the
         *         intersection point if intersect, a negative number if
         *         no intersection
         */
        virtual float Intersect( Ray ray ) const = 0;

        /**
         * Convert the primitive into world space.
         *
         * @param localToWorldMatrix the local to world matrix
         *
         * @return a primitive copy in world space
         */
        virtual Primitive*
        ToWorldSpace( float4x4 localToWorldMatrix ) const = 0;

        /**
         * Convert the primitive into camera space.
         *
         * @param worldToCameraMatrix the world to camera matrix
         *
         * @return a primitive copy in camera space
         */
        virtual Primitive*
        ToCameraSpace( float4x4 worldToCameraMatrix ) const = 0;

    public:
        /** the mesh this primitive in */
        const Mesh* mesh;

    }; // Primitive
} // RayTracing

#endif // PRIMITIVE_H
