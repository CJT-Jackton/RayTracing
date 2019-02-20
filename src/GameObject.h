//
// GameObject.h
//
// Base class for all entities in the Scenes.
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "pch.h"

namespace RayTracer {
    /**
     * Base class for all entities in the Scenes.
     */
    class GameObject : public Object {
    public:
        /**
         * Create a GameObject.
         */
        GameObject();

        /**
         * Create a GameObject with name.
         *
         * @param name the name
         */
        GameObject( std::string name );

        /**
         * Copy from another GameObject.
         *
         * @param other the GameObject to copy from
         */
        GameObject( const GameObject& other );

        /**
         * Destroy the GameObject.
         */
        ~GameObject();

        /**
         * Assign the GameObject with another GameObject.
         *
         * @param other the GameObject to assign
         *
         * @return this GameObject
         */
        GameObject& operator=( const GameObject& other );

        /**
         * Add a Component to the GameObject.
         *
         * @tparam T the component type
         *
         * @return the component added
         */
        template< typename T >
        T* AddComponent();

        /**
         * Get the Component attached to the GameObject, null if no
         * Component attached.
         *
         * @tparam T the component type
         *
         * @return the component
         */
        template< typename T >
        T* GetComponent() const;

        /**
         * Activates/Deactivates the GameObject.
         *
         * @param value active state
         */
        void SetActive( bool value );

        /**
         * Move the GameObjec to a Scene.
         *
         * @param scene the scene
         */
        void MoveToScene( Scene& scene );

        /**
         * Determine whether the GameObject is active.
         *
         * @return true if the GameObject is active, false if not
         */
        operator bool() const override;

    protected:
        /** the transform of the GameObject */
        Transform* _transform;

        /** the renderer of the GameObject */
        Renderer* _renderer;

        std::vector< Component* > components;

        /** scene that the GameObject is part of */
        Scene* _scene;

    public:
        /** the active state */
        bool active;

        /** the tag */
        std::string tag;

        /** the transform of the GameObject */
        Transform* const& transform;

        /** the renderer of the GameObject */
//        Renderer* const& renderer;

        /** scene that the GameObject is part of */
        Scene* const& scene;

    }; // GameObject
} // RayTracer

#endif // GAMEOBJECT_H
