#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "diffuse.h"
#include "metal.h"
#include "dielectric.h"
#include "moving_sphere.h"
#include <iostream>
#include<fstream>

vec3 color(const ray& r, const hitable* world, int depth) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if(rec.mat->scatter(r, rec, attenuation, scattered)){
            return attenuation*color(scattered, world, depth-1);
        } else {
            return vec3(0,0,0);
        }
    }
    vec3 unit_direction = unit_vec(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int width=400, height=200;
    int sample_per_pixel = 100;
    int max_depth = 50;
    ofstream img ("1.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;

//    hitable *list[5];
//    list[0] = new sphere(vec3(0,0,-1), 0.5, new diffuse(vec3(0.2,0.3,0.0)));
//    list[1] = new sphere(vec3(0,-100.5,-1), 100, new diffuse(vec3(0.5,0.5,0.5)));
//    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.2,0.3,0.0), 0.0));
//    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
//    list[4] = new sphere(vec3(-1,0,-1), -0.499, new dielectric(1.5));
//
//    hitable* world = new hitable_list(list, 5);

    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0), 1000, new diffuse(vec3(0.7, 0.6, 0.5)));
    int i = 1;
    for (int a = -10; a < 10; a++){
        for(int b = -10; b < 10; b++){
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
            if((center-vec3(4,0.2,0)).length() > 0.9){
                if(choose_mat < 0.8){
                    list[i++] = new moving_sphere(center, center+vec3(0, random_float(0,0.5), 0), 0.0, 1.0, 0.2, new diffuse(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48())));
                } else if (choose_mat < 0.95){
                    list[i++] = new sphere (center, 0.2, new metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())),0.5*drand48()));
                } else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(0,1,0), 1.0, new dielectric(1.5));
    list[i++] = new moving_sphere(vec3(-4,1,0), vec3(-4,1,1),0.0,1.0, 1.0, new diffuse(vec3(0.4,0.2,0.1)));
    list[i++] = new sphere(vec3(4,1,0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    hitable *world = new hitable_list(list, i);

//    vec3 look_from(3,3,2);
//    vec3 look_at(0,0,-1);
//    vec3 vup(0,1,0);
//    float focus = (look_from-look_at).length();

    vec3 look_from(13,2,3);
    vec3 look_at(0,0,0);
    vec3 vup(0,1,0);
    auto focus = 10.0;
    auto aperture = 0.0;

    camera cam(look_from, look_at, vup, 20, (width/height), aperture, focus,0.0,1.0);

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < sample_per_pixel; s++){
                auto u = double(i+drand48()) / width;
                auto v = double(j+drand48()) / height;
                ray r = cam.get_ray(u,v);
                col += color(r, world, max_depth);
            }

            col /= float(sample_per_pixel);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = static_cast<int>(255.999 * col[0]);
            int ig = static_cast<int>(255.999 * col[1]);
            int ib = static_cast<int>(255.999 * col[2]);
            img << ir << ' ' << ig << ' ' << ib << endl;
        }
    }
}