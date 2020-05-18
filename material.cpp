//
// Created by neptune on 09-04-20.
//

#include "material.h"

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