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
        auto cos_theta = dot(-r_in.direction(), rec.normal)/r_in.direction().length()*rec.normal.length();
        auto theta = acos(cos_theta);
        attenuation = (1.5-2*theta/M_PI)*albedo->value(rec.u,rec.v,rec.intersection);
        if(static_cast<int>(cos_theta) == 1){
            attenuation = albedo->value(rec.u,rec.v,rec.intersection);
        }
    //attenuation = albedo->value(rec.u, rec.v, rec.intersection);
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
