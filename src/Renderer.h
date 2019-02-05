//
// Renderer.h
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "Object.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"

class Renderer : public Object {

public:
    Renderer();

    Material& GetMaterial() const;

    Mesh& GetMesh() const;

public:

    bool enabled;

    Material material;
    Mesh mesh;

    float4x4 localToWorldMatrix;
    float4x4 worldToLocalMatrix;

protected:
    const GameObject* _gameObject;
}; // Renderer

#endif // RENDERER_H
