//
// Created by neptune on 08-04-20.
//

#ifndef BASIC_RAY_TRACER_RAY_H
#define BASIC_RAY_TRACER_RAY_H

#include "vec3.h"
#include "vec3.cpp"

class ray {
private:
    vec3 origin;
    vec3 dir;
public:
    ray() {}
    ray(const vec3& ori, const vec3& direction) : origin(ori), dir(direction){}
    vec3 origin_point() const {return origin;}
    vec3 direction() const {return dir;}
    vec3 point_at(float t) const {return origin + t*dir;}

};


#endif //BASIC_RAY_TRACER_RAY_H
