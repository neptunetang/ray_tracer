//
// Created by neptune on 09-06-20.
//

#pragma once
#include <cstdlib>

inline float random_float() {
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}
