//
// main.cpp
//
// Created by Jietong Chen on 2/1/2019.
//

#include "pch.h"

using namespace RayTracer;

int RayTracer::THREAD_NUMBER = 8;

void checkLibpng() {
    std::cout << "libpng: " << PNG_LIBPNG_VER << std::endl;
}

int main() {
    checkLibpng();

    std::chrono::time_point scene_start = std::chrono::high_resolution_clock::now();

    Screen::SetResolution( 3200, 2400 );
    Scene scene( "RayTracingScene" );
    scene.renderSettings.maxRayBounces = 4;

    std::shared_ptr< Material > defaultSkybox{
            new Material( new Skybox_Procedural() ) };
    scene.renderSettings.skybox = defaultSkybox;

    Checkerboard2D* checkerboard2D = new Checkerboard2D();
    checkerboard2D->filterMode = Texture::FilterMode::Bilinear;
    checkerboard2D->mainColor = float4( 0.2f, 0.2f, 0.2f, 1.0f );
    checkerboard2D->secondaryColor = float4( 0.67f, 0.67f, 0.67f, 1.0f );

    PerlinNoise* perlinNoise = new PerlinNoise();
    perlinNoise->mainColor = float4( 1.0f, 1.0f, 1.0f, 1.0f );
    perlinNoise->secondaryColor = float4( 0.0f, 0.0f, 0.0f, 1.0f );

//    SceneSetUp( scene );
    GameObject floor = GameObject( "Floor" );
    floor.MoveToScene( scene );

    Renderer* renderer3 = floor.AddComponent< Renderer >();

    Texture2D* tiger = new Texture2D( 500, 500 );
    tiger->ReadTextureFromPNG( "Textures/tiger_head_3.png" );
    tiger->filterMode = Texture::FilterMode::Bilinear;

    std::shared_ptr< Material > M_Floor{ new Material( new Phong() ) };
    M_Floor->color = float4( 0.7f, 0.7f, 0.7f, 1.0f );
    M_Floor->mainTexture = ( Texture* ) checkerboard2D;
    M_Floor->mainTextureScale = float2( 8.0f, 16.0f );

    renderer3->material = M_Floor;
//    renderer3->GetMaterial()->color = float4( 0.7f, 0.7f, 0.7f, 1.0f );
    renderer3->GetMaterial()->UseShader( Shader::Phong );

    Phong* bshader3 = ( Phong* ) renderer3->GetMaterial()->shader;
//    bshader3->mainColor = float4( 0.7f, 0.7f, 0.7f, 1.0f );
    bshader3->shininess = 1.0f;
    bshader3->kd = 1.0f;
    bshader3->ks = 1.0f;

    // bshader3->mainTexture = ( Texture* ) tiger;

    renderer3->mesh = std::make_shared< Mesh >( Mesh() );
    renderer3->GetMesh()->renderer = renderer3;
    std::unique_ptr< Triangle > t1 = std::make_unique< Triangle >();
    std::unique_ptr< Triangle > t2 = std::make_unique< Triangle >();

    t1->vertices[ 0 ] = float3( -5, 0, -10 );
    t1->vertices[ 1 ] = float3( 5, 0, -10 );
    t1->vertices[ 2 ] = float3( -5, 0, 10 );

    t1->normals[ 0 ] = float3( 0, 1, 0 );
    t1->normals[ 1 ] = float3( 0, 1, 0 );
    t1->normals[ 2 ] = float3( 0, 1, 0 );

    t1->uv[ 0 ] = float2( 0, 0 );
    t1->uv[ 1 ] = float2( 1, 0 );
    t1->uv[ 2 ] = float2( 0, 1 );

    t2->vertices[ 0 ] = float3( -5, 0, 10 );
    t2->vertices[ 1 ] = float3( 5, 0, -10 );
    t2->vertices[ 2 ] = float3( 5, 0, 10 );

    t2->normals[ 0 ] = float3( 0, 1, 0 );
    t2->normals[ 1 ] = float3( 0, 1, 0 );
    t2->normals[ 2 ] = float3( 0, 1, 0 );

    t2->uv[ 0 ] = float2( 0, 1 );
    t2->uv[ 1 ] = float2( 1, 0 );
    t2->uv[ 2 ] = float2( 1, 1 );

    renderer3->GetMesh()->AddPrimitive( std::move( t1 ) );
    renderer3->GetMesh()->AddPrimitive( std::move( t2 ) );

    GameObject sphere1 = GameObject( "Sphere 1" );
    sphere1.MoveToScene( scene );

//    sphere1.GetComponent< Transform >()->Translate( -3.413f, 1.326f, -9.88f );
    sphere1.GetComponent< Transform >()->Translate( -3.553f, 1.0f, -9.3f );
    Renderer* renderer1 = sphere1.AddComponent< Renderer >();

    std::shared_ptr< Material > M_Sphere_Transparent{
            new Material( new Phong() ) };
    renderer1->material = M_Sphere_Transparent;
//    renderer1->GetMaterial()->color = float4( 0.65f, 0.4f, 0.0f, 1.0f );
    renderer1->GetMaterial()->UseShader( Shader::Cook_Torrance );

    Cook_Torrance* bshader1 = ( Cook_Torrance* ) renderer1->GetMaterial()->shader;
//    bshader1->mainColor = float4( 0.65f, 0.4f, 0.0f, 0.1f );
    bshader1->mainColor = float4( 1.0f, 1.0f, 1.0f, 1.0f );
//    bshader1->shininess = 1.0f;
//    bshader1->kd = 1.0f;
//    bshader1->ks = 1.0f;
    bshader1->smoothness = 0.2f;
    bshader1->metallic = 0.0f;

    renderer1->mesh = std::make_shared< Mesh >( Mesh() );
    renderer1->GetMesh()->renderer = renderer1;
    std::unique_ptr< Sphere > p = std::make_unique< Sphere >();
    p->radius = .5f;
    renderer1->GetMesh()->AddPrimitive( std::move( p ) );

    GameObject sphere2 = GameObject( "Sphere 2" );
    sphere2.MoveToScene( scene );

    sphere2.GetComponent< Transform >()->Translate( -2.628f, 0.949f, -8.732f );
    Renderer* renderer2 = sphere2.AddComponent< Renderer >();

    std::shared_ptr< Material > M_Sphere_Metal{ new Material( new Phong() ) };
//    Material M_Sphere_Metal( new Phong() );
//    M_Sphere_Metal->color = float4( 0.1f, 0.6f, 0.21f, 1.0f );
    renderer2->material = M_Sphere_Metal;
//    renderer2->GetMaterial()->color = float4( 0.1f, 0.6f, 0.21f, 1.0f );
    renderer2->GetMaterial()->UseShader( Shader::Phong );

    Phong* bshader2 = ( Phong* ) renderer2->GetMaterial()->shader;
//    bshader2->mainColor = float4( 0.1f, 0.6f, 0.21f, 1.0f );
    bshader2->shininess = 1.0f;
    bshader2->kd = 1.0f;
    bshader2->ks = 1.0f;

    renderer2->mesh = std::make_shared< Mesh >( Mesh() );
    renderer2->GetMesh()->renderer = renderer2;
    std::unique_ptr< Sphere > p2 = std::make_unique< Sphere >();
    p2->radius = .5f;
    renderer2->GetMesh()->AddPrimitive( std::move( p2 ) );


    GameObject cube = GameObject( "Cube" );
    cube.MoveToScene( scene );

    cube.GetComponent< Transform >()->Translate( -1.51f, 1.94f, -6.708f );
    cube.GetComponent< Transform >()->Rotate( 8.8f, -13.88f, 0.0f );

//    floor.SetActive( false );
//    sphere1.SetActive( false );
    sphere2.SetActive( false );
    cube.SetActive( false );

    Renderer* renderer4 = cube.AddComponent< Renderer >();

    std::shared_ptr< Material > M_Cube{ new Material( new Phong() ) };
    renderer4->material = M_Cube;
//    renderer4->GetMaterial()->color = float4( 0.2f, 0.3f, 0.78f, 1.0f );
    renderer4->GetMaterial()->UseShader( Shader::Phong );

    Phong* bshader4 = ( Phong* ) renderer4->GetMaterial()->shader;
//    bshader4->mainColor = float4( 0.2f, 0.3f, 0.78f, 1.0f );
    bshader4->shininess = 1.0f;
    bshader4->kd = 1.0f;
    bshader4->ks = 1.0f;

    renderer4->mesh = std::make_shared< Mesh >( Mesh() );
    renderer4->GetMesh()->renderer = renderer4;
    renderer4->GetMesh()->ReadOBJ( "cube.obj" );

    // Lighting
    GameObject dLight = GameObject( "Directional Light" );
    dLight.MoveToScene( scene );

    dLight.GetComponent< Transform >()->Rotate( 40.0f, 15.0f, 0.0f );

    Light* light = dLight.AddComponent< Light >();
    light->type = Light::Directional;

//    light->color = float4( 1.0f, 0.9568627f, 0.8392157f, 1.0f );
    light->color = float4( 1.0f, 1.0f, 1.0f, 1.0f );
    light->intensity = 1.0f;

    GameObject dLight2 = GameObject( "Directional Light" );
    dLight2.MoveToScene( scene );

    dLight2.GetComponent< Transform >()->Rotate( 36.5f, -77.9f, 0.0f );

    light = dLight2.AddComponent< Light >();
    light->type = Light::Directional;
    light->color = float4( 1.0f, 1.0f, 1.0f, 1.0f );
    light->intensity = 1.0f;

    GameObject pLight = GameObject( "Point Light" );
    pLight.MoveToScene( scene );

//    pLight.GetComponent< Transform >()->Translate( -0.973f, 2.808f, -10.094f );
    pLight.GetComponent< Transform >()->Translate( -0.973f, 2.808f, -9.88f );

    Light* light2 = pLight.AddComponent< Light >();
    light2->type = Light::Point;

    light2->color = float4( 1.0f, 1.0f, 1.0f, 1.0f );
    light2->intensity = 1.0f;

//    dLight.SetActive( false );
    dLight2.SetActive( false );
    pLight.SetActive( false );

    // use the directional light as sun
    scene.renderSettings.sun = light;

    // Cameras
    Camera camera1;
    camera1.MoveToScene( scene );

    camera1.GetComponent< Transform >()->Translate( -3.428f, 1.283f, -12.022f );

//    camera1.allowMSAA = true;

    Camera camera2;
    camera2.MoveToScene( scene );

    camera2.GetComponent< Transform >()->Translate( -6.95f, 3.4f, -5.88f );
    camera2.GetComponent< Transform >()->Rotate( 25.1f, 120.0f, 0.0f );

//    camera2.allowMSAA = true;

    std::chrono::time_point scene_end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds time =
            std::chrono::duration_cast< std::chrono::milliseconds >(
                    scene_end - scene_start );

    std::cout << "scene construction:\t" << std::setprecision( 3 ) << std::fixed
              << time.count() * 0.001 << "s" << std::endl;

    std::chrono::time_point render_start = std::chrono::high_resolution_clock::now();

    Camera::main = Camera::allCameras[ 0 ];
    Camera::main->Render();

    std::chrono::time_point render_end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast< std::chrono::milliseconds >(
            render_end - render_start );

    std::cout << "scene rendering:\t" << time.count() * 0.001 << "s"
              << std::endl;

    Texture2D color = Texture2D( Screen::width, Screen::height );
    BYTE* ptr = Camera::main->targetTexture.colorBuffer.GetNativeRenderBufferPtr();
    color.LoadRawTextureData(
            ptr );
    color.SaveTextureToPNG( scene.name + ".png" );

    Texture2D depth = Texture2D( Screen::width, Screen::height,
                                 Texture2D::RFloat );
//    ptr = Camera::main->targetTexture.depthBuffer.GetNativeRenderBufferPtr();
//    depth.LoadRawTextureData(
//            ptr );
//    depth.SaveTextureToPNG( scene.name + "_depth.png" );

    delete ( tiger );

    return 0;
}
