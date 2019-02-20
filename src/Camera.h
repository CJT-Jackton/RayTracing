//
// Camera.h
//
// The camera views the world.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "pch.h"

namespace RayTracer {
    /**
     * The camera views the world.
     */
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
                          std::vector< Primitive* >& primitives,
                          std::vector< Light* >& lights );

        void RenderBlock( int start, int end,
                          std::vector< Primitive* >& primitives,
                          std::vector< Light* >& lights );

    public:
        /** the aspect ratio (width divided by height) */
        const float& aspect;

        /** the background color */
        float4 backgroundColor;

        /** the camera focal length */
        float focalLength;

        /** the near clipping plane distance */
        float nearClipPlane;

        /** the far clipping plane distance */
        float farClipPlane;

        /** the field of view of the camera in degrees */
        float fieldOfView;

        /** the width in pixel */
        const int& pixelWidth;

        /** the height in pixel */
        const int& pixelHeight;

        /** the matrix transforms from camera space to world space */
        const float4x4& cameraToWorldMatrix;

        /** the matrix transforms from world space to world camera */
        const float4x4& worldToCameraMatrix;

        /** the destination render texture */
        RenderTexture targetTexture;

        /** an array of all enabled cameras in the Scene */
        static std::vector< Camera* > allCameras;

        /** the number of cameras in the current Scene */
        static const unsigned int& allCamerasCount;

        /** the main camera */
        static Camera* main;

    protected:
        /** the aspect ratio (width divided by height) */
        float _aspect;

        /** the width in pixel */
        int _pixelWidth;

        /** the height in pixel */
        int _pixelHeight;

        /** the width of film plane */
        float filmPlaneWidth;

        /** the height of film plane */
        float filmPlaneHeight;

        /** the width of a single pixel */
        float pixelUnitWidth;

        /** the height of a single pixel */
        float pixelUnitHeight;

        /** the matrix transforms from camera space to world space */
        float4x4 _cameraToWorldMatrix;

        /** the matrix transforms from world space to world camera */
        float4x4 _worldToCameraMatrix;

    }; // Camera
} // RayTracer

#endif // CAMERA_H
