//
// Created by neptune on 23-04-20.
//

#include "triangle.h"

bool triangle::is_hit(ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 ab = b-a;
    vec3 ac = c-a;
    vec3 bc = c - b;
    vec3 normal = cross(ab,ac);
    float area = normal.length();

    if(fabs(dot(normal, r.direction())) < 0.0001)
        //ray is parallel to the plane
        return false;

    float d = dot(normal, a);
    auto t = dot(normal, r.origin_point());
    if (t < t_min || t > t_max)
        return false;

    vec3 intersection = r.origin_point() + t*r.direction();
    vec3 ai = intersection - a;
    vec3 k1 = cross(ab, ai);

    vec3 k2 = cross(ac, ai);

    vec3 bi = intersection - b;
    vec3 k3 = cross(bc, bi);

    if(dot(normal, k1) < 0 || dot(normal, k2) < 0 || dot(normal, k3) < 0)
        //intersection is outside the triangle
        return false;

    rec.intersection = intersection;
    rec.normal = normal;
    rec.mat = mat;
    return true;

}
