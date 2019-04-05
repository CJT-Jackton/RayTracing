//
// Unlit.h
//
// The unlit shader. Unlit shader does not affect by any light source.
//
// Created by Jietong Chen on 2019/3/22.
//

#ifndef UNLIT_H
#define UNLIT_H

#include "Shader.h"

namespace RayTracer {
    /**
     * The unlit shader. Unlit shader does not affect by any light source.
     */
    class Unlit : public Shader {
    public:
        /**
         * Default constructor.
         */
        Unlit();

        /**
         * Copy the unlit shader from another unlit shader.
         *
         * @param other the unlit shader to copy from
         */
        Unlit( const Unlit& other );

        /**
         * Assign the unlit shader with another unlit shader.
         *
         * @param other the unlit shader to assign
         *
         * @return this unlit shader
         */
        Unlit& operator=( const Unlit& other );

        /**
         * Use the shader program shade a point.
         *
         * @return the color of the point
         */
        float4 Shading() const;

        float4 DirectShading( float3 lightPosition[],
                              float4 lightColor[] ) const override;

        float4 IndirectShading() const override;

        /**
         * The type of the shader program.
         *
         * @return the shader type
         */
        ShaderType Type() const;

    public:
        /** the main color */
        float4 mainColor;

    }; // Unlit
} // RayTracer

#endif // UNLIT_H
