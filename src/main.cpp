//
// main.cpp
//
// Created by Jietong Chen on 2/1/2019.
//

#include "pch.h"

#include <iostream>

using namespace RayTracing;

void checkLibpng() {
    std::cout << "libpng: " << PNG_LIBPNG_VER << std::endl;
}

int main() {
    checkLibpng();

    Screen::SetResolution( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    Scene scene( "RayTracingScene" );

//    SceneSetUp( scene );
    GameObject sphere1 = GameObject( "Sphere 1" );
    sphere1.MoveToScene( scene );

    sphere1.GetComponent< Transform >()->Translate( -3.413f, 1.326f, -9.88f );
    Renderer* renderer1 = sphere1.AddComponent< Renderer >();

    renderer1->GetMaterial()->color = float4( 0.65f, 0.4f, 0.0f, 1.0f );

    renderer1->mesh = new Mesh();
    renderer1->GetMesh()->renderer = renderer1;
    std::unique_ptr< Sphere > p = std::make_unique< Sphere >();
    p->radius = .5f;
    renderer1->GetMesh()->AddPrimitive( std::move( p ) );

    GameObject sphere2 = GameObject( "Sphere 2" );
    sphere2.MoveToScene( scene );

    sphere2.GetComponent< Transform >()->Translate( -2.628f, 0.949f, -8.732f );
    Renderer* renderer2 = sphere2.AddComponent< Renderer >();

    renderer2->GetMaterial()->color = float4( 0.1f, 0.6f, 0.21f, 1.0f );

    renderer2->mesh = new Mesh();
    renderer2->GetMesh()->renderer = renderer2;
    std::unique_ptr< Sphere > p2 = std::make_unique< Sphere >();
    p2->radius = .5f;
    renderer2->GetMesh()->AddPrimitive( std::move( p2 ) );

    GameObject floor = GameObject( "Floor" );
    floor.MoveToScene( scene );

    Renderer* renderer3 = floor.AddComponent< Renderer >();

    renderer3->GetMaterial()->color = float4( 0.7f, 0.7f, 0.7f, 1.0f );

    renderer3->mesh = new Mesh();
    renderer3->GetMesh()->renderer = renderer3;
    std::unique_ptr< Triangle > t1 = std::make_unique< Triangle >();
    std::unique_ptr< Triangle > t2 = std::make_unique< Triangle >();

    t1->vertices[ 0 ] = float3( -5, 0, -10 );
    t1->vertices[ 1 ] = float3( 5, 0, -10 );
    t1->vertices[ 2 ] = float3( -5, 0, 10 );

    t2->vertices[ 0 ] = float3( -5, 0, 10 );
    t2->vertices[ 1 ] = float3( 5, 0, -10 );
    t2->vertices[ 2 ] = float3( 5, 0, 10 );

    renderer3->GetMesh()->AddPrimitive( std::move( t1 ) );
    renderer3->GetMesh()->AddPrimitive( std::move( t2 ) );

    //AddCamera( scene );
    Camera camera1;
    camera1.MoveToScene( scene );

    camera1.GetComponent< Transform >()->Translate( -3.428f, 1.283f, -12.022f );
    camera1.fieldOfView = 60.0f;
    camera1.focalLength = 1000.0f;

    Camera::main = Camera::allCameras[ 0 ];

    Camera::main->Render();

    Texture2D color = Texture2D( Screen::width, Screen::height );
    color.LoadRawTextureData(
            Camera::main->targetTexture.colorBuffer.GetNativeRenderBufferPtr() );
    color.SaveTextureToPNG( "result.png" );

    return 0;
}
