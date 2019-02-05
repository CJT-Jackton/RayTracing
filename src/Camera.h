//
// Camera.h
//
// Created by Jietong Chen on 1/31/2019.
//


#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Ray.h"
#include "Texture.h"
#include "RenderTexture.h"

class Camera : public GameObject {
public:
    Camera();

    Camera( const Camera& other );

    ~Camera() override;

    void Render();

    Ray ViewportPointToRay( float3 position ) const;

    void ResetAspect();

    void ResetWorldToCameraMatrix();

    static std::vector< Camera* >& GetAllCameras();

public:

    float aspect;

    float4 backgroundColor;

    float focalLength;

    float nearClipPlane;

    float farClipPlane;

    float fieldOfView;

    int pixelWidth;

    int pixelHeight;

    float4x4 cameraToWorldMatrix;

    float4x4 worldToCameraMatrix;

    RenderTexture targetTexture;

    static std::vector< Camera* > allCameras = {};

    static const int& allCamerasCount = allCameras.size();

    static Camera* main;

};

#endif // CAMERA_H
