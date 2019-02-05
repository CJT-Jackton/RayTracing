//
// Material.h
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Object.h"

class Material : public Object {
public:
    Material();

public:
    float4 color;
}; // Material

#endif // MATERIAL_H
