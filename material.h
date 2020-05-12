//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_MATERIAL_H
#define BASIC_RAY_TRACER_MATERIAL_H

#include "hitable.h"
#include "common_method.h"

class material {
public:

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const = 0;

    virtual vec3 emitted(float u, float v, const vec3& p, vec3& attenuation) const {
        return vec3(0,0,0);
    }
    virtual float scatter_pdf(const ray& r_in, const hit_record& rec, const ray& scattered
    ) const {
        return 0;
    }
};

vec3 random_in_unit_sphere();
vec3 random_on_unit_sphere();
vec3 reflect(const vec3& in, const vec3 &n);


#endif //BASIC_RAY_TRACER_MATERIAL_H
