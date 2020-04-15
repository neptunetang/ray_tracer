//
// Created by neptune on 15-04-20.
//

#include "perlin.h"

float perlin::linear_interp(float (*c)[2][2], float u, float v, float w) const {
    float accum = 0.0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++) {
                accum += (i*u + (1-i)*(1-u))*
                         (j*v + (1-j)*(1-v))*
                         (k*w + (1-k)*(1-w))*c[i][j][k];
            }
        }
    }
    return accum;
}

void perlin::permute(int *p, int n) {
    for (int i = n-1; i > 0; i--) {
        int target = random_int(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

int *perlin::perlin_generate_perm() {
    auto p = new int[point_count];

    for (int i = 0; i < perlin::point_count; i++)
        p[i] = i;

    permute(p, point_count);

    return p;
}

float perlin::noise(const vec3 &p) const {
    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());

    float u = p.x()-i;
    float v = p.y()-j;
    float w = p.z()-k;

    u = u*u*(3-2*u);
    v = v*v*(3-2*v);
    w = w*w*(3-2*w);


    float list[2][2][2];

    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            for (int c = 0; c < 2; c++) {
                list[a][b][c] = ranfloat[
                        perm_x[(i+a) & 255]
                        ^ perm_y[(j+b) & 255]
                        ^ perm_z[(k+c) & 255]
                ];
            }
        }
    }
    return linear_interp(list,u,v,w);
}
