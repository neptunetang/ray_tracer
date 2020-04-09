//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_SPHERE_H
#define BASIC_RAY_TRACER_SPHERE_H

#include "hitable.h"

class sphere :public hitable{
public:
    vec3 center;
    float radius{};
    material *mat;

    sphere()= default;
    sphere(vec3 c, float r, material *m) : center(c), radius(r), mat(m) {};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};


#endif //BASIC_RAY_TRACER_SPHERE_H
