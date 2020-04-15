//
// Created by neptune on 13-04-20.
//

#ifndef BASIC_RAY_TRACER_CONSTANT_TEXTURE_H
#define BASIC_RAY_TRACER_CONSTANT_TEXTURE_H

#include "texture.h"

class constant_texture :public texture {
private:
    vec3 c;
public:
    constant_texture() = default;
    constant_texture(const vec3& color):c(color){}
    virtual vec3 value(float u, float v, const vec3 &p)const;

    inline const vec3 color() const {return c;}
};


#endif //BASIC_RAY_TRACER_CONSTANT_TEXTURE_H
