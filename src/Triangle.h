//
// Triangle.h
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <hlsl++.h>
#include "Primitive.h"

class Triangle : public Primitive {
public:
    Triangle();

    Triangle( const Triangle& other );

    Triangle* Clone() const;

    float Intersect( Ray ray ) const;

    Triangle* ToWorldSpace( float4x4 localToWorldMatrix ) const;

	Triangle* ToCameraSpace( float4x4 worldToCameraMatrix ) const;

public:
    float3 vertices[3];
    float3 normals[3];
    float2 uv[3];
    float4 color[3];
};

#endif // TRIANGLE_H
