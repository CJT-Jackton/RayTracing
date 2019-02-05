//
// Transform.h
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include "Object.h"
#include "GameObject.h"

class Transform : public Object {
public:
    Transform();

    /**
     * Copy construction is forbidden.
     */
    Transform( const Transform& other ) = delete;

    /**
     * Assignment is forbidden.
     */
    Transform& operator=( const Transform& other ) = delete;

    ~Transform() override = default;

    void DetachChildren();

//    Transform Find( std::string name ) const;

    Transform* GetChild( uint32_t index ) const;

    bool isChildOf( Transform& parent ) const;

    void SetParent( Transform& parent );

    void Translate( float3 translation );

    void Translate( float x, float y, float z );

    std::vector< Transform* >::iterator begin();

    std::vector< Transform* >::iterator end();

public:
    const float3& positon;
    const float3& rotation;
    const float3& scale;

    const float3& right;
    const float3& up;
    const float3& forward;

    Transform* root;
    int childCount;

    const float4x4& localToWorldMatrix;
    const float4x4& worldToLocalMatrix;

private:
    const GameObject* _gameObject;

    std::vector< Transform* > _children;

    Transform* _parent;

    float3 _position;
    float3 _rotation;
    float3 _scale;

    float3 _right;
    float3 _up;
    float3 _forward;

    float4x4 _localToWorldMatrix;
    float4x4 _worldToLocalMatrix;

}; // Transform

#endif // TRANSFORM_H
