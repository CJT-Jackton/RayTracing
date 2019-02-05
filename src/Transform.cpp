//
// Transform.cpp
//
// Created by Jietong Chen on 1/30/2019.
//

#include "Transform.h"

Transform::Transform() :
        Object{ "Transform" },
        positon{ _position },
        rotation{ _rotation },
        scale{ _scale },
        right{ _right },
        up{ _up },
        forward{ _forward },
        localToWorldMatrix{ _localToWorldMatrix },
        worldToLocalMatrix{ _worldToLocalMatrix },
        _children{},
        _parent{ nullptr },
        _position{},
        _rotation{},
        _scale{ 1, 1, 1 },
        _right{ 1, 0, 0 },
        _up{ 0, 1, 0 },
        _forward{ 0, 0, 1 } {
}

void Transform::DetachChildren() {
    _children.clear();
}

Transform* Transform::GetChild( uint32_t index ) const {
    return _children.at( index );
}

bool Transform::isChildOf( Transform& parent ) const {
    return *_parent == parent;
}

void Transform::SetParent( Transform& parent ) {
    _parent = &parent;
}

void Transform::Translate( float3 translation ) {
    _position += translation;
}

void Transform::Translate( float x, float y, float z ) {
	_position += float3(x, y, z);
}

std::vector< Transform* >::iterator Transform::begin() {
    return _children.begin();
}

std::vector< Transform* >::iterator Transform::end() {
    return _children.end();
}
