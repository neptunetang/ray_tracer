//
// Created by neptune on 13-04-20.
//

#include "checker_texture.h"

vec3 checker_texture::value(float u, float v, const vec3 &p) const {
    auto sine = sin(10*p.x()) * sin(10*p.y())*sin(10*p.z());
    if (sine < 0)
        return odd->value(u,v,p);
    else
        return even->value(u,v,p);
}
