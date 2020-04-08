//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_SPHERE_H
#define BASIC_RAY_TRACER_SPHERE_H

#include "hitable.h"
#include "vec3.h"

class sphere :public hitable{
public:
    vec3 center;
    float radius{};

    sphere()= default;
    sphere(vec3 cen, float r) : center(cen), radius(r){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};


#endif //BASIC_RAY_TRACER_SPHERE_H
