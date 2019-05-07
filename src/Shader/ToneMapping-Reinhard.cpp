//
// ToneMapping-Reinhard.cpp
//
// Created by Jietong Chen on 2019/5/6.
//

#include "../pch.h"

using RayTracer::ToneMapping_Reinhard;
using RayTracer::Shader;

ToneMapping_Reinhard::ToneMapping_Reinhard() :
        Shader{ "ToneMapping-Reinhard" },
        color{ 0.0f, 0.0f, 0.0f, 0.0f },
        grayV{ 0.18f, 0.18f, 0.18f },
        avgLuminance{ 0.0f },
        maxLuminance{ 0.0f } {
}

ToneMapping_Reinhard::ToneMapping_Reinhard(
        const ToneMapping_Reinhard& other ) :
        Shader{ "ToneMapping-Reinhard" },
        color{ other.color },
        grayV{ other.grayV },
        avgLuminance{ other.avgLuminance },
        maxLuminance{ other.maxLuminance } {
}

ToneMapping_Reinhard& ToneMapping_Reinhard::operator=(
        const ToneMapping_Reinhard& other ) {
    if( this != &other ) {
        color = other.color;
        grayV = other.grayV;
        avgLuminance = other.avgLuminance;
        maxLuminance = other.maxLuminance;
    }

    return *this;
}

float4 ToneMapping_Reinhard::Shading() const {
    float3 scaledLuminance = float3( grayV.r / avgLuminance * color.r,
                                     grayV.g / avgLuminance * color.g,
                                     grayV.b / avgLuminance * color.b );

    float3 reflectance = scaledLuminance / ( 1.0f + scaledLuminance );
    float3 targetLuminance = reflectance * maxLuminance;

    return float4( targetLuminance, 1.0f );
}

float4 ToneMapping_Reinhard::DirectShading( float3* lightPosition,
                                            float4* lightColor ) const {
    return Shading();
}

float4 ToneMapping_Reinhard::IndirectShading() const {
    return Shading();
}

Shader::ShaderType ToneMapping_Reinhard::Type() const {
    return Shader::ToneMapping_Reinhard;
}
