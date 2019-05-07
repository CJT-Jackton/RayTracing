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
    //float depth = 0;

    if( x == 350 && y == 432 ) {
        x = 350;
    }

    if( !allowMSAA ) {
        Ray ray = ViewportPointToRay( point );
        finalColor = RenderRay( ray, primitives, lights, 0 );

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

            Ray ray = ViewportPointToRay( samplingPoint );
            subColor = RenderRay( ray, primitives, lights, 0 );

            finalColor += 0.25f * subColor;
        }
    }

    //targetTexture.WriteDepthBuffer( x, y, depth, 110 );
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

float4 Camera::RenderRay( const Ray& ray,
                          const std::vector< Primitive* >& primitives,
                          const std::vector< Light* >& lights,
                          int rayBouncesNumber ) {
    if( rayBouncesNumber >= _scene->renderSettings.maxRayBounces ) {
        return float4( 0.0f );
    }

    RaycastHit hit;
    RaycastHit hitInfo;

    // the final color of the ray
    float4 finalColor = backgroundColor;

    float depth = farClipPlane;

    // the index of nearest object got hit
    int nearestIndex = -1;

    // calculate the intersect between ray and primitives
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
        // ray hit an primitive in the scene
        finalColor = float4( 0.0f );

        // the shader of the hit primitive
        Shader* shader =
                primitives[ nearestIndex ]->mesh->renderer->material->shader;

        float transparency =
                primitives[ nearestIndex ]->mesh->renderer->material->color.a;

        // calculate direct light iluminate
        for( const Light* light : lights ) {
            // the strength of shadow
            float3 shadow = float3( 1.0f );

            Ray shadowRay = light->GetShadowRay( hit.point );

            // don't calculate the shadow if the point doesn't face the light
            if( dot( hit.normal, shadowRay.direction ) < 0.0f ) {
                shadow = float3( 1.0f );
            }

            RaycastHit h;

            if( light->shadows != Light::LightShadows::None ) {
                for( unsigned int i = 0; i < primitives.size(); ++i ) {
                    if( i == nearestIndex ) {
                        continue;
                    }

                    if( primitives[ i ]->Intersect( shadowRay, h ) ) {
                        if( light->shadows == Light::LightShadows::Hard ) {
                            break;

                        } else if( light->shadows ==
                                   Light::LightShadows::Translucent ) {
                            shadow -= ( float ) primitives[ i ]->mesh->renderer->material->color.a;
                        }

                        // no light illuminate the hit point
                        if( shadow.x < 0.0f ) {
                            shadow = float3( 0.0f );
                            break;
                        }
                    }
                }
            }

            if( shader->Type() == Shader::Phong ) {
                Phong pshader = Phong( ( const Phong& ) *shader );

                pshader.view = -ray.direction;
                pshader.normal = hit.normal;
                pshader.light = shadowRay.direction;
                pshader.uv = hit.textureCoord;

                pshader.shadow = shadow;

                pshader.lightPositon = light->gameObject->transform->positon;
                pshader.lightColor = ( light->color * light->intensity ).xyz;

                finalColor += pshader.Shading();

            } else if( shader->Type() == Shader::BlinnPhong ) {
                BlinnPhong bshader = BlinnPhong(
                        ( const BlinnPhong& ) *shader );

                bshader.view = -ray.direction;
                bshader.normal = hit.normal;
                bshader.light = shadowRay.direction;
                bshader.uv = hit.textureCoord;

                bshader.shadow = shadow;

                bshader.lightPositon = light->gameObject->transform->positon;
                bshader.lightColor = ( light->color * light->intensity ).xyz;

                finalColor += bshader.Shading();

            } else if( shader->Type() == Shader::Cook_Torrance ) {
                float3 reflectionVector = reflect( ray.direction, hit.normal );
                Ray reflectionRay( hit.point + reflectionVector * 0.01f,
                                   reflectionVector );
                float4 reflection = RenderRay( reflectionRay, primitives,
                                               lights, rayBouncesNumber + 1 );

                // the ratio of indices of refraction
                float refractiveIndex = 1.125f;

                // the ratio of indices of refraction
                float eta;

                float3 refractionVector;

                if( ( float ) dot( ray.direction, hit.normal ) < 0.0f ) {
                    eta = _scene->renderSettings.airRefractiveIndex /
                          refractiveIndex;
                    refractionVector = refract( ray.direction, hit.normal,
                                                eta );
                } else {
                    // ray inside the object
                    eta = refractiveIndex /
                          _scene->renderSettings.airRefractiveIndex;
                    refractionVector = refract( ray.direction, -hit.normal,
                                                eta );
                }

                float4 refraction;

                if( ( float ) length( refractionVector ) != 0.0f ) {
                    // compute refraction
                    Ray refractionRay( hit.point + refractionVector * 0.0001f,
                                       refractionVector );
                    refraction = RenderRay( refractionRay, primitives, lights,
                                            rayBouncesNumber + 1 );
                } else {
                    // no refraction
                    refraction = float4( 0.0f );
                }

                if( ( float ) dot( ray.direction, hit.normal ) >= 0.0f ) {
//                    finalColor += refraction;
                    continue;
                }

                Cook_Torrance cshader = Cook_Torrance(
                        ( const Cook_Torrance& ) *shader );

                cshader.view = -ray.direction;
                cshader.normal = hit.normal;
                cshader.light = shadowRay.direction;
                cshader.uv = hit.textureCoord;

                cshader.shadow = shadow;

                cshader.lightPositon = light->gameObject->transform->positon;
                cshader.lightColor = ( light->color * light->intensity ).rgb;

                cshader.irradiance = reflection.rgb;
//                cshader.reflect = reflection.rgb;
//                cshader.transmit = refraction.rgb;

                finalColor += cshader.Shading();
//                finalColor +=
//                        ( float ) cshader.mainColor.a * cshader.Shading() +
//                        ( 1.0f - ( float ) cshader.mainColor.a ) * refraction;

            } else if( shader->Type() == Shader::Unlit ) {
                finalColor += shader->Shading();
            }
        }

        // calculate indirect light iluminate
        if( shader->Type() == Shader::Phong ) {
            Phong pshader = Phong( ( const Phong& ) *shader );

            finalColor += pshader.IndirectShading();

        } else if( shader->Type() == Shader::BlinnPhong ) {
            BlinnPhong bshader = BlinnPhong( ( const BlinnPhong& ) *shader );

            finalColor += bshader.IndirectShading();

        } else if( shader->Type() == Shader::Cook_Torrance ) {
            // reflection
            float3 reflectionVector = reflect( ray.direction, hit.normal );
            Ray reflectionRay( hit.point + reflectionVector * 0.01f,
                               reflectionVector );
            float4 reflection = RenderRay( reflectionRay, primitives,
                                           lights, rayBouncesNumber + 1 );

            float4 irradiance = float4( 0.0f );

            // tangent vector
            float3 tangent = normalize(
                    float3( 0.0f, 1.0f, -( hit.normal.y / hit.normal.z ) ) );

            // bitangent vector
            float3 bitangent = cross( hit.normal, tangent );

            // convert vector from tangent space to camera space
            float3x3 TBN = float3x3( tangent._vec,
                                     bitangent._vec,
                                     hit.normal._vec );

            std::random_device rd;
            std::mt19937 generator( rd() );
            std::uniform_real_distribution< float > distribution( -1.0f, 1.0f );
            std::uniform_real_distribution< float > distributionh( 0.0f, 1.0f );

            int nSampleRay = _scene->renderSettings.maxSampleRayNumber;
            float wSample = 1.0f / nSampleRay;

//            for( int _ = 0; _ < nSampleRay; ++_ ) {
//                float x = distribution( generator );
//                float y = distributionh( generator );
//                float z = distribution( generator );
//
//                float3 sampleDir = mul( TBN, normalize( float3( x, y, z ) ) );
//                Ray sampleRay = Ray( hit.point + sampleDir * 0.0001f,
//                                     sampleDir );
//                irradiance +=
//                        wSample * RenderRay( sampleRay, primitives, lights,
//                                             rayBouncesNumber + 1 );
//            }
            irradiance = reflection;

            // refraction
            float4 refraction;

            // compute refraction only when needed
            if( transparency < 1.0f ) {
                // the ratio of indices of refraction
                float refractiveIndex = 1.025f;

                // the ratio of indices of refraction
                float eta;

                // the direction of refraction ray
                float3 refractionVector;

                if( ( float ) dot( ray.direction, hit.normal ) < 0.0f ) {
                    // ray shooting from outside
                    eta = _scene->renderSettings.airRefractiveIndex /
                          refractiveIndex;
                    refractionVector = refract( ray.direction, hit.normal,
                                                eta );
                } else {
                    // ray inside the object
                    eta = refractiveIndex /
                          _scene->renderSettings.airRefractiveIndex;
                    refractionVector = refract( ray.direction, -hit.normal,
                                                eta );
                }

                if( ( float ) length( refractionVector ) != 0.0f ) {
                    // compute refraction
                    Ray refractionRay( hit.point + refractionVector * 0.0001f,
                                       refractionVector );
                    refraction = RenderRay( refractionRay, primitives, lights,
                                            rayBouncesNumber + 1 );
                } else {
                    // no refraction
                    refraction = float4( 0.0f );
                }
            } else {
                // no refraction
                refraction = float4( 0.0f );
            }

            Cook_Torrance cshader = Cook_Torrance(
                    ( const Cook_Torrance& ) *shader );

            cshader.view = -ray.direction;
            cshader.normal = hit.normal;
            cshader.uv = hit.textureCoord;

            cshader.irradiance = irradiance.rgb;
            cshader.reflect = reflection.rgb;
            cshader.transmit = refraction.rgb;

            finalColor += cshader.IndirectShading();
        }

    } else {
        // ray hit nothing, return the color of skybox
        if( _scene->renderSettings.skybox ) {
            std::shared_ptr< Material > M_Skybox = _scene->renderSettings.skybox;

            if( M_Skybox->shader->Type() == Shader::Skybox_Procedural ) {
                Skybox_Procedural skyshader = Skybox_Procedural(
                        ( const Skybox_Procedural& ) *M_Skybox->shader );

                if( _scene->renderSettings.sun ) {
                    skyshader._SunDirection =
                            -_scene->renderSettings.sun->gameObject->transform->forward;
                    skyshader._SunColor = _scene->renderSettings.sun->color.xyz;
                }

                float3x3 vectorCameraToWorld = float3x3(
                        _cameraToWorldMatrix._vec0,
                        _cameraToWorldMatrix._vec1,
                        _cameraToWorldMatrix._vec2 );
                vectorCameraToWorld = inverse(
                        transpose( vectorCameraToWorld ) );

//                skyshader.viewRay = mul(
//                        inverse( transpose( _cameraToWorldMatrix ) ),
//                        float4( ray.direction, 1.0f ) ).xyz;
//                skyshader.viewRay = float3(
//                        mul( vectorCameraToWorld, ray.direction )._vec );
                skyshader.viewRay = mul( vectorCameraToWorld,
                                         ray.direction ).xyz;

                finalColor = skyshader.Shading();
            }
        }
    }

//    depth = ( 1 / depth - 1 / nearClipPlane ) /
//            ( 1 / farClipPlane - 1 / nearClipPlane );
//
//    depth = depth > 1.0f ? 1.0f : depth;
//    depth = depth < 0.0f ? 0.0f : depth;
//
//    depth = 1.0f - depth;

    return finalColor;
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
