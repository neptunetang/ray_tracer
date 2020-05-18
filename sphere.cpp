//
// Created by neptune on 09-04-20.
//

#include "sphere.h"

bool sphere::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 origin_to_center = r.origin_point() - center;
    auto a = r.direction().squared_length();
    auto half_b = dot(origin_to_center, r.direction());
    auto c = origin_to_center.squared_length() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a; // smaller root
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.intersection = r.point_at(rec.t);
            rec.normal = (rec.intersection - center) / radius;
            rec.mat = mat;
            rec.front = true;
            get_sphere_uv((rec.intersection-center)/radius, rec.u, rec.v);
            return true;
        }
        temp = (-half_b + root) / a; //larger root
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.intersection = r.point_at(rec.t);
            rec.normal = (rec.intersection - center) / radius;
            rec.mat = mat;
            rec.front = true;
            get_sphere_uv((rec.intersection-center)/radius, rec.u, rec.v);
            return true;
        }
    }
    return false;
}

void get_sphere_uv(const vec3 intersection, float& u, float& v) {
    auto theta = asin(intersection.y());
    auto phi = atan2(intersection.z(), intersection.x());
    u = 1 - (phi + M_PI) / (2*M_PI);
    v = (theta + M_PI/2) / M_PI;
}
