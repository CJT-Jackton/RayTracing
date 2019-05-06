//
// Bounds.cpp
//
// The implementation of Bounds.
//
// Created by Jietong Chen on 2019/4/9.
//

#include "pch.h"

using RayTracer::Bounds;

/**
 * Create an axis aligned bounding box.
 *
 * @param max the maximal point
 * @param min the minimal point
 */
Bounds::Bounds( float3 max, float3 min ) :
        Object{ "Bounding Box" },
        center{ ( max + min ) / 2.0f },
        extents{ ( max - min ) / 2.0f },
        max{ max },
        min{ min },
        size{ max - min } {
}

/**
 * Cpoy the bounding box from another bounding box.
 *
 * @param other the Bounds to copy from
 */
Bounds::Bounds( const Bounds& other ) :
        Object{ "Bounding Box" },
        center{ other.center },
        extents{ other.extents },
        max{ other.max },
        min{ other.min },
        size{ other.size } {
}

/**
 * Assign the bounding box with another bounding box.
 *
 * @param other the Bounds to assign
 *
 * @return this bounding box
 */
Bounds& Bounds::operator=( const Bounds& other ) {
    if( this != &other ) {
        center = other.center;
        extents = other.extents;
        max = other.max;
        min = other.min;
        size = other.size;
    }

    return *this;
}

/**
 * Determine whether the bounding box intersect with another bounding
 * box.
 *
 * @param other the other bounding box
 *
 * @return true if there is intersection, false if not
 */
bool Bounds::Intersect( const Bounds& other ) const {
    if( other.min.x > max.x || other.max.x < min.x ||
        other.min.y > max.y || other.max.y < min.y ||
        other.min.z > max.z || other.max.z < min.z ) {
        return false;
    } else {
        return true;
    }
}

/**
 * Merge the bounding box with another bounding box.
 *
 * @param other the bounding box to merge
 */
void Bounds::Merge( const Bounds& other ) {
    float3 mergeMax = float3( max.x > other.max.x ? max.x : other.max.x,
                              max.y > other.max.y ? max.y : other.max.y,
                              max.z > other.max.z ? max.z : other.max.z );

    float3 mergeMin = float3( min.x < other.min.x ? min.x : other.min.x,
                              min.y < other.min.y ? min.y : other.min.y,
                              min.z < other.min.z ? min.z : other.min.z );

    max = mergeMax;
    min = mergeMin;

    // recalculate the variables
    center = ( max + min ) / 2.0f;
    size = max - min;
    extents = ( max - min ) / 2.0f;
}
