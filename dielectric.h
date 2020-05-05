//
// Created by neptune on 02-04-20.
//

#ifndef BASIC_DIELECTRIC_H
#define BASIC_DIELECTRIC_H


#include "material.h"
#include "texture.h"
#include "common_method.h"

class dielectric: public material{
public:
    double ref_idx;


    dielectric(double ri) : ref_idx(ri) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
};


#endif //BASIC_DIELECTRIC_H
