//
// Created by neptune on 09-06-20.
//
#include "common_method.h"

double luminance(vec3 c) {
    int r = static_cast<int>(255.99f * c.r());
    int g = static_cast<int>(255.99f * c.g());
    int b = static_cast<int>(255.99f * c.b());
    auto result = dot(vec3(0.2126, 0.7152, 0.0722), vec3(r, g, b));
    return result;
}

vec3 erpt_color(const ray& r, const vec3& background, const hitable* world, int depth, light light_source, vector<hit_record> &path, int index = -1, bool nne_flag = true) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        double pdf;
        vec3 emitted = rec.mat->emitted(rec.u, rec.v, rec.intersection, rec);

        if(rec.mat->scatter(r, rec, attenuation, scattered, pdf)) {
            rec.color = attenuation;
            rec.index = index;
            path.push_back(rec);
            return attenuation * erpt_color(scattered, background, world, depth - 1, light_source, path);
        } else {
            rec.color = emitted;
            rec.index = index;
            path.push_back(rec);
            return emitted;
        }

    }
    return background;
}

vec3 mutate(vector<hit_record> &path, int height, int width, camera cam, hitable* world, light light_source){
    int current_index = path[0].index;
    do{
        if(random_float() > 0.5){
            current_index += round(random_float(0,5));
        } else {
            current_index -= round(random_float(0,5));
        }
        if(random_float() > 0.5){
            current_index += width*round(random_float(0,5));
        }else {
            current_index -= width*round(random_float(0,5));
        }
    } while(current_index < 0  || current_index >= height*width);

    int x = current_index%width;
    int y = height - current_index/width;

//    cout << "before" << path[0].index%width << " " << height -path[0].index/width << endl;
//    cout << "changed" << x << " "<< y << endl;

    auto u = double(x+random_float()) / float(width);
    auto v = double(y+random_float()) / float(height);
    ray r = cam.get_ray(u, v);
    hit_record tmp;
    vec3 color;
    double pdf;
    ray scattered;
    if(world->is_hit(r, 0.0001, MAXFLOAT, tmp)) {
        tmp.mat->scatter(r, tmp, path[0].color, scattered, pdf);
        ray connection(tmp.intersection, path[1].intersection - tmp.intersection);
        if (world->is_hit(connection, 0.0001, MAXFLOAT, tmp)) {
            if (tmp.intersection == path[1].intersection) {
                color = path[0].color;
                for (int i = 1; i < path.size(); i++) {
                    color *= path[i].color;
                }
                path[0] = tmp;
                path[0].index = current_index;
                return color;
            }
        }
    }
    return vec3(0,0,0);

}

void calculate_erpt_color(block_job job, std::vector<block_job>& imageBlocks, int height, camera cam, hitable* world, light light_source,
                          std::mutex& mutex, std::condition_variable& cv, std::atomic<int>& completedThreads, const double ed, const int mutation) {
    int max_depth = 4;
    for (int j = job.row_start; j < job.row_end; ++j) {
        for (int i = 0; i < job.col_size; ++i) {
            vec3 col(0,0,0);
            const unsigned int index = (height-j-1) * job.col_size + i;
            for (int s = 0; s < job.spp; ++s) {

                int root = int(sqrt(job.spp));
                auto stratum_x = s%root/root;
                auto stratum_y = s/job.spp;
                auto u = double(i+stratum_x+random_float()*0.25) / float(job.col_size);
                auto v = double(j+stratum_y+random_float()*0.25) / height;
                ray r = cam.get_ray(u, v);
                vector<hit_record> path;
                vec3 c = erpt_color(r, vec3(0,0,0), world, max_depth, light_source, path, ((height-j-1) * job.col_size + i));
                if(isnan(c.r())||isnan(c.g())||isnan(c.b())) {
                    continue;
                }

                if(luminance(c) > 0.0){
                    if(!path.empty()){
                        if(path[0].mat->type(path[0]) == 'l'){
                            job.indices.push_back(index);
                            job.colors.push_back(c/job.spp);
                            continue;
                        }
                        const int numChains = std::floor(random_float() + luminance(c) / (mutation * ed));


                        vec3 dep_value = c / luminance(c) * ed / sqrt(job.spp);


                        for (int i=0; i<numChains; i++){
                            auto current_path = path;
                            int current_index;
                            double current_f = luminance(c);
                            int max_fail_mutate = 0;

                            for(int j=0; j<mutation; j++){
                                auto mutated_color = mutate(path, height, job.col_size, cam, world, light_source);
                                double mutated_f = luminance(mutated_color);
                                double q = mutated_f/current_f;
                                if(q > random_float(0,1)){
                                    current_index = path[0].index;
                                    if(current_index == index){
                                        max_fail_mutate++;
                                    }
                                    if (max_fail_mutate < 10) {
                                        job.indices.push_back(current_index);
                                        job.colors.push_back(dep_value);
                                        max_fail_mutate = 0;
                                    } else {
                                        continue;
                                    }
                                }

                            }

                        }
                    }
                }
                col += c;
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        imageBlocks.push_back(job);
        completedThreads++;
        cv.notify_one();
    }
}
