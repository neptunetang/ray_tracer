//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_SPHERE_H
#define BASIC_RAY_TRACER_SPHERE_H

#include "hitable.h"
#include "material.h"
#include <cmath>

class sphere :public hitable{
public:
    vec3 center;
    float radius{};
    material *mat;

    sphere()= default;
    sphere(vec3 c, float r, material *m) : center(c), radius(r), mat(m) {};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual ray random_ray() const {
        vec3 random_starting_point = random_in_unit_sphere()*radius + center;
        vec3 dir = random_starting_point - center;
        ray light_ray(random_starting_point, dir);
        return light_ray;
    }
};

void get_sphere_uv(const vec3 intersection, float& u, float& v);

#endif //BASIC_RAY_TRACER_SPHERE_H
