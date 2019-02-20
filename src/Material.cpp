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
        mainTexture{ nullptr } {
    if( shader->Type() == Shader::Phong ) {
        Phong* pshader = ( Phong* ) shader;
        pshader->mainColor = color;
        pshader->specularColor = color;
        pshader->mainTexture = mainTexture;
    } else if( shader->Type() == Shader::BlinnPhong ) {
        BlinnPhong* bshader = ( BlinnPhong* ) shader;

        bshader->mainColor = color;
        bshader->specularColor = color;
        bshader->mainTexture = mainTexture;
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
    if( type != shader->Type() ) {
        delete shader;

        if( type == Shader::Phong ) {
            shader = new Phong();
            Phong* pshader = ( Phong* ) shader;

            pshader->mainColor = color;
            pshader->specularColor = color;
            pshader->mainTexture = mainTexture;
        } else if( type == Shader::BlinnPhong ) {
            shader = new BlinnPhong();
            BlinnPhong* bshader = ( BlinnPhong* ) shader;

            bshader->mainColor = color;
            bshader->specularColor = color;
            bshader->mainTexture = mainTexture;
        }
    }
}
