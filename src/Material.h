//
// Material.h
//
// The material class.
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "pch.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"

namespace RayTracer {
    /**
     * The material class.
     */
    class Material : public Object {
    public:
        /**
         * Create a Material.
         *
         * @param shader the shader used by the material
         */
        Material( Shader* shader );

        /**
         * Delete the Material.
         */
        ~Material();

        /**
         * Use another type of shader.
         *
         * @param type the type of shader
         */
        void UseShader( Shader::ShaderType type );

    public:
        /** the shader used by the material */
        Shader* shader;

        /** the color */
        float4 color;

        /** the texture used by the material */
        Texture* mainTexture;

        /** the texture offset of the main texture */
        float2 mainTextureOffset;

        /** the texture scale of the main texture */
        float2 mainTextureScale;
    }; // Material
} // RayTracer

#endif // MATERIAL_H
