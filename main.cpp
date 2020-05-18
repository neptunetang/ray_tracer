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
#include <iostream>
#include<fstream>

void shooting_rays(const ray& r, const hitable* world, int depth, light& light_source, vector<hit_record>& light_path){
    //cout << "shooting!" << endl;
    if (depth <= 0){
        light_source.save_light_rec(light_path);
        return;
    }

    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)) {
        //cout << "hit something" << endl;
        ray scattered;
        vec3 attenuation;
        if(rec.mat->scatter(r, rec, attenuation, scattered)) {
            //cout << "rec:" << rec.intersection.x() << "  " << rec.intersection.y() << "  " << rec.intersection.z() << endl;
            light_path.push_back(rec);
            return shooting_rays(scattered, world, depth - 1, light_source, light_path);
        } else if(depth == 2){
            ray origin(rec.intersection, r.direction());
            return shooting_rays(origin, world, depth, light_source, light_path);
        }
    }
}

void create_path(light& light_source, int sample_per_light, int depth, const hitable* world){
    //cout << "sampling" << endl;
    for(int i=0; i<sample_per_light; i++){
        vector<hit_record> light_path;
        shooting_rays(light_source.area->random_ray(), world, depth, light_source, light_path);
        //cout << "center:" << light_area.center.x() << " " << light_area.center.y() << " " << light_area.center.z() << endl;
        //cout << "direction:" << dir.x() << " " << dir.y() << " " << dir.z() << endl;
    }
}

vec3 color(const ray& r, const vec3& background, const hitable* world, int depth, light light_source) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat->emitted(r, rec.u, rec.v, rec.intersection, rec);
        if(rec.mat->scatter(r, rec, attenuation, scattered)){
            float p = random_float(0,1);
            if(false){
                int depth_of_light = 2;
                create_path(light_source, 10, depth_of_light, world);
                //cout << "sample finish" << endl;
                int useful_path = 0;
                vec3 final_attenuation(0,0,0);
                for(int i=0; i<light_source.light_path.size(); i++) {
                    for (int j = depth_of_light - 1; j >= 0; j--) {
                        vec3 dir = rec.intersection - light_source.light_path[i][j].intersection;
                        ray connection(rec.intersection, dir);
                        hit_record tmp;
                        if (!world->is_hit(connection, 0.0001, MAXFLOAT, tmp)) {
                            useful_path++;
                            hit_record current_path = light_source.light_path[i][j];
                            vec3 new_attenuation;
                            rec.mat->scatter(connection, current_path, new_attenuation, scattered);
                            for (int k = j; k > 0; k--) {
                                vec3 current_attenuation;
                                ray current_path(light_source.light_path[i][k].intersection,
                                                 light_source.light_path[i][k].intersection -
                                                 light_source.light_path[i][k - 1].intersection);
                                rec.mat->scatter(current_path, light_source.light_path[i][k - 1], current_attenuation,
                                                 scattered);
                                //cout << "current_attenuation: " << current_attenuation.x() << "  " << current_attenuation.y() << "  " << current_attenuation.z() << endl;
                                new_attenuation *= current_attenuation;
                            }

                            attenuation *= new_attenuation;
                            final_attenuation += attenuation;

                            //cout << "attenuation: " << attenuation.x() << "  " << attenuation.y() << "  " << attenuation.z() << endl;
                        }
                    }
                }
                //cout << "connecting finish, useful path:" << useful_path <<endl;
                if(useful_path != 0)
                    final_attenuation /= useful_path;
                //cout << "final_attenuation: " << final_attenuation.x() << "  " << final_attenuation.y() << "  " << final_attenuation.z() << endl;
                return final_attenuation*light_source.color;
            }
            return emitted+attenuation*color(scattered, background, world, depth-1, light_source);


        } else {
            return emitted;
        }
    }
    return background;
}


void run(int scene){
    int width=500, height=500;
    int sample_per_pixel = 40;
    int max_depth = 3;
    ofstream img ("m.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    const vec3 background(0,0,0);

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


    vec3 light_color;
    float light_strength;

    light light_area;

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
            list[i++] = new flip_face(new yz_rect(0,555,0,555,555, new diffuse(new constant_texture(vec3(0.6,0.3,0.3)))));
            list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.5,0.1,0.5))));
//            list[i++] = new flip_face(new yz_rect(0,555,0,555,555, white));
//            list[i++] = new yz_rect(0,555,0,555,0, white);
            list[i++] = new xz_rect(0,555,0,555,0, white);
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            //list[i++] = new xz_rect(0,555,0,555,200, white);
            //list[i++] = new xz_rect(0,555,0,555,201, white);
            list[i++] = new xy_rect(0,555,0,555,555, white);
            //list[i++] = new sphere(vec3(400,554,400), 10, new diffuse_light(new constant_texture(vec3(0,1,0))));


            list[i++] = new flip_face(new yz_rect(200,350,200,350,200, white));
            list[i++] = new yz_rect(200,350,200,350,350, white);
            list[i++] = new xy_rect(200,350,200,350,200, white);
            list[i++] = new flip_face(new xy_rect(200,350,200,350,350, white));
            list[i++] = new flip_face(new xz_rect(200,350,200,350,350, white));

            list[i++] = new sphere(vec3(275,275,275), 50, new diffuse_light(new constant_texture(vec3(10,10,10))));
            light_area = light(new sphere (vec3(275,275,275), 50, new diffuse_light(new constant_texture(vec3(10,10,10)))),
                    vec3(1,1,1), 10);
//            light_area = light(new xz_rect(150,400,150,400,300,new diffuse_light(new constant_texture(vec3(5,5,5)))),vec3(1,1,1), 10 );
//            list[i++] = new xz_rect(150,400,150,400,300,new diffuse_light(new constant_texture(vec3(5,5,5))));

//            box1 = new box(vec3(0,0,0), vec3(165,330,165), white);
//            box1 = new rotate_y(box1, 15);
//            list[i++] = new translate(box1, vec3(265,0,295));

            //list[i++] = new sphere(vec3(300,100,300),100, new diffuse(new constant_texture(vec3(1,1,1))));
//            list[i++] = new sphere(vec3(300,100,300),100, white);

//            box2 = new box(vec3(0,0,0), vec3(165,100,165), white);
//            box2 = new rotate_y(box2, -18);
//            list[i++] = new translate(box2, vec3(195,0,65));

            look_from = vec3(278, 278, -800);
            look_at = vec3(278,278,0);

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
            list[i++] = new xz_rect(113,443,127,432,554, new diffuse_light(new constant_texture(vec3(0.5,0.7,0.2))));

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
            auto light = new diffuse_light(new constant_texture(vec3(7,7,7)));
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

    camera cam(look_from, look_at, vup, 40, (width/height), aperture, focus,0.0,0.0);

    for (int j = height-1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < sample_per_pixel; s++){
                auto u = double(i+random_float()) / width;
                auto v = double(j+random_float()) / height;
                ray r2 = cam.get_ray(u,v);
                col += color(r2, background, world, max_depth, light_area);
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
                //cout << "error!" << endl;
            }
            img << ir << ' ' << ig << ' ' << ib << endl;
        }
    }
}

int main() {
    int scene = 5;
    run(scene);
}