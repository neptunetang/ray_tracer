//
// Created by neptune on 22-04-20.
//

#ifndef BASIC_RAY_TRACER_TRANSLATE_H
#define BASIC_RAY_TRACER_TRANSLATE_H

#include "hitable.h"

class translate : public hitable{
public:
    hitable* obj;
    vec3 offset;
    translate(hitable* p, vec3 displacement): obj(p), offset(displacement){}
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
        ray moved_ray (r.origin_point()-offset, r.direction(), r.time());
        if(!obj->is_hit(moved_ray, t_min, t_max, rec))
            return false;

        rec.intersection += offset;
        rec.set_normal(moved_ray.direction(), rec.normal);

        return true;
    }

};


#endif //BASIC_RAY_TRACER_TRANSLATE_H
