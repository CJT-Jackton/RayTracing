//
// GameObject.h
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object.h"
#include "Renderer.h"
#include "Scene.h"
#include "Transform.h"

class GameObject : public Object {
public:
    GameObject();

    GameObject( std::string name );

    void SetActive( bool value );

    void MoveToScene( Scene& scene );

public:
    Transform transform;

    Renderer renderer;

    bool active;

    std::string tag;

    /** Scene that the GameObject is part of */
    Scene* scene;

}; // GameObject

#endif // GAMEOBJECT_H
