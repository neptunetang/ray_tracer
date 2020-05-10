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
#include "light.h"
#include "light_list.h"
#include <iostream>
#include<fstream>

vec3 color_under_light(vec3 intersection, light light_source, const hitable* world, vec3 camera_dir){
    vec3 light_ray = intersection-light_source.position;
    vec3 light_dir = light_source.point_at-light_source.position;

    float distance = light_ray.length();
    float max_distance = light_source.intensity;

    auto cos_theta = dot(light_ray, light_dir)/(light_ray.length()*light_dir.length());
    float theta;
    if(static_cast<int>(cos_theta) == 1)
        theta = 0;
    else
        theta = acos(cos_theta);

    hit_record tmp;
    vec3 light_effect;
    ray l(light_source.position, light_ray);
    if(world->is_hit(l, 0.0001, MAXFLOAT, tmp)){
        if(!(tmp.intersection == intersection))
            return vec3(0,0,0);
    }

    if(distance > max_distance) {
        return  vec3(0, 0, 0);
    } else{
        auto division = theta/(M_PI/4);

        light_effect =  light_source.color*(1.0-division);
    }

    ray scattered;
    vec3 origin_color;

    vec3 light_to_cam;

    if(tmp.mat->scatter(l, tmp, origin_color, scattered)){
        float cos_cam_theta = dot(scattered.direction(), camera_dir)/(scattered.direction().length()*camera_dir.length());
        auto a = acos(cos_cam_theta)/M_PI*180;
        if(a > 90)
            light_to_cam = light_source.color*(a/90-1);
        else
            light_to_cam = vec3(0,0,0);
    }
    cout << theta << "  " << distance << endl;
    auto distance_division = distance/max_distance;
    return light_effect+light_to_cam*(1-distance_division);
}

vec3 color(const ray& r, const vec3& background, const hitable* world, int depth, light_list light_source) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        vec3 light_effect(0,0,0);
        vec3 emitted = rec.mat->emitted(rec.u, rec.v, rec.intersection, attenuation);
        int size = light_source.size;
        for(int i=0; i<size; i++){
            light_effect += color_under_light(rec.intersection, light_source.list[i], world, r.direction());
        }
        if(rec.mat->scatter(r, rec, attenuation, scattered)){
            return emitted+attenuation*color(scattered, background, world, depth-1, light_source);
//            auto on_light = vec3(random_float(213,343), 554, random_float(227,332));
//            auto to_light = on_light - rec.intersection;
//            auto distance_squared = to_light.squared_length();
//            to_light.make_unit();
//
//            if(dot(to_light,rec.normal) < 0){
//                return emitted;
//            } else {
//                double light_area = (343-213)*(332-227);
//                auto light_cos = fabs(to_light.y());
//                if(light_cos < 0.0000001){
//                    return emitted;
//                }
//                //auto pdf = distance_squared/(light_cos*light_area);
//                auto pdf = 0.5/M_PI;
//                scattered = ray(rec.intersection, to_light, r.time());
//                //cout << pdf << " " << rec.mat->scatter_pdf(r, rec, scattered) << endl;
//                return emitted + attenuation*10*rec.mat->scatter_pdf(r, rec, scattered)*color(scattered, background, world, depth-1, light_source);
//            }

        } else {
            return emitted;
        }
    }
    return background;
}

