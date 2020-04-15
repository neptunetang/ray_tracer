//
// Created by neptune on 13-04-20.
//

#ifndef BASIC_RAY_TRACER_CHECKER_TEXTURE_H
#define BASIC_RAY_TRACER_CHECKER_TEXTURE_H

#include "texture.h"

class checker_texture :public  texture{
public:
    texture* odd;
    texture* even;

    checker_texture() = default;
    checker_texture(texture* t0, texture* t1):even(t0), odd(t1){}

    virtual vec3 value(float u, float v, const vec3& p) const;
};


#endif //BASIC_RAY_TRACER_CHECKER_TEXTURE_H
