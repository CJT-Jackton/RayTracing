//
// RenderSettings.cpp
//
// The implementation of RenderSettings.
//
// Created by Jietong Chen on 2019/3/21.
//

#include "pch.h"

using RayTracer::RenderSettings;
using RayTracer::Material;
using RayTracer::Light;

/**
 * Create a new Render Settings.
 */
RenderSettings::RenderSettings() :
        Object{ "Render Settings" },
        skybox{},
        sun{} {
}

/**
 * Copy the Render Settings from another Render Settings.
 *
 * @param other the RenderSettings to copy from.
 */
RenderSettings::RenderSettings( const RenderSettings& other ) :
        Object{ "Render Settings" },
        skybox{ other.skybox },
        sun{ other.sun } {
}

/**
 * Assign the Render Settings with another Render Settings.
 *
 * @param other the RenderSettings to assign
 *
 * @return this RenderSettins
 */
RenderSettings& RenderSettings::operator=( const RenderSettings& other ) {
    if( this != &other ) {
        skybox = other.skybox;
        sun = other.sun;
    }

    return *this;
}
