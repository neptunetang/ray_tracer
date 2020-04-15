//
// Created by neptune on 13-04-20.
//

#ifndef BASIC_RAY_TRACER_TEXTURE_H
#define BASIC_RAY_TRACER_TEXTURE_H

#include "ray.h"

class texture {
public:
    virtual vec3 value(float u, float v, const vec3 &p)const = 0;
};


#endif //BASIC_RAY_TRACER_TEXTURE_H
