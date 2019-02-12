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

#include <hlsl++.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
//#include <png.h>
#include <png.hpp>

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600

namespace RayTracing {
    typedef unsigned char BYTE;
    typedef unsigned int png_uint_32;

    class Camera;

    class Component;

    class GameObject;

    class Light;

    class Material;

    class Mesh;

    class Object;

    class Primitive;

    class Ray;

    struct RenderBuffer;

    class Renderer;

    class RenderTexture;

    class Scene;

    class Screen;

    class Sphere;

    class Texture;

    class Texture2D;

    class Transform;

    class Triangle;
} // RayTracing

#include "Object.h"
#include "Component.h"
#include "Scene.h"
#include "Screen.h"
#include "Ray.h"
#include "Primitive.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Texture.h"
#include "RenderBuffer.h"
#include "RenderTexture.h"
#include "Texture2D.h"
#include "Material.h"
#include "Transform.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"

#endif // PCH_H