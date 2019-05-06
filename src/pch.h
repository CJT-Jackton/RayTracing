//
// pch.h
//
// Precomilped header.
//
// Created by Jietong Chen on 2/1/2019.
//

#ifndef PCH_H
#define PCH_H

#define _USE_MATH_DEFINES

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600

#define MULTI_THREAD true

#include <hlsl++.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <memory>
#include <mutex>
#include <vector>
//#include <png.h>
#include <png.hpp>

#if MULTI_THREAD

#include <thread>

#endif

namespace hlslpp {
    hlslpp_inline float3 refract( const float3& i, const float3& n,
                                  const float1& k ) {
        float1 t = 1.0f - k * k * ( 1.0f - dot( n, i ) * dot( n, i ) );
        if( t.x < 0.0f )
            return float3( 0.0f );
        else
            return k * i - ( k * dot( n, i ) + sqrt( t ) ) * n;
    }
}

namespace RayTracer {
    extern int THREAD_NUMBER;

    typedef unsigned char BYTE;
    typedef unsigned int png_uint_32;

    /**
     * Union of float and 4-byte.
     */
    union floatBYTE {
        float f;
        BYTE byte[4];
    };

    class BLAS;

    class BlinnPhong;

    class Bounds;

    class Camera;

    class Checkerboard2D;

    class Component;

    class Cook_Torrance;

    class GameObject;

    class Light;

    class Material;

    class Mesh;

    class Object;

    class PerlinNoise;

    class Phong;

    class Primitive;

    class ProceduralTexture;

    class Ray;

    struct RaycastHit;

    struct RenderBuffer;

    class Renderer;

    class RenderSettings;

    class RenderTexture;

    class Scene;

    class Screen;

    class Shader;

    class Skybox_Procedural;

    class Sphere;

    class Texture;

    class Texture2D;

    class TLAS;

    class Transform;

    class Triangle;

    class Unlit;

} // RayTracer

#include "Object.h"
#include "Bounds.h"
#include "BLAS.h"
#include "TLAS.h"
#include "Component.h"
#include "Scene.h"
#include "Screen.h"
#include "RenderSettings.h"
#include "RaycastHit.h"
#include "Ray.h"
#include "Primitive.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderBuffer.h"
#include "RenderTexture.h"
#include "Texture2D.h"
#include "ProceduralTexture.h"
#include "Checkerboard2D.h"
#include "PerlinNoise.h"
#include "Shader/Shader.h"
#include "Shader/Phong.h"
#include "Shader/BlinnPhong.h"
#include "Shader/Cook-Torrance.h"
#include "Shader/Skybox-Procedural.h"
#include "Shader/Unlit.h"
#include "Material.h"
#include "Transform.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"

#endif // PCH_H
