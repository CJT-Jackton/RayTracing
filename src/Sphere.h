//
// Sphere.h
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive {
public:
    Sphere();
    Sphere( const Sphere& other );

    Sphere* Clone() const;

    float Intersect( Ray ray ) const;

    Sphere* ToWorldSpace( float4x4 localToWorldMatrix ) const;

    Sphere* ToCameraSpace( float4x4 worldToCameraMatrix ) const;

public:
    float3 center;
    float radius;
};

#endif // SPHERE_H
