//
// Scene.h
//
// The scene.
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef SCENE_H
#define SCENE_H

#include "pch.h"

namespace RayTracer {
    /**
     * The scene.
     */
    class Scene {
    public:
        /**
         * Create a empty scene.
         */
        Scene();

        /**
         * Create a empty scene with name.
         *
         * @param name the name
         */
        Scene( std::string name );

        /**
         * Destroy the scene.
         */
        ~Scene();

        /**
         * Add a GameObject into the scene.
         *
         * @param gameObject the GameObject
         */
        void AddRootGameObject( GameObject* gameObject );

        /**
         * Get the all the GameObject at the root.
         *
         * @return the array of root GameObject
         */
        std::vector< GameObject* > GetRootGameObjects() const;

    private:
        /** the root GameObject */
        std::vector< GameObject* > rootGameObjects;

        /** the number root GameObject */
        const unsigned int& rootCount;

    public:
        /** the name of the scene */
        const std::string name;

    }; // Scene
} // RayTracer

#endif // SCENE_H
