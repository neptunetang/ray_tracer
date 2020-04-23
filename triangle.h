//
// Created by neptune on 23-04-20.
//

#ifndef BASIC_RAY_TRACER_TRIANGLE_H
#define BASIC_RAY_TRACER_TRIANGLE_H

#include "hitable.h"

class triangle :public hitable{
public:
    vec3 a,b,c;
    material *mat;
    triangle() = default;
    triangle(vec3 x, vec3 y, vec3 z, material* m) : a(x), b(y), c(z), mat(m){}

    virtual bool is_hit(ray &r, float t_min, float t_max, hit_record& rec) const;
};


#endif //BASIC_RAY_TRACER_TRIANGLE_H
