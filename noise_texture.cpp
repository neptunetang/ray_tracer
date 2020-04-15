//
// Created by neptune on 15-04-20.
//

#include "noise_texture.h"

vec3 noise_texture::value(float u, float v, const vec3 &p) const {
    return vec3(1,1,1)*noise.noise(p*scale);
}
