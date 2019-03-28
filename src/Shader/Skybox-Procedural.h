//
// Skybox-Procedural.h
//
// The procedural skybox shader. Modified from the Unity built-in
// skybox-procedural shader.
//
// Created by Jietong Chen on 2019/3/19.
//

#ifndef SKYBOX_PROCEDURAL_H
#define SKYBOX_PROCEDURAL_H

#include "Shader.h"

namespace RayTracer {
    /**
     * The procedural skybox shader. Modified from the Unity built-in
     * skybox-procedural shader.
     */
    class Skybox_Procedural : public Shader {
    public:
        /**
         * Create a new procedural skybox shader.
         */
        Skybox_Procedural();

        /**
         * Copy the procedural skybox shader from another procedural skybox
         * shader.
         *
         * @param other the procedural skybox shader to copy from
         */
        Skybox_Procedural( const Skybox_Procedural& other );

        /**
         * Assign the procedural skybox shader with another procedural skybox
         * shader.
         *
         * @param other the procedural skybox shader to assign
         *
         * @return this procedural skybox shader
         */
        Skybox_Procedural& operator=( const Skybox_Procedural& other );

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
        struct v2f {

            // for HQ sun disk, we need vertex itself to calculate ray-dir per-pixel
            float3 vertex;

            // calculate sky colors in vprog
            float3 groundColor;
            float3 skyColor;

            float3 sunColor;
        };

    private:
        v2f vert() const;

        float4 frag( v2f IN ) const;

        float1 getRayleighPhase( float1 eyeCos2 ) const;

        float1 getRayleighPhase( float3 light, float3 ray ) const;

        float1 scale( float1 inCos ) const;

        float1 getMiePhase( float eyeCos, float eyeCos2 ) const;

        float1 calcSunAttenuation( float3 lightPos, float3 ray ) const;

    public:
        float3 viewRay;

        // Directional lights: (world space direction, 0). Other lights: (world space position, 1).
        float3 _SunDirection;
        float3 _SunColor;

        float _Exposure;     // HDR exposure
        float3 _GroundColor;
        float _SunSize;
        float _SunSizeConvergence;
        float3 _SkyTint;
        float _AtmosphereThickness;

        // RGB wavelengths
        // .35 (.62=158), .43 (.68=174), .525 (.75=190)
        static const float3 kDefaultScatteringWavelength;
        static const float3 kVariableRangeForScatteringWavelength;

#define OUTER_RADIUS 1.025f
        static const float kOuterRadius;
        static const float kOuterRadius2;
        static const float kInnerRadius;
        static const float kInnerRadius2;

        static const float kCameraHeight;

#define kRAYLEIGH (lerp((float1)0.0f, (float1)0.0025f, (float1)pow(_AtmosphereThickness,2.5f)))      // Rayleigh constant
#define kMIE 0.0010f             // Mie constant
#define kSUN_BRIGHTNESS 20.0f    // Sun brightness

#define kMAX_SCATTER 50.0f // Maximum scattering value, to prevent math overflows on Adrenos

        static const float kHDSundiskIntensityFactor;
        static const float kSimpleSundiskIntensityFactor;

        static const float kSunScale;
        static const float kKmESun;
        static const float kKm4PI;
        static const float kScale;
        static const float kScaleDepth;
        static const float kScaleOverScaleDepth;
        static const float kSamples; // THIS IS UNROLLED MANUALLY, DON'T TOUCH

#define MIE_G (-0.990f)
#define MIE_G2 0.9801f

#define SKY_GROUND_THRESHOLD 0.02f

        // fine tuning of performance. You can override defines here if you want some specific setup
        // or keep as is and allow later code to set it according to target api

        // if set vprog will output color in final color space (instead of linear always)
        // in case of rendering in gamma mode that means that we will do lerps in gamma mode too, so there will be tiny difference around horizon
        // #define SKYBOX_COLOR_IN_TARGET_COLOR_SPACE 0

        // sun disk rendering:
        // no sun disk - the fastest option
#define SKYBOX_SUNDISK_NONE 0
        // simplistic sun disk - without mie phase function
#define SKYBOX_SUNDISK_SIMPLE 1
        // full calculation - uses mie phase function
#define SKYBOX_SUNDISK_HQ 2

        // uncomment this line and change SKYBOX_SUNDISK_SIMPLE to override material settings
        // #define SKYBOX_SUNDISK SKYBOX_SUNDISK_SIMPLE

#ifndef SKYBOX_SUNDISK
#if defined(_SUNDISK_NONE)
#define SKYBOX_SUNDISK SKYBOX_SUNDISK_NONE
#elif defined(_SUNDISK_SIMPLE)
#define SKYBOX_SUNDISK SKYBOX_SUNDISK_SIMPLE
#else
#define SKYBOX_SUNDISK SKYBOX_SUNDISK_HQ
#endif
#endif
    }; // Skybox_Procedural
} // RayTracer

#endif // SKYBOX_PROCEDURAL_H
