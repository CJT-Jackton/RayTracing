//
// Renderer.h
//
// Component of a GameObject that render the mesh.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "pch.h"

namespace RayTracing {
    /**
     * Component of a GameObject that render the mesh.
     */
    class Renderer : public Component {
    public:
        /**
         * Create a Renderer attached to a GameObject.
         *
         * @param gameObject the GameObject to attach
         */
        Renderer( GameObject* gameObject );

        /**
         *
         *
         * @param other
         */
        Renderer( const Renderer& other );

        /**
         * Destroy the Renderer.
         */
        ~Renderer() override;

        Renderer& operator=( const Renderer& other );

        /**
         * Get the Material assigned to the Renderer.
         *
         * @return the material assigned to the Renderer
         */
        Material* GetMaterial() const;

        /**
         * Get the Mesh assigned to the Renderer.
         *
         * @return the Mesh assigned to the Renderer
         */
        Mesh* GetMesh() const;

        /**
         *
         *
         * @return
         */
        std::vector< Primitive* > GetPrimitives() const;

        /**
         * Determine whether the Renderer enabled or not.
         *
         * @return true if the Renderer is enabled, false if not
         */
        operator bool() const override;

    private:
        /** the local to world matrix */
        float4x4 _localToWorldMatrix;

        /** the world to local matrix */
        float4x4 _worldToLocalMatrix;

    public:
        /** the enable state */
        bool enabled;

        /** the material assigned */
        Material* material;

        /** the mesh assigned */
        Mesh* mesh;

        /** the local to world matrix */
        const float4x4& localToWorldMatrix;

        /** the world to local matrix */
        const float4x4& worldToLocalMatrix;

    }; // Renderer
} // RayTracing

#endif // RENDERER_H
