//
// Skybox-Procedural.cpp
//
// The implementation of procedural skybox shader.
//
// Created by Jietong Chen on 2019/3/19.
//

#include "../pch.h"

using RayTracer::Skybox_Procedural;
using RayTracer::Shader;

// RGB wavelengths
// .35 (.62=158), .43 (.68=174), .525 (.75=190)
const float3 Skybox_Procedural::kDefaultScatteringWavelength =
        float3( .65f, .57f, .475f );
const float3 Skybox_Procedural::kVariableRangeForScatteringWavelength =
        float3( .15f, .15f, .15f );

const float Skybox_Procedural::kOuterRadius = OUTER_RADIUS;
const float Skybox_Procedural::kOuterRadius2 = OUTER_RADIUS * OUTER_RADIUS;
const float Skybox_Procedural::kInnerRadius = 1.0f;
const float Skybox_Procedural::kInnerRadius2 = 1.0f;

const float Skybox_Procedural::kCameraHeight = 0.0001f;

const float Skybox_Procedural::kHDSundiskIntensityFactor = 15.0f;
const float Skybox_Procedural::kSimpleSundiskIntensityFactor = 27.0f;

const float Skybox_Procedural::kSunScale = 400.0f * kSUN_BRIGHTNESS;
const float Skybox_Procedural::kKmESun = kMIE * kSUN_BRIGHTNESS;
const float Skybox_Procedural::kKm4PI = kMIE * 4.0f * 3.14159265f;
const float Skybox_Procedural::kScale = 1.0f / ( OUTER_RADIUS - 1.0f );
const float Skybox_Procedural::kScaleDepth = 0.25f;
const float Skybox_Procedural::kScaleOverScaleDepth =
        ( 1.0f / ( OUTER_RADIUS - 1.0f ) ) / 0.25f;
const float Skybox_Procedural::kSamples = 2.0f; // THIS IS UNROLLED MANUALLY, DON'T TOUCH

/**
 * Create a new procedural skybox shader.
 */
Skybox_Procedural::Skybox_Procedural() :
        Shader{ "Skybox-Procedural" },
        _SunSize{ 0.04f },
        _SunSizeConvergence{ 5 },
        _AtmosphereThickness{ 1 },
        _SkyTint{ 0.5f, 0.5f, 0.5f },
        _GroundColor{ 0.369f, 0.349f, 0.341f },
        _Exposure{ 1.3f },
        viewRay{},
        _SunDirection{ 0.0f, -1.0f, 0.0f },
        _SunColor{ 1.0f, 1.0f, 1.0f } {
}

/**
 * Copy the procedural skybox shader from another procedural skybox shader.
 *
 * @param other the procedural skybox shader to copy from
 */
Skybox_Procedural::Skybox_Procedural( const Skybox_Procedural& other ) :
        Shader{ "Skybox-Procedural" },
        _SunSize{ other._SunSize },
        _SunSizeConvergence{ other._SunSizeConvergence },
        _AtmosphereThickness{ other._AtmosphereThickness },
        _SkyTint{ other._SkyTint },
        _GroundColor{ other._GroundColor },
        _Exposure{ other._Exposure },
        viewRay{},
        _SunDirection{ other._SunDirection },
        _SunColor{ other._SunColor } {
}

/**
 * Assign the procedural skybox shader with another procedural skybox shader.
 *
 * @param other the procedural skybox shader to assign
 *
 * @return this procedural skybox shader
 */
Skybox_Procedural& Skybox_Procedural::operator=(
        const Skybox_Procedural& other ) {
    if( this != &other ) {
        _SunSize = other._SunSize;
        _SunSizeConvergence = other._SunSizeConvergence;
        _AtmosphereThickness = other._AtmosphereThickness;
        _SkyTint = other._SkyTint;
        _GroundColor = other._GroundColor;
        _Exposure = other._Exposure;
        viewRay = other.viewRay;
        _SunDirection = other._SunDirection;
        _SunColor = other._SunColor;
    }

    return *this;
}

/**
 * Use the shader program shade a point.
 *
 * @return the color of the point
 */
float4 Skybox_Procedural::Shading() const {
    return frag( vert() );
}