void run(int scene){
    int width=400, height=400;
    int sample_per_pixel = 100;
    int max_depth = 5;
    ofstream img ("k.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    const vec3 background(1,1,1);

    material* white = new diffuse(new constant_texture(vec3(1,1,1)));

    int pic_x, pic_y, pic_n;
    unsigned char* texture_data = stbi_load("e.jpg", &pic_x, &pic_y, &pic_n, 0);
    texture* earth_surface = new image_texture(texture_data, pic_x, pic_y);

    int m_x, m_y, m_n;
    unsigned char* m_data = stbi_load("m.jpg", &m_x, &m_y, &m_n, 0);
    texture* moon_surface = new image_texture(m_data, m_x, m_y);

    texture* checker = new checker_texture(
            new constant_texture(vec3(0.2,0.3,0.1)),
            new constant_texture(vec3(0.9,0.9,0.9))
    );

    texture* perlintex = new noise_texture(100);

    int i, n;

    vec3 look_from, look_at(0,0,0);
    vec3 vup(0,1,0);
    auto focus = 10.0;
    auto aperture = 0.0;
    hitable* box1;
    hitable* box2;
    hitable *world;
    hitable **list;


    vec3 light_point;
    vec3 light_to;
    float angle;
    vec3 light_color;
    float light_strength;

    light* point_lights;
    light_list lights;

    switch(scene){
        case 1 :
            list = new hitable*[2];
            list[0] = new sphere(vec3(0,0,-1), 0.5, new metal(new constant_texture(vec3(0.2,0.3,0.0)), 0.0));
            list[1] = new sphere(vec3(0,-100.5,-1), 100, new diffuse(new constant_texture(vec3(0.5,0.5,0.5))));look_from = vec3(0,0,1);

            world = new hitable_list(list, 2);
            break;

        case 2:
            n = 500;
            list = new hitable*[n+1];
            list[0] = new sphere(vec3(0,-1000,0), 1000, new diffuse(perlintex));
            i = 1;
            for (int a = -10; a < 10; a++){
                for(int b = -10; b < 10; b++){
                    float choose_mat = random_float();
                    vec3 center(a+0.9*random_float(), 0.2, b+0.9*random_float());
                    if((center-vec3(4,0.2,0)).length() > 0.9){
                        if(choose_mat < 0.8){
                            list[i++] = new moving_sphere(center, center+vec3(0, random_float(0,0.5), 0), 0.0, 1.0, 0.2,
                                                          new diffuse(new constant_texture(vec3(random_float()*random_float(),random_float()*random_float(),random_float()*random_float()))));
                        } else if (choose_mat < 0.95){
                            list[i++] = new sphere (center, 0.2, new metal(new constant_texture(vec3(0.5*(1+random_float()), 0.5*(1+random_float()), 0.5*(1+random_float()))),0.5*random_float()));
                        } else {
                            list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                        }
                    }
                }
            }
            look_from = vec3(13,2,3);

            world = new hitable_list(list, i);
            break;

        case 3:
            list = new hitable*[3];
            list[0] = new sphere(vec3(0,1,0), 1.0, new dielectric(1.5));
            list[1] = new moving_sphere(vec3(-4,1,0), vec3(-4,1,1),0.0,1.0, 1.0, new diffuse(new constant_texture(vec3(0.4,0.2,0.1))));
            list[2] = new sphere(vec3(4,1,0), 1.0, new metal(new constant_texture(vec3(0.7, 0.6, 0.5)), 0.0));

            look_from = vec3(13,2,3);
            world = new hitable_list(list, 3);
            break;

        case 4:
            list = new hitable*[3];
            list[0] = new sphere(vec3(4,1,0), 1, new diffuse(new constant_texture(vec3(0.7,0,0))));
            //list[1] = new sphere(vec3(3,1,0), 0.2, new diffuse_light(new constant_texture(vec3(0.5,0.8,0.2)),10));
//            list[1] = new xy_rect(5,10,5,10,-2, new diffuse_light((new constant_texture(vec3(5,5,5)))));
//            list[2] = new xy_rect(5,10,5,10,2, new diffuse_light((new constant_texture(vec3(5,5,5)))));
            //list[1] = new xz_rect(0,5,0,5,2, new diffuse_light(new constant_texture(vec3(4,4,4))));
            list[1] = new xy_rect(0,5,0,5,-2, white);
            look_from = vec3(13,2,3);

            world = new hitable_list(list, 2);
            break;

        case 5:
            n = 10;
            list = new hitable*[n+1];
            i = 0;
            //list[i++] = new flip_face(new yz_rect(0,555,0,555,555, new diffuse(new constant_texture(vec3(0.6,0.3,0.3)))));
            //list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.5,0.1,0.5))));
            list[i++] = new xz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.5,0.1,0.5))));
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            //list[i++] = new xz_rect(0,555,0,555,200, white);
            //list[i++] = new xz_rect(0,555,0,555,201, white);
            //list[i++] = new xy_rect(0,555,0,555,555, white);
            //list[i++] = new sphere(vec3(400,554,400), 10, new diffuse_light(new constant_texture(vec3(0,1,0)), 1));

            list[i++] = new xz_rect(213,343,227,332,554,new diffuse_light(new constant_texture(vec3(5,5,5)),10));

//            box1 = new box(vec3(0,0,0), vec3(165,330,165), white);
//            box1 = new rotate_y(box1, 15);
//            list[i++] = new translate(box1, vec3(265,0,295));

            //list[i++] = new sphere(vec3(300,100,300),100, new metal(new constant_texture(vec3(1,1,1)),0.0));
