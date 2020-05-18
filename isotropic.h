//
// Created by neptune on 22-04-20.
//

#ifndef BASIC_RAY_TRACER_ISOTROPIC_H
#define BASIC_RAY_TRACER_ISOTROPIC_H

#include "texture.h"
#include "material.h"

class isotropic : public material{
public:
    texture* albedo;
    isotropic(texture* t) : albedo(t){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, double& pdf) const {
        scattered = ray(rec.intersection, random_in_unit_sphere(), r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.intersection);
        return true;
    }
};


#endif //BASIC_RAY_TRACER_ISOTROPIC_H
