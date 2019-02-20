//
// Shader.h
//
// Shader program use for rendering.
//
// Created by Jietong Chen on 2/18/2019.
//

#ifndef SHADER_H
#define SHADER_H

#include "pch.h"

namespace RayTracer {
    /**
     * Shader program use for rendering.
     */
    class Shader : public Object {
    public:
        /**
         * The type of shader.
         */
        enum ShaderType {
            Phong,
            BlinnPhong
        };

        /**
         * Use the shader program shade a point.
         *
         * @return the color of the point
         */
        virtual float4 Shading() const = 0;

        /**
         * The type of the shader program.
         *
         * @return the shader type
         */
        virtual ShaderType Type() const = 0;

    protected:
        /**
         * Constructor of the shader program.
         *
         * @param name the name
         */
        Shader( std::string name );

        /** only Material has access to shader */
        friend class Material;

    }; // Shader
} // RayTracer

#endif // SHADER_H
