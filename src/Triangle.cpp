//
// Triangle.cpp
//
// The implementation of Triangle.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Triangle;
using RayTracer::Ray;
using RayTracer::RaycastHit;

/**
 * Create a Triangle.
 */
Triangle::Triangle() :
        vertices{},
        normals{},
        uv{},
        color{} {
}

/**
 * Copy the Triangle from another Triangle.
 *
 * @param other the Triangle to copy from.
 */
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
 * Determine whether a ray intersect with the primitive.
 *
 * @param ray the ray
 * @param hit the intersection information
 *
 * @return true if there is intersection, false if not
 */
bool Triangle::Intersect( Ray ray, RaycastHit& hit ) const {
    float3 e1 = vertices[ 1 ] - vertices[ 0 ];
    float3 e2 = vertices[ 2 ] - vertices[ 0 ];

    float3 T = ray.origin - vertices[ 0 ];
    float3 P = cross( ray.direction, e2 );
    float3 Q = cross( T, e1 );

    if( dot( P, e1 ) == 0.0f ) {
        return false;
    }

    float3 result = 1.0f / dot( P, e1 )
                    * float3( dot( Q, e2 ), dot( P, T ),
                              dot( Q, ray.direction ) );

    if( result.x < 0.0f ) {
        return false;
    }

    if( result.y < 0.0f || result.z < 0.0f || result.y + result.z > 1.0f ) {
        return false;
    }

    hit.primitive = ( Primitive * )
    this;
    hit.distance = result.x;
    hit.point = ray.GetPoint( hit.distance );

    float3 w = GetBarycentricCoordinates( hit.point );

    hit.normal = w.x * normals[ 0 ] + w.y * normals[ 1 ] + w.z * normals[ 2 ];
    hit.textureCoord = w.x * uv[ 0 ] + w.y * uv[ 1 ] + w.z * uv[ 2 ];

    return true;
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
    float4x4 normalMatrix = transpose( inverse( localToWorldMatrix ) );

    for( int i = 0; i < 3; ++i ) {
        triangle->vertices[ i ] = mul( localToWorldMatrix,
                                       float4( vertices[ i ], 1.0f ) ).xyz;
        triangle->normals[ i ] = mul( normalMatrix,
                                      float4( normals[ i ], 1.0f ) ).xyz;
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
    float4x4 normalMatrix = transpose( inverse( worldToCameraMatrix ) );

    for( int i = 0; i < 3; ++i ) {
        triangle->vertices[ i ] = mul( worldToCameraMatrix,
                                       float4( vertices[ i ], 1.0f ) ).xyz;
        triangle->normals[ i ] = mul( normalMatrix,
                                      float4( normals[ i ], 1.0f ) ).xyz;
    }

    return triangle;
}

/**
 * Calculate the barycentric coordinate of a point.
 *
 * @param point the point
 *
 * @return the barycentric coordinate
 */
float3 Triangle::GetBarycentricCoordinates( float3 point ) const {
    float area = length( cross( vertices[ 0 ] - vertices[ 1 ],
                                vertices[ 0 ] - vertices[ 2 ] ) );

    float a = length( cross( vertices[ 1 ] - point,
                             vertices[ 2 ] - point ) ) / area;
    float b = length( cross( vertices[ 2 ] - point,
                             vertices[ 0 ] - point ) ) / area;
    float c = length( cross( vertices[ 0 ] - point,
                             vertices[ 1 ] - point ) ) / area;

    return float3( a, b, c );
}
