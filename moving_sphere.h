//
// Created by neptune on 12-04-20.
//

#ifndef BASIC_RAY_TRACER_MOVING_SPHERE_H
#define BASIC_RAY_TRACER_MOVING_SPHERE_H

#include "hitable.h"

class moving_sphere :public hitable{
public:
    vec3 center0, center1;
    float time0, time1;
    float radius;
    material *mat;
    moving_sphere() = default;
    moving_sphere(vec3 c0, vec3 c1, double t0, double t1, double r, material *m):
    center0(c0), center1(c1), time0(t0), time1(t1), radius(r), mat(m){};

    virtual bool is_hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

    vec3 center(double time) const;
};


#endif //BASIC_RAY_TRACER_MOVING_SPHERE_H
