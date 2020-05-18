//
// Created by neptune on 15-04-20.
//

#ifndef BASIC_RAY_TRACER_NOISE_TEXTURE_H
#define BASIC_RAY_TRACER_NOISE_TEXTURE_H

#include "texture.h"
#include "perlin.h"

class noise_texture :public texture{
public:
    noise_texture() = default;
    noise_texture(float s) : scale(s){}
    virtual vec3 value (float u, float v, const vec3& p)const;

private:
    perlin noise;
    float scale;
};


#endif //BASIC_RAY_TRACER_NOISE_TEXTURE_H
