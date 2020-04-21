//
// Created by neptune on 21-04-20.
//

#ifndef BASIC_RAY_TRACER_BOX_H
#define BASIC_RAY_TRACER_BOX_H

#include "hitable.h"
#include "hitable_list.h"
#include "rectangle.h"

class box : public hitable{
public:
    vec3 box_min;
    vec3 box_max;
    hitable_list* sides;

    box() = default;
    box(const vec3& p0, const vec3& p1, material* mat);
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};


#endif //BASIC_RAY_TRACER_BOX_H
