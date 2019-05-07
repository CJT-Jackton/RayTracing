//
// ToneMapping-ACESFilm.cpp
//
// Created by Jietong Chen on 2019/5/6.
//

#include "../pch.h"

using RayTracer::ToneMapping_ACESFilm;
using RayTracer::Shader;

ToneMapping_ACESFilm::ToneMapping_ACESFilm() :
        Shader{ "ToneMapping-ACESFilm" },
        color{ 0.0, 0.0, 0.0, 0.0 } {
}

ToneMapping_ACESFilm::ToneMapping_ACESFilm(
        const ToneMapping_ACESFilm& other ) :
        Shader{ "ToneMapping-ACESFilm" },
        color{ other.color } {
}

ToneMapping_ACESFilm& ToneMapping_ACESFilm::operator=(
        const ToneMapping_ACESFilm& other ) {
    if( this != &other ) {
        color = other.color;
    }

    return *this;
}

float4 ToneMapping_ACESFilm::Shading() const {
    float3 x = color.rgb;
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return float4(
            saturate( ( x * ( a * x + b ) ) / ( x * ( c * x + d ) + e ) ),
            1.0f );
}

float4 ToneMapping_ACESFilm::DirectShading( float3* lightPosition,
                                            float4* lightColor ) const {
    return Shading();
}

float4 ToneMapping_ACESFilm::IndirectShading() const {
    return Shading();
}

Shader::ShaderType ToneMapping_ACESFilm::Type() const {
    return Shader::ToneMapping_ACESFilm;
}
