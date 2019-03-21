//
// RenderSettings.h
//
// The Render Settings contain values for a range of visual elements in
// the Scene, like sun light and skybox.
//
// Created by Jietong Chen on 2019/3/21.
//

#ifndef RENDERSETTINGS_H
#define RENDERSETTINGS_H

#include "Object.h"

namespace RayTracer {
    /**
     * The Render Settings contain values for a range of visual elements in
     * the Scene, like sun light and skybox.
     */
    class RenderSettings : public Object {
    public:
        /**
         * Create a new Render Settings.
         */
        RenderSettings();

        /**
         * Copy the Render Settings from another Render Settings.
         *
         * @param other the RenderSettings to copy from.
         */
        RenderSettings( const RenderSettings& other );

        /**
         * Assign the Render Settings with another Render Settings.
         *
         * @param other the RenderSettings to assign
         *
         * @return this RenderSettins
         */
        RenderSettings& operator=( const RenderSettings& other );

    public:
        /** the global skybox material to use */
        std::shared_ptr< Material > skybox;

        /** the light used by the procedural skybox */
        Light* sun;

    }; // RenderSettings
} // RayTracer

#endif // RENDERSETTINGS_H
