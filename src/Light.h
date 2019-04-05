//
// Light.h
//
// The light component.
//
// Created by Jietong Chen on 1/31/2019.
//

#ifndef LIGHT_H
#define LIGHT_H

#include "pch.h"

namespace RayTracer {
    /**
     * The light component.
     */
    class Light : public Component {
    public:
        /**
         * The type of a Light.
         */
        enum LightType {
            Directional,
            Point,
            Spot
        };

        /**
         * Shadow casting options for a Light.
         */
        enum LightShadows{
            None,
            Hard,
            Translucent
        };

        /**
         * Create a Light attached to a GameObject.
         *
         * @param gameObject the GameObject to attach
         */
        Light( GameObject* gameObject );

        /**
         * Create a Light attached to a GameObject with given name.
         *
         * @param gameObject the GameObject to attach
         * @param name the name
         */
        Light( GameObject* gameObject, std::string name );

        /**
         * Assign the Light with another Light.
         *
         * @param other the Light to assign
         *
         * @return this Light
         */
        Light& operator=( const Light& other );

        /**
         * Calculate the shadow ray of a point. Shadow ray is a ray from a
         * given point pointing to the light source.
         *
         * @param point the point
         *
         * @return the shadow ray
         */
        Ray GetShadowRay( float3 point ) const;

    public:
        /** the type of the light */
        LightType type;

        /** the color of the light */
        float4 color;

        /** the intensity of a light is multiplied with the Light color */
        float intensity;

        /** how this light casts shadow */
        LightShadows shadows;

        /** shadow ray constant bias */
        float shadowBias;

    }; // Light
} // RayTracer

#endif // LIGHT_H
