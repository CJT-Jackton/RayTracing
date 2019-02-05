//
// Mesh.h
//
// Created by Jietong Chen on 1/31/2019.
//


#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Object.h"
#include "Primitive.h"
#include "Renderer.h"

class Mesh : public Object {
public:
    Mesh();

    void AddPrimitive( Primitive&& primitive );

    const std::vector< Primitive* >& GetPrimitives() const;

    std::vector< Primitive* > GetPrimitivesInWorldSpace() const;

public:
    std::vector< Primitive* > primitives;

    Renderer* renderer;
};

#endif // MESH_H
