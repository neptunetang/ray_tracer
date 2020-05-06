//
// Created by neptune on 21-04-20.
//

#ifndef BASIC_RAY_TRACER_DIFFUSE_LIGHT_H
#define BASIC_RAY_TRACER_DIFFUSE_LIGHT_H

#include "material.h"
#include "texture.h"
#include "constant_texture.h"

class diffuse_light :public material{
public:
    texture* emit;
    float strength;

    diffuse_light(texture *t, float s) : emit(t), strength(s){}
    virtual bool scatter(const ray& in, const hit_record& rec, vec3& attenuation, ray& scattered)
    const {
        return false;
    }

    virtual vec3 emitted(float u, float v, const vec3& p, vec3& attenuation) const {
        //for light emitting material
        attenuation = emit->value(u,v,p);
        return emit->value(u,v,p);
    }
};


#endif //BASIC_RAY_TRACER_DIFFUSE_LIGHT_H
