//
// Created by neptune on 05-05-20.
//

#ifndef BASIC_RAY_TRACER_LIGHT_LIST_H
#define BASIC_RAY_TRACER_LIGHT_LIST_H

#include "light.h"

class light_list {
public:
    light* list;
    int size;

    light_list() = default;
    light_list(light* l, int s): list(l), size(s){}
};


#endif //BASIC_RAY_TRACER_LIGHT_LIST_H
