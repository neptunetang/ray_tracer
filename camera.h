//
// Created by neptune on 09-04-20.
//

#ifndef BASIC_RAY_TRACER_CAMERA_H
#define BASIC_RAY_TRACER_CAMERA_H

#include "common_method.h"

vec3 random_in_unit_disk() {
    while (true) {
        vec3 p = vec3(drand48()*2-1, drand48()*2-1, 0);
        if (p.squared_length() >= 1) continue;
        return p;
    }
}

class camera {
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

    ray get_ray(float s, float t){
        float r = random_float(time0, time1);
        if(lens_radius == 0.0)
            return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin, r);
        vec3 random_dot = lens_radius * random_in_unit_disk();
        vec3 offset = u * random_dot.x() + v * random_dot.y();
        return ray(origin+offset,
                   lower_left_corner+s*horizontal + t*vertical - origin - offset, r);
    }
};

#endif //BASIC_RAY_TRACER_CAMERA_H
