//
// Sphere.h
//
// The basic sphere shape.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "pch.h"

namespace RayTracer {
    /**
     * The basic sphere shape.
     */
    class Sphere : public Primitive {
    public:
        /**
         * Create a Sphere.
         */
        Sphere();

        /**
         * Copy a Sphere from another Sphere
         *
         * @param other the Sphere to copy from
         */
        Sphere( const Sphere& other );

        Sphere* Clone() const;

        /**
         * Determine whether a ray intersect with the primitive.
         *
         * @param ray the ray
         * @param hit the intersection information
         *
         * @return true if there is intersection, false if not
         */
        bool Intersect( Ray ray, RaycastHit& hit ) const override;

        Bounds GetBound() const override;

        /**
         * Convert the sphere into world space.
         *
         * @param localToWorldMatrix the local to world matrix
         *
         * @return a sphere copy in world space
         */
        Sphere* ToWorldSpace( float4x4 localToWorldMatrix ) const override;

        /**
         * Convert the sphere into camera space.
         *
         * @param worldToCameraMatrix the world to camera matrix
         *
         * @return a sphere copy in camera space
         */
        Sphere* ToCameraSpace( float4x4 worldToCameraMatrix ) const override;

    public:
        /** the center */
        float3 center;

        /** the radius */
        float radius;

    }; // Sphere
} // RayTracer

#endif // SPHERE_H
