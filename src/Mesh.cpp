//
// Mesh.cpp
//
// Created by Jietong Chen on 2/1/2019.
//

#include "Mesh.h"

Mesh::Mesh() :
        Object{ "Empty-Mesh" } {
}

void Mesh::AddPrimitive( Primitive&& primitive ) {
    primitive.mesh = this;
    primitives.emplace_back( primitive );
}

const std::vector< Primitive* >& Mesh::GetPrimitives() const {
    return primitives;
}

std::vector< Primitive* > Mesh::GetPrimitivesInWorldSpace() const {
    std::vector< Primitive* > primitivesInWorld( primitives );

    for( Primitive* p : primitivesInWorld ) {
        p->ToWorldSpace( renderer->localToWorldMatrix );
    }

    return primitivesInWorld;
}
