//
// RaycastHit.h
//
// Structure used to get information back from a raycast.
//
// Created by Jietong Chen on 2/18/2019.
//

#ifndef RAYCASTHIT_H
#define RAYCASTHIT_H

#include "pch.h"

namespace RayTracer {
    /**
     * Structure used to get information back from a raycast.
     */
    struct RaycastHit {
        /**
         * Assign the RaycastHit with another RaycastHit.
         *
         * @param other the other RaycastHit
         *
         * @return this RaycastHit
         */
        RaycastHit& operator=( const RaycastHit& other );

        /**
         * Determine whether the information in this structure are valid.
         *
         * @return true if the information are valid.
         */
        operator bool() const;

        /** the primitive that was hit */
        Primitive* primitive = nullptr;

        /** the distance from the ray's origin to the impact point */
        float distance;

        /** the normal of the surface the ray hit */
        float3 normal;

        /** the impact point where the ray hit the collider */
        float3 point;

        /** the uv texture coordinate at the collision location */
        float2 textureCoord;

    }; // RaycastHit
} // RayTracer

#endif // RAYCASTHIT_H
