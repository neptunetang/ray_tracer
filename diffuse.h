//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_DIFFUSE_H
#define BASIC_RAY_TRACER_DIFFUSE_H

#include "material.h"
#include "texture.h"
#include "orthnormal_base.h"

class diffuse : public material {
public:
    diffuse(texture *t) : albedo(t) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, double& pdf
    ) const{
        orthonormal_base onb;
        onb.build_from_w(rec.normal);
        //vec3 scatter_direction = rec.normal+random_in_unit_sphere();
        vec3 scatter_direction = onb.local(random_cosine_direction());
        scattered = ray(rec.intersection, unit_vec(scatter_direction), r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.intersection);
        pdf = dot(onb.w(), scattered.direction())/M_PI;
        return true;
    }

    virtual float scatter_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
    ) const {
        auto cosine = dot(rec.normal, unit_vec(scattered.direction()));
        return cosine < 0 ? 0 : cosine/M_PI;
    }

public:
    texture* albedo;
};


#endif //BASIC_RAY_TRACER_DIFFUSE_H
