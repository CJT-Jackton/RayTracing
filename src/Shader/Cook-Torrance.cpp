//
// Cook-Torrance.cpp
//
// Created by Jietong Chen on 2019/3/22.
//

#include "../pch.h"

using RayTracer::Cook_Torrance;
using RayTracer::Shader;

Cook_Torrance::Cook_Torrance() :
        Shader{ "Cook-Torrance" },
        view{},
        normal{},
        light{},
        uv{},
        lightPositon{},
        lightColor{},
        shadow{},
        irradiance{},
        transmit{},
        mainColor{},
        mainTexture{},
        mainTextureOffset{ float2( 0.0f ) },
        mainTextureScale{ float2( 1.0f ) },
        metallic{ 0.0f },
        smoothness{ 0.5f } {
}

Cook_Torrance::Cook_Torrance( const Cook_Torrance& other ) :
        Shader{ "Cook-Torrance" },
        view{ other.view },
        normal{ other.normal },
        light{ other.light },
        uv{ other.uv },
        lightPositon{ other.lightPositon },
        lightColor{ other.lightColor },
        shadow{ other.shadow },
        irradiance{ other.irradiance },
        transmit{ other.transmit },
        mainColor{ other.mainColor },
        mainTexture{ other.mainTexture },
        mainTextureOffset{ other.mainTextureOffset },
        mainTextureScale{ other.mainTextureScale },
        metallic{ other.metallic },
        smoothness{ other.smoothness } {

}

Cook_Torrance& Cook_Torrance::operator=( const Cook_Torrance& other ) {
    if( this != &other ) {
        view = other.view;
        normal = other.normal;
        light = other.light;
        uv = other.uv;
        lightPositon = other.lightPositon;
        lightColor = other.lightColor;
        shadow = other.shadow;
        irradiance = other.irradiance;
        transmit = other.transmit;
        mainColor = other.mainColor;
        mainTexture = other.mainTexture;
        mainTextureScale = other.mainTextureScale;
        mainTextureOffset = other.mainTextureOffset;
        metallic = other.metallic;
        smoothness = other.smoothness;
    }

    return *this;
}

float4 Cook_Torrance::Shading() const {
    float4 finalColor = float4( 0.0f );
    float3 albedo = mainColor.xyz;

    if( mainTexture ) {
        // use texture color if has texture
        albedo = Texture::Sample( mainTexture,
                                  uv * mainTextureScale +
                                  mainTextureOffset ).xyz;
    }

    float3 F0 = float3( 0.04f );
    F0 = lerp( F0, albedo, metallic );

    float3 half = normalize( view + light );

    float normalDistribution = NormalDistributionGGX( normal, half,
                                                      smoothness );
    float geometry = GeometrySmith( normal, view, light, smoothness );
    float3 fresnel = FresnelSchlick( max( dot( half, view ), float1( 0.0f ) ),
                                     F0 );

    float3 kSpecular = fresnel;
    float3 kDiffuse = float3( 1.0f ) - kSpecular;
    kDiffuse *= 1 - metallic;

//    float3 diffuse = kDiffuse * albedo / M_PI;
    float3 diffuse = kDiffuse * albedo;

    float3 numerator = normalDistribution * geometry * fresnel;
    float1 denominator = 4.0f * max( dot( normal, view ), float1( 0.0f ) ) *
                         max( dot( normal, light ), float1( 0.0f ) );
    float3 specular = numerator / max( denominator, float1( 0.001f ) );

    float3 kCookTorrance = diffuse + specular;

    float1 cos = max( dot( normal, light ), float1( 0.0f ) );
    float3 color = kCookTorrance * lightColor * cos;

    color = shadow * color;

    // ambient lighting
//    float3 kS = FresnelSchlick( max( dot( normal, view ), float1( 0.0f ) ),
//                                F0 );
//    float3 kD = 1.0f - kS;
//    kD *= 1.0f - metallic;
//    diffuse = irradiance * albedo;
//    specular = irradiance * kS;
//    float3 ambient = kD * diffuse + specular;
//
//    color = color + ambient;
    float3 kS = fresnel;
    float transparency = mainColor.a;
    float3 kReflect = kS * transparency + float3( transparency );

    color = kReflect * color;

    return float4( color, 1.0f );
}

float4 Cook_Torrance::DirectShading( float3* lightPosition,
                                     float4* lightColor ) const {
    return Shading();
}

float4 Cook_Torrance::IndirectShading() const {
    if( ( float ) dot( view, normal ) < 0.0f ) {
        return float4( transmit, 1.0f );
    }

    float3 albedo = mainColor.rgb;
    float transparency = mainColor.a;

    if( mainTexture ) {
        // use texture color if has texture
        albedo = Texture::Sample( mainTexture,
                                  uv * mainTextureScale +
                                  mainTextureOffset ).xyz;
    }

    float3 F0 = float3( 0.04f );
    F0 = lerp( F0, albedo, metallic );

    float3 kS = FresnelSchlick( max( dot( normal, view ), float1( 0.0f ) ),
                                F0 );
    float3 kD = 1.0f - kS;
    kD *= 1.0f - metallic;
    float3 diffuse = irradiance * albedo;
    float3 specular = irradiance * kS;
    float3 ambient = kD * diffuse + specular;

    float3 kReflect = kS * ( 1.0f - transparency ) + float3( transparency );
    float3 kTransmit = 1.0f - kReflect;

    float3 finalColor = kReflect * ambient + kTransmit * transmit;

    return float4( finalColor, 1.0f );
}

float Cook_Torrance::NormalDistributionGGX( float3 normal, float3 half,
                                            float smoothness ) const {
    float a = smoothness * smoothness;
    float a2 = a * a;

    float cos = dot( normal, half );
    float cos2 = cos * cos;
    float demon = cos2 * ( a2 - 1.0f ) + 1.0f;
    demon = ( float ) M_PI * demon * demon;

    return a2 / demon;
}

float Cook_Torrance::GeometrySchlickGGX( float cos, float k ) const {
    return cos / ( cos * ( 1.0f - k ) + k );
}

float Cook_Torrance::GeometrySmith( float3 normal, float3 view, float3 light,
                                    float k ) const {
    float NdotV = max( dot( normal, view ), float1( 0.0f ) );
    float NdotL = max( dot( normal, light ), float1( 0.0f ) );
    float ggx1 = GeometrySchlickGGX( NdotV, k );
    float ggx2 = GeometrySchlickGGX( NdotL, k );

    return ggx1 * ggx2;
}

float3 Cook_Torrance::FresnelSchlick( float cos, float3 F0 ) const {
    return F0 + ( 1.0f - F0 ) * pow( 1.0f - cos, 5.0f );
}

Shader::ShaderType Cook_Torrance::Type() const {
    return Shader::Cook_Torrance;
}
