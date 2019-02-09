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

namespace RayTracing {
    /**
     * The basic sphere shape.
     */
    class Sphere : public Primitive {
    public:
        Sphere();

        Sphere( const Sphere& other );

        Sphere* Clone() const;

        /**
         * Determine whether a ray intersect with the sphere.
         *
         * @param ray the ray
         *
         * @return the distance between the origin of the ray and the
         *         intersection point if intersect, a negative number if
         *         no intersection
         */
        float Intersect( Ray ray ) const override;

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
} // RayTracing

#endif // SPHERE_H
