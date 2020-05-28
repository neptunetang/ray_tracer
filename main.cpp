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
#include <fstream>

#include <chrono>
#include <string>

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <condition_variable>

int counter = 0;
int counter1 = 0;

std::mutex writeM;

struct BlockJob
{
    int rowStart;
    int rowEnd;
    int colSize;
    int spp;
    std::vector<int> indices;
    std::vector<vec3> colors;
    std::vector<int> indices2;
    std::vector<vec3> colors2;
};

double luminance(vec3 c){
//    int r = static_cast<int>(255.99f * c.r());
//    int g = static_cast<int>(255.99f * c.g());
//    int b = static_cast<int>(255.99f * c.b());
    return dot(vec3(0.2126, 0.7152, 0.0722), c);
}

vec3 nne(const hit_record rec, const hitable* world, light light_source, ray r_in, vector<hit_record> path){
    vec3 emitted = vec3(0,0,0);
    vec3 solid_angle = vec3(0,0,0);
    vec3 sample_light_point = light_source.start();
    ray connection(rec.intersection, sample_light_point-rec.intersection);
    hit_record tmp;
    if(world->is_hit(connection, 0.0001, MAXFLOAT, tmp)){
        //counter++;
        if(light_source.on_light(tmp.intersection)){
            emitted = light_source.color;

            solid_angle = (dot(tmp.normal,-(sample_light_point-rec.intersection))*sample_light_point)/((sample_light_point-rec.intersection).squared_length());
            if(solid_angle<vec3(0,0,0))
                solid_angle = vec3(0,0,0);
            tmp.color = emitted*rec.mat->scatter_pdf(r_in ,rec, connection)*solid_angle;
            tmp.nne = true;
            path.push_back(tmp);
        }
    }
    //cout << emitted*rec.mat->scatter_pdf(r_in ,rec, connection)*solid_angle << endl;
    return emitted*rec.mat->scatter_pdf(r_in ,rec, connection)*solid_angle;

}

vec3 color(const ray& r, const vec3& background, const hitable* world, int depth, light light_source, char previous_type, vector<hit_record> &path, int index = -1, bool nne_flag = true) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        double pdf;
        vec3 emitted = rec.mat->emitted(rec.u, rec.v, rec.intersection, rec);

        if(rec.mat->scatter(r, rec, attenuation, scattered, pdf)) {

            if(rec.mat->type(rec) == 'n' || !nne_flag){
                rec.color = attenuation;
                rec.index = index;
                rec.nne = false;
                path.push_back(rec);
                return attenuation * color(scattered, background, world, depth - 1, light_source, rec.mat->type(rec), path);
            }else{
                rec.color = attenuation;
                rec.index = index;
                rec.nne = false;
                path.push_back(rec);
                return attenuation*nne(rec, world, light_source, r, path)/4 + attenuation*rec.mat->scatter_pdf(r, rec, scattered)*color(scattered, background, world, depth-1, light_source, rec.mat->type(rec), path)/pdf;
            }

        } else {
            rec.color = emitted;
            rec.index = index;
            rec.nne = false;

            if(previous_type == 'n' && nne_flag){
                rec.color = emitted/2;
                path.push_back(rec);
                return emitted/2;
            }
            path.push_back(rec);
            //return emitted;

        }
            //return emitted/2;

        //}

    }
    return background;
}

