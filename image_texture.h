//
// Created by neptune on 14-04-20.
//

#ifndef BASIC_RAY_TRACER_IMAGE_TEXTURE_H
#define BASIC_RAY_TRACER_IMAGE_TEXTURE_H

#include "texture.h"

class image_texture : public texture {
public:
    unsigned char *data;
    int nx, ny;

    image_texture() = default;
    image_texture(unsigned char *pixels, int x, int y):data(pixels), nx(x), ny(y){}
    ~image_texture(){ delete data;}

    virtual vec3 value(float u, float v, const vec3& p) const;
};


#endif //BASIC_RAY_TRACER_IMAGE_TEXTURE_H
