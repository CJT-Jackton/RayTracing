//
// Scene.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "Scene.h"

Scene::Scene() :
        name{ "SampleScene" } {
}

Scene::Scene( std::string name ) :
        name{ std::move( name ) } {
}

Scene::~Scene() {
    rootGameObjects.clear();
}

std::vector< GameObject* > Scene::GetRootGameObjects() const {
    return rootGameObjects;
}
