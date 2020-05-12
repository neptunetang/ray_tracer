//
// Created by neptune on 05-05-20.
//

#ifndef BASIC_RAY_TRACER_LIGHT_H
#define BASIC_RAY_TRACER_LIGHT_H

#include "ray.h"
#include "hitable.h"

#include <vector>

class light{
public:
    vector<vector<hit_record>> light_path;
    sphere area;
    vec3 color;
    float intensity;
    light() = default;
    light(sphere shape, vec3 c, float s): area(shape), color(c), intensity(s){}

    void save_light_rec(vector<hit_record> positions){
        light_path.push_back(positions);
    }
};


#endif //BASIC_RAY_TRACER_LIGHT_H
