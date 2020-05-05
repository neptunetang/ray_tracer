//
// Created by neptune on 31-03-20.
//

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef BASIC_VEC3_H
#define BASIC_VEC3_H


class vec3 {
public:
    float e[3];
    vec3(){}
    vec3(float e0, float e1, float e2) {e[0] = e0; e[1] = e1; e[2] = e2;}
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const {return *this;}
    inline vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const {return e[i];}
    inline float& operator[](int i) {return e[i]; }


    inline bool operator==(const vec3 &v);
    inline vec3& operator+=(const vec3 &v);
    inline vec3& operator-=(const vec3 &v);
    inline vec3& operator/=(const vec3 &v);
    inline vec3& operator*=(const vec3 &v);
    inline vec3& operator/=(const float f);
    inline vec3& operator*=(const float f);
    inline float length() const { return sqrt(squared_length()); }
    inline float squared_length() const {return (e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
    inline void make_unit();
};

#endif //BASIC_VEC3_H
