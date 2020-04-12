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
    float t;
public:
    ray() {}
    ray(const vec3& ori, const vec3& direction, float time = 0.0) : origin(ori), dir(direction), t(time){}
    vec3 origin_point() const {return origin;}
    vec3 direction() const {return dir;}
    float time() const {return t;}
    vec3 point_at(float t) const {return origin + t*dir;}

};


#endif //BASIC_RAY_TRACER_RAY_H
