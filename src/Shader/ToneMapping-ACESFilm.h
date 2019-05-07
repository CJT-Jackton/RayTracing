//
// ToneMapping-ACESFilm.h
//
// Created by Jietong Chen on 2019/5/6.
//


#ifndef RAYTRACING_TONEMAPPING_ACESFILM_H
#define RAYTRACING_TONEMAPPING_ACESFILM_H

#include "../pch.h"

namespace RayTracer {
    class ToneMapping_ACESFilm : public Shader {
    public:
        ToneMapping_ACESFilm();

        ToneMapping_ACESFilm( const ToneMapping_ACESFilm& other );

        ToneMapping_ACESFilm& operator=( const ToneMapping_ACESFilm& other );

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
    };
}

#endif //RAYTRACING_TONEMAPPING_ACESFILM_H
