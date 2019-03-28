//
// Shader.cpp
//
// The implementation of Shader.
//
// Created by Jietong Chen on 2/18/2019.
//

#include "../pch.h"

using RayTracer::Shader;
using RayTracer::Phong;

/**
 * Constructor of the shader program.
 *
 * @param name the name
 */
Shader::Shader( std::string name ) :
        Object{ std::move( name ) } {
}
