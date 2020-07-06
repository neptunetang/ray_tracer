//
// Created by neptune on 05-05-20.
//

#ifndef BASIC_RAY_TRACER_LIGHT_H
#define BASIC_RAY_TRACER_LIGHT_H

#include "ray.h"
#include "../shapes/hitable.h"

class light{
public:
    hitable* area;
    vec3 color;
    float intensity;
    light() = default;
    light(hitable* shape, vec3 c, float s): area(shape), color(c), intensity(s){}


    vec3 start(){
        return area->random_start();
    }

    bool on_light(vec3 a){
        return area->on(a);
    }
};


#endif //BASIC_RAY_TRACER_LIGHT_H