Skybox_Procedural::v2f Skybox_Procedural::vert() const {
    Skybox_Procedural::v2f OUT;

    float3 kSkyTintInGammaSpace = _SkyTint; // convert tint from Linear back to Gamma
    float3 kScatteringWavelength = lerp(
            kDefaultScatteringWavelength -
            kVariableRangeForScatteringWavelength,
            kDefaultScatteringWavelength +
            kVariableRangeForScatteringWavelength,
            float3( 1.0f, 1.0f, 1.0f ) -
            kSkyTintInGammaSpace ); // using Tint in sRGB gamma allows for more visually linear interpolation and to keep (.5) at (128, gray in sRGB) point

//    float3 kInvWavelength =
//            float3( 1.0f ) / pow( kScatteringWavelength, float3( 4.0f ) );
    // hlslpp function not working here.
    float kInvWavelengthR = 1.0f / pow( kScatteringWavelength.x, 4.0f );
    float kInvWavelengthG = 1.0f / pow( kScatteringWavelength.y, 4.0f );
    float kInvWavelengthB = 1.0f / pow( kScatteringWavelength.z, 4.0f );
    float3 kInvWavelength = float3( kInvWavelengthR,
                                    kInvWavelengthG,
                                    kInvWavelengthB );

    float kKrESun = kRAYLEIGH * kSUN_BRIGHTNESS;
    float kKr4PI = kRAYLEIGH * 4.0f * 3.14159265f;

    // The camera's current position
    float3 cameraPos = float3( 0, kInnerRadius + kCameraHeight, 0.0f );

    // Get the ray from the camera to the vertex and its length (which is the far point of the ray passing through the atmosphere)
    float3 eyeRay = viewRay;

    float far = 0.0;
    float3 cIn, cOut;

    if( eyeRay.y >= 0.0f ) {
        // Sky
        // Calculate the length of the "atmosphere"
        far = sqrt( kOuterRadius2 + kInnerRadius2 * eyeRay.y * eyeRay.y -
                    kInnerRadius2 ) - kInnerRadius * eyeRay.y;

        float3 pos = cameraPos + far * eyeRay;

        // Calculate the ray's starting position, then calculate its scattering offset
        float height = kInnerRadius + kCameraHeight;
        float depth = exp( kScaleOverScaleDepth * ( -kCameraHeight ) );
        float startAngle = dot( eyeRay, cameraPos ) / height;
        float startOffset = depth * scale( startAngle );


        // Initialize the scattering loop variables
        float sampleLength = far / kSamples;
        float scaledLength = sampleLength * kScale;
        float3 sampleRay = eyeRay * sampleLength;
        float3 samplePoint = cameraPos + sampleRay * 0.5f;

        // Now loop through the sample rays
        float3 frontColor = float3( 0.0f, 0.0f, 0.0f );
        for( int i = 0; i < int( kSamples ); i++ ) {
            float height = length( samplePoint );
            float depth = exp(
                    kScaleOverScaleDepth * ( kInnerRadius - height ) );
            float lightAngle = dot( _SunDirection, samplePoint ) / height;
            float cameraAngle = dot( eyeRay, samplePoint ) / height;
            float1 scatter = ( startOffset + depth * ( scale( lightAngle ) -
                                                       scale( cameraAngle ) ) );
            float3 attenuate = exp( float3( -clamp( scatter, ( float1 ) 0.0f,
                                                    ( float1 ) kMAX_SCATTER ) )
                                    * ( kInvWavelength * kKr4PI + kKm4PI ) );

            frontColor += attenuate * ( depth * scaledLength );
            samplePoint += sampleRay;
        }

        // Finally, scale the Mie and Rayleigh colors and set up the varying variables for the pixel shader
        cIn = frontColor * ( kInvWavelength * kKrESun );
        cOut = frontColor * kKmESun;

    } else {
        // Ground
        far = ( -kCameraHeight ) / ( min( ( float1 ) -0.001f, eyeRay.y ) );

        float3 pos = cameraPos + far * eyeRay;

        // Calculate the ray's starting position, then calculate its scattering offset
        float depth = exp( ( -kCameraHeight ) * ( 1.0f / kScaleDepth ) );
        float cameraAngle = dot( -eyeRay, pos );
        float lightAngle = dot( _SunDirection, pos );
        float cameraScale = scale( cameraAngle );
        float lightScale = scale( lightAngle );
        float cameraOffset = depth * cameraScale;
        float temp = ( lightScale + cameraScale );

        // Initialize the scattering loop variables
        float sampleLength = far / kSamples;
        float scaledLength = sampleLength * kScale;
        float3 sampleRay = eyeRay * sampleLength;
        float3 samplePoint = cameraPos + sampleRay * 0.5f;

        // Now loop through the sample rays
        float3 frontColor = float3( 0.0f, 0.0f, 0.0f );
        float3 attenuate;

        for( int i = 0; i < int( kSamples ); i++ ) {
            float height = length( samplePoint );
            float depth = exp(
                    kScaleOverScaleDepth * ( kInnerRadius - height ) );
            float1 scatter = depth * temp - cameraOffset;
            attenuate = exp( float3( -clamp( scatter, ( float1 ) 0.0f,
                                             ( float1 ) kMAX_SCATTER ) ) *
                             ( kInvWavelength * kKr4PI + kKm4PI ) );
            frontColor += attenuate * ( depth * scaledLength );
            samplePoint += sampleRay;
        }

        cIn = frontColor * ( kInvWavelength * kKrESun + kKmESun );
        cOut = clamp( attenuate, float3( 0.0f ), float3( 1.0f ) );
    }

    OUT.vertex = -viewRay;
//    OUT.vertex = -eyeRay;

    // if we want to calculate color in vprog:
    // 1. in case of linear: multiply by _Exposure in here (even in case of lerp it will be common multiplier, so we can skip mul in fshader)
    // 2. in case of gamma and SKYBOX_COLOR_IN_TARGET_COLOR_SPACE: do sqrt right away instead of doing that in fshader

    OUT.groundColor = _Exposure * ( cIn + _GroundColor * _GroundColor * cOut );
    OUT.skyColor = _Exposure * ( cIn *
                                 getRayleighPhase( _SunDirection, -eyeRay ) );

    // The sun should have a stable intensity in its course in the sky. Moreover it should match the highlight of a purely specular material.
    // This matching was done using the standard shader BRDF1 on the 5/31/2017
    // Finally we want the sun to be always bright even in LDR thus the normalization of the lightColor for low intensity.
    float lightColorIntensity = clamp( length( _SunColor ), ( float1 ) 0.25f,
                                       ( float1 ) 1 );

    OUT.sunColor = kHDSundiskIntensityFactor * saturate( cOut ) * _SunColor /
                   lightColorIntensity;
//    OUT.sunColor =
//            kSimpleSundiskIntensityFactor * saturate( cOut * kSunScale ) *
//            _SunColor / lightColorIntensity;

    return OUT;
}

