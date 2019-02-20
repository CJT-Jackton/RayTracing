//
// Transform.cpp
//
// The implementation of Transform.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracer::Transform;
using RayTracer::GameObject;

/**
 * Create a Transform for a GameObject.
 *
 * @param gameObject the GameObject attach to
 */
Transform::Transform( GameObject* gameObject ) :
        Component{ gameObject, "Transform" },
        positon{ _position },
        rotation{ _euler },
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
        _euler{ 0, 0, 0 },
        _rotation{ euler( float3( 0, 0, 0 ) ) },
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
        rotation{ _euler },
        scale{ _scale },
        right{ _right },
        up{ _up },
        forward{ _forward },
        localToWorldMatrix{ _localToWorldMatrix },
        worldToLocalMatrix{ _worldToLocalMatrix },
        _children{ other._children },
        _parent{ other._parent },
        _position{ other._position },
        _euler{ other._euler },
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
        _localToWorldMatrix = other._localToWorldMatrix;
        _worldToLocalMatrix = other._worldToLocalMatrix;
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
 * Rotate the transform with given euler angles degrees around the
 * x axis, y axis, z axis (in that order).
 *
 * @param eulers euler angles of rotation
 */
void Transform::Rotate( float3 eulers ) {
    _euler = eulers;
    _rotation = euler( _euler * 3.14159265f / 180.0f );

    // recalculate the model matrix
    UpdateLocalToWorldMatrix();
    UpdateWorldToLocalMatrix();

    // recalculate the right, up, front vector of the transform
    float4x4 m = transpose( inverse( GetRotationMatrix() ) );
    _right = mul( m, float4( _right, 1.0f ) ).xyz;
    _up = mul( m, float4( _up, 1.0f ) ).xyz;
    _forward = mul( m, float4( _forward, 1.0f ) ).xyz;
}

/**
 * Rotate the transform with given euler angles degree around the
 * x axis, y axis, z axis (in that order).
 *
 * @param xAngle degrees to rotate around the x axis
 * @param yAngle degrees to rotate around the y axis
 * @param zAngle degrees to rotate around the z axis
 */
void Transform::Rotate( float xAngle, float yAngle, float zAngle ) {
    Rotate( float3( xAngle, yAngle, zAngle ) );
}

void Transform::ToSpace( float4x4 matrix ) {
    _position = mul( matrix, float4( _position, 1.0f ) ).xyz;

    float4x4 m_r = matrix;
    m_r._14 = 0.0f;
    m_r._24 = 0.0f;
    m_r._34 = 0.0f;
    _euler = mul( m_r, float4( _euler, 1.0f ) ).xyz;
    _scale = mul( m_r, float4( _scale, 1.0f ) ).xyz;

    float4x4 m = transpose( inverse( matrix ) );
    _right = mul( m, float4( _right, 1.0f ) ).xyz;
    _up = mul( m, float4( _up, 1.0f ) ).xyz;
    _forward = mul( m, float4( _forward, 1.0f ) ).xyz;

    _localToWorldMatrix = mul( localToWorldMatrix, matrix );
    _worldToLocalMatrix = inverse( _localToWorldMatrix );
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
            1, 0, 0, _position.x,
            0, 1, 0, _position.y,
            0, 0, 1, _position.z,
            0, 0, 0, 1
    );
}

/**
 * Get the rotation transform matrix.
 *
 * @return the rotation transform matrix
 */
float4x4 Transform::GetRotationMatrix() const {
    // convert euler angles from degrees to radians
    float3 rad = _euler * 3.14159265f / 180.0f;

    float4x4 rotationAroundX( 1, 0, 0, 0,
                              0, cosf( rad.x ), -sinf( rad.x ), 0,
                              0, sinf( rad.x ), cosf( rad.x ), 0,
                              0, 0, 0, 1
    );

    float4x4 rotationAroundY( cosf( rad.y ), 0, sinf( rad.y ), 0,
                              0, 1, 0, 0,
                              -sinf( rad.y ), 0, cosf( rad.y ), 0,
                              0, 0, 0, 1
    );

    float4x4 rotationAroundZ( cosf( rad.z ), -sinf( rad.z ), 0, 0,
                              sinf( rad.z ), cosf( rad.z ), 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1
    );

    // apply the rotation in x, y, z order
    return mul( rotationAroundZ, mul( rotationAroundX, rotationAroundY ) );
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
    _localToWorldMatrix = mul( GetRotationMatrix(), GetTranslateMatrix() );

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
