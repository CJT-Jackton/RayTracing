//
// Renderer.cpp
//
// The implementation of Renderer.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracing::Renderer;
using RayTracing::GameObject;
using RayTracing::Component;
using RayTracing::Material;
using RayTracing::Mesh;
using RayTracing::Primitive;

/**
 * Create a Renderer attached to a GameObject.
 *
 * @param gameObject the GameObject to attach
 */
Renderer::Renderer( GameObject* gameObject ) :
        Component( gameObject, "Renderer" ),
        enabled{ true },
        material{ new Material() },
        mesh{},
        _localToWorldMatrix{},
        _worldToLocalMatrix{},
        localToWorldMatrix{ _localToWorldMatrix },
        worldToLocalMatrix{ _worldToLocalMatrix } {
    if( gameObject ) {
        _localToWorldMatrix = gameObject->transform->localToWorldMatrix;
        _worldToLocalMatrix = gameObject->transform->worldToLocalMatrix;
    }
}

/**
 *
 *
 * @param other
 */
Renderer::Renderer( const Renderer& other ) :
        Component( other.gameObject, "Renderer" ),
        enabled{ other.enabled },
        material{ other.material },
        mesh{ other.mesh },
        _localToWorldMatrix{ gameObject->transform->localToWorldMatrix },
        _worldToLocalMatrix{ gameObject->transform->worldToLocalMatrix },
        localToWorldMatrix{ _localToWorldMatrix },
        worldToLocalMatrix{ _worldToLocalMatrix } {
    if( gameObject ) {
        _localToWorldMatrix = gameObject->transform->localToWorldMatrix;
        _worldToLocalMatrix = gameObject->transform->worldToLocalMatrix;
    }
}

/**
 * Destroy the Renderer.
 */
Renderer::~Renderer() {
    if( material ) {
        delete ( material );
    }

    if( mesh ) {
        delete ( mesh );
    }
}

Renderer& Renderer::operator=( const Renderer& other ) {
    if( this != &other ) {
        Component::operator=( other );

        enabled = other.enabled;
        material = other.material;
        mesh = other.mesh;
    }

    return *this;
}

/**
 * Get the Material assigned to the Renderer.
 *
 * @return the material assigned to the Renderer
 */
Material* Renderer::GetMaterial() const {
    return material;
}

/**
 * Get the Mesh assigned to the Renderer.
 *
 * @return the Mesh assigned to the Renderer
 */
Mesh* Renderer::GetMesh() const {
    return mesh;
}

std::vector< Primitive* > Renderer::GetPrimitives() const {
    std::vector< Primitive* > primitives;

    for( const std::unique_ptr< Primitive >& p : mesh->GetPrimitives() ) {
        primitives.emplace_back( p->ToWorldSpace( _localToWorldMatrix ) );
    }

    return primitives;
}

/**
 * Determine whether the Renderer enabled or not.
 *
 * @return true if the Renderer is enabled, false if not
 */
Renderer::operator bool() const {
    return enabled;
}
