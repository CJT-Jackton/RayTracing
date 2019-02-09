//
// Triangle.h
//
// The basic triangle.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "pch.h"

namespace RayTracing {
    /**
     * The basic triangle.
     */
    class Triangle : public Primitive {
    public:
        Triangle();

        Triangle( const Triangle& other );

        Triangle* Clone() const;

        /**
         * Determine whether a ray intersect with the triangle.
         *
         * @param ray the ray
         *
         * @return the distance between the origin of the ray and the
         *         intersection point if intersect, a negative number if
         *         no intersection
         */
        float Intersect( Ray ray ) const;

        /**
         * Convert the triangle into world space.
         *
         * @param localToWorldMatrix the local to world matrix
         *
         * @return a triangle copy in world space
         */
        Triangle* ToWorldSpace( float4x4 localToWorldMatrix ) const;

        /**
         * Convert the triange into camera space.
         *
         * @param worldToCameraMatrix the world to camera matrix
         *
         * @return a triange copy in camera space
         */
        Triangle* ToCameraSpace( float4x4 worldToCameraMatrix ) const;

    public:
        /** the vertices */
        float3 vertices[3];

        /** the normal vectors */
        float3 normals[3];

        /** the uv coordinates */
        float2 uv[3];

        /** the colors */
        float4 color[3];

    }; // Triangle
} // RayTracing

#endif // TRIANGLE_H
