//
// main.cpp
//
// Created by Jietong Chen on 2/1/2019.
//

#include "pch.h"

void AddCamera( Scene& scene ) {
    Camera camera1;

    camera1.transform.Translate( -3.428f, 1.283f, -12.022f );
    camera1.fieldOfView = 60.0f;

    Camera::main = Camera::allCameras[0];
}

void SceneSetUp( Scene& scene ) {
    GameObject sphere1 = GameObject( "Sphere 1" );
    sphere1.MoveToScene( scene );

    sphere1.transform.Translate( -3.413f, 1.326f, -9.88f );
    sphere1.renderer = Renderer();

    sphere1.renderer.material.color = float4( 0.65f, 0.4f, 0.0f, 1.0f );

    sphere1.renderer.mesh = Mesh();
    Sphere p = Sphere();
    p.radius = .5f;
    sphere1.renderer.mesh.AddPrimitive( std::move( p ) );

    GameObject sphere2 = GameObject( "Sphere 2" );
    sphere2.MoveToScene( scene );

    sphere2.transform.Translate( -2.628f, 0.949f, -8.732f );
    sphere2.renderer = Renderer();

    sphere2.renderer.material.color = float4( 0.1f, 0.2f, 0.61f, 1.0f );

    sphere2.renderer.mesh = Mesh();
    Sphere p2 = Sphere();
    p2.radius = .5f;
    sphere2.renderer.mesh.AddPrimitive( std::move( p2 ) );
}

int main() {
    Screen::SetResolution( 800, 600 );
    Scene scene( "RayTracingScene" );
    SceneSetUp( scene );

    Camera::main->Render();

    return 0;
}
