//
// PostProcess.h
//
// Created by Jietong Chen on 2019/5/6.
//

#ifndef RAYTRACING_POSTPROCESS_H
#define RAYTRACING_POSTPROCESS_H

#include "Object.h"

namespace RayTracer {
    class PostProcess : public Object {
    public:
        /**
         * The format of the pixel data in the texture.
         */
        enum ToneMapping {
            None,
            Ward,
            Reinhard,
            ACESFilm
        };

        PostProcess();

        void PostProcessing() const;

        void CalculateLuminance();

    private:
        void ProcessBlock( int start, int end, Shader* shader ) const;

        void ProcessPixel( int x, int y, Shader* shader ) const;


        float CalculateBlockLuminance( int start, int end ) const;

        float Luminance( int x, int y ) const;

    public:
        RenderTexture* activeTexture;

        bool useToneMapping;
        ToneMapping toneMappingMode;

        float logAvgLuminance;
    }; // PostProcess
} // RayTracer

#endif //RAYTRACING_POSTPROCESS_H
