//
// Sphere.cpp
//
// The implementation of Sphere.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracing::Sphere;
using RayTracing::Ray;

Sphere::Sphere() :
        center{ 0, 0, 0 },
        radius{ 1 } {
}

Sphere::Sphere( const Sphere& other ) :
        Primitive( other ),
        center{ other.center },
        radius{ other.radius } {
}

Sphere* Sphere::Clone() const {
    return new Sphere( *this );
}

/**
 * Determine whether a ray intersect with the sphere.
 *
 * @param ray the ray
 *
 * @return the distance between the origin of the ray and the
 *         intersection point if intersect, a negative number if
 *         no intersection
 */
float Sphere::Intersect( Ray ray ) const {
    float B = 2.0f * ( ( ray.direction.x * ( ray.origin.x - center.x ) +
                         ray.direction.y * ( ray.origin.y - center.y ) +
                         ray.direction.z * ( ray.origin.z - center.z ) ) );
    float C = pow( ray.origin.x - center.x, 2 ) +
              pow( ray.origin.y - center.y, 2 ) +
              pow( ray.origin.z - center.z, 2 ) -
              pow( radius, 2 );

    float delta = pow( B, 2 ) - 4 * C;

    if( delta < 0 ) {
        return -1;
    } else if( delta == 0 ) {
        return -B / 2.0f;
    } else {
        if( ( -B - delta ) / 2.0f > 0 ) {
            return ( -B - delta ) / 2.0f;
        } else {
            return ( -B + delta ) / 2.0f;
        }
    }
}

/**
 * Convert the sphere into world space.
 *
 * @param localToWorldMatrix the local to world matrix
 *
 * @return a sphere copy in world space
 */
Sphere* Sphere::ToWorldSpace( float4x4 localToWorldMatrix ) const {
    Sphere* sphere = new Sphere( *this );

    sphere->center = mul( localToWorldMatrix,
                          float4( center.x, center.y, center.z, 1.0f ) ).xyz;

    return sphere;
}

/**
 * Convert the sphere into camera space.
 *
 * @param worldToCameraMatrix the world to camera matrix
 *
 * @return a sphere copy in camera space
 */
Sphere* Sphere::ToCameraSpace( float4x4 worldToCameraMatrix ) const {
    Sphere* sphere = new Sphere( *this );

    sphere->center = mul( worldToCameraMatrix,
                          float4( center.x, center.y, center.z, 1.0f ) ).xyz;

    return sphere;
}
