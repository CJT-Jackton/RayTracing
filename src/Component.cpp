//
// Component.cpp
//
// The implementation of Component.
//
// Created by Jietong Chen on 2/5/2019.
//

#include "pch.h"

using RayTracing::Component;
using RayTracing::GameObject;

/**
 * Create a Component attached to a GameObject.
 *
 * @param gameObject the GameObject to attach
 */
Component::Component( GameObject* gameObject ) :
        _gameObject{ gameObject },
        gameObject{ _gameObject } {
}

/**
 * Create a Component with name attached to a GameObject.
 *
 * @param gameObject the GameObject to attach
 * @param name the name
 */
Component::Component( GameObject* gameObject, std::string name ) :
        Object{ std::move( name ) },
        _gameObject{ gameObject },
        gameObject{ _gameObject } {
}

/**
 *
 *
 * @param other
 */
Component::Component( const Component& other ) :
        _gameObject{ other._gameObject },
        gameObject{ _gameObject } {
}

/**
 *
 *
 * @param other
 * @return
 */
Component& Component::operator=( const Component& other ) {
    if( this != &other ) {
        _gameObject = other._gameObject;
    }

    return *this;
}
