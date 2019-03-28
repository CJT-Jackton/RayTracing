//
// Sphere.cpp
//
// The implementation of Sphere.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Sphere;
using RayTracer::Ray;
using RayTracer::RaycastHit;

/**
 * Create a Sphere.
 */
Sphere::Sphere() :
        center{ 0, 0, 0 },
        radius{ 1 } {
}

/**
 * Copy a Sphere from another Sphere
 *
 * @param other the Sphere to copy from
 */
Sphere::Sphere( const Sphere& other ) :
        Primitive( other ),
        center{ other.center },
        radius{ other.radius } {
}

Sphere* Sphere::Clone() const {
    return new Sphere( *this );
}

/**
 * Determine whether a ray intersect with the primitive.
 *
 * @param ray the ray
 * @param hit the intersection information
 *
 * @return true if there is intersection, false if not
 */
bool Sphere::Intersect( Ray ray, RaycastHit& hit ) const {
    float B = 2.0f * ( ( ray.direction.x * ( ray.origin.x - center.x ) +
                         ray.direction.y * ( ray.origin.y - center.y ) +
                         ray.direction.z * ( ray.origin.z - center.z ) ) );
    float C = pow( ray.origin.x - center.x, 2 ) +
              pow( ray.origin.y - center.y, 2 ) +
              pow( ray.origin.z - center.z, 2 ) -
              pow( radius, 2 );

    float delta = pow( B, 2 ) - 4 * C;
    float distance;

    if( delta < 0 ) {
        return false;
    } else if( delta == 0 ) {
        distance = -B / 2.0f;
    } else {
        float w = ( -B - sqrt( delta ) ) / 2.0f;

        if( w > 0 ) {
            distance = w;
        } else {
            distance = ( -B + sqrt( delta ) ) / 2.0f;
        }
    }

    if( distance < 0.0f ) {
        return false;
    }

    hit.primitive = ( Primitive * )
    this;
    hit.distance = distance;
    hit.point = ray.GetPoint( hit.distance );
    hit.normal = normalize( hit.point - center );
    hit.textureCoord = float2( 0.0f );

    return true;
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
