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

namespace RayTracer {
    /**
     * The basic triangle.
     */
    class Triangle : public Primitive {
    public:
        /**
         * Create a Triangle.
         */
        Triangle();

        /**
         * Copy the Triangle from another Triangle.
         *
         * @param other the Triangle to copy from.
         */
        Triangle( const Triangle& other );

        Triangle* Clone() const;

        /**
         * Determine whether a ray intersect with the primitive.
         *
         * @param ray the ray
         * @param hit the intersection information
         *
         * @return true if there is intersection, false if not
         */
        bool Intersect( Ray ray, RaycastHit& hit ) const;

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

        /**
         * Calculate the barycentric coordinate of a point.
         *
         * @param point the point
         *
         * @return the barycentric coordinate
         */
        float3 GetBarycentricCoordinates( float3 point ) const;

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
} // RayTracer

#endif // TRIANGLE_H
