//
// Created by neptune on 10-04-20.
//

#ifndef BASIC_RAY_TRACER_METAL_H
#define BASIC_RAY_TRACER_METAL_H

#include "material.h"
#include "../texture/texture.h"

class metal : public material{
public:
    metal(texture* a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, double& pdf
    ) const{
        vec3 reflected = reflect(unit_vec(r_in.direction()), rec.normal);
        scattered = ray(rec.intersection, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo->value(rec.u, rec.v, rec.intersection);
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    texture* albedo;
    double fuzz;
};


#endif //BASIC_RAY_TRACER_METAL_H
