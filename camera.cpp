//
// Created by neptune on 09-04-20.
//

#include "camera.h"
vec3 random_in_unit_disk() {
    while (true) {
        vec3 p = vec3(drand48()*2-1, drand48()*2-1, 0);
        if (p.squared_lenght() >= 1) continue;
        return p;
    }
}


ray camera::get_ray(float s, float t) {
    float r = random_float(time0, time1);
    if(lens_radius == 0.0)
        return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin, r);
    vec3 random_dot = lens_radius * random_in_unit_disk();
    vec3 offset = u * random_dot.x() + v * random_dot.y();
    return ray(origin+offset,
            lower_left_corner+s*horizontal + t*vertical - origin - offset, r);
}