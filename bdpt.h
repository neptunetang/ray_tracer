//
// Created by neptune on 09-06-20.
//
#include "geometry/common_method.h"

void create_light_path(ray r, hitable* world, int depth, light light_source, vector<hit_record> &light_path){
    if (depth <= 0){
        return;
    }
    hit_record rec;
    double pdf;
    ray scattered;
    if(world->is_hit(r, 0.0001, MAXFLOAT, rec)){
        if(rec.mat->scatter(r, rec, rec.color, scattered, pdf)){
            light_path.push_back(rec);
            return create_light_path(scattered, world, depth-1, light_source, light_path);
        } else if (depth == 1) {
            r = ray(rec.intersection, r.direction());
            return create_light_path(r, world, depth, light_source, light_path);
        }
    }
}


void create_cam_path(ray r, hitable* world, int depth, vector<hit_record> &cam_path){
    if (depth <= 0){
        return;
    }
    hit_record rec;
    double pdf;
    ray scattered;
    if(world->is_hit(r, 0.0001, MAXFLOAT, rec)){
        if(rec.mat->scatter(r, rec, rec.color, scattered, pdf)) {
            cam_path.push_back(rec);
            return create_cam_path(scattered, world, depth - 1, cam_path);
        } else {
            rec.color = rec.mat->emitted(rec.u, rec.v, rec.intersection, rec);
            cam_path.push_back(rec);
        }
    }
}

vec3 bdpt_color(vec3 background, hitable* world, light light_source, vector<hit_record> light_path, vector<hit_record> cam_path, vec3 light_origin) {
    float all=0;
    vec3 step_color;
    vec3 final_color = background;
    hit_record rec;
    for (int i = 0; i < cam_path.size(); i++) {
        double pdf;
        vec3 col;
        ray scattered;
        if (!cam_path[0].mat->scatter(ray(), rec, col, scattered, pdf)) {
            if(!(cam_path[0].color == vec3(0,0,0))){
                return cam_path[0].color;
            }

        }
        step_color = cam_path[0].color;
        for (int m = 1; m <= i; m++) {
            if (!cam_path[m].mat->scatter(ray(), rec, col, scattered, pdf)) {
                if(!(cam_path[m].color == vec3(0,0,0))){
                    step_color *= cam_path[m].color;
                    return step_color;
                }
            }
            step_color *= cam_path[m].color;
        }
        auto color = step_color;
        for (int j = 0; j < light_path.size(); j++) {

            ray connection(cam_path[i].intersection, light_path[i].intersection - cam_path[i].intersection);
            if (world->is_hit(connection, 0.0001, MAXFLOAT, rec)) {
                if (rec.intersection == light_path[i].intersection) {
                    for (int k = j; k >= 0; k--) {
                        step_color *= light_path[k].color;
                    }

                    final_color += (step_color/(i+j+3));
                    step_color = color;
                    all += (i+j+3);
                }
            }
        }
    }
    return final_color*(1-all/55);

}

void calculate_bdpt_color(block_job job, std::vector<block_job>& imageBlocks, int height, camera cam, hitable* world, light light_source,
                          std::mutex& mutex, std::condition_variable& cv, std::atomic<int>& completedThreads)
{
    int max_depth = 5;
    for (int j = job.row_start; j < job.row_end; ++j) {
        for (int i = 0; i < job.col_size; ++i) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < job.spp; ++s) {
                float u = float(i + random_float()) / float(job.col_size);
                float v = float(j + random_float()) / float(height);
                ray r = cam.get_ray(u, v);
                vector<hit_record> light_path;
                vector<hit_record> cam_path;
                ray start = light_source.area->random_ray();
                create_light_path(start, world, 2, light_source, light_path);
                create_cam_path(r, world, 5, cam_path);
                col += bdpt_color(vec3(0,0,0), world, light_source, light_path, cam_path, start.origin_point());
            }
            col /= float(job.spp);
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