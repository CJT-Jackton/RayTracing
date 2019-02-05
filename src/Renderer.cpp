//
// Renderer.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "Renderer.h"

Renderer::Renderer() :
        enabled{ true },
        material{},
        localToWorldMatrix{},
        worldToLocalMatrix{} {
}

Material& Renderer::GetMaterial() const {
    return material;
}

Mesh& Renderer::GetMesh() const {
    return mesh;
}
