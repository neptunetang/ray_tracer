//
// Created by neptune on 15-04-20.
//

#ifndef BASIC_RAY_TRACER_PERLIN_H
#define BASIC_RAY_TRACER_PERLIN_H

#include "common_method.h"
#include "ray.h"

class perlin {
public:
    perlin() {
        ranfloat = new float[point_count];
        for (int i = 0; i < point_count; ++i) {
            ranfloat[i] = random_float();
        }

        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

    ~perlin() {
        delete[] ranfloat;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    float noise(const vec3& p) const;

    float linear_interp(float c[2][2][2], float u, float v, float w) const;

private:
    static const int point_count = 256;
    float* ranfloat;
    int* perm_x;
    int* perm_y;
    int* perm_z;

    static int* perlin_generate_perm();

    static void permute(int* p, int n);
};

#endif //BASIC_RAY_TRACER_PERLIN_H
