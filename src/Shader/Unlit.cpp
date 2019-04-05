//
// Unlit.cpp
//
// The implementation of unlit shader.
//
// Created by Jietong Chen on 2019/3/22.
//

#include "../pch.h"

using RayTracer::Unlit;
using RayTracer::Shader;

/**
 * Default constructor.
 */
Unlit::Unlit() :
        Shader{ "Unlit" },
        mainColor{ float4( 1.0f ) } {
}

/**
 * Copy the unlit shader from another unlit shader.
 *
 * @param other the unlit shader to copy from
 */
Unlit::Unlit( const Unlit& other ) :
        Shader{ "Unlit" },
        mainColor{ other.mainColor } {
}

/**
 * Assign the unlit shader with another unlit shader.
 *
 * @param other the unlit shader to assign
 *
 * @return this unlit shader
 */
Unlit& Unlit::operator=( const Unlit& other ) {
    if( this != &other ) {
        mainColor = other.mainColor;
    }

    return *this;
}

/**
 * Use the shader program shade a point.
 *
 * @return the color of the point
 */
float4 Unlit::Shading() const {
    return mainColor;
}

float4 Unlit::DirectShading( float3* lightPosition,
                             float4* lightColor ) const {
    return float4( 0.0f );
}

float4 Unlit::IndirectShading() const {
    return mainColor;
}

/**
 * The type of the shader program.
 *
 * @return the shader type
 */
Shader::ShaderType Unlit::Type() const {
    return Shader::Unlit;
}
