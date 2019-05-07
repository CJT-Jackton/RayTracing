//
// PostProcess.cpp
//
// Created by Jietong Chen on 2019/5/6.
//

#include "pch.h"

using RayTracer::PostProcess;
using RayTracer::RenderTexture;
using RayTracer::Shader;
using RayTracer::ToneMapping_ACESFilm;

PostProcess::PostProcess() :
        Object{ "Post-Processing" } {
}

void PostProcess::PostProcessing() const {
    if( useToneMapping ) {
        Shader* shader = nullptr;

        if( toneMappingMode == PostProcess::Ward ) {
            shader = new ToneMapping_Ward();
        } else if( toneMappingMode == PostProcess::Reinhard ) {
            shader = new ToneMapping_Reinhard();
        } else if( toneMappingMode == PostProcess::ACESFilm ) {
            shader = new ToneMapping_ACESFilm();
        }

        if( shader != nullptr ) {
#if MULTI_THREAD
            std::vector< std::thread > threads;

            int totalPixel = activeTexture->width * activeTexture->height;
            int blockSize = ( int ) ceil(
                    totalPixel / ( double ) RayTracer::THREAD_NUMBER );

            for( int i = 0; i < RayTracer::THREAD_NUMBER - 1; ++i ) {
                threads.emplace_back( std::move( std::thread( [ & ] {
                    ProcessBlock( i * blockSize, ( i + 1 ) * blockSize,
                                  shader );
                } ) ) );

                std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
            }

            threads.emplace_back( std::move( std::thread( [ & ] {
                ProcessBlock( ( RayTracer::THREAD_NUMBER - 1 ) * blockSize,
                              totalPixel, shader );
            } ) ) );

            for( auto& t : threads ) {
                t.join();
            }
#else
            for( int i = 0; i < activeTexture->width * activeTexture->height; ++i ) {
            int x = i % activeTexture->width;
            int y = i / activeTexture->height;
            ProcessPixel( x, y, shader );
            }
#endif
        }
    }
}

void PostProcess::ProcessBlock( int start, int end, Shader* shader ) const {
    for( int i = start; i < end; ++i ) {
        int x = i % activeTexture->width;
        int y = i / activeTexture->width;

        ProcessPixel( x, y, shader );
    }
}

void PostProcess::ProcessPixel( int x, int y, Shader* shader ) const {
    if( x == 100 && y == 18 ) {
        x = 100;
    }

    if( shader->Type() == Shader::ToneMapping_ACESFilm ) {
        ToneMapping_ACESFilm tshader = ToneMapping_ACESFilm(
                ( const ToneMapping_ACESFilm& ) *shader );

        tshader.color = activeTexture->ReadColorBuffer( x, y );
        activeTexture->WriteColorBuffer( x, y, tshader.Shading() );

    } else if( shader->Type() == Shader::ToneMapping_Reinhard ) {
        ToneMapping_Reinhard tshader = ToneMapping_Reinhard(
                ( const ToneMapping_Reinhard& ) *shader );

        tshader.color = activeTexture->ReadColorBuffer( x, y );
        tshader.grayV = float3( 0.18f );
        tshader.avgLuminance = logAvgLuminance;
        tshader.maxLuminance = 4.0f;
        activeTexture->WriteColorBuffer( x, y, tshader.Shading() );

    } else if( shader->Type() == Shader::ToneMapping_Ward ) {
        ToneMapping_Ward tshader = ToneMapping_Ward(
                ( const ToneMapping_Ward& ) *shader );

        tshader.color = activeTexture->ReadColorBuffer( x, y );
        float Ldmax = 2.0f;
        float sf =
                   powf( ( 1.219f + powf( ( Ldmax / 2.0f ), 0.4f ) ) /
                         ( 1.219f + powf( logAvgLuminance, 0.4f ) ), 2.5f );
        tshader.scalefactor = sf;
        activeTexture->WriteColorBuffer( x, y, tshader.Shading() );
    }
}

void PostProcess::CalculateLuminance() {
    float totalLuminance = 0.0f;
    int totalPixel = activeTexture->width * activeTexture->height;

#if MULTI_THREAD
    std::vector< std::thread > threads;

    int blockSize = ( int ) ceil(
            totalPixel / ( double ) RayTracer::THREAD_NUMBER );

    for( int i = 0; i < RayTracer::THREAD_NUMBER - 1; ++i ) {
        threads.emplace_back( std::move( std::thread( [ & ] {
            totalLuminance += CalculateBlockLuminance( i * blockSize,
                                                       ( i + 1 ) * blockSize );
        } ) ) );

        std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
    }

    threads.emplace_back( std::move( std::thread( [ & ] {
        totalLuminance += CalculateBlockLuminance(
                ( RayTracer::THREAD_NUMBER - 1 ) * blockSize, totalPixel );
    } ) ) );

    for( auto& t : threads ) {
        t.join();
    }
#else
    for( int i = 0; i < totalPixel; ++i ) {
            int x = i % activeTexture->width;
            int y = i / activeTexture->height;
            float pixelLuminance = logf(
                std::numeric_limits< float >::min() + Luminance( x, y ) );
            totalLuminance += pixelLuminance;
     }
#endif

    logAvgLuminance = expf( 1.0f / totalPixel * totalLuminance );
    float Ldmax = 2.0f;
    float sf =
            1.0f / Ldmax * powf( ( 1.219f + powf( ( Ldmax / 2.0f ), 0.4f ) ) /
                                 ( 1.219f + powf( logAvgLuminance, 0.4f ) ),
                                 2.5f );

    //sf += std::numeric_limits< float >::min();
}

float PostProcess::CalculateBlockLuminance( int start, int end ) const {
    float blockLuminance = 0.0f;

    for( int i = start; i < end; ++i ) {
        int x = i % activeTexture->width;
        int y = i / activeTexture->width;

        float pixelLuminance = log10f(
                std::numeric_limits< float >::min() + Luminance( x, y ) );
        blockLuminance += pixelLuminance;
    }

    return blockLuminance;
}

float PostProcess::Luminance( int x, int y ) const {
    float4 color = activeTexture->ReadColorBuffer( x, y );
    return 0.27f * color.r + 0.67f * color.g + 0.06f * color.b;
}
