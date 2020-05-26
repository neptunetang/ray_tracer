//
// Created by neptune on 09-04-20.
//

#include "material.h"
#include "common_method.h"

vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    }while (p.squared_length() >= 1.0);
    return p;
}

vec3 reflect(const vec3& in, const vec3 &n) {
    return in-2*dot(in,n)*n;
}

vec3 random_cosine_direction(){
    auto r1 = random_float();
    auto r2 = random_float();
    auto z = sqrt(1-r2);

    auto phi = 2*M_PI*r1;
    auto x = cos(phi)*sqrt(r2);
    auto y = sin(phi)*sqrt(r2);

    return vec3(x, y, z);
}