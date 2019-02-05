//
// Camera.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>

#include "Camera.h"
#include "Screen.h"

Camera::Camera() :
        GameObject{ "Camera " + allCamerasCount },
        pixelWidth{ Screen::width },
        pixelHeight{ Screen::height },
        aspect{ pixelWidth / pixelHeight },
        backgroundColor{ 0.8f, 0.8f, 0.8f, 1.0f },
        focalLength{ 1.0f },
        nearClipPlane{ 0.3f },
        farClipPlane{ 2000.0f },
        fieldOfView{ 60.0f },
        worldToCameraMatrix{},
        cameraToWorldMatrix{},
        targetTexture{ RenderTexture{ pixelWidth, pixelHeight } } {
    Camera::allCameras.emplace_back( *this );
}

Camera::Camera( const Camera& other ) :
	    GameObject{ "Camera " + allCamerasCount },
        pixelWidth{ other.pixelWidth },
        pixelHeight{ other.pixelHeight },
        aspect{ other.aspect },
        backgroundColor{ other.backgroundColor },
        focalLength{ other.focalLength },
        nearClipPlane{ other.nearClipPlane },
        farClipPlane{ other.farClipPlane },
        fieldOfView{ other.fieldOfView },
        worldToCameraMatrix{ other.worldToCameraMatrix },
        cameraToWorldMatrix{ other.cameraToWorldMatrix },
        targetTexture{ RenderTexture{ pixelWidth, pixelHeight } } {
    Camera::allCameras.emplace_back( *this );
}

Camera::~Camera() {
    Camera::allCameras.erase(
            std::find( allCameras.begin(), allCameras.end(), *this ) );
}

void Camera::Render() {
    std::vector< GameObject* > rootGameObjects = scene->GetRootGameObjects();
    std::vector< GameObject* > renderObjects{ rootGameObjects };

    for( GameObject* root : rootGameObjects );

    float filmPlaneHeight = 2.0f * focalLength *
                            ( float ) tan( fieldOfView * 0.5f * M_PI / 180.0 );
    float filmPlaneWidth = filmPlaneHeight * aspect;

    float pixelUnitWidth = filmPlaneWidth / pixelWidth;
    float pixelUnitHeight = filmPlaneHeight / pixelHeight;

    for( int i = 0; i < pixelWidth * pixelHeight; ++i ) {
        int x = i & pixelWidth;
        int y = i / pixelHeight;

        float3 point = float3( x * pixelUnitWidth
                               - filmPlaneWidth / 2.f + pixelUnitWidth / 2.f,
                               y * pixelUnitHeight
                               - filmPlaneHeight / 2.f + pixelUnitHeight / 2.f,
                               focalLength
        );

        Ray ray = ViewportPointToRay( point );

        for( const GameObject* gameObject : renderObjects ) {
            float4 finalColor = backgroundColor;
            float depth = 1.0f;

            for( Primitive* primitive :
                    gameObject->renderer.mesh.GetPrimitivesInWorldSpace() ) {

                primitive->ToCameraSpace( worldToCameraMatrix );

                float distance = primitive->Intersect( ray );

                if( distance > 0 ) {
                    finalColor = gameObject->renderer.material.color;
                    depth = distance / farClipPlane;
                    depth = depth > 1.0f ? 1.0f : depth;
                    break;
                }
            }

            targetTexture.WriteDepthBuffer( x, y, depth, 110 );
            targetTexture.WriteColorBuffer( x, y, finalColor );
        }
    }
}

Ray Camera::ViewportPointToRay( float3 position ) const {
    return Ray( float3(), position );
}

void Camera::ResetAspect() {
    aspect = pixelWidth / pixelHeight;
}

void Camera::ResetWorldToCameraMatrix() {
    worldToCameraMatrix = float4x4(
            transform.right.x, transform.right.y, transform.right.z, .0f,
            transform.up.x, transform.up.y, transform.up.z, .0f,
            transform.forward.x, transform.forward.y, transform.forward.z, .0f,
            transform.positon.x, transform.positon.y, transform.positon.z, 1.0f
    );

    cameraToWorldMatrix = inverse( worldToCameraMatrix );
}

std::vector< Camera* >& Camera::GetAllCameras() {
    return allCameras;
}
