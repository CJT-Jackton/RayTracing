//
// Phong.h
//
// The Phong shading shader. This shader use Phong reflection model.
//
// Created by Jietong Chen on 2/18/2019.
//

#ifndef PHONG_H
#define PHONG_H

#include "../pch.h"

namespace RayTracer {
    /**
     * The Phong shading shader.
     */
    class Phong : public Shader {
    public:
        /**
         * Default constructor.
         */
        Phong();

        /**
         * Copy the Phong shader from another Phong shader.
         *
         * @param other the Phong shader to copy from
         */
        Phong( const Phong& other );

        /**
         * Assign the Phong shader with another Phong shader.
         *
         * @param other the Phong to assign
         *
         * @return this Phong shader
         */
        Phong& operator=( const Phong& other );

        /**
         * Use the shader program shade a point.
         *
         * @return the color of the point
         */
        float4 Shading() const override;

        /**
         * The type of the shader program.
         *
         * @return the shader type
         */
        ShaderType Type() const override;

    public:
        /** the view vector */
        float3 view;

        /** the normal of the surface */
        float3 normal;

        /** the light vector from surface pointing to light source */
        float3 light;

        /** the texture coordinate */
        float2 uv;

        /** the light position */
        float3 lightPositon;

        /** the light color */
        float4 lightColor;

        /** the albedo color */
        float4 mainColor;

        /** the specular highlight color */
        float4 specularColor;

        /** the texture */
        Texture* mainTexture;

        /** the texture offset */
        float2 mainTextureOffset;

        /** the texture scale */
        float2 mainTextureScale;

        /** diffuse reflection factor */
        float kd;

        /** specular reflection factor */
        float ks;

        /** shininess coefficient */
        float shininess;

    }; // Phong
} // RayTracer

#endif // PHONG_H
