#include "run.h"

int main() {
    int scene = 5;

    //0 for erpt, 1 for pt, 2 for bdpt, 3 for nne
    int mode = 0;

    int width=400, height=400;

    int sample_per_pixel = 1;

    int mutation = 1;

    run(scene, mode, width, height, sample_per_pixel, mutation);
}