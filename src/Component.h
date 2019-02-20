//
// Component.h
//
// Base class for everything attached to GameObjects. A component is always
// attached to a game object.
//
// Created by Jietong Chen on 2/5/2019.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "pch.h"

namespace RayTracer {
    /**
     * Base class for everything attached to GameObjects.
     */
    class Component : public Object {
    public:
        /**
         * Create a Component attached to a GameObject.
         *
         * @param gameObject the GameObject to attach
         */
        Component( GameObject* gameObject );

        /**
         * Create a Component with name attached to a GameObject.
         *
         * @param gameObject the GameObject to attach
         * @param name the name
         */
        Component( GameObject* gameObject, std::string name );

        Component( const Component& other );

        Component& operator=( const Component& other );

    protected:
        /** the GameObject attached to */
        GameObject* _gameObject;

    public:
        /** the GameObject attached to */
        GameObject* const& gameObject;
    }; // Component
} // RayTracer

#endif // COMPONENT_H
