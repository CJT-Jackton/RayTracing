//
// Ray.cpp
//
// The implementation of Ray.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Ray;

/**
 * Create a ray.
 *
 * @param ori the origin point
 * @param dir the direction
 */
Ray::Ray( float3 ori, float3 dir ) :
        Object{ "Ray" },
        _origin{ ori },
        _direction{ normalize( dir ) },
        origin{ _origin },
        direction{ _direction } {
}

Ray::Ray( const Ray& other ) :
        Object{ other },
        _origin{ other._origin },
        _direction{ other._direction },
        origin{ _origin },
        direction{ _direction } {
}

Ray& Ray::operator=( const Ray& other ) {
    if( other != *this ) {
        _origin = other._origin;
        _direction = other._direction;
    }

    return *this;
}

/**
 * Get a point at distance unit along the ray.
 *
 * @param distance the distance
 *
 * @return the point at distance unit along the ray
 */
float3 Ray::GetPoint( float distance ) const {
    return origin + direction * distance;
}

//bool Ray::Raycast( std::vector< Primitive* >& primitives, RaycastHit& hit ) {
//    RaycastHit hitInfo;
//    float depth = 2000.0f;
//    bool intersect = false;
//
//    for( Primitive* primitive : primitives ) {
//        if( primitive->Intersect( *this, hitInfo ) ) {
//            intersect = true;
//
//            if( hitInfo.distance < depth && hitInfo.distance > 0 ) {
//                hit = hitInfo;
//                depth = hitInfo.distance;
//            }
//        }
//    }
//
//    return intersect;
//}
