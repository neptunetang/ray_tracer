//
// Created by neptune on 09-04-20.
//

#include "diffuse.h"

bool diffuse::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered)  const  {
    vec3 scatter_direction = rec.normal + random_in_unit_sphere();
    scattered = ray(rec.intersection, scatter_direction,r_in.time());
    attenuation = albedo->value(rec.u,rec.v,rec.intersection);
    return true;
}
