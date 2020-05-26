//
// Created by neptune on 10-04-20.
//

#include "metal.h"

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered, double& pdf) const {
    vec3 reflected = reflect(unit_vec(r_in.direction()), rec.normal);
    scattered = ray(rec.intersection, reflected + fuzz*random_in_unit_sphere());
    attenuation = albedo->value(rec.u, rec.v, rec.intersection);
    return (dot(scattered.direction(), rec.normal) > 0);
}