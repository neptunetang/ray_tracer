//
// Created by neptune on 02-04-20.
//

#include "dielectric.h"

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted){
    vec3 unit_v = unit_vec(v);
    float dot_t = dot(unit_v, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dot_t*dot_t);
    if(discriminant > 0){
        refracted = ni_over_nt*(unit_v - n*dot_t) - n*sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cos, float ref_idx) {
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cos), 5);
}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered, double& pdf) const {
    attenuation = vec3(1.0,1.0,1.0);
    float ni_over_nt;
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    vec3 refracted;
    float reflect_prob;
    float cos;
    if(dot(r_in.direction(), rec.normal) > 0){
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cos = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0/ref_idx;
        cos = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)){
        reflect_prob = schlick(cos, ref_idx);
    } else {
        scattered = ray(rec.intersection, reflected);
        reflect_prob = 1.0;
    }

    if(random_float() < reflect_prob) {
        scattered = ray(rec.intersection, reflected);
    } else {
        scattered = ray(rec.intersection, refracted);
    }
    return true;
}
