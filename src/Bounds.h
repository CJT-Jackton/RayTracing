//
// Bounds.h
//
// An axis-aligned bounding box, or AABB for short, is a box aligned with
// coordinate axes and fully enclosing some object.
//
// Created by Jietong Chen on 2019/4/9.
//

#ifndef BOUNDS_H
#define BOUNDS_H

#include "Object.h"

namespace RayTracer {
    /**
     * Represents an axis aligned bounding box.
     */
    class Bounds : public Object {
    public:
        /**
         * Create an axis aligned bounding box.
         *
         * @param max the maximal point
         * @param min the minimal point
         */
        Bounds( float3 max, float3 min );

        /**
         * Cpoy the bounding box from another bounding box.
         *
         * @param other the Bounds to copy from
         */
        Bounds( const Bounds& other );

        /**
         * Assign the bounding box with another bounding box.
         *
         * @param other the Bounds to assign
         *
         * @return this bounding box
         */
        Bounds& operator=( const Bounds& other );

        /**
         * Determine whether the bounding box intersect with another bounding
         * box.
         *
         * @param other the other bounding box
         *
         * @return true if there is intersection, false if not
         */
        bool Intersect( const Bounds& other ) const;

        /**
         * Merge the bounding box with another bounding box.
         *
         * @param other the bounding box to merge
         */
        void Merge( const Bounds& other );

    public:
        /** the center of the bounding box */
        float3 center;

        /** the extents of the bounding box */
        float3 extents;

        /** the maximal point of the bounding box */
        float3 max;

        /** the minimal point of the bounding box */
        float3 min;

        /** the total size of the bounding box */
        float3 size;

    }; // Bounds
} // RayTracer

#endif // BOUNDS_H