//            list[i++] = new sphere(vec3(300,100,300),100, white);

            box2 = new box(vec3(0,0,0), vec3(165,100,165), white);
            box2 = new rotate_y(box2, -18);
            list[i++] = new translate(box2, vec3(195,0,65));

            look_from = vec3(278, 278, -800);
            look_at = vec3(278,278,0);


            point_lights = new light[3];

            light_point = vec3(250, 554, 250);
            light_to = vec3(250,1,250);
            angle = 45;
            light_color = vec3(0,1,0);
            light_strength = 700;
            point_lights[0] = light(light_point, light_color, light_strength, light_to, angle);

            light_point = vec3(250, 554, 250);
            light_to = vec3(200,1,400);
            angle = 30;
            light_color = vec3(0,1,0);
            light_strength = 700;
            point_lights[1] = light(light_point, light_color, light_strength, light_to, angle);

            light_point = vec3(250, 554, 250);
            light_to = vec3(400,1,300);
            angle = 30;
            light_color = vec3(0,0,1);
            light_strength = 700;
            point_lights[2] = light(light_point, light_color, light_strength, light_to, angle);

            lights = light_list(point_lights, 0);
            world = new hitable_list(list, i);
            break;

        case 6:
            n = 10;
            list = new hitable*[n+1];
            i = 0;
            list[i++] = new flip_face(new yz_rect(0,555,0,555,555,new diffuse(new constant_texture(vec3(0.12,0.45,0.15)))));
            list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.65,0.05,0.05))));
            list[i++] = new xz_rect(0,555,0,555,0, white);
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            list[i++] = new flip_face(new xy_rect(0,555,0,555,555, new diffuse (new constant_texture(vec3(0.05,0.05,0.73)))));
            list[i++] = new xz_rect(113,443,127,432,554, new diffuse_light(new constant_texture(vec3(0.5,0.7,0.2)),10));

            box1 = new box(vec3(0,0,0), vec3(165,330,165), white);
            box1 = new rotate_y(box1, 15);
            box1 = new translate(box1, vec3(265,0,295));
            list[i++] = new constant_medium(box1, 0.006, new constant_texture(vec3(0,0,0)));

            box2 = new box(vec3(0,0,0), vec3(165,165,165), white);
            box2 = new rotate_y(box2, -18);
            box2 = new translate(box2, vec3(130,0,65));
            list[i++] = new constant_medium(box2, 0.006, new constant_texture(vec3(1,1,1)));

            look_from = vec3(278, 278, -800);
            look_at = vec3(278,278,0);

            world = new hitable_list(list, i);
            break;

        case 7:
            //ground with randomly generated boxes
            i = 0;
            auto ground = new diffuse(new constant_texture(vec3(0.48,0.83,0.53)));
            for(int m=0; m<20; m++){
                for (int n=0; n<20; n++){
                    auto w = 100.0;
                    auto x0 = -1000.0+m*w;
                    auto z0 = -1000.0+n*w;
                    auto y0 = 0.0;
                    auto x1 = x0+w;
                    auto z1 = z0+w;
                    auto y1 = random_float(1,101);
                    list[i++] = new box(vec3(x0,y0,z0), vec3(x1,y1,z1), ground);
                }
            }

            //light emitting rectangle
            auto light = new diffuse_light(new constant_texture(vec3(7,7,7)), 1);
            list[i++] = new xz_rect(123,423,147,412,554, light);

            // moving sphere
            auto moving_sphere_material = new diffuse(new constant_texture(vec3(0.7,0.3,0.1)));
            list[i++] = new moving_sphere(vec3(400,400,400), vec3(430,400,200), 0,1,50, moving_sphere_material);

            //glass sphere
            list[i++] = new sphere(vec3(260,150,45), 50, new dielectric(1.5));

            //metal sphere
            list[i++] = new sphere(vec3(0,150,145), 50, new metal(new constant_texture(vec3(0.5,0.5,0.5)), 2.5));

            //volumn surounded by glass sphere
            auto boundary = new sphere(vec3(360,150,145), 70, new dielectric(1.5));
            list[i++] = new constant_medium(boundary, 0.1, new constant_texture(vec3(0.5,0.3,0.7)));

            //earth
            list[i++] = new sphere(vec3(400,200,400), 70, new diffuse(earth_surface));

            //perlin noise sphere
            list[i++] = new sphere(vec3(220,280,300), 80, new diffuse(perlintex));

            //foggy
            boundary = new sphere(vec3(0,0,0), 5000, new dielectric(1.5));
            list[i++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1,1,1)));

            //randomly generated white ball in given area(box)
            auto white = new diffuse(new constant_texture(vec3(1,1,1)));
            for (int k=0; k<100; k++){
                auto x = random_float(0,165);
                auto y = random_float(0,165);
                auto z = random_float(0,165);
                auto small_sphere = new sphere(vec3(x,y,z), 10, white);
                list[i++] = new translate(new rotate_y(small_sphere, 15), vec3(-100,270,395));
            }

            look_from = vec3(478,278,-600);
            look_at = vec3(278,278,0);

            world = new hitable_list(list ,i);

    }

    camera cam(look_from, look_at, vup, 40, (width/height), aperture, focus,0.0,1.0);

    for (int j = height-1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < sample_per_pixel; s++){
                auto u = double(i+random_float()) / width;
                auto v = double(j+random_float()) / height;
                ray r2 = cam.get_ray(u,v);
                col += color(r2, background, world, max_depth, lights);
            }

            col /= float(sample_per_pixel);
            if(col[0]<0)
                col[0] = 0;
            if(col[1]<0)
                col[1] = 0;
            if(col[2]<0)
                col[2] = 0;
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = static_cast<int>(255.999 * col[0]);
            int ig = static_cast<int>(255.999 * col[1]);
            int ib = static_cast<int>(255.999 * col[2]);
            if(ir<0 || ig < 0 || ib < 0){
                cout << "error!" << endl;
            }
            img << ir << ' ' << ig << ' ' << ib << endl;
        }
    }
}

int main() {
    int scene = 4;
    run(scene);
}