//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_DIFFUSE_H
#define BASIC_RAY_TRACER_DIFFUSE_H

#include "material.h"
#include "texture.h"

class diffuse : public material {
public:
    diffuse(texture *t) : albedo(t) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const{
        vec3 scatter_direction = rec.normal + random_in_unit_sphere();
        scattered = ray(rec.intersection, scatter_direction,r_in.time());
        attenuation = albedo->value(rec.u,rec.v,rec.intersection);
        return true;
    }

public:
    texture* albedo;
};


#endif //BASIC_RAY_TRACER_DIFFUSE_H
