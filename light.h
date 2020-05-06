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
    vec3 point_at;
    float angle;
    vec3 color;
    float strength;
    light() = default;
    light(vec3 p, vec3 c, float s, vec3 d, float a):position(p), color(c), strength(s), point_at(d), angle(a){}
};


#endif //BASIC_RAY_TRACER_LIGHT_H
