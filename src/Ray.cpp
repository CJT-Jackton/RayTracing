//
// Ray.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "Ray.h"

Ray::Ray() :
        origin{},
        direction{ 0, 0, 1 } {
}

Ray::Ray( float3 ori, float3 dir ) :
        origin{ ori },
        direction{ normalize( dir ) } {
}

float3 Ray::GetPoint( float distance ) const {
    return origin + direction * distance;
}
