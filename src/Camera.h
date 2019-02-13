//
// Camera.h
//
// Created by Jietong Chen on 1/31/2019.
//


#ifndef CAMERA_H
#define CAMERA_H

#include "pch.h"
//#include "GameObject.h"
//#include "Ray.h"
//#include "Texture.h"
//#include "RenderTexture.h"

namespace RayTracing {
    class Camera : public GameObject {
    public:
        Camera();

        Camera( const Camera& other );

        ~Camera() override;

        void Render();

        Ray ViewportPointToRay( float3 position ) const;

        void Reset();

        void ResetAspect();

        void ResetWorldToCameraMatrix();

        static std::vector< Camera* >& GetAllCameras();

    protected:
        void RenderPixel( int x, int y,
                          std::vector< Primitive* >& primitives );

        void RenderBlock( int start, int end,
                          std::vector< Primitive* >& primitives );

    public:

        const float& aspect;

        float4 backgroundColor;

        float focalLength;

        float nearClipPlane;

        float farClipPlane;

        float fieldOfView;

        const int& pixelWidth;

        const int& pixelHeight;

        const float4x4& cameraToWorldMatrix;

        const float4x4& worldToCameraMatrix;

        RenderTexture targetTexture;

        static std::vector< Camera* > allCameras;

        static const unsigned int& allCamerasCount;

        static Camera* main;

    protected:
        float _aspect;

        int _pixelWidth;

        int _pixelHeight;

        float filmPlaneHeight;

        float filmPlaneWidth;

        float pixelUnitWidth;

        float pixelUnitHeight;

        float4x4 _cameraToWorldMatrix;

        float4x4 _worldToCameraMatrix;

    };
}

#endif // CAMERA_H
