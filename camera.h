//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_CAMERA_H
#define BASIC_RAY_TRACER_CAMERA_H

#include "ray.h"

class camera {
public:
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u,v,w;
    float lens_radius;
    float time0, time1;

    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
            float aperture, float focus, float t0 = 0, float t1 = 0){
        origin = lookfrom;
        lens_radius = aperture / 2;

        time0 = t0;
        time1 = t1;

        float theta = vfov*M_PI/180.0;
        float half_h = tan(theta/2);
        float half_w = aspect * half_h;

        w = unit_vec(lookfrom-lookat);
        u = unit_vec(cross(vup, w));
        v = unit_vec(cross(w,u));

        lower_left_corner = origin - half_w*focus*u - half_h*focus*v - focus*w;
        horizontal = 2 * half_w * focus * u;
        vertical = 2 * half_h * focus * v;

    }

    ray get_ray(float u, float v);
};

inline float random_float();
inline float random_float(float min, float max);
#endif //BASIC_RAY_TRACER_CAMERA_H