vec3 mutate(vector<hit_record> &path, int height, int width, camera cam, hitable* world, light light_source){
    double r1 = 0.1;
    double r2 = 0.05*height*width;
    int current_index;
    do{
        double u = random_float(0,1);
        int r = floor(r2*exp(-u * log(r2/r1)));
        if(random_float(0,1) > 0.5){
            current_index = path[0].index+r/2;
        } else {
            current_index = path[0].index+r/2;
        }
    }while(current_index < 0  || current_index >= height*width || current_index==path[0].index);

    int x = current_index%width;
    int y = current_index/width;

//    cout << "before" << path[0].index%width << " " << path[0].index/width << endl;
//    cout << "changed" << x << " "<< y << endl;

    auto u = double(x+random_float()) / float(width);
    auto v = double(y+random_float()) / float(height);
    ray r = cam.get_ray(u, v);
    hit_record tmp;
    vec3 color;
    double pdf;
    ray scattered;
    if(world->is_hit(r, 0.0001, MAXFLOAT, tmp)){
        tmp.mat->scatter(r, tmp, path[0].color, scattered, pdf);
        ray connection(tmp.intersection, path[1].intersection - tmp.intersection);
        if(world->is_hit(connection, 0.0001, MAXFLOAT, tmp)){
            if(tmp.intersection == path[1].intersection){
                color = path[0].color;
                for(int i=1; i<path.size(); i++){
                    color *= path[i].color;
                }
                path[0] = tmp;
                path[0].index = current_index;
                //cout << "success" << endl;
                return color;
            }
        }
    }

    //cout << "before:" << path[0].index << endl;
    //cout << current_index << endl;
    return vec3(0,0,0);

}

void calculate_color(BlockJob job, std::vector<BlockJob>& imageBlocks, int height, camera cam, hitable* world, light light_source,
                     std::mutex& mutex, std::condition_variable& cv, std::atomic<int>& completedThreads, const double ed, const int mutation)
{
    int max_depth = 4;
    for (int j = job.rowStart; j < job.rowEnd; ++j) {
        for (int i = 0; i < job.colSize; ++i) {
            //cout << "calculating: " << i << " " << j << endl;
            vec3 col(0,0,0);
            const unsigned int index = (height-j-1) * job.colSize + i;
            for (int s = 0; s < job.spp; ++s) {

                int root = int(sqrt(job.spp));
                auto stratum_x = s%root/root;
                auto stratum_y = s/job.spp;
                auto u = double(i+stratum_x+random_float()*0.25) / float(job.colSize);
                auto v = double(j+stratum_y+random_float()*0.25) / height;
                ray r = cam.get_ray(u, v);
                vector<hit_record> path;
                vec3 c = color(r, vec3(0,0,0), world, max_depth, light_source, 'n', path, ((height-j-1) * job.colSize + i));
                //cout << "basic color : " << c << endl;
                if(isnan(c.r())||isnan(c.g())||isnan(c.b())) {
                    continue;
                }

                if(luminance(c) > 0.0){
                    if(!path.empty()){
                        if(path[0].mat->type(path[0]) == 'l'){
                            job.indices.push_back(index);
                            job.colors.push_back(c);
                            job.indices2.push_back(index);
                            job.colors2.push_back(c);
                            continue;
                        }
                        //counter1 ++ ;
                        const int numChains = std::floor(random_float() + luminance(c) / (mutation * ed));

                        //cout << luminance(c) << endl;
                        int max_fail_mutate = 0;
                        bool specular = false;
                        for(int k=0; i<path.size(); k++){
                            if(path[i].mat->type(path[i]) == 'n'){
                                specular = true;
                            }
                        }

                        for (int i=0; i<numChains; i++){
                            auto current_path = path;
                            int current_index = index;
                            double current_f = luminance(c);
                            vec3 dep_value = c / luminance(c) * ed/job.spp;
                            for(int j=0; j<mutation; j++){
                                auto mutated_color = mutate(path, height, job.colSize, cam, world, light_source);
                                double mutated_f = luminance(mutated_color);

//                            double mutated_f;
//                            if(specular && random_float(0,1) < 0.5)
//                                mutated_f = luminance(c_mutate(path));
//                            else
//                                mutated_f = luminance(l_mutate(path));
                                double q = mutated_f/current_f;
                                if(q > random_float(0,1)){
                                    current_index = path[0].index;
                                }
                                job.indices.push_back(current_index);
                                job.colors.push_back(dep_value);
                                if(current_index == index){
                                    path = current_path;
                                    max_fail_mutate++;
                                } else if (max_fail_mutate < 10) {

                                    //counter++;
                                    //cout << current_index << endl;
                                    //cout << "before" << dep_value << endl;
                                    vec3 d = dep_value;

                                    dep_value = mutated_color / luminance(mutated_color) * ed/job.spp;
                                    if(isnan(dep_value.r())||isnan(dep_value.g())||isnan(dep_value.b())) {
                                        dep_value = d;
                                    }
                                    //cout << "after" << dep_value << endl;
                                    max_fail_mutate = 0;
                                }
                            }

                        }
                    }
                }
                col += c;
            }
            //cout << col << endl;
            col /= job.spp;
            job.indices2.push_back(index);
            job.colors2.push_back(col);
            counter++;
            if(counter % 10000 == 0)
                cout << counter << endl;
        }
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        imageBlocks.push_back(job);
        completedThreads++;
        cv.notify_one();
    }

}

