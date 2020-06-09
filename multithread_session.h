//
// Created by neptune on 09-06-20.
//

#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include "ray.h"


struct block_job
{
    int row_start;
    int row_end;
    int col_size;
    int spp;
    vector<int> indices;
    vector<vec3> colors;
};