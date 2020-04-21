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

    diffuse_light(texture *t) : emit(t){}
    virtual bool scatter(const ray& in, const hit_record& rec, vec3& attenuation, ray& scattered)
    const {
        return false;
    }

    virtual vec3 emitted(float u, float v, const vec3& p) const {
        //for light emitting material
        return emit->value(u,v,p);
    }
};


#endif //BASIC_RAY_TRACER_DIFFUSE_LIGHT_H
