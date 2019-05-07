//
// ToneMapping-Ward.cpp
//
// Created by Jietong Chen on 2019/5/6.
//

#include "../pch.h"

using RayTracer::ToneMapping_Ward;
using RayTracer::Shader;

ToneMapping_Ward::ToneMapping_Ward() :
        Shader{ "ToneMapping-Ward" },
        scalefactor{ 0.0f } {
}

ToneMapping_Ward::ToneMapping_Ward( const ToneMapping_Ward& other ) :
        Shader{ "ToneMapping-Ward" },
        scalefactor{ other.scalefactor } {
}

ToneMapping_Ward& ToneMapping_Ward::operator=(
        const ToneMapping_Ward& other ) {
    if( this != &other ) {
        scalefactor = other.scalefactor;
    }

    return *this;
}

float4 ToneMapping_Ward::Shading() const {
    return scalefactor * color;
}

float4 ToneMapping_Ward::DirectShading( float3* lightPosition,
                                        float4* lightColor ) const {
    return Shading();
}

float4 ToneMapping_Ward::IndirectShading() const {
    return Shading();
}

Shader::ShaderType ToneMapping_Ward::Type() const {
    return Shader::ToneMapping_Ward;
}
