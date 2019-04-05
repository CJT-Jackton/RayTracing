//
// Phong.cpp
//
// The implementation of Phong shader.
//
// Created by Jietong Chen on 2/18/2019.
//

#include "../pch.h"

using RayTracer::Phong;
using RayTracer::Shader;

/**
 * Default constructor.
 */
Phong::Phong() :
        Shader{ "Phong" },
        view{},
        normal{},
        light{},
        uv{},
        lightPositon{},
        lightColor{},
        shadow{},
        mainColor{},
        specularColor{},
        mainTexture{},
        mainTextureScale{ float2( 1.0f ) },
        mainTextureOffset{ float2( 0.0f ) },
        kd{ 1.0f },
        ks{ 1.0f },
        shininess{ 0.078125f } {
}

/**
 * Copy the Phong shader from another Phong shader.
 *
 * @param other the Phong shader to copy from
 */
Phong::Phong( const Phong& other ) :
        Shader{ "Phong" },
        view{ other.view },
        normal{ other.normal },
        light{ other.light },
        uv{ other.uv },
        lightPositon{ other.lightPositon },
        lightColor{ other.lightColor },
        shadow{ other.shadow },
        mainColor{ other.mainColor },
        specularColor{ other.specularColor },
        mainTexture{ other.mainTexture },
        mainTextureScale{ other.mainTextureScale },
        mainTextureOffset{ other.mainTextureOffset },
        kd{ other.kd },
        ks{ other.ks },
        shininess{ other.shininess } {
}

/**
 * Assign the Phong shader with another Phong shader.
 *
 * @param other the Phong to assign
 *
 * @return this Phong shader
 */
Phong& Phong::operator=( const Phong& other ) {
    if( this != &other ) {
        view = other.view;
        normal = other.normal;
        light = other.light;
        uv = other.uv;
        lightPositon = other.lightPositon;
        lightColor = other.lightColor;
        shadow = other.shadow;
        mainColor = other.mainColor;
        specularColor = other.specularColor;
        mainTexture = other.mainTexture;
        mainTextureScale = other.mainTextureScale;
        mainTextureOffset = other.mainTextureOffset;
        kd = other.kd;
        ks = other.ks;
        shininess = other.shininess;
    }

    return *this;
}

/**
 * Use the shader program shade a point.
 *
 * @return the color of the point
 */
float4 Phong::Shading() const {
    float3 albedo = mainColor;

    if( mainTexture ) {
        // use texture color if has texture
        albedo = Texture::Sample( mainTexture, uv * mainTextureScale +
                                               mainTextureOffset ).xyz;
    }

    float cos = saturate( dot( light, normal ) );

    float3 diffuse = kd * albedo * cos * lightColor;

    cos = saturate( dot( reflect( -light, normal ), view ) );

    float3 specular =
            ks * specularColor * std::pow( cos, shininess * 32 ) * lightColor;

    float3 finalColor = shadow * ( diffuse + specular );

    return float4( finalColor, 1.0f );
}

/**
 * The type of the shader program.
 *
 * @return the shader type
 */
Shader::ShaderType Phong::Type() const {
    return Shader::Phong;
}
