#include "common_method.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "diffuse.h"
#include "metal.h"
#include "dielectric.h"
#include "moving_sphere.h"
#include "constant_texture.h"
#include "checker_texture.h"
#include "noise_texture.h"
#include "image.h"
#include "image_texture.h"
#include "diffuse_light.h"
#include "rectangle.h"
#include "box.h"
#include "translate.h"
#include "rotate.h"
#include "constant_medium.h"
#include "object_loader.h"
#include <iostream>
#include<fstream>

vec3 color(const ray& r, const vec3& background, const hitable* world, int depth) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat->emitted(rec.u, rec.v, rec.intersection);
        if(rec.mat->scatter(r, rec, attenuation, scattered)){
            return attenuation*color(scattered, background, world, depth-1);
        } else {
            return vec3(0,0,0);
        }
    }
    //return background;
    vec3 unit_direction = unit_vec(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int width=200, height=100;
    int sample_per_pixel = 100;
    int max_depth = 50;
    ofstream img ("test.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    const vec3 background(0,0,0);

    material* white = new diffuse(new constant_texture(vec3(1,1,1)));
    hitable *list[2];
    //list[0] = new sphere(vec3(0,0,-1), 0.5, new diffuse(new constant_texture(vec3(0.2,0.3,0.0))));
    list[0] = new xz_rect(-1,1,-1,1,0,new diffuse(new constant_texture(vec3(0.2,0.3,0.0))));
//    list[1] = new sphere(vec3(0,-100.5,-1), 100, new diffuse(vec3(0.5,0.5,0.5)));
//    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.2,0.3,0.0), 0.0));
//    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
//    list[4] = new sphere(vec3(-1,0,-1), -0.499, new dielectric(1.5));
//
//    hitable* world = new hitable_list(list, 5);
//    int n = 1000;
//    hitable **list = new hitable*[n+1];
    texture* checker = new checker_texture(
            new constant_texture(vec3(0.2,0.3,0.1)),
            new constant_texture(vec3(0.9,0.9,0.9))
            );

    texture* perlintex = new noise_texture(100);


    int pic_x, pic_y, pic_n;
    unsigned char* texture_data = stbi_load("e.jpg", &pic_x, &pic_y, &pic_n, 0);
    texture* earth_surface = new image_texture(texture_data, pic_x, pic_y);

    int m_x, m_y, m_n;
    unsigned char* m_data = stbi_load("m.jpg", &m_x, &m_y, &m_n, 0);
    texture* moon_surface = new image_texture(m_data, m_x, m_y);

//    list[0] = new sphere(vec3(0,-1000,0), 1000, new diffuse(perlintex));
//    int i = 1;
//    for (int a = -10; a < 10; a++){
//        for(int b = -10; b < 10; b++){
//            float choose_mat = drand48();
//            vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
//            if((center-vec3(4,0.2,0)).length() > 0.9){
//                if(choose_mat < 0.8){
//                    list[i++] = new moving_sphere(center, center+vec3(0, random_float(0,0.5), 0), 0.0, 1.0, 0.2, new diffuse(new constant_texture(vec3(drand48()*drand48(),drand48()*drand48(),drand48()*drand48()))));
//                } else if (choose_mat < 0.95){
//                    list[i++] = new sphere (center, 0.2, new metal(new constant_texture(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48()))),0.5*drand48()));
//                } else {
//                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
//                }
//            }
//        }
//    }


//list[i++] = new sphere(vec3(4,1,0), 1, new diffuse(perlintex));
//list[i++] = new xy_rect(3,5,1,3,-2, new diffuse_light((new constant_texture(vec3(15,15,15)))));

//material* white = new diffuse(new constant_texture(vec3(1,1,1)));
//
//list[i++] = new flip_face(new yz_rect(0,555,0,555,555,new diffuse(new constant_texture(vec3(0.12,0.45,0.15)))));
//list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.65,0.05,0.05))));
//list[i++] = new xz_rect(0,555,0,555,0, white);
//list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
//list[i++] = new flip_face(new xy_rect(0,555,0,555,555, new diffuse (new constant_texture(vec3(0.05,0.05,0.73)))));
//list[i++] = new xz_rect(113,443,127,432,554, new diffuse_light(new constant_texture(vec3(4,4,4))));
//
//hitable* box1 = new box(vec3(0,0,0), vec3(165,330,165), white);
//box1 = new rotate_y(box1, 15);
//box1 = new translate(box1, vec3(265,0,295));
//list[i++] = new constant_medium(box1, 0.006, new constant_texture(vec3(0,0,0)));
//
//hitable* box2 = new box(vec3(0,0,0), vec3(165,165,165), white);
//box2 = new rotate_y(box2, -18);
//box2 = new translate(box2, vec3(130,0,65));
//list[i++] = new constant_medium(box2, 0.006, new constant_texture(vec3(1,1,1)));


//    list[i++] = new sphere(vec3(0,1,0), 1.0, new dielectric(1.5));
//    list[i++] = new moving_sphere(vec3(-4,1,0), vec3(-4,1,1),0.0,1.0, 1.0, new diffuse(new constant_texture(vec3(0.4,0.2,0.1))));
//    list[i++] = new sphere(vec3(4,1,0), 1.0, new metal(new constant_texture(vec3(0.7, 0.6, 0.5)), 0.0));

////ground with randomly generated boxes
//int i = 0;
//auto ground = new diffuse(new constant_texture(vec3(0.48,0.83,0.53)));
//for(int m=0; m<20; m++){
//    for (int n=0; n<20; n++){
//        auto w = 100.0;
//        auto x0 = -1000.0+m*w;
//        auto z0 = -1000.0+n*w;
//        auto y0 = 0.0;
//        auto x1 = x0+w;
//        auto z1 = z0+w;
//        auto y1 = random_float(1,101);
//        list[i++] = new box(vec3(x0,y0,z0), vec3(x1,y1,z1), ground);
//    }
//}
//
////light emitting rectangle
//auto light = new diffuse_light(new constant_texture(vec3(7,7,7)));
//list[i++] = new xz_rect(123,423,147,412,554, light);
//
//// moving sphere
//auto moving_sphere_material = new diffuse(new constant_texture(vec3(0.7,0.3,0.1)));
//list[i++] = new moving_sphere(vec3(400,400,400), vec3(430,400,200), 0,1,50, moving_sphere_material);
//
////glass sphere
//list[i++] = new sphere(vec3(260,150,45), 50, new dielectric(1.5));
//
////metal sphere
//list[i++] = new sphere(vec3(0,150,145), 50, new metal(new constant_texture(vec3(0.5,0.5,0.5)), 2.5));
//
////volumn surounded by glass sphere
//auto boundary = new sphere(vec3(360,150,145), 70, new dielectric(1.5));
//
////earth
//list[i++] = new sphere(vec3(400,200,400), 70, new diffuse(earth_surface));
//
////perlin noise sphere
//list[i++] = new sphere(vec3(220,280,300), 80, new diffuse(perlintex));
//
////foggy
//boundary = new sphere(vec3(0,0,0), 5000, new dielectric(1.5));
//list[i++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1,1,1)));
//
////randomly generated white ball in given area(box)
//auto white = new diffuse(new constant_texture(vec3(1,1,1)));
//for (int k=0; k<100; k++){
//    auto x = random_float(0,165);
//    auto y = random_float(0,165);
//    auto z = random_float(0,165);
//    auto small_sphere = new sphere(vec3(x,y,z), 10, white);
//    list[i++] = new translate(new rotate_y(small_sphere, 15), vec3(-100,270,395));
//}


    hitable *world = new hitable_list(list, 1);

    vec3 look_from(0,3,0.5);
    vec3 look_at(0,0,0);
    vec3 vup(0,1,0);
    float focus = 10.0;
    auto aperture = 0.0;

//    vec3 look_from(13,2,3);
//    vec3 look_at(0,0,0);
//    vec3 vup(0,1,0);
//    auto focus = 10.0;
//    auto aperture = 0.0;

//    vec3 look_from(278, 278, -800);
//    vec3 look_at(278,278,0);
//    vec3 vup(0,1,0);
//    auto focus = 10.0;
//    auto aperture = 0.0;

//    vec3 look_from(478, 278, -600);
//    vec3 look_at(278,278,0);
//    vec3 vup(0,1,0);
//    auto focus = 10.0;
//    auto aperture = 0.0;

    camera cam(look_from, look_at, vup, 40, (width/height), aperture, focus,0.0,1.0);

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < sample_per_pixel; s++){
                auto u = double(i+drand48()) / width;
                auto v = double(j+drand48()) / height;
                ray r = cam.get_ray(u,v);
                col += color(r, background, world, max_depth);
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