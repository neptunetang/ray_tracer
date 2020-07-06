//
// Created by neptune on 09-06-20.
//
#include "geometry/common_method.h"

vec3 path_tracer_color(const ray& r, const vec3& background, const hitable* world, int depth, light light_source) {
    if (depth <= 0)
        return vec3(0,0,0);
    hit_record rec;
    if(world->is_hit(r,0.0001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        double pdf;
        vec3 emitted = rec.mat->emitted(rec.u, rec.v, rec.intersection, rec);
        if(rec.mat->scatter(r, rec, attenuation, scattered, pdf)) {
            return attenuation *
                   path_tracer_color(scattered, background, world, depth - 1, light_source);
        }
        else {
            return emitted;
        }
    }
    return background;
}


void calculate_pt_color(block_job job, std::vector<block_job>& imageBlocks, int height, camera cam, hitable* world, light light_source,
                        std::mutex& mutex, std::condition_variable& cv, std::atomic<int>& completedThreads)
{
    int max_depth = 4;
    for (int j = job.row_start; j < job.row_end; ++j) {
        for (int i = 0; i < job.col_size; ++i) {
            vec3 col(0, 0, 0);
            int useful_sample = 0;
            for (int s = 0; s < job.spp; ++s) {
                int root = int(sqrt(job.spp));
                auto stratum_x = s%root/root;
                auto stratum_y = s/job.spp;
                auto u = double(i+stratum_x+random_float()*0.25) / float(job.col_size);
                auto v = double(j+stratum_y+random_float()*0.25) / height;
                ray r = cam.get_ray(u, v);
                vec3 c = path_tracer_color(r, vec3(0,0,0), world, max_depth, light_source);
                if(isnan(c.r())||isnan(c.g())||isnan(c.b())){
                    continue;
                }
                col += c;
                useful_sample++;
            }

            col /= float(useful_sample);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            const unsigned int index = (height-j-1) * job.col_size + i;
            job.indices.push_back(index);
            job.colors.push_back(col);
        }
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        imageBlocks.push_back(job);
        completedThreads++;
        cv.notify_one();
    }
}