float4 Skybox_Procedural::frag( Skybox_Procedural::v2f IN ) const {
    float3 col = float3( 0.0f, 0.0f, 0.0f );

    // if y > 1 [eyeRay.y < -SKY_GROUND_THRESHOLD] - ground
    // if y >= 0 and < 1 [eyeRay.y <= 0 and > -SKY_GROUND_THRESHOLD] - horizon
    // if y < 0 [eyeRay.y > 0] - sky
    float3 ray = IN.vertex;
    float1 y = ray.y / float1( SKY_GROUND_THRESHOLD );

    // if we did precalculate color in vprog: just do lerp between them
    col = lerp( IN.skyColor, IN.groundColor, float3( saturate( y ) ) );

    if( ( float ) y < 0.0f ) {
        col += IN.sunColor *
               calcSunAttenuation( _SunDirection, -ray );
    }

    return float4( col, 1.0f );
}

float1 Skybox_Procedural::getRayleighPhase( float1 eyeCos2 ) const {
    return 0.75f + 0.75f * eyeCos2;

}

float1 Skybox_Procedural::getRayleighPhase( float3 light, float3 ray ) const {
    float eyeCos = dot( light, ray );
    return getRayleighPhase( eyeCos * eyeCos );
}

float1 Skybox_Procedural::scale( float1 inCos ) const {
    float1 x = 1.0f - inCos;
    return 0.25f *
           exp( -0.00287f +
                x *
                ( 0.459f + x * ( 3.83f + x * ( -6.80f + x * 5.25f ) ) ) );
}

float1 Skybox_Procedural::getMiePhase( float eyeCos, float eyeCos2 ) const {
    float1 temp = 1.0 + MIE_G2 - 2.0 * MIE_G * eyeCos;
    temp = pow( temp, float1( pow( _SunSize, 0.65f ) * 10 ) );
    temp = max( temp,
                ( float1 ) 1.0e-4 ); // prevent division by zero, esp. in half precision
    temp = 1.5f * ( ( 1.0f - MIE_G2 ) / ( 2.0f + MIE_G2 ) ) *
           ( 1.0f + eyeCos2 ) / temp;

    return temp;
}

float1
Skybox_Procedural::calcSunAttenuation( float3 lightPos, float3 ray ) const {
    float focusedEyeCos = std::pow( saturate( dot( lightPos, ray ) ),
                                    _SunSizeConvergence );
    return getMiePhase( -focusedEyeCos, focusedEyeCos * focusedEyeCos );
//    float3 delta = lightPos - ray;
//    float1 dist = length( delta );
//    float1 spot =
//            1.0f - smoothstep( ( float1 ) 0.0f, ( float1 ) _SunSize, dist );
//    return spot * spot;
}

/**
 * The type of the shader program.
 *
 * @return the shader type
 */
Shader::ShaderType Skybox_Procedural::Type() const {
    return Shader::Skybox_Procedural;
}
