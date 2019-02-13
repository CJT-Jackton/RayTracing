//
// Camera.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracing::Camera;
using RayTracing::Ray;
using RayTracing::Primitive;

std::vector< Camera* >Camera::allCameras;
const unsigned int& Camera::allCamerasCount = Camera::allCameras.size();
Camera* Camera::main = nullptr;

Camera::Camera() :
        GameObject{ "Camera " + allCamerasCount },
        _pixelWidth{ Screen::width },
        _pixelHeight{ Screen::height },
        _aspect{ Screen::width / ( float ) Screen::height },
        pixelWidth{ _pixelWidth },
        pixelHeight{ _pixelHeight },
        aspect{ _aspect },
        backgroundColor{ 0.2f, 0.2f, 0.2f, 1.0f },
        focalLength{ 1.0f },
        nearClipPlane{ 0.3f },
        farClipPlane{ 2000.0f },
        fieldOfView{ 60.0f },
        _worldToCameraMatrix{},
        _cameraToWorldMatrix{},
        worldToCameraMatrix{ _worldToCameraMatrix },
        cameraToWorldMatrix{ _cameraToWorldMatrix },
        targetTexture{ RenderTexture{ Screen::width, Screen::height } } {
    Camera::allCameras.emplace_back( this );
}

Camera::Camera( const Camera& other ) :
        GameObject{ "Camera " + allCamerasCount },
        _pixelWidth{ other._pixelWidth },
        _pixelHeight{ other._pixelHeight },
        _aspect{ other._aspect },
        pixelWidth{ _pixelWidth },
        pixelHeight{ _pixelHeight },
        aspect{ _aspect },
        backgroundColor{ other.backgroundColor },
        focalLength{ other.focalLength },
        nearClipPlane{ other.nearClipPlane },
        farClipPlane{ other.farClipPlane },
        fieldOfView{ other.fieldOfView },
        _worldToCameraMatrix{ other._worldToCameraMatrix },
        _cameraToWorldMatrix{ other._cameraToWorldMatrix },
        worldToCameraMatrix{ _worldToCameraMatrix },
        cameraToWorldMatrix{ _cameraToWorldMatrix },
        targetTexture{
                RenderTexture{ other._pixelWidth, other._pixelHeight } } {
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
        if( *renderObject && renderObject->GetComponent< Renderer >() ) {
            for( Primitive* p :
                    renderObject->GetComponent< Renderer >()->GetPrimitives() ) {

                primitives.emplace_back(
                        p->ToCameraSpace( worldToCameraMatrix ) );
            }
        }
    }

    filmPlaneHeight = 2.0f * focalLength *
                      ( float ) tan( fieldOfView * 0.5f * M_PI / 180.0 );
    filmPlaneWidth = filmPlaneHeight * aspect;

    pixelUnitWidth = filmPlaneWidth / pixelWidth;
    pixelUnitHeight = filmPlaneHeight / pixelHeight;

#if MULTI_THREAD
    std::vector< std::thread > threads;

    int totalPixel = pixelWidth * pixelHeight;
    int blockSize = ( int ) ceil(
            totalPixel / ( double ) RayTracing::THREAD_NUMBER );

    for( int i = 0; i < RayTracing::THREAD_NUMBER - 1; ++i ) {
        threads.emplace_back( std::thread( [ & ] {
            RenderBlock( i * blockSize, ( i + 1 ) * blockSize,
                         primitives );
        } ) );
    }

    threads.emplace_back( std::thread( [ & ] {
        RenderBlock( ( RayTracing::THREAD_NUMBER - 1 ) * blockSize, totalPixel,
                     primitives );
    } ) );

    for( auto& t : threads ) {
        t.join();
    }

#else
    for( int i = 0; i < pixelWidth * pixelHeight; ++i ) {
        int x = i % pixelWidth;
        int y = i / pixelWidth;

        RenderPixel( x, y, primitives );
    }

    for( Primitive* primitive : primitives ) {
        delete ( primitive );
    }
#endif
}

void Camera::RenderPixel( int x, int y,
                          std::vector< Primitive* >& primitives ) {
    float3 point( x * pixelUnitWidth - filmPlaneWidth * 0.5f +
                  pixelUnitWidth * 0.5f,
                  -y * pixelUnitHeight + filmPlaneHeight * 0.5f -
                  pixelUnitHeight * 0.5f,
                  focalLength
    );

    Ray ray = ViewportPointToRay( point );
    float4 finalColor = backgroundColor;
    float depth = farClipPlane;

    for( Primitive* primitive : primitives ) {
        float distance = primitive->Intersect( ray );

        if( distance > 0 && distance < depth ) {
            finalColor = primitive->mesh->renderer->material->color;
            depth = distance;
        }
    }

//    depth /= farClipPlane;
//    depth = 1.0f - depth;
//    depth = farClipPlane - depth;

    depth = ( 1 / depth - 1 / nearClipPlane ) /
            ( 1 / farClipPlane - 1 / nearClipPlane );

    depth = depth > 1.0f ? 1.0f : depth;
    depth = depth < 0.0f ? 0.0f : depth;

    depth = 1.0f - depth;

//    depth = logf( 1 * depth + 1 ) / logf( 1 * farClipPlane + 1 ) *
//            depth;

    targetTexture.WriteDepthBuffer( x, y, depth, 110 );
    targetTexture.WriteColorBuffer( x, y, finalColor );
}

void Camera::RenderBlock( int start, int end,
                          std::vector< Primitive* >& primitives ) {
    for( int i = start; i < end; ++i ) {
        int x = i % pixelWidth;
        int y = i / pixelWidth;

        RenderPixel( x, y, primitives );
    }
}

Ray Camera::ViewportPointToRay( float3 position ) const {
    return Ray( float3( 0, 0, 0 ), position );
}

void Camera::Reset() {
    _pixelWidth = Screen::width;
    _pixelHeight = Screen::height;
    _aspect = Screen::width / ( float ) Screen::height;
    backgroundColor = float4( 0.2f, 0.2f, 0.2f, 1.0f );
    focalLength = 1.0f;
    nearClipPlane = 0.3f;
    farClipPlane = 2000.0f;
    fieldOfView = 60.0f;
}

void Camera::ResetAspect() {
    _aspect = _pixelWidth / ( float ) _pixelHeight;
}

void Camera::ResetWorldToCameraMatrix() {
    _worldToCameraMatrix = float4x4(
            transform->right.x, transform->right.y, transform->right.z,
            -dot( transform->right, transform->positon ),
            transform->up.x, transform->up.y, transform->up.z,
            -dot( transform->up, transform->positon ),
            transform->forward.x, transform->forward.y, transform->forward.z,
            -dot( transform->forward, transform->positon ),
            0.0f, 0.0f, 0.0f, 1.0f
    );

    _cameraToWorldMatrix = inverse( _worldToCameraMatrix );
}

std::vector< Camera* >& Camera::GetAllCameras() {
    return allCameras;
}
