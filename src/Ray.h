//
// Ray.h
//
// Class of ray. A ray is an infinite line starting at origin and going in
// some direction.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef RAY_H
#define RAY_H

#include "pch.h"

namespace RayTracing {
    /**
     * Class of ray.
     */
    class Ray : public Object {
    public:
        /**
         * Create a ray.
         *
         * @param ori the origin point
         * @param dir the direction
         */
        Ray( float3 ori, float3 dir );

        /**
         *
         *
         * @param other
         */
        Ray( const Ray& other );

        Ray& operator=( const Ray& other );

        /**
         * Get a point at distance unit along the ray.
         *
         * @param distance the distance
         *
         * @return the point at distance unit along the ray
         */
        float3 GetPoint( float distance ) const;

    private:
        /** the origin point of the ray */
        float3 _origin;

        /** the direction of the ray */
        float3 _direction;

    public:
        /** the origin point of the ray */
        const float3 origin;

        /** the direction of the ray */
        const float3 direction;

    }; // Ray
} // RayTracing

#endif // RAY_H
