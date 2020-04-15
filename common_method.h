//
// Created by neptune on 15-04-20.
//

#ifndef BASIC_RAY_TRACER_COMMON_METHOD_H
#define BASIC_RAY_TRACER_COMMON_METHOD_H

#include <cmath>

inline float random_float() {
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}


inline int random_int(int min, int max) {
    // Returns a random real in [min,max).
    return static_cast<int>(min + (max-min)*random_float());
}

#endif //BASIC_RAY_TRACER_COMMON_METHOD_H
