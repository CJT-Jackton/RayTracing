//
// ToneMapping-Reinhard.h
//
// Created by Jietong Chen on 2019/5/6.
//


#ifndef RAYTRACING_TONEMAPPING_REINHARD_H
#define RAYTRACING_TONEMAPPING_REINHARD_H

#include "../pch.h"

namespace RayTracer{
    class ToneMapping_Reinhard : public Shader {
    public:
        ToneMapping_Reinhard();

        ToneMapping_Reinhard( const ToneMapping_Reinhard& other );

        ToneMapping_Reinhard& operator=( const ToneMapping_Reinhard& other );

        float4 DirectShading( float3 lightPosition[],
                              float4 lightColor[] ) const override;

        float4 IndirectShading() const override;

        /**
         * Use the shader program shade a point.
         *
         * @return the color of the point
         */
        float4 Shading() const override;

        /**
         * The type of the shader program.
         *
         * @return the shader type
         */
        ShaderType Type() const override;

    public:
        float4 color;
        float3 grayV;
        float avgLuminance;
        float maxLuminance;
    };
}

#endif //RAYTRACING_TONEMAPPING_REINHARD_H
