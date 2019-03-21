//
// Scene.cpp
//
// The implementation of Scene.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Scene;
using RayTracer::GameObject;

/**
 * Create a empty scene.
 */
Scene::Scene() :
        name{ "SampleScene" },
        renderSettings{},
        rootGameObjects{},
        rootCount{ rootGameObjects.size() } {
}

/**
 * Create a empty scene with name.
 *
 * @param name the name
 */
Scene::Scene( std::string name ) :
        name{ std::move( name ) },
        renderSettings{},
        rootGameObjects{},
        rootCount{ rootGameObjects.size() } {
}

/**
 * Destroy the scene.
 */
Scene::~Scene() {
    rootGameObjects.clear();
}

/**
 * Add a GameObject into the scene.
 *
 * @param gameObject the GameObject
 */
void Scene::AddRootGameObject( GameObject* gameObject ) {
    rootGameObjects.emplace_back( gameObject );
}

/**
 * Get the all the GameObject at the root.
 *
 * @return the array of root GameObject
 */
std::vector< GameObject* > Scene::GetRootGameObjects() const {
    return rootGameObjects;
}
