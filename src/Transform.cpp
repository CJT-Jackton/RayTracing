//
// Transform.cpp
//
// The implementation of Transform.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracing::Transform;
using RayTracing::GameObject;

/**
 * Create a Transform for a GameObject.
 *
 * @param gameObject the GameObject attach to
 */
Transform::Transform( GameObject* gameObject ) :
        Component{ gameObject, "Transform" },
        positon{ _position },
        rotation{ _rotation },
        scale{ _scale },
        right{ _right },
        up{ _up },
        forward{ _forward },
        localToWorldMatrix{ _localToWorldMatrix },
        worldToLocalMatrix{ _worldToLocalMatrix },
        childCount{ _children.size() },
        _children{},
        _parent{},
        _position{ 0, 0, 0 },
        _rotation{ 0, 0, 0 },
        _scale{ 1, 1, 1 },
        _right{ 1, 0, 0 },
        _up{ 0, 1, 0 },
        _forward{ 0, 0, 1 } {
    UpdateLocalToWorldMatrix();
    UpdateWorldToLocalMatrix();
}

/**
 * Copy construction is forbidden.
 */
Transform::Transform( const Transform& other ) :
        Component{ other.gameObject, "Transform" },
        positon{ _position },
        rotation{ _rotation },
        scale{ _scale },
        right{ _right },
        up{ _up },
        forward{ _forward },
        localToWorldMatrix{ _localToWorldMatrix },
        worldToLocalMatrix{ _worldToLocalMatrix },
        _children{ other._children },
        _parent{ other._parent },
        _position{ other._position },
        _rotation{ other._rotation },
        _scale{ other._scale },
        _right{ other._right },
        _up{ other._up },
        _forward{ other._forward },
        _localToWorldMatrix{ other._localToWorldMatrix },
        _worldToLocalMatrix{ other._worldToLocalMatrix } {
}

Transform& Transform::operator=( const Transform& other ) {
    if( this != &other ) {
        _children = other._children;
        _parent = other._parent;
        _position = other._position;
        _rotation = other._rotation;
        _scale = other._scale;
        _right = other._right;
        _up = other._up;
        _forward = other._forward;
    }

    return *this;
}

/**
 * Unparents all children.
 */
void Transform::DetachChildren() {
    _children.clear();
}

/**
 * Returns a transform child by index.
 *
 * @param index the index of child
 *
 * @return the transform of child
 */
Transform* Transform::GetChild( uint32_t index ) const {
    return _children.at( index );
}

/**
 * Determine whether this transform is child of parent.
 *
 * @param parent the parent transform
 *
 * @return true if this transform is child of parent, false if not
 */
bool Transform::isChildOf( Transform& parent ) const {
    return *_parent == parent;
}

/**
 * Set the parent of the transform.
 *
 * @param parent the parent transform
 */
void Transform::SetParent( Transform& parent ) {
    _parent = &parent;

    UpdateLocalToWorldMatrix();
    UpdateWorldToLocalMatrix();
}

/**
 * Moves the transform in the direction and distance of translation.
 *
 * @param translation the translation vector
 */
void Transform::Translate( float3 translation ) {
    _position += translation;

    UpdateLocalToWorldMatrix();
    UpdateWorldToLocalMatrix();
}

/**
 * Moves the transform in the direction and distance of translation.
 *
 * @param x move distance along x-axis
 * @param y move distance along y-axis
 * @param z move distance along z-axis
 */
void Transform::Translate( float x, float y, float z ) {
    _position += float3( x, y, z );

    UpdateLocalToWorldMatrix();
    UpdateWorldToLocalMatrix();
}

/**
 * Get interator pointing to the first child of the Transform.
 *
 * @return interator pointing to the first child of the Transform
 */
std::vector< Transform* >::iterator Transform::begin() {
    return _children.begin();
}

/**
 * Get interator pointing to the past-the-end child of the Transform.
 *
 * @return interator pointing to the past-the-end child of the Transform
 */
std::vector< Transform* >::iterator Transform::end() {
    return _children.end();
}

/**
 * Get the translate transform matrix.
 *
 * @return the translate transform matrix
 */
float4x4 Transform::GetTranslateMatrix() const {
    return float4x4(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            _position.x, _position.y, _position.z, 1
    );
}

/**
 * Get the scale transform matrix.
 *
 * @return the scale transform matrix
 */
float4x4 Transform::GetScaleMatrix() const {
    return float4x4(
            _scale.x, 0, 0, 0,
            0, _scale.y, 0, 0,
            0, 0, _scale.z, 0,
            0, 0, 0, 1
    );
}

/**
 * Recalculate the local to world matrix.
 */
void Transform::UpdateLocalToWorldMatrix() {
    _localToWorldMatrix = GetScaleMatrix();
    _localToWorldMatrix = mul( GetTranslateMatrix(), _localToWorldMatrix );

    if( root ) {
        _localToWorldMatrix = mul( _localToWorldMatrix,
                                   _parent->_localToWorldMatrix );
    }
}

/**
 * Recalculate the world to local matrix.
 */
void Transform::UpdateWorldToLocalMatrix() {
    _worldToLocalMatrix = inverse( _localToWorldMatrix );
}
