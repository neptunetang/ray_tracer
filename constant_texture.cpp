//
// Created by neptune on 13-04-20.
//

#include "constant_texture.h"

vec3 constant_texture::value(float u, float v, const vec3 &p) const {
    return c;
}
