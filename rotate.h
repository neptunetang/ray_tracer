//
// Created by neptune on 22-04-20.
//

#ifndef BASIC_RAY_TRACER_ROTATE_H
#define BASIC_RAY_TRACER_ROTATE_H

#include "hitable.h"

class rotate_y : public hitable{
public:
    hitable* obj;
    float sin_theta, cos_theta;
    rotate_y(hitable* object, float angle): obj(object) {
            auto radians = angle*2*M_PI/180.0;
            sin_theta = sin(radians);
            cos_theta = cos(radians);
    }
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};


#endif //BASIC_RAY_TRACER_ROTATE_H
