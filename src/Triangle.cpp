//
// Triangle.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "Triangle.h"

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

    return result.x;
}

Triangle* Triangle::ToWorldSpace( float4x4 localToWorldMatrix ) const {
    Triangle* triangle = new Triangle( *this );

    for( int i = 0; i < 3; ++i ) {
        /*float4 tmp = mul(
                float4( vertices[ i ].x, vertices[ i ].y, vertices[ i ].z,
                        .0f ), localToWorldMatrix );
        triangle->vertices[ i ] = float3( tmp.x, tmp.y, tmp.z );*/

        triangle->vertices[ i ] = mul(
                float4( vertices[ i ].x, vertices[ i ].y, vertices[ i ].z,
                        0.0f ), localToWorldMatrix ).xyz;
    }

    return triangle;
}

Triangle* Triangle::ToCameraSpace( float4x4 worldToCameraMatrix ) const {
    Triangle* triangle = new Triangle( *this );

    for( int i = 0; i < 3; ++i ) {
        /*float4 tmp = mul(
                float4( vertices[ i ].x, vertices[ i ].y, vertices[ i ].z,
                        .0f ), worldToCameraMatrix );
        triangle->vertices[ i ] = float3( tmp.x, tmp.y, tmp.z );*/

        triangle->vertices[ i ] = mul(
                float4( vertices[ i ].x, vertices[ i ].y, vertices[ i ].z,
                        0.0f ), worldToCameraMatrix ).xyz;
    }

    return triangle;
}
