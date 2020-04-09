//
// Created by neptune on 10-04-20.
//

#ifndef BASIC_RAY_TRACER_METAL_H
#define BASIC_RAY_TRACER_METAL_H

#include "material.h"

class metal : public material{
public:
    metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const;

public:
    vec3 albedo;
    double fuzz;
};


#endif //BASIC_RAY_TRACER_METAL_H
