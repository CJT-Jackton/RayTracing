//
// GameObject.cpp
//
// The implementation of GameObject.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracer::GameObject;
using RayTracer::Component;
using RayTracer::Transform;
using RayTracer::Renderer;
using RayTracer::Light;
using RayTracer::Scene;

/**
 * Create a GameObject.
 */
GameObject::GameObject() :
        Object{},
        active{ true },
        tag{},
        _transform{},
        _renderer{},
        components{},
        _scene{},
        transform{ _transform },
//        renderer{ _renderer },
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
        components{},
        _scene{},
        transform{ _transform },
//        renderer{ _renderer },
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
        components{},
        _scene{ other._scene },
        transform{ _transform },
//        renderer{ _renderer },
        scene{ _scene } {
    // create a transform for the game object
    AddComponent< Transform >();
    _transform = other._transform;

    // copy component
//    if( other.GetComponent< Renderer >() ) {
//        AddComponent< Renderer >();
//        _renderer = other._renderer;
//    }

    for( Component* component : other.components ) {
        if( Renderer* renderer = dynamic_cast<Renderer*>(component) ) {
            Renderer* newRenderer = AddComponent< Renderer >();
            *newRenderer = *renderer;
        } else if( Light* light = dynamic_cast<Light*>(component) ) {
            Light* newLight = AddComponent< Light >();
            *newLight = *light;
        }
    }

    // move to same scene
//    if( other._scene ) {
//        MoveToScene( *other._scene );
//    }
}

/**
 * Destroy the GameObject.
 */
GameObject::~GameObject() {
    if( GetComponent< Transform >() ) {
        delete ( transform );
    }

    for( Component* component : components ) {
        delete ( component );
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

template Light* GameObject::AddComponent< Light >();

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
        Renderer* renderer = ( Renderer* ) new T( this );
        components.emplace_back( renderer );
        return ( T* ) renderer;
    } else if( typeid( T ) == typeid( Light ) ) {
        Light* light = ( Light* ) new T( this );
        components.emplace_back( light );
        return ( T* ) light;
    }

    return nullptr;
}

// Explicit instantiation
template Transform* GameObject::GetComponent< Transform >() const;

template Renderer* GameObject::GetComponent< Renderer >() const;

template Light* GameObject::GetComponent< Light >() const;

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
        for( Component* component : components ) {
            if( Renderer* renderer = dynamic_cast<Renderer*>(component) ) {
                return ( T* ) renderer;
            }
        }
    } else if( typeid( T ) == typeid( Light ) ) {
        for( Component* component : components ) {
            if( Light* light = dynamic_cast<Light*>(component) ) {
                return ( T* ) light;
            }
        }
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

/**
 * Determine whether the GameObject is active.
 *
 * @return true if the GameObject is active, false if not
 */
GameObject::operator bool() const {
    return active;
}
