//
// Camera.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"
//#define _USE_MATH_DEFINES
//#include <algorithm>
//#include <cmath>
//
//#include "Camera.h"
//#include "Screen.h"

using RayTracing::Camera;
using RayTracing::Ray;

std::vector< Camera* >Camera::allCameras;
const unsigned int& Camera::allCamerasCount = Camera::allCameras.size();
Camera* Camera::main = nullptr;

Camera::Camera() :
        GameObject{ "Camera " + allCamerasCount },
        pixelWidth{ Screen::width },
        pixelHeight{ Screen::height },
        aspect{ Screen::width / ( float ) Screen::height },
        backgroundColor{ 0.2f, 0.2f, 0.2f, 1.0f },
        focalLength{ 1.0f },
        nearClipPlane{ 0.3f },
        farClipPlane{ 2000.0f },
        fieldOfView{ 60.0f },
        worldToCameraMatrix{},
        cameraToWorldMatrix{},
        targetTexture{ RenderTexture{ pixelWidth, pixelHeight } } {
    Camera::allCameras.emplace_back( this );
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
    Camera::allCameras.emplace_back( this );
}

Camera::~Camera() {
    Camera::allCameras.erase(
            std::find( allCameras.begin(), allCameras.end(), this ) );
}

void Camera::Render() {
    ResetWorldToCameraMatrix();

    std::vector< GameObject* > rootGameObjects = scene->GetRootGameObjects();
    std::vector< GameObject* > renderObjects{ rootGameObjects };

    std::vector< Primitive* > primitives;

    for( GameObject* renderObject : renderObjects ) {
        if( renderObject->GetComponent< Renderer >() ) {
            for( Primitive* p :
                    renderObject->GetComponent< Renderer >()->GetPrimitives() ) {

                primitives.emplace_back(
                        p->ToCameraSpace( worldToCameraMatrix ) );
            }
        }
    }

    float filmPlaneHeight = 2.0f * focalLength *
                            ( float ) tan( fieldOfView * 0.5f * M_PI / 180.0 );
    float filmPlaneWidth = filmPlaneHeight * aspect;

    float pixelUnitWidth = filmPlaneWidth / pixelWidth;
    float pixelUnitHeight = filmPlaneHeight / pixelHeight;

    for( int i = 0; i < pixelWidth * pixelHeight; ++i ) {
        int x = i % pixelWidth;
        int y = i / pixelWidth;

        float3 point = float3( x * pixelUnitWidth
                               - filmPlaneWidth * 0.5f + pixelUnitWidth *0.5f,
                               -y * pixelUnitHeight
                               + filmPlaneHeight *0.5f - pixelUnitHeight *0.5f,
                               focalLength
        );

        Ray ray = ViewportPointToRay( point );
        float4 finalColor = backgroundColor;
        float depth = 0.0f;

//        for( const GameObject* renderObject : renderObjects ) {
//            if( !renderObject->GetComponent< Renderer >() ) {
//                continue;
//            }
//
//            for( Primitive* primitive :
//                    renderObject->GetComponent< Renderer >()->GetPrimitives() ) {
//
//                primitive = primitive->ToCameraSpace( worldToCameraMatrix );
//
//                float distance = primitive->Intersect( ray );
//
//                if( distance > depth ) {
//                    finalColor = renderObject->GetComponent< Renderer >()->material->color;
//                    depth = distance;
//                    break;
//                }
//            }
//        }

        for( Primitive* primitive:primitives ) {
            float distance = primitive->Intersect( ray );

            if( distance > depth ) {
                finalColor = primitive->mesh->renderer->material->color;
                depth = distance;
                break;
            }
        }

        targetTexture.WriteDepthBuffer( x, y, depth, 110 );
        targetTexture.WriteColorBuffer( x, y, finalColor );
    }

    for( Primitive* primitive : primitives ) {
        delete ( primitive );
    }
}

Ray Camera::ViewportPointToRay( float3 position ) const {
    return Ray( float3( 0, 0, 0 ), position );
}

void Camera::ResetAspect() {
    aspect = pixelWidth / ( float ) pixelHeight;
}

void Camera::ResetWorldToCameraMatrix() {
//    worldToCameraMatrix = float4x4(
//            transform->right.x, transform->right.y, transform->right.z,
//            -dot( transform->right, transform->positon ),
//            transform->up.x, transform->up.y, transform->up.z,
//            -dot( transform->up, transform->positon ),
//            transform->forward.x, transform->forward.y, transform->forward.z,
//            -dot( transform->forward, transform->positon ),
//            0.0f, 0.0f, 0.0f, 1.0f
//    );

    worldToCameraMatrix = float4x4(
            transform->right.x, transform->up.x, transform->forward.x, 0.0f,
            transform->right.y, transform->up.y, transform->forward.y, 0.0f,
            transform->right.z, transform->up.z, transform->forward.z, 0.0f,
            -dot( transform->right, transform->positon ),
            -dot( transform->up, transform->positon ),
            -dot( transform->forward, transform->positon ), 1.0f
    );

    cameraToWorldMatrix = inverse( worldToCameraMatrix );
}

std::vector< Camera* >& Camera::GetAllCameras() {
    return allCameras;
}
