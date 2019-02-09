//
// Material.cpp
//
// The implementation of Material.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracing::Material;

/**
 * Create a Material.
 */
Material::Material() :
        Object{ "Default-Material" },
        color{ 0.8f, 0.8f, 0.8f, 1.0f } {
}
