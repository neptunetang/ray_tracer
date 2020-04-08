//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_HITABLE_LIST_H
#define BASIC_RAY_TRACER_HITABLE_LIST_H

#include "hitable.h"

class hitable_list :public hitable{
public:
    int list_size;
    hitable **list;
    hitable_list() = default;
    hitable_list(hitable **l, int n){
        list = l;
        list_size = n;
    }
    virtual bool is_hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
};


#endif //BASIC_RAY_TRACER_HITABLE_LIST_H
