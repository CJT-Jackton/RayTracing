//
// BlinnPhong.h
//
// The Blinn-Phong shading shader. This shader use Blinn-Phong shading model.
//
// Created by Jietong Chen on 2/19/2019.
//

#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "pch.h"

namespace RayTracer {
    /**
     * The Blinn-Phong shading shader.
     */
    class BlinnPhong : public Shader {
    public:
        /**
         * Default constructor.
         */
        BlinnPhong();

        /**
         * Copy the Blinn-Phong shader from another Blinn-Phong shader.
         *
         * @param other the Blinn-Phong shader to copy from
         */
        BlinnPhong( const BlinnPhong& other );

        /**
         * Assign the Blinn-Phong shader with another Blinn-Phong shader.
         *
         * @param other the Blinn-Phong to assign
         *
         * @return this Blinn-Phong shader
         */
        BlinnPhong& operator=( const BlinnPhong& other );

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

        /** diffuse reflection factor */
        float kd;

        /** specular reflection factor */
        float ks;

        /** shininess coefficient */
        float shininess;

    }; // BlinnPhong
} // RayTracer

#endif // BLINNPHONG_H
