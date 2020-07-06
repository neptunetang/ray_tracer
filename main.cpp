#include "run.h"

int main() {
    //1-3 only for pt, 4 for erpt, 5-8 for all
    int scene = 6;

    //0 for erpt, 1 for pt, 2 for bdpt, 3 for nne
    int mode = 1;

    int width=400, height=400;

    int sample_per_pixel = 16;

    //only for erpt
    int mutation = 10;

    string filename = "output.ppm";

    run(scene, mode, width, height, sample_per_pixel, mutation, filename);
}