void run(int scene){
    int width=400, height=400;
    int sample_per_pixel = 10;
    int mutation = 100;
    int pixelCount = width * height;
    ofstream img ("14b.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    vec3* image = new vec3[pixelCount];
    memset(&image[0], 0, pixelCount * sizeof(vec3));

    vec3* tmp_image = new vec3[pixelCount];
    memset(&tmp_image[0], 0, pixelCount * sizeof(vec3));

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
            list[i++] = new xz_rect(0,555,0,555,0, white);
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            //list[i++] = new xz_rect(0,555,0,555,200, white);
            //list[i++] = new xz_rect(0,555,0,555,201, white);
            list[i++] = new xy_rect(0,555,0,555,555, white);

//            list[i++] = new flip_face(new yz_rect(200,350,200,350,200, white));
//            list[i++] = new yz_rect(200,350,200,350,350, white);
//            list[i++] = new xy_rect(200,350,200,350,200, white);
//            list[i++] = new flip_face(new xy_rect(200,350,200,350,350, white));
//            list[i++] = new flip_face(new xz_rect(200,350,200,350,350, white));

            list[i++] = new sphere(vec3(275,275,275), 50, new diffuse_light(new constant_texture(vec3(10,10,10))));
            light_area = light(new sphere (vec3(275,275,275), 50, new diffuse_light(new constant_texture(vec3(10,10,10)))),
                               vec3(10,10,10), 10);
            //list[i++] = new xz_rect(213,343,227,332,554,new diffuse_light(new constant_texture(vec3(5,5,5)),10));

//            box1 = new box(vec3(0,0,0), vec3(165,330,165), white);
//            box1 = new rotate_y(box1, 15);
//            list[i++] = new translate(box1, vec3(265,0,295));

            //list[i++] = new sphere(vec3(300,70,300),70, new metal(new constant_texture(vec3(1,1,1)),0.0));
            //list[i++] = new sphere(vec3(200,70,200),70, white);

            //list[i++] = new sphere(vec3(300,100,300), 100, new dielectric(1.5));

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

    camera cam(look_from, look_at, vup, 40, (width/height), aperture, focus,0.0,1.0);

    vec3 sum(0,0,0);

    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x ++) {
            auto u = double(x+random_float()) / float(width);
            auto v = double(y+random_float()) / float(height);
            ray r = cam.get_ray(u, v);
            vector<hit_record> path;
            vec3 c = color(r, vec3(0,0,0), world, 4, light_area, 'n', path);
            c = vec3(sqrt(c.r()), sqrt(c.g()), sqrt(c.b()));
            sum += c;
        }
    }


    const double ed = luminance(sum)/(mutation*(width * height));
    //cout << luminance(sum) << endl;
    cout << ed << endl;

    auto fulltime = std::chrono::high_resolution_clock::now();

    const int nThreads = std::thread::hardware_concurrency();
    int rowsPerThread = height / nThreads;
    int leftOver = height % nThreads;

    std::mutex mutex;
    std::condition_variable cvResults;
    std::vector<BlockJob> imageBlocks;
    std::atomic<int> completedThreads = { 0 };
    std::vector<std::thread> threads;

    for (int i = 0; i < nThreads; ++i)
    {
        BlockJob job;
        job.rowStart = i * rowsPerThread;
        job.rowEnd = job.rowStart + rowsPerThread;
        if (i == nThreads - 1)
        {
            job.rowEnd = job.rowStart + rowsPerThread + leftOver;
        }
        job.colSize = width;
        job.spp = sample_per_pixel;

        std::thread t([job, &imageBlocks, height, &cam, &world, &light_area, &mutex, &cvResults, &completedThreads, &ed, &mutation]() {
            calculate_color(job, imageBlocks, height, cam, world, light_area, mutex, cvResults, completedThreads, ed, mutation);
        });
        threads.push_back(std::move(t));
    }


    {
        std::unique_lock<std::mutex> lock(mutex);
        cvResults.wait(lock, [&completedThreads, &nThreads] {
            return completedThreads == nThreads;
        });
    }

    for (std::thread& t : threads){
        t.join();
    }

    for (BlockJob job : imageBlocks){
        int index = job.rowStart;
        int colorIndex = 0;
        //cout << job.colors.size() << endl;
        for (vec3& col : job.colors)
        {
            int colIndex = job.indices[colorIndex];
            image[colIndex] += col;
            ++colorIndex;
        }
        int color_index = 0;
        for(vec3& col: job.colors2){
            int col_index = job.indices2[color_index];
            tmp_image[col_index] += col;
            ++color_index;
        }
    }


    vec3 sum_nne(0,0,0);
    vec3 sum_erpt(0,0,0);
    for (unsigned int i = 0; i < pixelCount; i++){
        sum_nne += vec3(sqrt(tmp_image[i].e[0]), sqrt(tmp_image[i].e[1]), sqrt(tmp_image[i].e[2]));
        sum_erpt += vec3(sqrt(image[i].e[0]), sqrt(image[i].e[1]), sqrt(image[i].e[2]));
        sum += vec3(sqrt(image[i].e[0]*tmp_image[i].e[0]), sqrt(image[i].e[1]*tmp_image[i].e[1]), sqrt(image[i].e[2]*tmp_image[i].e[2]));
        vec3 col = vec3(sqrt(image[i].e[0])*0.9, sqrt(image[i].e[1])*1.1, sqrt(image[i].e[2]));
        //vec3 col = vec3(sqrt(tmp_image[i].e[0]), sqrt(tmp_image[i].e[1]), sqrt(tmp_image[i].e[2]));
        //vec3 col = vec3(sqrt(image[i].e[0])/2+sqrt(tmp_image[i].e[0]), sqrt(image[i].e[1])/2+sqrt(tmp_image[i].e[1]), sqrt(image[i].e[2])/2+sqrt(tmp_image[i].e[2]));

        img
                << static_cast<int>(255.99f * col.r()) << " "
                << static_cast<int>(255.99f * col.g()) << " "
                << static_cast<int>(255.99f * col.b()) << "\n";
    }

    auto timeSpan = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - fulltime);
    int frameTimeMs = static_cast<int>(timeSpan.count());
    std::cout << " - time " << frameTimeMs << " s \n";
    std::cout << "File Saved" << std::endl;
    auto scale = luminance(sum_nne/pixelCount)/luminance(sum/pixelCount);
    cout << scale << endl;
    cout << "origin"<< sum_nne << endl;
    cout <<"erpt" << sum_erpt << endl;
    //cout << luminance(sum/pixelCount) << endl;
//    cout << "useful_path" << counter1 << endl;
//    cout << "success mutate" << counter << endl;
    delete[] image;

}

int main() {
    int scene = 5;
    run(scene);
}