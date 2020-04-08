//
// Created by neptune on 31-03-20.
//

#include "vec3.h"

inline vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}


inline vec3& vec3::operator*=(const vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const float f) {
    e[0] /= f;
    e[1] /= f;
    e[2] /= f;
    return *this;
}

inline vec3& vec3::operator*=(const float f) {
    e[0] *= f;
    e[1] *= f;
    e[2] *= f;
    return *this;
}

inline void vec3::make_unit() {
    e[0] /= length();
    e[1] /= length();
    e[2] /= length();
}

inline istream& operator>> (istream &is, vec3 &t){
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline ostream& operator<< (ostream &os, const vec3 &t){
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0]+v2.e[0], v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]};
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0]-v2.e[0], v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]};
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0]*v2.e[0], v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]};
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0]/v2.e[0], v1.e[1]/v2.e[1],v1.e[2]/v2.e[2]};
}

inline vec3 operator*(float t, const vec3 &v){
    return {t*v.e[0], t*v.e[1], t*v.e[2]};
}

inline vec3 operator*(const vec3 &v, float t){
    return {t*v.e[0], t*v.e[1], t*v.e[2]};
}

inline vec3 operator/(vec3 v, float t){
    return {v.e[0]/t, v.e[1]/t, v.e[2]/t};
}

inline float dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2){
    return { (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
             (v1.e[2]*v2.e[0] - v1.e[0]*v2.e[2]),
             (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0])};
}

inline vec3 unit_vec(vec3 v) {
    return v / v.length();
}
