//
// Created by neptune on 05-05-20.
//

#ifndef BASIC_RAY_TRACER_LIGHT_H
#define BASIC_RAY_TRACER_LIGHT_H

#include "ray.h"
#include "hitable.h"

class light{
public:
    vec3 position;
    vec3 color;
    float strength;
    light() = default;
    light(vec3 p, vec3 c, float s):position(p), color(c), strength(s){}
};


#endif //BASIC_RAY_TRACER_LIGHT_H
