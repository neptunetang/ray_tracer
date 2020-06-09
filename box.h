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
    box(const vec3& p0, const vec3& p1, material* mat){
        box_max = p1;
        box_min = p0;

        hitable **list = new hitable*[6];
        int i=0;
        list[i++] = new xy_rect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), mat);
        list[i++] = new flip_face(new xy_rect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), mat));
        list[i++] = new flip_face(new xz_rect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), mat));
        list[i++] = new flip_face(new xz_rect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), mat));
        list[i++] = new yz_rect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), mat);
        list[i++] = new flip_face(new yz_rect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), mat));

        sides = new hitable_list(list, 6);
    }
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
        return sides->is_hit(r, t_min, t_max, rec);
    }
};


#endif //BASIC_RAY_TRACER_BOX_H
