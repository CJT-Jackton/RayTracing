//
// Material.cpp
//
// The implementation of Material.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracer::Material;
using RayTracer::Shader;
using RayTracer::Phong;
using RayTracer::BlinnPhong;

/**
 * Create a Material.
 *
 * @param shader the shader used by the material
 */
Material::Material( Shader* shader ) :
        Object{ "Default-Material" },
        shader{ shader },
        color{ 0.8f, 0.8f, 0.8f, 1.0f },
        mainTexture{ nullptr },
        mainTextureOffset{ float2( 0.0f ) },
        mainTextureScale{ float2( 1.0f ) } {

    if( shader->Type() == Shader::Phong ) {
        Phong* pshader = ( Phong* ) shader;

        pshader->mainColor = color;
        pshader->specularColor = color;
        pshader->mainTexture = mainTexture;
        pshader->mainTextureOffset = mainTextureOffset;
        pshader->mainTextureScale = mainTextureScale;

    } else if( shader->Type() == Shader::BlinnPhong ) {
        BlinnPhong* bshader = ( BlinnPhong* ) shader;

        bshader->mainColor = color;
        bshader->specularColor = color;
        bshader->mainTexture = mainTexture;
        bshader->mainTextureOffset = mainTextureOffset;
        bshader->mainTextureScale = mainTextureScale;

    } else if( shader->Type() == Shader::Cook_Torrance ) {
        Cook_Torrance* cshader = ( Cook_Torrance* ) shader;

        cshader->mainColor = color;
        cshader->mainTexture = mainTexture;
        cshader->mainTextureOffset = mainTextureOffset;
        cshader->mainTextureScale = mainTextureScale;

    } else if( shader->Type() == Shader::Unlit ) {
        Unlit* ushader = ( Unlit* ) shader;

        ushader->mainColor = color;
    }
}

/**
 * Delete the Material.
 */
Material::~Material() {
    delete shader;
}

/**
 * Use another type of shader.
 *
 * @param type the type of shader
 */
void Material::UseShader( Shader::ShaderType type ) {
    //if( type != shader->Type() ) {
    delete shader;

    if( type == Shader::Phong ) {
        shader = new Phong();
        Phong* pshader = ( Phong* ) shader;

        pshader->mainColor = color;
        pshader->specularColor = color;
        pshader->mainTexture = mainTexture;
        pshader->mainTextureOffset = mainTextureOffset;
        pshader->mainTextureScale = mainTextureScale;

    } else if( type == Shader::BlinnPhong ) {
        shader = new BlinnPhong();
        BlinnPhong* bshader = ( BlinnPhong* ) shader;

        bshader->mainColor = color;
        bshader->specularColor = color;
        bshader->mainTexture = mainTexture;
        bshader->mainTextureOffset = mainTextureOffset;
        bshader->mainTextureScale = mainTextureScale;

    } else if( type == Shader::Cook_Torrance ) {
        shader = new Cook_Torrance();
        Cook_Torrance* cshader = ( Cook_Torrance* ) shader;

        cshader->mainColor = color;
        cshader->mainTexture = mainTexture;
        cshader->mainTextureOffset = mainTextureOffset;
        cshader->mainTextureScale = mainTextureScale;

    } else if( type == Shader::Skybox_Procedural ) {
        shader = new Skybox_Procedural();

    } else if( type == Shader::Unlit ) {
        shader = new Unlit();
        Unlit* ushader = ( Unlit* ) shader;

        ushader->mainColor = color;
    }
    //}
}
