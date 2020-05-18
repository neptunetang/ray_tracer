//
// Created by neptune on 21-04-20.
//

#ifndef BASIC_RAY_TRACER_DIFFUSE_LIGHT_H
#define BASIC_RAY_TRACER_DIFFUSE_LIGHT_H

#include "material.h"

class diffuse_light :public material{
public:
    texture* emit;

    diffuse_light(texture *t) : emit(t){}
    virtual bool scatter(const ray& in, const hit_record& rec, vec3& attenuation, ray& scattered, double& pdf)
    const {
        return false;
    }

    virtual vec3 emitted(ray in, float u, float v, const vec3& p, hit_record rec) const {
        //for light emitting material
        if (rec.front) {
            return emit->value(u, v, p);
        }
        else
            return vec3(0, 0, 0);
    }
};


#endif //BASIC_RAY_TRACER_DIFFUSE_LIGHT_H
