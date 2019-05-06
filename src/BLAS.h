//
// BLAS.h
//
// Created by Jietong Chen on 2019/4/9.
//

#ifndef BLAS_H
#define BLAS_H

#include "Primitive.h"
#include "RaycastHit.h"

namespace RayTracer {
    class BLAS {
    private:
        enum BinaryTreeNodeType {
            X, Y, Z, Leaf, Unknown
        };

        struct BinaryTreeNode {
            BinaryTreeNodeType type = Unknown;
            float value = 0.0f;

            BinaryTreeNode* left = nullptr;
            BinaryTreeNode* right = nullptr;

            std::vector< Primitive* > data = {};
        };

    public:
        BLAS();

        ~BLAS();

        void AddPrimitives( std::vector< Primitive > primitives );

        bool AnyHit( RaycastHit& hit );

        void Generate();

    private:
        BinaryTreeNode*
        GenerateNode( std::vector< Primitive* > primitives, Bounds bound,
                      BinaryTreeNodeType type );

        float GetSubdivisonPlane( const Bounds& bound,
                                  BinaryTreeNodeType type ) const;

        inline bool Terminate( const std::vector< Primitive* > primitives,
                               const Bounds& bound ) const;

    private:

        std::vector< Primitive > primitives;

        std::vector< Bounds > bounds;

        BinaryTreeNode* root;

        std::vector< BinaryTreeNode > nodes;

        unsigned int subdivideThreshold;
    };
}

#endif // BLAS_H
