//
// Primitive.h
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Ray.h"
#include "Mesh.h"

class Primitive {
public:
    Primitive() = default;

//    Primitive( const Primitive& other ) = 0;

    virtual ~Primitive() = default;

    Primitive( const Primitive& other );

    virtual Primitive* Clone() const = 0;

    virtual float Intersect( Ray ray ) const = 0;

    virtual Primitive* ToWorldSpace( float4x4 localToWorldMatrix ) const = 0;

    virtual Primitive* ToCameraSpace( float4x4 worldToCameraMatrix ) const = 0;

public:
    const Mesh* mesh;
};

#endif // PRIMITIVE_H
