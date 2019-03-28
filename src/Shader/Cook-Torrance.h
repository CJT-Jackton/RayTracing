//
// Cook-Torrance.h
//
// Created by Jietong Chen on 2019/3/22.
//

#ifndef COOK_TORRANCE_H
#define COOK_TORRANCE_H

#include "Shader.h"

namespace RayTracer {
    class Cook_Torrance : public Shader {
    public:
        Cook_Torrance();

        Cook_Torrance( const Cook_Torrance& other );

        Cook_Torrance& operator=( const Cook_Torrance& other );

        float4 Shading() const;

        ShaderType Type() const;

    private:
        float NormalDistributionGGX( float3 normal, float3 half,
                                     float smoothness ) const;

        float GeometrySchlickGGX( float cos, float k ) const;

        float GeometrySmith( float3 normal, float3 view, float3 light,
                             float k ) const;

        float3 FresnelSchlick( float cos, float3 F0 ) const;

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

        /** the texture */
        Texture* mainTexture;

        /** the texture offset */
        float2 mainTextureOffset;

        /** the texture scale */
        float2 mainTextureScale;

        float metallic;

        float smoothness;

        float3 irradiance;

        float3 reflection;

    }; // Cook_Torrance
} // RayTracer

#endif // COOK_TORRANCE_H
