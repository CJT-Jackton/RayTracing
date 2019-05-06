//
// BLAS.cpp
//
// Created by Jietong Chen on 2019/4/10.
//

#include "pch.h"

using RayTracer::BLAS;
using RayTracer::Bounds;
using RayTracer::Primitive;

BLAS::BLAS() :
        primitives{},
        bounds{},
        root{ nullptr },
        nodes{},
        subdivideThreshold{ 4 } {
}

void BLAS::Generate() {
    Bounds bound( float3( 0.0f ), float3( 0.0f ) );

    std::vector< Primitive* > primitivePointers;

    for( const Primitive& primitive : primitives ) {
        //primitivePointers.emplace_back( &primitive );
    }

    root = GenerateNode( primitivePointers, bound, X );
}

BLAS::BinaryTreeNode* BLAS::GenerateNode( std::vector< Primitive* > primitives,
                                          Bounds bound,
                                          BinaryTreeNodeType type ) {
    if( Terminate( primitives, bound ) ) {
        BLAS::BinaryTreeNode node;

        //node.data = primitives;
        //node.type = Leaf;

        //nodes.emplace_back( node );

        //return &nodes.back();
        return nullptr;
    }

    float separate = GetSubdivisonPlane( bound, type );

    //Bounds leftBound();
    //Bounds rightBound();

    return nullptr;
}

float
BLAS::GetSubdivisonPlane( const Bounds& bound, BinaryTreeNodeType type ) const {
    if( type == X ) {
        return ( bound.max.x + bound.min.x ) / 2.0f;
    } else if( type == Y ) {
        return ( bound.max.y + bound.min.y ) / 2.0f;
    } else if( type == Z ) {
        return ( bound.max.z + bound.min.z ) / 2.0f;
    }

    return 0.0f;
}

inline bool BLAS::Terminate( const std::vector< Primitive* > primitives,
                             const Bounds& bound ) const {
    if( primitives.size() <= subdivideThreshold ) {
        return true;
    }

    return false;
}
