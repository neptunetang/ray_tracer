//
// Created by neptune on 22-04-20.
//

#include "rotate.h"

bool rotate_y::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 origin = r.origin_point();
    vec3 dir = r.direction();

    origin[0] = cos_theta*r.origin_point().x() - sin_theta*r.origin_point().z();
    origin[2] = sin_theta*r.origin_point().x() + cos_theta*r.origin_point().z();

    dir[0] = cos_theta*r.direction().x() - sin_theta*r.direction().z();
    dir[2] = sin_theta*r.direction().x() + cos_theta*r.direction().z();

    ray rotated_ray(origin, dir, r.time());

    if(!obj->is_hit(rotated_ray, t_min, t_max, rec))
        return false;

    vec3 intersection = rec.intersection;
    vec3 normal = rec.normal;

    intersection[0] = cos_theta*rec.intersection.x() + sin_theta*rec.intersection.z();
    intersection[2] = -sin_theta*rec.intersection.x() + cos_theta*rec.intersection.z();

    normal[0] = cos_theta*rec.normal.x() + sin_theta*rec.normal.z();
    normal[2] = -sin_theta*rec.normal.x() + cos_theta*rec.normal.z();

    rec.intersection = intersection;
    rec.set_normal(rotated_ray.direction(), normal);
    return true;

}
