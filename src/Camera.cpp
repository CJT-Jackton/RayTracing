//
// Camera.cpp
//
// The implementation of Camera.
//
// Created by Jietong Chen on 1/31/2019.
//

#include "pch.h"

using RayTracer::Camera;
using RayTracer::Ray;
using RayTracer::Primitive;
using RayTracer::Light;
using RayTracer::Shader;
using RayTracer::Phong;
using RayTracer::BlinnPhong;

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
        allowMSAA{ false },
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
        allowMSAA{ other.allowMSAA },
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
//    std::vector< GameObject* > allObjects{ rootGameObjects };
    std::vector< GameObject* > allObjects;

    for( GameObject* gameObject : rootGameObjects ) {
        if( this != gameObject ) {
            GameObject* goInCameraSpace = new GameObject( *gameObject );
            goInCameraSpace->transform->ToSpace( worldToCameraMatrix );
            allObjects.emplace_back( goInCameraSpace );
        }
    }

    std::vector< Primitive* > primitives;
    std::vector< Light* > lights;

    for( GameObject* gameObject : allObjects ) {
        if( *gameObject && gameObject->GetComponent< Renderer >() ) {
            for( Primitive* p :
                    gameObject->GetComponent< Renderer >()->GetPrimitives() ) {

                primitives.emplace_back( p );
            }
        }

        if( *gameObject && gameObject->GetComponent< Light >() ) {
            lights.emplace_back( gameObject->GetComponent< Light >() );
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
            totalPixel / ( double ) RayTracer::THREAD_NUMBER );

    for( int i = 0; i < RayTracer::THREAD_NUMBER - 1; ++i ) {
        threads.emplace_back( std::move( std::thread( [ & ] {
            RenderBlock( i * blockSize, ( i + 1 ) * blockSize,
                         primitives, lights );
        } ) ) );

        std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
    }

    threads.emplace_back( std::move( std::thread( [ & ] {
        RenderBlock( ( RayTracer::THREAD_NUMBER - 1 ) * blockSize, totalPixel,
                     primitives, lights );
    } ) ) );

    for( auto& t : threads ) {
        t.join();
    }

#else
    for( int i = 0; i < pixelWidth * pixelHeight; ++i ) {
        int x = i % pixelWidth;
        int y = i / pixelWidth;

        RenderPixel( x, y, primitives, lights );
    }

    for( Primitive* primitive : primitives ) {
        delete ( primitive );
    }
#endif

//    for( GameObject* gameObject : allObjects ) {
//        delete ( gameObject );
//    }
}

void Camera::RenderPixel( int x, int y,
                          std::vector< Primitive* >& primitives,
                          std::vector< Light* >& lights ) {
    float3 point( x * pixelUnitWidth - filmPlaneWidth * 0.5f +
                  pixelUnitWidth * 0.5f,
                  -y * pixelUnitHeight + filmPlaneHeight * 0.5f -
                  pixelUnitHeight * 0.5f,
                  focalLength );

    float4 finalColor( 0.0f );
    float depth = 0;

    if( !allowMSAA ) {
        Ray ray = ViewportPointToRay( point );
        RenderRay( ray, finalColor, depth, primitives, lights );

    } else {
        float3 samplingPoints[4];

        // 4-rooks pattern
        samplingPoints[ 0 ] = point + float3( 0.125f * pixelUnitWidth,
                                              0.375f * pixelUnitHeight,
                                              0.0f );
        samplingPoints[ 1 ] = point + float3( 0.375f * pixelUnitWidth,
                                              -0.125f * pixelUnitHeight,
                                              0.0f );
        samplingPoints[ 2 ] = point + float3( -0.125f * pixelUnitWidth,
                                              -0.375f * pixelUnitHeight,
                                              0.0f );
        samplingPoints[ 3 ] = point + float3( -0.375f * pixelUnitWidth,
                                              0.125f * pixelUnitHeight,
                                              0.0f );

        for( const float3& samplingPoint : samplingPoints ) {
            float4 subColor;
            float subDepth;

            Ray ray = ViewportPointToRay( samplingPoint );
            RenderRay( ray, subColor, subDepth, primitives, lights );

            finalColor += 0.25f * subColor;
            depth += 0.25f * subDepth;
        }
    }

    targetTexture.WriteDepthBuffer( x, y, depth, 110 );
    targetTexture.WriteColorBuffer( x, y, finalColor );
}

void Camera::RenderBlock( int start, int end,
                          std::vector< Primitive* >& primitives,
                          std::vector< Light* >& lights ) {
    for( int i = start; i < end; ++i ) {
        int x = i % pixelWidth;
        int y = i / pixelWidth;

        RenderPixel( x, y, primitives, lights );
    }
}

void Camera::RenderRay( const Ray& ray, float4& color, float& depth,
                        const std::vector< Primitive* >& primitives,
                        const std::vector< Light* >& lights ) {
    RaycastHit hit;
    RaycastHit hitInfo;

    float4 finalColor = backgroundColor;
    depth = farClipPlane;
    int nearestIndex = -1;

    for( unsigned int i = 0; i < primitives.size(); ++i ) {
        if( primitives[ i ]->Intersect( ray, hitInfo ) ) {
            if( hitInfo.distance < depth ) {
                nearestIndex = i;
                depth = hitInfo.distance;
                hit = hitInfo;
            }
        }
    }

    if( nearestIndex >= 0 ) {
        finalColor = float4( 0.0f );

        for( const Light* light : lights ) {
            bool inShadow = false;
            Ray shadowRay = light->GetShadowRay( hit.point );
            RaycastHit h;

            for( unsigned int i = 0; i < primitives.size(); ++i ) {
                if( i != nearestIndex ) {
                    if( primitives[ i ]->Intersect( shadowRay, h ) ) {
                        inShadow = true;
                        break;
                    }
                }
            }

            if( inShadow ) {
                continue;
            }

            Shader* shader =
                    primitives[ nearestIndex ]->mesh->renderer->material->shader;

            if( shader->Type() == Shader::Phong ) {
                Phong pshader = Phong( ( const Phong& ) *shader );

                pshader.view = -ray.direction;
                pshader.normal = hit.normal;
                pshader.light = shadowRay.direction;
                pshader.uv = hit.textureCoord;

                pshader.lightPositon = light->gameObject->transform->positon;
                pshader.lightColor = light->color * light->intensity;

                finalColor += pshader.Shading();
            } else if( shader->Type() == Shader::BlinnPhong ) {
                BlinnPhong bshader = BlinnPhong(
                        ( const BlinnPhong& ) *shader );

                bshader.view = -ray.direction;
                bshader.normal = hit.normal;
                bshader.light = shadowRay.direction;
                bshader.uv = hit.textureCoord;

                bshader.lightPositon = light->gameObject->transform->positon;
                bshader.lightColor = light->color * light->intensity;

                finalColor += bshader.Shading();
            }
        }
    }

    depth = ( 1 / depth - 1 / nearClipPlane ) /
            ( 1 / farClipPlane - 1 / nearClipPlane );

    depth = depth > 1.0f ? 1.0f : depth;
    depth = depth < 0.0f ? 0.0f : depth;

    depth = 1.0f - depth;

    color = finalColor;
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
