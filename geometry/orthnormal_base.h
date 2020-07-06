//
// Created by neptune on 18-05-20.
//

#ifndef BASIC_RAY_TRACER_ORTHNORMAL_BASE_H
#define BASIC_RAY_TRACER_ORTHNORMAL_BASE_H

#include "ray.h"

class orthonormal_base {
public:
    orthonormal_base() = default;

    vec3 axis[3];


    vec3 operator[](int i) const {return axis[i];}
    vec3 u() const {return axis[0];}
    vec3 v() const {return axis[1];}
    vec3 w() const {return axis[2];}

    vec3 local(double a, double b, double c) const {
        return a*u()+ b*v() + c*w();
    }

    vec3 local(const vec3& a) const {
        return a.x()*u() + a.y()*v() + a.z()*w();
    }

    void build_from_w(const vec3& n){
        axis[2] = unit_vec(n);
        vec3 a = (fabs(w().x()) > 0.9) ? vec3(0,1,0) : vec3(1,0,0);
        axis[1] = unit_vec(cross(w(), a));
        axis[0] = cross(w(), v());
    }

};


#endif //BASIC_RAY_TRACER_ORTHNORMAL_BASE_H
