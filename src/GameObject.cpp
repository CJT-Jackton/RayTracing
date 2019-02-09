//
// GameObject.cpp
//
// The implementation of GameObject.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracing::GameObject;
using RayTracing::Transform;
using RayTracing::Renderer;
using RayTracing::Scene;

/**
 * Create a GameObject.
 */
GameObject::GameObject() :
        Object{},
        active{ true },
        tag{},
        _transform{},
        _renderer{},
        _scene{},
        transform{ _transform },
        renderer{ _renderer },
        scene{ _scene } {
    // create a transform for the game object
    AddComponent< Transform >();
}

/**
 * Create a GameObject with name.
 *
 * @param name the name
 */
GameObject::GameObject( std::string name ) :
        Object{ std::move( name ) },
        active{ true },
        tag{},
        _transform{},
        _renderer{},
        _scene{},
        transform{ _transform },
        renderer{ _renderer },
        scene{ _scene } {
    // create a transform for the game object
    AddComponent< Transform >();
}

/**
 * Copy from another GameObject.
 *
 * @param other the GameObject to copy from
 */
GameObject::GameObject( const GameObject& other ) :
        Object( other ),
        active{ other.active },
        tag{ other.tag },
        _transform{},
        _renderer{},
        _scene{},
        transform{ _transform },
        renderer{ _renderer },
        scene{ _scene } {
    // create a transform for the game object
    AddComponent< Transform >();
    _transform = other._transform;

    // copy component
    if( other.GetComponent< Renderer >() ) {
        AddComponent< Renderer >();
        _renderer = other._renderer;
    }

    // move to same scene
    if( other._scene ) {
        MoveToScene( *other._scene );
    }
}

/**
 * Destroy the GameObject.
 */
GameObject::~GameObject() {
    if( GetComponent< Transform >() ) {
        delete ( transform );
    }

    if( GetComponent< Renderer >() ) {
        delete ( renderer );
    }
}

/**
 * Assign the GameObject with another GameObject.
 *
 * @param other the GameObject to assign
 *
 * @return this GameObject
 */
GameObject& GameObject::operator=( const GameObject& other ) {
    if( this == &other ) {
        _transform = other._transform;

        active = other.active;
        tag = other.tag;
        _scene = other._scene;
    }

    return *this;
}

// Explicit instantiation
template Transform* GameObject::AddComponent< Transform >();

template Renderer* GameObject::AddComponent< Renderer >();

/**
 * Add a Component to the GameObject.
 *
 * @tparam T the component type
 *
 * @return the component added
 */
template< typename T >
T* GameObject::AddComponent() {
    if( typeid( T ) == typeid( Transform ) ) {
        _transform = ( Transform* ) new T( this );
        return ( T* ) transform;
    } else if( typeid( T ) == typeid( Renderer ) ) {
        _renderer = ( Renderer* ) new T( this );
        return ( T* ) renderer;
    }

    return nullptr;
}

// Explicit instantiation
template Transform* GameObject::GetComponent< Transform >() const;

template Renderer* GameObject::GetComponent< Renderer >() const;

/**
 * Get the Component attached to the GameObject, null if no Component attached.
 *
 * @tparam T the component type
 *
 * @return the component
 */
template< typename T >
T* GameObject::GetComponent() const {
    if( typeid( T ) == typeid( Transform ) ) {
        return ( T* ) transform;
    } else if( typeid( T ) == typeid( Renderer ) ) {
        return ( T* ) renderer;
    }

    return nullptr;
}

/**
 * Activates/Deactivates the GameObject.
 *
 * @param value active state
 */
void GameObject::SetActive( bool value ) {
    active = value;
}

/**
 * Move the GameObjec to a Scene.
 *
 * @param scene the scene
 */
void GameObject::MoveToScene( Scene& scene ) {
    // only move if the GameObject is root object
    if( !transform->root ) {
        _scene = &scene;
        _scene->AddRootGameObject( this );
    }
}
