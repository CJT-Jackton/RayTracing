//
// main.cpp
//
// Created by Jietong Chen on 2/1/2019.
//

#include "pch.h"

using namespace RayTracing;

int RayTracing::THREAD_NUMBER = 4;

void checkLibpng() {
    std::cout << "libpng: " << PNG_LIBPNG_VER << std::endl;
}

int main() {
    checkLibpng();

    Screen::SetResolution( 3200, 2400 );
    Scene scene( "RayTracingScene" );

//    SceneSetUp( scene );
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


    GameObject cube = GameObject( "Cube" );
    cube.MoveToScene( scene );

    cube.GetComponent< Transform >()->Translate( -1.51f, 1.94f, -6.708f );
    cube.GetComponent< Transform >()->Rotate( 8.8f, -13.88f, 0.0f );

//    sphere1.SetActive( false );
//    sphere2.SetActive( false );
//    cube.SetActive( false );

    Renderer* renderer4 = cube.AddComponent< Renderer >();

    renderer4->GetMaterial()->color = float4( 0.2f, 0.3f, 0.78f, 1.0f );

    renderer4->mesh = new Mesh();
    renderer4->GetMesh()->renderer = renderer4;
    renderer4->GetMesh()->ReadOBJ( "cube.obj" );

    //AddCamera( scene );
    Camera camera1;
    camera1.MoveToScene( scene );

    camera1.GetComponent< Transform >()->Translate( -3.428f, 1.283f, -12.022f );

    Camera camera2;
    camera2.MoveToScene( scene );

    camera2.GetComponent< Transform >()->Translate( -6.95f, 3.4f, -5.88f );
    camera2.GetComponent< Transform >()->Rotate( 25.1f, 120.0f, 0.0f );

    Camera::main = Camera::allCameras[ 0 ];

    Camera::main->Render();

    Texture2D color = Texture2D( Screen::width, Screen::height );
    BYTE* ptr = Camera::main->targetTexture.colorBuffer.GetNativeRenderBufferPtr();
    color.LoadRawTextureData(
            ptr );
    color.SaveTextureToPNG( scene.name + ".png" );

    Texture2D depth = Texture2D( Screen::width, Screen::height,
                                 Texture2D::RFloat );
    ptr = Camera::main->targetTexture.depthBuffer.GetNativeRenderBufferPtr();
    depth.LoadRawTextureData(
            ptr );
    depth.SaveTextureToPNG( scene.name + "_depth.png" );

    return 0;
}
