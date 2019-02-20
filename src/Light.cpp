//
// Light.cpp
//
// The implementation of Light.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Light;
using RayTracer::GameObject;

/**
 * Create a Light attached to a GameObject.
 *
 * @param gameObject the GameObject to attach
 */
Light::Light( GameObject* gameObject ) :
        Component{ gameObject },
        type{ LightType::Directional },
        color{ 1.0f, 1.0f, 1.0f, 1.0f },
        intensity{ 1.0f } {
}

/**
 * Create a Light attached to a GameObject with given name.
 *
 * @param gameObject the GameObject to attach
 * @param name the name
 */
Light::Light( GameObject* gameObject, std::string name ) :
        Component{ gameObject, std::move( name ) },
        type{ LightType::Directional },
        color{ 1.0f, 0.9568627f, 0.8392157f, 1.0f },
        intensity{ 1.0f } {
}

/**
 * Assign the Light with another Light.
 *
 * @param other the Light to assign
 *
 * @return this Light
 */
Light& Light::operator=( const Light& other ) {
    if( this != &other ) {
        type = other.type;
        color = other.color;
        intensity = other.intensity;
    }

    return *this;
}

/**
 * Calculate the shadow ray of a point. Shadow ray is a ray from a
 * given point pointing to the light source.
 *
 * @param point the point
 *
 * @return the shadow ray
 */
RayTracer::Ray Light::GetShadowRay( float3 point ) const {
    if( type == LightType::Directional ) {
        return Ray( point, -gameObject->transform->forward );
    } else if( type == LightType::Point ) {
        return Ray( point, gameObject->transform->positon - point );
    } else if( type == LightType::Spot ) {
        return Ray( point, gameObject->transform->positon - point );
    }

    return Ray( float3(), float3() );
}
