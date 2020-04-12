//
// Created by neptune on 12-04-20.
//

#include "moving_sphere.h"

vec3 moving_sphere::center(double time) const {
    return center0 + (time-time0)/(time1-time0)*(center1-center0);
}

bool moving_sphere::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 origin_to_center = r.origin_point() - center(r.time());
    auto a = r.direction().squared_lenght();
    auto half_b = dot(origin_to_center, r.direction());
    auto c = origin_to_center.squared_lenght() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a; // smaller root
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.intersection = r.point_at(rec.t);
            rec.normal = (rec.intersection - center(r.time())) / radius;
            rec.mat = mat;
            return true;
        }
        temp = (-half_b + root) / a; //larger root
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.intersection = r.point_at(rec.t);
            rec.normal = (rec.intersection - center(r.time())) / radius;
            rec.mat = mat;
            return true;
        }
    }
    return false;
}
