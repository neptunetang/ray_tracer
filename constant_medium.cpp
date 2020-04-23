//
// Created by neptune on 22-04-20.
//

#include "constant_medium.h"
#include "common_method.h"

bool constant_medium::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const {

    hit_record rec1, rec2;

    if (!obj->is_hit(r, -infinity, infinity, rec1))
        return false;

    if (!obj->is_hit(r, rec1.t+0.0001, infinity, rec2))
        return false;

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t = t_max;

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0)
        rec1.t = 0;

    const auto ray_length = r.direction().length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    const auto hit_distance = density * log(random_float());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.t = rec1.t + hit_distance / ray_length;
    rec.intersection = r.point_at(rec.t);

    rec.normal = vec3(random_float(0,1),random_float(0,1),random_float(0,1));  // arbitrary
    rec.front = true;     // also arbitrary
    rec.mat = phase;

    return true;
}
