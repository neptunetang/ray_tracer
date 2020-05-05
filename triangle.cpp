//
// Created by neptune on 23-04-20.
//

#include "triangle.h"

bool triangle::is_hit(const ray &r, float t_min, float t_max, hit_record &rec) const {

    //formula plane: Ax + By + Cz = D

    vec3 normal = vec3((b.y()-a.y())*(c.z()-a.z()) - (b.z()-a.z())*(c.y()-a.y()),
                       (b.z()-a.z())*(c.x()-a.x()) - (b.x()-a.x())*(c.z()-a.z()),
                       (b.x()-a.x())*(c.y()-a.y()) - (b.y()-a.y())*(c.x()-a.x()));

    if(fabs(dot(normal, r.direction())) < 0.0001) {
        //ray is parallel to the plane
        return false;
    }

    float d = dot(normal, a);
    auto t = (d-dot(normal, r.origin_point()))/(dot(normal, r.direction()));
    if (t < t_min) {
        return false;
    }

    vec3 intersection = r.origin_point() + t*r.direction();
    vec3 ab = b-a;
    vec3 ca = a-c;
    vec3 bc = c-b;

    vec3 ai = intersection - a;
    vec3 k1 = cross(ab, ai);

    vec3 ci = intersection - c;
    vec3 k2 = cross(ca, ci);

    vec3 bi = intersection - b;
    vec3 k3 = cross(bc, bi);

    if(dot(k1, normal) < 0 || dot(k2, normal) < 0 || dot(k3,normal) < 0) {
        //intersection is outside the triangle
        return false;
    }

    rec.intersection = intersection;
    rec.set_normal(r.direction(), normal);
    rec.mat = mat;
    return true;

}
