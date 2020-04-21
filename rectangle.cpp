//
// Created by neptune on 21-04-20.
//

#include "rectangle.h"


bool xy_rect::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const{
    auto t = (k-r.origin_point().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin_point().x() + t*r.direction().x();
    auto y = r.origin_point().y() + t*r.direction().y();
    if (x < p0 || x > p1 || y < q0 || y > q1)
        return false;
    rec.u = (x-p0)/(p1-p0);
    rec.v = (y-q0)/(q1-q0);
    rec.t = t;
    vec3 outward_normal = vec3(0, 0, 1);
    rec.set_normal(r.direction(), outward_normal);
    rec.mat = mat;
    rec.intersection = r.point_at(t);
    return true;
}

bool xz_rect::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const{
    auto t = (k-r.origin_point().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin_point().x() + t*r.direction().x();
    auto z = r.origin_point().z() + t*r.direction().z();
    if (x < p0 || x > p1 || z < q0 || z > q1)
        return false;
    rec.u = (x-p0)/(p1-p0);
    rec.v = (z-q0)/(q1-q0);
    rec.t = t;
    vec3 outward_normal = vec3(0, 1, 0);
    rec.set_normal(r.direction(), outward_normal);
    rec.mat = mat;
    rec.intersection = r.point_at(t);
    return true;
}

bool yz_rect::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const{
    auto t = (k-r.origin_point().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;

    auto y = r.origin_point().y() + t*r.direction().y();
    auto z = r.origin_point().z() + t*r.direction().z();

    if (y < p0 || y > p1 || z < q0 || z > q1)
        return false;
    rec.u = (y-p0)/(p1-p0);
    rec.v = (z-q0)/(q1-q0);
    rec.t = t;
    vec3 outward_normal = vec3(1, 0, 0);

    rec.set_normal(r.direction(), outward_normal);
    rec.mat = mat;
    rec.intersection = r.point_at(t);
    return true;
}
