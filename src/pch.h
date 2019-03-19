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

	class BlinnPhong;

	class Camera;

	class Checkerboard2D;

	class Component;

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

	class RenderTexture;

	class Scene;

	class Screen;

	class Shader;

	class Skybox_Procedural

	class Sphere;

	class Texture;

	class Texture2D;

	class Transform;

	class Triangle;

} // RayTracer

#include "Object.h"
#include "Component.h"
#include "Scene.h"
#include "Screen.h"
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
#include "Shader.h"
#include "Phong.h"
#include "BlinnPhong.h"
#include "Skybox-Procedural.h"
#include "Material.h"
#include "Transform.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"

#endif // PCH_H
