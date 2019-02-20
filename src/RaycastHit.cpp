//
// RaycastHit.cpp
//
// The implementation of RaycastHit.
//
// Created by Jietong Chen on 2/18/2019.
//

#include "pch.h"

using RayTracer::RaycastHit;

/**
 * Assign the RaycastHit with another RaycastHit.
 *
 * @param other the other RaycastHit
 *
 * @return this RaycastHit
 */
RaycastHit& RaycastHit::operator=( const RaycastHit& other ) {
    if( this != &other ) {
        primitive = other.primitive;
        distance = other.distance;
        normal = other.normal;
        point = other.point;
        textureCoord = other.textureCoord;
    }

    return *this;
}

/**
 * Determine whether the information in this structure are valid.
 *
 * @return true if the information are valid.
 */
RaycastHit::operator bool() const {
    return primitive != nullptr;
}
