#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>
#include<fstream>

vec3 color(const ray& r, const hitable* world) {
    hit_record rec;
    if(world->is_hit(r,0.001, MAXFLOAT, rec)){
        return 0.5*(rec.normal+vec3(1,1,1));
    }
    vec3 unit_direction = unit_vec(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int width=400, height=200;
    int sample_per_pixel = 100;
    ofstream img ("6.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;

    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hitable* world = new hitable_list(list, 2);

    camera cam;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < sample_per_pixel; s++){
                auto u = double(i+drand48()) / width;
                auto v = double(j+drand48()) / height;
                ray r = cam.get_ray(u,v);
                col += color(r, world);
            }

            col /= float(sample_per_pixel);

            int ir = static_cast<int>(255.999 * col[0]);
            int ig = static_cast<int>(255.999 * col[1]);
            int ib = static_cast<int>(255.999 * col[2]);
            img << ir << ' ' << ig << ' ' << ib << endl;
        }
    }
}