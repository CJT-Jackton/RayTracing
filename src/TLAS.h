//
// TLAS.h
//
// Created by Jietong Chen on 2019/4/9.
//

#ifndef TLAS_H
#define TLAS_H


#include "Shader/Shader.h"

namespace RayTracer {
    class TLAS {
    public:
        TLAS();

    private:
        std::vector< Shader* > shaderTable;
    };
} // RayTracer

#endif // TLAS_H
