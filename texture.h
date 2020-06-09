//
// Created by neptune on 13-04-20.
//

#ifndef BASIC_RAY_TRACER_TEXTURE_H
#define BASIC_RAY_TRACER_TEXTURE_H

#include "ray.h"

class texture {
public:
    virtual vec3 value(float u, float v, const vec3 &p)const = 0;
};

class image_texture : public texture {
public:
    unsigned char *data;
    int nx, ny;

    image_texture() = default;
    image_texture(unsigned char *pixels, int x, int y):data(pixels), nx(x), ny(y){}
    ~image_texture(){ delete data;}

    virtual vec3 value(float u, float v, const vec3& p) const{
        if (data == nullptr) {
            return vec3(0, 0, 0);
        } else {
            auto i = static_cast<int>(u*nx);
            auto j = static_cast<int>((1-v)*ny-0.001);

            if(i<0) i=0;
            if(j<0) j=0;
            if(i>nx-1) i = nx-1;
            if(j>ny-1) j = ny-1;

            auto r = static_cast<int>(data[3*i + 3*nx*j+0])/255.0;
            auto g = static_cast<int>(data[3*i + 3*nx*j+1])/255.0;
            auto b = static_cast<int>(data[3*i + 3*nx*j+2])/255.0;

            return vec3(r,g,b);
        }
    }
};

class constant_texture :public texture {
private:
    vec3 c;
public:
    constant_texture() = default;
    constant_texture(const vec3& color):c(color){}
    virtual vec3 value(float u, float v, const vec3 &p) const{return c;}

    inline const vec3 color() const {return c;}
};

class checker_texture :public  texture{
public:
    texture* odd;
    texture* even;

    checker_texture() = default;
    checker_texture(texture* t0, texture* t1):even(t0), odd(t1){}

    virtual vec3 value(float u, float v, const vec3& p) const{
        auto sine = sin(10*p.x()) * sin(10*p.y())*sin(10*p.z());
        if (sine < 0)
            return odd->value(u,v,p);
        else
            return even->value(u,v,p);
    }
};

#endif //BASIC_RAY_TRACER_TEXTURE_H
