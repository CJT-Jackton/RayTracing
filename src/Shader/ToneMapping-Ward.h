//
// ToneMapping-Ward.h
//
// Created by Jietong Chen on 2019/5/6.
//

#ifndef RAYTRACING_TONEMAPPING_WARD_H
#define RAYTRACING_TONEMAPPING_WARD_H


#include "Shader.h"

namespace RayTracer {

    class ToneMapping_Ward : public Shader {
    public:
        ToneMapping_Ward();

        ToneMapping_Ward( const ToneMapping_Ward& other );

        ToneMapping_Ward& operator=( const ToneMapping_Ward& other );

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
        float scalefactor;
    };
}

#endif //RAYTRACING_TONEMAPPING_WARD_H
