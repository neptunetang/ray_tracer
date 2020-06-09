//
// Created by neptune on 09-06-20.
//

#include "camera.h"
#include "scene.h"
#include "bdpt.h"
#include "erpt.h"
#include "nne.h"
#include "pt.h"

#include <iostream>
#include <fstream>

void run(int scene, int mode, int width, int height, int sample_per_pixel, int mutation = 0){
    int pixelCount = width * height;
    ofstream img ("5.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;
    vec3* image = new vec3[pixelCount];
    memset(&image[0], 0, pixelCount * sizeof(vec3));

    vec3 look_from, look_at(0,0,0);
    vec3 vup(0,1,0);
    auto focus = 10.0;
    auto aperture = 0.0;
    hitable *world;
    light light_area;

    create_scene(look_from, look_at, world, light_area, scene);
    camera cam(look_from, look_at, vup, 40, (width/height), aperture, focus,0.0,1.0);

    vec3 sum(0,0,0);
    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x ++) {
            auto u = double(x+random_float()) / float(width);
            auto v = double(y+random_float()) / float(height);
            ray r = cam.get_ray(u, v);
            vector<hit_record> path;
            vec3 c = erpt_color(r, vec3(0,0,0), world, 4, light_area, path);
            sum += c;
        }
    }

    const double ed = luminance(sum)/(width * height);

    auto full_time = std::chrono::high_resolution_clock::now();

    const int n_threads = std::thread::hardware_concurrency();
    int rows_per_thread = height / n_threads;
    int left_over = height % n_threads;

    std::mutex mutex;
    std::condition_variable cvResults;
    std::vector<block_job> image_block;
    std::atomic<int> completed_threads = {0 };
    std::vector<std::thread> threads;

    switch(mode) {
        case 0:
            for (int i = 0; i < n_threads; ++i)
            {
                block_job job;
                job.row_start = i * rows_per_thread;
                job.row_end = job.row_start + rows_per_thread;
                if (i == n_threads - 1)
                {
                    job.row_end = job.row_start + rows_per_thread + left_over;
                }
                job.col_size = width;
                job.spp = sample_per_pixel;

                std::thread t([job, &image_block, height, &cam, &world, &light_area, &mutex, &cvResults, &completed_threads, &ed, &mutation]() {
                    calculate_erpt_color(job, image_block, height, cam, world, light_area, mutex, cvResults, completed_threads, ed, mutation);
                });
                threads.push_back(std::move(t));
            }
            break;

        case 1:
            for (int i = 0; i < n_threads; ++i)
            {
                block_job job;
                job.row_start = i * rows_per_thread;
                job.row_end = job.row_start + rows_per_thread;
                if (i == n_threads - 1)
                {
                    job.row_end = job.row_start + rows_per_thread + left_over;
                }
                job.col_size = width;
                job.spp = sample_per_pixel;

                std::thread t([job, &image_block, height, &cam, &world, &light_area, &mutex, &cvResults, &completed_threads, &ed, &mutation]() {
                    calculate_pt_color(job, image_block, height, cam, world, light_area, mutex, cvResults, completed_threads);
                });
                threads.push_back(std::move(t));
            }
            break;

        case 2:
            for (int i = 0; i < n_threads; ++i)
            {
                block_job job;
                job.row_start = i * rows_per_thread;
                job.row_end = job.row_start + rows_per_thread;
                if (i == n_threads - 1)
                {
                    job.row_end = job.row_start + rows_per_thread + left_over;
                }
                job.col_size = width;
                job.spp = sample_per_pixel;

                std::thread t([job, &image_block, height, &cam, &world, &light_area, &mutex, &cvResults, &completed_threads, &ed, &mutation]() {
                    calculate_bdpt_color(job, image_block, height, cam, world, light_area, mutex, cvResults, completed_threads);
                });
                threads.push_back(std::move(t));
            }
            break;

        case 3:
            for (int i = 0; i < n_threads; ++i)
            {
                block_job job;
                job.row_start = i * rows_per_thread;
                job.row_end = job.row_start + rows_per_thread;
                if (i == n_threads - 1)
                {
                    job.row_end = job.row_start + rows_per_thread + left_over;
                }
                job.col_size = width;
                job.spp = sample_per_pixel;

                std::thread t([job, &image_block, height, &cam, &world, &light_area, &mutex, &cvResults, &completed_threads, &ed, &mutation]() {
                    calculate_nne_color(job, image_block, height, cam, world, light_area, mutex, cvResults, completed_threads);
                });
                threads.push_back(std::move(t));
            }
            break;

    }


    {
        std::unique_lock<std::mutex> lock(mutex);
        cvResults.wait(lock, [&completed_threads, &n_threads] {
            return completed_threads == n_threads;
        });
    }

    for (std::thread& t : threads){
        t.join();
    }

    for (block_job job : image_block){
        int color_index = 0;
        for (vec3& col : job.colors)
        {
            int col_index = job.indices[color_index];
            image[col_index] += col;
            ++color_index;
        }
    }


    vec3 sum_erpt(0,0,0);
    for (unsigned int i = 0; i < pixelCount; i++){
        vec3 col = vec3(sqrt(image[i].e[0]), sqrt(image[i].e[1]), sqrt(image[i].e[2]));
        sum_erpt += col;
        img
                << static_cast<int>(255.99f * col.r()) << " "
                << static_cast<int>(255.99f * col.g()) << " "
                << static_cast<int>(255.99f * col.b()) << "\n";
    }

    auto time_span = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - full_time);
    int times = static_cast<int>(time_span.count());
    cout << " - time " << times << " s \n";

    delete[] image;

}
