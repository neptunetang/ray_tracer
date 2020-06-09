//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_HITABLE_H
#define BASIC_RAY_TRACER_HITABLE_H
#include "ray.h"

class material;

struct hit_record{
    float t;
    vec3 intersection;
    vec3 normal;
    material *mat;
    float u;
    float v;
    bool front;
    vec3 color;
    int index;

inline void set_normal(vec3 dir, vec3 outward_normal){
    front = dot(dir, outward_normal)<0;
    normal = front ? outward_normal : -outward_normal;
}
};

class hitable {
public:
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    virtual vec3 random_start()const {
        return vec3(0,0,0);
    };
    virtual bool on(vec3 a) const{
        return true;
    }
    virtual ray random_ray() const {
        return ray();
    }

};


#endif //BASIC_RAY_TRACER_HITABLE_H
