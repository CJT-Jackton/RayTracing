//
// BlinnPhong.cpp
//
// The implementation of Blinn-Phong shader.
//
// Created by Jietong Chen on 2/19/2019.
//

#include "pch.h"

using RayTracer::BlinnPhong;
using RayTracer::Shader;

/**
 * Default constructor.
 */
BlinnPhong::BlinnPhong() :
        Shader{ "Blinn-Phong" },
        view{},
        normal{},
        light{},
        uv{},
        lightPositon{},
        lightColor{},
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
 * Copy the Blinn-Phong shader from another Blinn-Phong shader.
 *
 * @param other the Blinn-Phong shader to copy from
 */
BlinnPhong::BlinnPhong( const BlinnPhong& other ) :
        Shader{ "Blinn-Phong" },
        view{ other.view },
        normal{ other.normal },
        light{ other.light },
        uv{ other.uv },
        lightPositon{ other.lightPositon },
        lightColor{ other.lightColor },
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
 * Assign the Blinn-Phong shader with another Blinn-Phong shader.
 *
 * @param other the Blinn-Phong to assign
 *
 * @return this Blinn-Phong shader
 */
BlinnPhong& BlinnPhong::operator=( const BlinnPhong& other ) {
    if( this != &other ) {
        view = other.view;
        normal = other.normal;
        light = other.light;
        uv = other.uv;
        lightPositon = other.lightPositon;
        lightColor = other.lightColor;
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
float4 BlinnPhong::Shading() const {
    float4 albedo = mainColor;

    if( mainTexture ) {
        // use texture color if has texture
        albedo = Texture::Sample( mainTexture,
                                  uv * mainTextureScale + mainTextureOffset );
    }

    float cos = saturate( dot( light, normal ) );

    float4 diffuse = kd * albedo * cos * lightColor;

    // the half way vector
    float3 half = normalize( light + view );
    cos = saturate( dot( normal, half ) );

    float4 specular =
            ks * specularColor * std::pow( cos, shininess * 64 ) * lightColor;

    return diffuse + specular;
}

/**
 * The type of the shader program.
 *
 * @return the shader type
 */
Shader::ShaderType BlinnPhong::Type() const {
    return Shader::BlinnPhong;
}
