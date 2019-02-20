//
// Transform.h
//
// Position, rotation and scale of an object.
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "pch.h"

namespace RayTracer {
    /**
     * Position, rotation and scale of an object.
     */
    class Transform : public Component {
    public:
        /**
         * Create a Transform for a GameObject.
         *
         * @param gameObject the GameObject attach to
         */
        Transform( GameObject* gameObject );

        /**
         * Copy construction is forbidden.
         */
        Transform( const Transform& other );

        /**
         * Assignment is forbidden.
         */
        Transform& operator=( const Transform& other );

        ~Transform() override = default;

        /**
         * Unparents all children.
         */
        void DetachChildren();

        /**
         * Returns a transform child by index.
         *
         * @param index the index of child
         *
         * @return the transform of child
         */
        Transform* GetChild( uint32_t index ) const;

        /**
         * Determine whether this transform is child of parent.
         *
         * @param parent the parent transform
         *
         * @return true if this transform is child of parent, false if not
         */
        bool isChildOf( Transform& parent ) const;

        /**
         * Set the parent of the transform.
         *
         * @param parent the parent transform
         */
        void SetParent( Transform& parent );

        /**
         * Moves the transform in the direction and distance of translation.
         *
         * @param translation the translation vector
         */
        void Translate( float3 translation );

        /**
         * Moves the transform in the direction and distance of translation.
         *
         * @param x move distance along x-axis
         * @param y move distance along y-axis
         * @param z move distance along z-axis
         */
        void Translate( float x, float y, float z );

        /**
         * Rotate the transform with given euler angles degrees around the
         * x axis, y axis, z axis (in that order).
         *
         * @param eulers euler angles of rotation
         */
        void Rotate( float3 eulers );

        /**
         * Rotate the transform with given euler angles degree around the
         * x axis, y axis, z axis (in that order).
         *
         * @param xAngle degrees to rotate around the x axis
         * @param yAngle degrees to rotate around the y axis
         * @param zAngle degrees to rotate around the z axis
         */
        void Rotate( float xAngle, float yAngle, float zAngle );

        void ToSpace( float4x4 matrix );

        /**
         * Get interator pointing to the first child of the Transform.
         *
         * @return interator pointing to the first child of the Transform
         */
        std::vector< Transform* >::iterator begin();

        /**
         * Get interator pointing to the past-the-end child of the Transform.
         *
         * @return interator pointing to the past-the-end child of the Transform
         */
        std::vector< Transform* >::iterator end();

    private:
        /**
         * Get the translate transform matrix.
         *
         * @return the translate transform matrix
         */
        float4x4 GetTranslateMatrix() const;

        /**
         * Get the rotation transform matrix.
         *
         * @return the rotation transform matrix
         */
        float4x4 GetRotationMatrix() const;

        /**
         * Get the scale transform matrix.
         *
         * @return the scale transform matrix
         */
        float4x4 GetScaleMatrix() const;

        /**
         * Recalculate the local to world matrix.
         */
        void UpdateLocalToWorldMatrix();

        /**
         * Recalculate the world to local matrix.
         */
        void UpdateWorldToLocalMatrix();

    public:
        /** the root transform */
        Transform* root;

        /** the number of child */
        unsigned int childCount;

        /** the position */
        const float3& positon;

        /** the rotation */
        const float3& rotation;

        /** the scale */
        const float3& scale;

        /** the right vector in world space */
        const float3& right;

        /** the up vector in world space */
        const float3& up;

        /** the front vector in world space */
        const float3& forward;

        /** the local to world matrix */
        const float4x4& localToWorldMatrix;

        /** the world to local matrix */
        const float4x4& worldToLocalMatrix;

    private:
        /** the children of this transform */
        std::vector< Transform* > _children;

        /** the parent transform */
        Transform* _parent;

        /** the position */
        float3 _position;

        /** the rotation in euler angles */
        float3 _euler;

        /** the rotation in quaternion */
        quaternion _rotation;

        /** the scale */
        float3 _scale;

        /** the right vector in world space */
        float3 _right;

        /** the up vector in world space */
        float3 _up;

        /** the forward vector in world space */
        float3 _forward;

        /** the local to world matrix */
        float4x4 _localToWorldMatrix;

        /** the world to local matrix */
        float4x4 _worldToLocalMatrix;

    }; // Transform
} // RayTracer

#endif // TRANSFORM_H
