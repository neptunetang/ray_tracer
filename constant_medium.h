//
// Created by neptune on 22-04-20.
//

#ifndef BASIC_RAY_TRACER_CONSTANT_MEDIUM_H
#define BASIC_RAY_TRACER_CONSTANT_MEDIUM_H

#include "hitable.h"
#include "isotropic.h"

class constant_medium : public hitable {
public:
    hitable* obj;
    material* phase;
    float density;

    constant_medium(hitable* object, float d, texture* t) : obj(object), density(-1.0/d){
        phase = new isotropic(t);
    }
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record&rec) const;
};


#endif //BASIC_RAY_TRACER_CONSTANT_MEDIUM_H
