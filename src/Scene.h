//
// Scene.h
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "GameObject.h"

class Scene {
public:
    Scene();

    Scene( std::string name );

    ~Scene();

    std::vector< GameObject* > GetRootGameObjects() const;

private:
    std::vector< GameObject* > rootGameObjects;

    int rootCount;

    std::string name;
}; // Scene

#endif // SCENE_H
