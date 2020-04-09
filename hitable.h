//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_HITABLE_H
#define BASIC_RAY_TRACER_HITABLE_H
#include "ray.h"

class material;

struct hit_record{
    float t;
    vec3 intersection;
    vec3 normal;
    material *mat;
};

class hitable {
public:
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};


#endif //BASIC_RAY_TRACER_HITABLE_H
