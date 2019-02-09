//
// Material.h
//
// The material class.
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef MATERIAL_H
#define MATERIAL_H

namespace RayTracing {
    /**
     * The material class.
     */
    class Material : public Object {
    public:
        /**
         * Create a Material.
         */
        Material();

    public:
        /** the color */
        float4 color;
    }; // Material
} // RayTracing

#endif // MATERIAL_H
