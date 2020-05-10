//
// Created by neptune on 05-05-20.
//

#ifndef BASIC_RAY_TRACER_LIGHT_H
#define BASIC_RAY_TRACER_LIGHT_H

#include "ray.h"
#include "hitable.h"

#include <vector>

struct light_rec {
    vec3 color;
    vec3 position;
};

class light{
public:
    vector<light_rec> light_path;
    sphere area;
    vec3 color;
    float intensity;
    light() = default;
    light(sphere shape, vec3 c, float s): area(shape), color(c), intensity(s){}

    void save_light_rec(vec3 color, vec3 position){
        light_rec rec;
        rec.color = color;
        rec.position = position;
        light_path.push_back(rec);
        //cout << "save the rec color:" << color.x() << " "<< color.y() << " " << color.z() << " " << "intersection:" << position.x()<< " " << position.y()<< " " << position.z()<< endl;
    }
};


#endif //BASIC_RAY_TRACER_LIGHT_H
