//
// Ray.h
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef RAY_H
#define RAY_H

#include <hlsl++.h>

#include "Object.h"

class Ray : public Object {
public:
    Ray();

    Ray( float3 ori, float3 dir );

    float3 GetPoint( float distance ) const;

public:
    const float3 origin;
    const float3 direction;
};

#endif // RAY_H
