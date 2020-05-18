//
// Created by neptune on 21-04-20.
//

#ifndef BASIC_RAY_TRACER_RECTANGLE_H
#define BASIC_RAY_TRACER_RECTANGLE_H

#include "hitable.h"
#include "material.h"

class rectangle : public hitable {
public:
    rectangle() = default;

    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

class flip_face : public hitable {
public:
    explicit flip_face(hitable* p) : ptr(p) {}

    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        if (!ptr->is_hit(r, t_min, t_max, rec))
            return false;
        rec.front = !rec.front;
        return true;
    }

public:
    hitable* ptr;
};

class xy_rect : public rectangle {
public:
    float p0, p1, q0, q1, k;
    material *mat;
    xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *m):
            p0(_x0), p1(_x1), q0(_y0), q1(_y1),k(_k), mat(m){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual ray random_ray() const;
};

class xz_rect : public rectangle {
public:
    float p0, p1, q0, q1, k;
    material *mat;
    xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *m):
            p0(_x0), p1(_x1), q0(_z0), q1(_z1),k(_k), mat(m){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual ray random_ray() const;
};

class yz_rect : public rectangle {
public:
    float p0, p1, q0, q1, k;
    material *mat;
    yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *m):
            p0(_y0), p1(_y1), q0(_z0), q1(_z1),k(_k), mat(m){};
    virtual bool is_hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual ray random_ray() const;
};



#endif //BASIC_RAY_TRACER_RECTANGLE_H
