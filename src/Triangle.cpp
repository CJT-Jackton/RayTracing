//
// Triangle.cpp
//
// The implementation of Triangle.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracing::Triangle;
using RayTracing::Ray;

Triangle::Triangle() :
        vertices{},
        normals{},
        uv{},
        color{} {
}

Triangle::Triangle( const Triangle& other ) :
        Primitive( other ),
        vertices{
                other.vertices[ 0 ], other.vertices[ 1 ], other.vertices[ 2 ] },
        normals{ other.normals[ 0 ], other.normals[ 1 ], other.normals[ 2 ] },
        uv{ other.uv[ 0 ], other.uv[ 1 ], other.uv[ 2 ] },
        color{ other.color[ 0 ], other.color[ 1 ], other.color[ 2 ] } {
}

Triangle* Triangle::Clone() const {
    return new Triangle( *this );
}

/**
 * Determine whether a ray intersect with the triangle.
 *
 * @param ray the ray
 *
 * @return the distance between the origin of the ray and the
 *         intersection point if intersect, a negative number if
 *         no intersection
 */
float Triangle::Intersect( Ray ray ) const {
    float3 e1 = vertices[ 1 ] - vertices[ 0 ];
    float3 e2 = vertices[ 2 ] - vertices[ 0 ];

    float3 T = ray.origin - vertices[ 0 ];
    float3 P = cross( ray.direction, e2 );
    float3 Q = cross( T, e1 );

    if( dot( P, e1 ) == 0.0f ) {
        return -1;
    }

    float3 result = 1.0f / dot( P, e1 )
                    * float3( dot( Q, e2 ), dot( P, T ),
                              dot( Q, ray.direction ) );

    if( result.y < 0.0f || result.z < 0.0f || result.y + result.z > 1.0f ) {
        return -1;
    }

    return result.x;
}

/**
 * Convert the triangle into world space.
 *
 * @param localToWorldMatrix the local to world matrix
 *
 * @return a triangle copy in world space
 */
Triangle* Triangle::ToWorldSpace( float4x4 localToWorldMatrix ) const {
    Triangle* triangle = new Triangle( *this );

    for( int i = 0; i < 3; ++i ) {
        triangle->vertices[ i ] = mul(
                float4( vertices[ i ].x, vertices[ i ].y, vertices[ i ].z,
                        1.0f ), localToWorldMatrix ).xyz;
    }

    return triangle;
}

/**
 * Convert the triange into camera space.
 *
 * @param worldToCameraMatrix the world to camera matrix
 *
 * @return a triange copy in camera space
 */
Triangle* Triangle::ToCameraSpace( float4x4 worldToCameraMatrix ) const {
    Triangle* triangle = new Triangle( *this );

    for( int i = 0; i < 3; ++i ) {
        float4 tmp = float4( vertices[ i ].x, vertices[ i ].y, vertices[ i ].z,
                             1.0f );

        triangle->vertices[ i ] = mul( tmp, worldToCameraMatrix ).xyz;
    }

    return triangle;
}
